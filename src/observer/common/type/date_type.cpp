/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/attr_type.h"
#include "common/type/date_type.h"
#include "common/value.h"
#include <iomanip>

int DateType::compare(const Value &left, const Value &right) const
{
  if (right.attr_type() == AttrType::NULLS) {
    return INT32_MAX;
  }
  ASSERT(left.attr_type() == AttrType::DATES, "left type is not dates");
  ASSERT(right.attr_type() == AttrType::DATES || right.attr_type() == AttrType::FLOATS, "right type is not dates");

  return common::compare_int((void *)&left.value_.int_value_, (void *)&right.value_.int_value_);
}

RC DateType::set_value_from_str(Value &val, const string &data) const
{
  RC           rc = RC::SUCCESS;
  stringstream deserialize_stream;
  deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
  deserialize_stream.str(data);
  int int_value;
  deserialize_stream >> int_value;
  if (!deserialize_stream || !deserialize_stream.eof()) {
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } else {
    val.set_int(int_value);
  }
  return rc;
}

RC DateType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  int          year  = val.value_.int_value_ / 10000;
  int          month = (val.value_.int_value_ / 100) % 100;
  int          day   = val.value_.int_value_ % 100;
  ss << std::setfill('0') << std::setw(4) << year << "-" << std::setw(2) << month << "-" << std::setw(2) << day;
  result = ss.str();
  return RC::SUCCESS;
}