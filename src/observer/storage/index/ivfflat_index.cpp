/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "storage/index/ivfflat_index.h"
#include "storage/index/index.h"
#include "storage/text/text_manager.h"
#include <vector>
#include <cmath>
#include <limits>
#include <unordered_map>
#include "storage/table/table.h"
#include "storage/db/db.h"

RC IvfflatIndex::create(
    Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta *field_metas[], int field_num)
{
 if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s, field:%s, unique:%d",
        file_name, index_meta.name(), index_meta.field(0), index_meta.unique());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas, field_num);

  BufferPoolManager &bpm = table->db()->buffer_pool_manager();

  AttrType attr_types[field_num];
  int attr_len[field_num];

  for(int i = 0; i < field_num; i++){
    attr_types[i] = field_metas[i]->type();
    attr_len[i] = field_metas[i]->len();
  }
  RC rc = index_handler_.create(table->db()->log_handler(), bpm, file_name, attr_types, attr_len, field_num, index_meta.unique());
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, field:%s, rc:%s",
        file_name, index_meta.name(), index_meta.field(0), strrc(rc));
    return rc;
  }

  inited_ = true;
  table_  = table;
  LOG_INFO("Successfully create index, file_name:%s, index:%s, field:%s, unique:%d" ,
    file_name, index_meta.name(), index_meta.field(0), index_meta.unique());
  return RC::SUCCESS;
};
