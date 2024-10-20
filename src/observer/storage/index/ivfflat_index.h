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

#include "common/types.h"
#include "storage/field/field_meta.h"
#include "storage/index/bplus_tree.h"
#include "storage/index/index.h"
#include "storage/table/table.h"
#include "storage/record/record.h"
#include "storage/text/text_manager.h"
#include "storage/trx/vacuous_trx.h"
#include <numeric>
#include <queue>
#include <vector>
#include <cmath>
#include <limits>
#include <unordered_map>

class Table;
enum dis_type
{
  l2_,
  inner_,
  cosine_,
};
class IvfflatIndexScanner : public IndexScanner
{
public:
  IvfflatIndexScanner(std::vector<RID> closest_rids) { closest_rids_.swap(closest_rids); }
  ~IvfflatIndexScanner() noexcept override {}

  RC next_entry(RID *rid) override
  {
    if (closest_rids_.empty()) {
      return RC::RECORD_EOF;
    }
    *rid = closest_rids_.front();
    closest_rids_.erase(closest_rids_.begin());
    return RC::SUCCESS;
  }
  RC destroy() override { return RC::SUCCESS; }

private:
  std::vector<RID> closest_rids_;
};


inline float euclidean_distance(const float *a, const float *b, int size, dis_type type)
{
  float dist = 0.0f;
  switch (type) {
    case l2_: {
      float diff = 0.0f;
      for (size_t i = 0; i < size; ++i) {
        diff = a[i] - b[i];
        dist += diff * diff;
      }
      //  return euclidean_distance_parallel(a,b,size,8);  // 这里不用开方也能保证相对大小
    } break;
    case cosine_: {

      float inner_p = 0.0;
      float mod_1   = 0.0;
      float mod_2   = 0.0;
      for (int i = 0; i < size; i++) {
        inner_p += a[i] * b[i];
        mod_1 += a[i] * b[i];
        mod_2 += a[i] * b[i];
      }
      mod_1 = sqrtf(mod_1);
      mod_2 = sqrtf(mod_2);
      return (1 - (inner_p / (mod_1 * mod_2)));
    } break;
    case inner_: {
      float f_result = 0.0;
      for (int i = 0; i < size; i++) {
        f_result += a[i] * b[i];
      }
      return f_result;
    } break;
  }
  return dist;
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
        centroids[i][j] = static_cast<float>((float)rand() / (float)RAND_MAX * 300);
      }
    }
  }

  void init(int num_clusters, int dim)
  {
    centroids.resize(num_clusters, std::vector<float>(dim, 0.0f));
    // 简单初始化：随机设定一些聚类中心（可以使用更好的方法）
    for (int i = 0; i < num_clusters; ++i) {
      for (int j = 0; j < dim; ++j) {
        centroids[i][j] = static_cast<float>((float)rand() / (float)RAND_MAX * 300);
      }
    }
    dim_ = dim;
  }

  // 找到最近的聚类中心
  std::vector<int> assign_cluster_with_probes(
      const float *vector, dis_type type, int probes)
  {
    // 使用最小堆保存最近的簇及其距离
    using Pair = std::pair<float, int>;  // first: 距离, second: 簇索引
    std::priority_queue<Pair> closest_clusters;

    for (size_t i = 0; i < centroids.size(); ++i) {
      float dist = euclidean_distance(vector, centroids[i].data(), dim_, type);

      // 如果堆未满或当前距离比堆中的最大距离小
      if (closest_clusters.size() < probes || dist < closest_clusters.top().first) {
        closest_clusters.push({dist, i});
        // 保证堆的大小最多为 probes
        if (closest_clusters.size() > probes) {
          closest_clusters.pop();
        }
      }
    }

    // 将堆中的簇索引返回
    std::vector<int> result;
    while (!closest_clusters.empty()) {
      result.push_back(closest_clusters.top().second);
      closest_clusters.pop();
    }

    // 反转结果，使得返回的簇按距离从近到远排列
    std::reverse(result.begin(), result.end());

    // 你可以根据需要返回 result 或对其进行进一步处理
    return result;
  }

  int assign_cluster(const float *vector, dis_type type)
  {
    int   closest      = -1;
    float closest_dist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < centroids.size(); ++i) {
      float dist = euclidean_distance(vector, centroids[i].data(), dim_, type);
      if (dist < closest_dist) {
        closest      = i;
        closest_dist = dist;
      }
    }
    return closest;
  }

  int dim_;
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

  RC close() { return RC::UNIMPLEMENTED; }

  RC insert_entry(Record &record, const RID *rid, const int record_size, int field_indexs[]) override
  {
    int cluster_id = kmeans.assign_cluster((float *)(record.data() + offset_), type_);
    std::vector<float> vector;
    for(int i=0;i<dim_;i++){
     vector.push_back(((float *)(record.data() + offset_))[i]);
    }
    inverted_list[cluster_id].push_back(make_pair(*rid,std::move(vector)));
    return RC::SUCCESS;
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

  IndexScanner *create_scanner(float *query, int limit)
  {
    IvfflatIndexScanner *index_scanner = new IvfflatIndexScanner(search(query, limit));
    return index_scanner;
  }

  struct CompareDistanceAndRID
  {
    bool operator()(const std::pair<float, RID> &lhs, const std::pair<float, RID> &rhs) const
    {
      return lhs.first < rhs.first;  // 按照距离进行比较，距离小的优先
    }
  };
  // 搜索最近的向量
  std::vector<RID> search(float *query, int limit)
  {
    // 1. 找到最近的聚类中心
    std::vector<int> cluster_ids = kmeans.assign_cluster_with_probes(query, type_, 3);

    // 2. 在该聚类内搜索最近的向量
    VacuousTrx       trx;
    Record           record;
    std::vector<RID> closest_rids;

    // 定义一个优先队列（小顶堆），存储距离和对应的 RID
    using DistanceAndRID = std::pair<float, RID>;
    std::priority_queue<DistanceAndRID, std::vector<DistanceAndRID>, CompareDistanceAndRID> closest_queue;
    for (auto &cluster_id : cluster_ids) {
      for (const auto &rid : inverted_list[cluster_id]) {
       // table_->get_record(rid, record);
        float dist = euclidean_distance(query, rid.second.data(), dim_, type_);

        // 如果小顶堆的大小小于 limit，直接插入
        if (closest_queue.size() < limit) {
          closest_queue.emplace(dist, rid.first);
        } else {
          // 如果堆已满，且当前距离比堆顶大，则替换堆顶
          if (dist < closest_queue.top().first) {
            closest_queue.pop();               // 移除堆顶
            closest_queue.emplace(dist, rid.first);  // 插入当前更近的向量
          }
        }
      }
    }
    // 遍历聚类中的所有向量

    // 将小顶堆中的结果放入 closest_rids 中
    while (!closest_queue.empty()) {
      closest_rids.push_back(closest_queue.top().second);
      closest_queue.pop();
    }
    std::reverse(closest_rids.begin(), closest_rids.end());

    return closest_rids;  // 返回 limit 个最近的向量
  }

private:
  KMeans                                    kmeans;         // 用于对数据进行聚类
  std::unordered_map<int, std::vector<pair<RID,vector<float>>>> inverted_list;  // 倒排列表

  int              lists_  = 1;
  int              probes_ = 1;
  int              dim_;
  dis_type         type_;
  int              offset_;
  Table           *table_;
  IndexMeta        index_meta_;
  BplusTreeHandler index_handler_;
  bool             inited_ = false;
};
