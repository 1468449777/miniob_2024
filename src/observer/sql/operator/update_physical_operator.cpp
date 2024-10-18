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
// Created by WangYunlai on 2022/6/27.
//

#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "common/type/attr_type.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include <cstring>

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  while (OB_SUCC(rc = child->next())) {

    // values_ 为空说明，stmt 阶段出现错误，比如要更新的值类型不匹配等
    if (values_.empty()) {
      return RC::ERROR;
    }

    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    // Record   new_record(record);                ///疑似存在浅拷贝问题，即new_record和record实际指向同一区域
    char *new_record_data = (char *)malloc(record.len() * sizeof(char));
    memcpy(new_record_data, record.data(), record.len());

    for (auto &it : values_) {
      if (it.first->type() == AttrType::TEXTS) {
        int copy_len = it.first->len();
        bool value_is_null = it.second.is_null();
        if (value_is_null) {
          int tmp_invalid_page = -1;
          memcpy(new_record_data + it.first->offset(), &(tmp_invalid_page), copy_len);
          
        }
        else {
          PageNum origin_page_num = *(int*)(record.data() + it.first->offset());
          PageNum new_page_num;
          table_->text_file_handler()->update_text(origin_page_num, it.second.get_string(), new_page_num);
          memcpy(new_record_data + it.first->offset(), &new_page_num, copy_len);
        }
        memcpy(new_record_data + record.len() - it.first->field_id() - 1, &value_is_null, 1);  // 修改null标记位
      }
      else {
        int copy_len = it.second.length();
        if (it.second.attr_type() == AttrType::CHARS && copy_len < it.first->len()) {
          ++copy_len;
        }
        bool value_is_null = it.second.is_null();
        memcpy(new_record_data + it.first->offset(), it.second.data(), copy_len);
        memcpy(new_record_data + record.len() - it.first->field_id() - 1, &value_is_null, 1);  // 修改null标记位
      }
    }
    // TODO: 需要做unique处理, 否则影响唯一性约束
    //
    rc = trx_->update_record(table_, record, new_record_data, record.len());

    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to Update record: %s", strrc(rc));
      return rc;
    }
  }

  table_->data_buffer_pool()->flush_all_pages();

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
