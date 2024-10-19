/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/07/08.
//

#include "sql/operator/vector_index_scan_physical_operator.h"
#include "common/value.h"
#include "storage/index/index.h"
#include "storage/trx/trx.h"

VectorIndexScanPhysicalOperator::VectorIndexScanPhysicalOperator(
    Table *table, Index *index, ReadWriteMode mode, Value vector, std::string table_alias)
    : table_(table), index_(index), mode_(mode), table_alias_(table_alias)
{}

RC VectorIndexScanPhysicalOperator::open(Trx *trx)
{
  RC rc = table_->get_record_scanner(record_scanner_, trx, mode_);
  if (rc == RC::SUCCESS) {
    tuple_.set_schema(table_, table_->table_meta().field_metas(), table_alias_);
  }
  trx_ = trx;
  return rc;
}

RC VectorIndexScanPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;

  bool filter_result = false;
  while (OB_SUCC(rc = record_scanner_.next(current_record_))) {
    LOG_TRACE("got a record. rid=%s", current_record_.rid().to_string().c_str());

    tuple_.set_record(&current_record_);
    rc = filter(tuple_, filter_result);
    if (rc != RC::SUCCESS) {
      LOG_TRACE("record filtered failed=%s", strrc(rc));
      return rc;
    }

    if (filter_result) {
      break;
    } else {
    }
  }
  return rc;
}

RC VectorIndexScanPhysicalOperator::close()
{
  for (auto tuple : copied_tuples_) {
    delete &tuple->record();
    delete tuple;
  }
  copied_tuples_.clear();

  return record_scanner_.close_scan();
}

Tuple *VectorIndexScanPhysicalOperator::current_tuple()
{
  Record   *copied_record = new Record(current_record_);
  RowTuple *tuple         = new RowTuple();
  copied_tuples_.push_back(tuple);

  // owner为true，copy了一份
  copied_record->copy_data(current_record_.data(), current_record_.len());

  tuple->set_record(copied_record);
  tuple->set_schema(table_, table_->table_meta().field_metas(),table_alias_);
  return tuple;
}

void VectorIndexScanPhysicalOperator::set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC VectorIndexScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (std::unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}

std::string VectorIndexScanPhysicalOperator::param() const
{
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}
