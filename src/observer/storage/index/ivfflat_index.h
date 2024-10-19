/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "storage/index/bplus_tree.h"
#include "storage/index/index.h"
#include "storage/text/text_manager.h"
#include <vector>
#include <cmath>
#include <limits>
#include <unordered_map>

class Table;

inline float euclidean_distance(const std::vector<float> &a, const std::vector<float> &b)
{
  float dist = 0.0f;
  for (size_t i = 0; i < a.size(); ++i) {
    float diff = a[i] - b[i];
    dist += diff * diff;
  }
  return std::sqrt(dist);
}

// KMeans 聚类中心，用于将向量划分到不同的簇
class KMeans
{
public:
  KMeans(){};
  std::vector<std::vector<float>> centroids;  // 聚类中心

  // 初始化聚类中心
  KMeans(int num_clusters, int dim)
  {
    centroids.resize(num_clusters, std::vector<float>(dim, 0.0f));
    // 简单初始化：随机设定一些聚类中心（可以使用更好的方法）
    for (int i = 0; i < num_clusters; ++i) {
      for (int j = 0; j < dim; ++j) {
        centroids[i][j] = static_cast<float>(rand() * 1000);
      }
    }
  }

  void init(int num_clusters, int dim)
  {
    centroids.resize(num_clusters, std::vector<float>(dim, 0.0f));
    // 简单初始化：随机设定一些聚类中心（可以使用更好的方法）
    for (int i = 0; i < num_clusters; ++i) {
      for (int j = 0; j < dim; ++j) {
        centroids[i][j] = static_cast<float>(rand() * 1000);
      }
    }
  }

  // 找到最近的聚类中心
  int assign_cluster(const std::vector<float> &vector)
  {
    int   closest      = -1;
    float closest_dist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < centroids.size(); ++i) {
      float dist = euclidean_distance(vector, centroids[i]);
      if (dist < closest_dist) {
        closest      = i;
        closest_dist = dist;
      }
    }
    return closest;
  }
};

/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */
class IvfflatIndex : public Index
{
public:
  IvfflatIndex(){};
  virtual ~IvfflatIndex() noexcept {};

  RC create(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta *field_metas[],
      int field_num) override;
  

  RC open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta *field_metas[],
      int field_num) override
  {

    return RC::UNIMPLEMENTED;
  };

  bool is_vector_index() override { return true; }

  vector<RID> ann_search(const vector<float> &base_vector, size_t limit) { return vector<RID>(); }

  RC close() { return RC::UNIMPLEMENTED; }

  RC insert_entry(Record &record, const RID *rid, const int record_size, int field_indexs[]) override
  {
    return RC::UNIMPLEMENTED;
  };
  RC delete_entry(const char *record, const RID *rid) override { return RC::UNIMPLEMENTED; };

  virtual RC update_entry(const char *record, const char *new_record, const RID *rid, int record_null) override
  {
    return RC::UNIMPLEMENTED;
  };
  RC sync() override { return RC::SUCCESS; };

  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
      int right_len, bool right_inclusive) override
  {
    return nullptr;
    ;
  }

public:
  KMeans                                                   kmeans;         // 用于对数据进行聚类
  std::unordered_map<int, std::vector<std::vector<float>>> inverted_list;  // 倒排列表

  // 将数据插入到对应的倒排列表中
  void add(const std::vector<float> &vector)
  {
    int cluster_id = kmeans.assign_cluster(vector);
    inverted_list[cluster_id].push_back(vector);
  }

  // 搜索最近的向量
  std::vector<float> search(const std::vector<float> &query)
  {
    // 1. 找到最近的聚类中心
    int cluster_id = kmeans.assign_cluster(query);

    // 2. 在该聚类内搜索最近的向量
    float              closest_dist = std::numeric_limits<float>::max();
    std::vector<float> closest_vector;
    for (const auto &vector : inverted_list[cluster_id]) {
      float dist = euclidean_distance(query, vector);
      if (dist < closest_dist) {
        closest_dist   = dist;
        closest_vector = vector;
      }
    }
    return closest_vector;  // 返回最近的向量
  }

private:
  // bool      inited_ = false;
  // Table    *table_  = nullptr;
  // int       lists_  = 1;
  // int       probes_ = 1;
  Table           *table_;
  IndexMeta        index_meta_;
  BplusTreeHandler index_handler_;
  bool             inited_ = false;
};
