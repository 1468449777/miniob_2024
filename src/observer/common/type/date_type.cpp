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
#include <ios>

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
  // set date format
  stringstream ss;
  string date_format = val.get_date_format();
  int          year  = val.value_.int_value_ / 10000;
  int          month = (val.value_.int_value_ / 100) % 100;
  int          day   = val.value_.int_value_ % 100;
  RC rc = RC::SUCCESS;

  if (date_format.empty()) {
    ss << std::setfill('0') << std::setw(4) << year << "-" << std::setw(2) << month << "-" << std::setw(2) << day;
  }
  else {
    for (int i = 0; i < date_format.length(); ) {
      if (date_format[i] == '%') {
        if (i + 1 >= date_format.length()) {
          LOG_ERROR("Function invalid argument.");
          rc = RC::INVALID_ARGUMENT;
          break;
        }
        else {
          std::streamsize oldWidth = ss.width();
          char oldFill = ss.fill();
          if (date_format[i + 1] == 'y' || date_format[i + 1] == 'Y') {
            ss << std::setfill('0') << std::setw(4) << year;
          }
          else if (date_format[i + 1] == 'm' || date_format[i + 1] == 'M') {
            ss << std::setfill('0') << std::setw(2) << month;
          }
          else if (date_format[i + 1] == 'd' || date_format[i + 1] == 'D') {
            ss << std::setfill('0') << std::setw(2) << day;
          }
          else if (date_format[i + 1] == '%') {
            ss << '%';
          }
          ss.width(oldWidth);
          ss.fill(oldFill);
        }
        i += 2;
      }
      else {
        ss << date_format[i];
        i++;
      }
    }
  }
  result = ss.str();
  return rc;
}