/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <cstring>
#include <limits.h>
#include <memory>
#include <string.h>
#include <vector>

#include "common/defs.h"
#include "common/lang/string.h"
#include "common/lang/span.h"
#include "common/lang/algorithm.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "common/rc.h"
#include "common/value.h"
#include "sql/expr/expression.h"
#include "sql/expr/sub_select_expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/update_stmt.h"
#include "storage/db/db.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/index/index.h"
#include "storage/record/record_manager.h"
#include "storage/table/table_meta.h"
#include "storage/trx/vacuous_trx.h"
#include "storage/view/view.h"
#include "storage/trx/trx.h"

View::~View() { LOG_INFO("view has been closed: %s", name()); }

RC View::create(Db *db, int32_t view_id, const char *name, std::unique_ptr<Expression> &&sub_select)
{
  SubSelectExpr               *sub_select_expr = static_cast<SubSelectExpr *>(sub_select.get());
  std::vector<AttrInfoSqlNode> attributes;
  sub_select_expr->field_meta(attributes, db);

  if (view_id < 0) {
    LOG_WARN("invalid view id. view_id=%d, view_name=%s", view_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }

  if (attributes.size() == 0) {
    LOG_WARN("Invalid arguments. view_name=%s, attribute_count=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  if ((rc = view_meta_.init(view_id, name, attributes, sub_select->name())) != RC::SUCCESS) {
    LOG_ERROR("Failed to init view meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }
  db_         = db;
  sub_select_ = move(sub_select);
  wirte_able_ = true;

  std::vector<Expression *> origin_exprs;
  sub_select_expr->get_field_exprs(origin_exprs);

  for (auto &expr : origin_exprs) {  // 只允许更新视图中的属性字段,检查是否可以更新
    if (expr->type() != ExprType::FIELD) {
      wirte_able_ = false;
    } else {
      FieldExpr *field_expr = static_cast<FieldExpr *>(expr);
      origin_tables_.insert(field_expr->table_name());
    }
  }

  return rc;
}

RC View::drop() { return RC::UNSUPPORTED; }

RC View::insert_record(Record &record) { return RC::UNSUPPORTED; }

const char *View::name() const { return view_meta_.name(); }

const ViewMeta &View::view_meta() const { return view_meta_; }

TableMeta View::table_meta()
{
  TableMeta table_meta;
  table_meta.init(&view_meta_);
  return table_meta;
}

RC View::make_record(int value_num, const Value *values, Record &record) { return RC::UNSUPPORTED; }

RC View::set_value_to_record(char *record_data, const Value &value, const FieldMeta *field, const int record_len)
{
  return RC::UNSUPPORTED;
}

RC View::delete_record(const RID &rid) { return RC::UNSUPPORTED; }

RC View::delete_record(const Record &record) { return RC::UNSUPPORTED; }

RC View::update_record(Record &record, char *new_record_data, int new_record_len)
{
  // // 这里实现的效率非常低，复杂度由 n 变为 最大情况下是n方 了
  // // 根据 new_record 构建 filter等信息，重走一遍update table 的更新流程
  // SubSelectExpr *sub_select = static_cast<SubSelectExpr *>(sub_select_.get());

  // std::vector<Expression *> origin_exprs;
  // if (OB_FAIL(sub_select->get_field_exprs(origin_exprs))) {
  //   return RC::ERROR;
  // }
  // for (auto &expr : origin_exprs) {  // 只允许更新视图中的属性字段,检查是否可以更新
  //   if (expr->type() != ExprType::FIELD) {
  //     return RC::ERROR;
  //   }
  // }

  // RowTuple tuple_tmp;
  // tuple_tmp.set_schema(db_->find_table(name()),
  //     table_meta().field_metas(),
  //     name());  //这个tablealias 假设update时不使用alias，如果需要的话还需要一开始传入
  // tuple_tmp.set_record(&record);

  // std::vector<Value> old_values;
  // for (int i = 0; i < tuple_tmp.cell_num(); i++) {  // 收集原来的值
  //   Value tmp;
  //   if (OB_FAIL(tuple_tmp.cell_at(i, tmp))) {
  //     return RC::ERROR;
  //   }
  //   old_values.push_back(tmp);
  // }

  // std::vector<Value> new_values;
  // record.set_data(new_record_data, new_record_len);
  // for (int i = 0; i < tuple_tmp.cell_num(); i++) {  // 收集原来的值
  //   Value tmp;
  //   if (OB_FAIL(tuple_tmp.cell_at(i, tmp))) {
  //     return RC::ERROR;
  //   }
  //   new_values.push_back(tmp);
  // }

  // UpdateSqlNode updates;
  // // 找到 View 的列对应的table。
  // updates.relation_name = static_cast<FieldExpr *>(origin_exprs.front())->table_name();
  // // 收集更新的值
  // for (int i = 0; i < new_values.size(); i++) {
  //   UpdateValueNode node;
  //   ValueExpr      *value_expr = new ValueExpr(new_values[i]);
  //   node.expr                  = unique_ptr<Expression>(value_expr);
  //   node.attribute_name        = static_cast<FieldExpr *>(origin_exprs[i])->field_name();
  //   if(strcmp(updates.relation_name.c_str(), static_cast<FieldExpr *>(origin_exprs[i])->table_name()) != 0 ){   //
  //   如果要
  //     return RC::ERROR;
  //   }
  //   updates.update_values.push_back(std::move(node));
  // }
  // // 收集过滤条件
  // for (int i = 0; i < old_values.size(); i++) {
  //   ConditionSqlNode condition;
  //   ValueExpr       *value_expr = new ValueExpr(old_values[i]);
  //   FieldExpr       *field_expr = new FieldExpr(static_cast<FieldExpr *>(exprs[i])->field().table(),
  //       static_cast<FieldExpr *>(exprs[i])->field().meta(),
  //       static_cast<FieldExpr *>(exprs[i])->table_name());
  //   condition.right_expression.emplace_back(value_expr);
  //   condition.left_expression.emplace_back(field_expr);
  //   condition.comp             = CompOp::EQUAL_TO;
  //   condition.conjunction_type = 0;
  //   updates.conditions.push_back(std::move(condition));
  // }

  // // 重新table scan ->filter ->update
  // RC    rc;
  // Stmt *update_stmt;
  // if (OB_FAIL(rc = UpdateStmt::create(db_, updates, update_stmt))) {
  //   return rc;
  // }
  // std::unique_ptr<LogicalOperator>  logical_operator;
  // LogicalPlanGenerator              logical_plan_generator;
  // std::unique_ptr<PhysicalOperator> oper;
  // rc = logical_plan_generator.create_plan(static_cast<UpdateStmt *>(update_stmt), logical_operator);

  // PhysicalPlanGenerator Physical_plan_generator;
  // rc = Physical_plan_generator.create(*logical_operator, oper);
  // VacuousTrx trx;
  // if (OB_FAIL(rc = oper->open(&trx))) {
  //   return rc;
  // }
  // rc = oper->close();

  // return rc;
  return RC::UNSUPPORTED;
}

PhysicalOperator *View::oper()
{
  SubSelectExpr *expr = static_cast<SubSelectExpr *>(sub_select_.get());
  return expr->physical_operator();
}
