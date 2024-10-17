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
// Created by Meiyi & Wangyunlai on 2021/5/12.
//

#pragma once

#include "common/lang/unordered_set.h"
#include "common/types.h"
#include "common/lang/span.h"
#include "common/lang/functional.h"
#include "sql/operator/physical_operator.h"
#include "storage/table/table.h"
#include "storage/view/view_meta.h"
#include "storage/table/table_meta.h"
#include "sql/expr/expression.h"
#include "sql/expr/sub_select_expression.h"
#include <memory>

class Record;

class ChunkFileScanner;

class Db;

/**
 * @brief 表(虚拟表)
 *
 */
class View
{
public:
  View() = default;
  ~View();

  /**
   * 创建一个视图
   * @param path 元数据保存的文件(完整路径)
   * @param name 表名
   * @param base_dir 表数据存放的路径，但现在只做内存
   * @param attribute_count 字段个数
   * @param attributes 字段
   */
  RC create(Db *db, int32_t view_id, const char *name, std::unique_ptr<Expression> &&sub_select);
  RC drop();

public:
  int32_t     view_id() const { return view_meta_.view_id(); }
  const char *name() const;

  Db *db() const { return db_; }

  const ViewMeta &view_meta() const;

  TableMeta table_meta();

  PhysicalOperator *oper();

  const SubSelectExpr *sub_select() { return static_cast<SubSelectExpr *>(sub_select_.get()); }

  unordered_set<string> &origin_tables() { return origin_tables_; }

  bool wirte_able() { return wirte_able_; }

private:
  Db                    *db_ = nullptr;
  ViewMeta               view_meta_;
  unique_ptr<Expression> sub_select_;
  string                 origin_sql_;  // 用于重启时重新解析Subselect；
  unordered_set<string>  origin_tables_;
  bool                   wirte_able_;
};
