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
#include <mutex>
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
#pragma omp parallel for reduction(+ : dist)
      for (size_t i = 0; i < size; ++i) {
        float diff = a[i] - b[i];
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
        centroids[i][j] = static_cast<float>((float)rand() / (float)RAND_MAX * 250);
      }
    }
  }

  void init(int num_clusters, int dim)
  {
    centroids.resize(num_clusters, std::vector<float>(dim, 0.0f));
    // 简单初始化：随机设定一些聚类中心（可以使用更好的方法）
    for (int i = 0; i < num_clusters; ++i) {
      for (int j = 0; j < dim; ++j) {
        centroids[i][j] = static_cast<float>((float)rand() / (float)RAND_MAX * 250);
      }
    }
    dim_ = dim;
  }

  // 找到最近的聚类中心
  std::vector<int> assign_cluster_with_probes(
      const float *vector, std::unordered_map<int, std::vector<RID>> &inverted_list, dis_type type, int probes)
  {
    // 使用最小堆保存最近的簇及其距离
    using Pair = std::pair<float, int>;  // first: 距离, second: 簇索引
    std::priority_queue<Pair> closest_clusters;

#pragma omp parallel for
    for (size_t i = 0; i < centroids.size(); ++i) {
      float dist = euclidean_distance(vector, centroids[i].data(), dim_, type);

      // 如果堆未满或当前距离比堆中的最大距离小
#pragma omp parallel critical
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

  void update_centroids(const std::unordered_map<int, std::vector<RID>> &inverted_list, Table *table, int offset)
  {
    std::vector<int>                counts(centroids.size(), 0);
    std::vector<std::vector<float>> new_centroids(centroids.size(), std::vector<float>(dim_, 0.0f));
    Record                          record;
    for (const auto &entry : inverted_list) {
      int         cluster_id = entry.first;   // 聚类 ID
      const auto &rids       = entry.second;  // 该聚类中的所有 RID

      for (const RID &rid : rids) {
        // 使用 rid.getfloats() 获取特征向量
        table->get_record(rid, record);
        float *feature_vector = (float *)(record.data() + offset);  // 假设 getfloats() 返回特征向量

        // 更新新聚类中心
        for (size_t i = 0; i < dim_; ++i) {
          new_centroids[cluster_id][i] += feature_vector[i];
        }
        counts[cluster_id] += 1;  // 计数
      }
    }

    // 计算均值，更新聚类中心
    for (size_t i = 0; i < centroids.size(); ++i) {
      if (counts[i] > 0) {
        for (size_t j = 0; j < dim_; ++j) {
          new_centroids[i][j] /= counts[i];  // 计算均值
        }
        centroids[i] = new_centroids[i];  // 更新聚类中心
      }
    }
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
    inverted_list[cluster_id].push_back(*rid);
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
    std::vector<int> cluster_ids = kmeans.assign_cluster_with_probes(query, inverted_list, type_, 3);

    // 2. 在该聚类内搜索最近的向量
    VacuousTrx       trx;
    Record           record;
    std::vector<RID> closest_rids;

    // 定义一个优先队列（小顶堆），存储距离和对应的 RID
    using DistanceAndRID = std::pair<float, RID>;
    std::priority_queue<DistanceAndRID, std::vector<DistanceAndRID>, CompareDistanceAndRID> closest_queue;

#pragma omp parallel for
    for (int i = 0; i < cluster_ids.size(); i++) {
#pragma omp parallel for
      for (const auto &rid : inverted_list[cluster_ids[i]]) {
        table_->get_record(rid, record);
        float dist = euclidean_distance(query, (float *)(record.data() + offset_), dim_, type_);

// 如果小顶堆的大小小于 limit，直接插入
#pragma omp critical
        if (closest_queue.size() < limit) {
          closest_queue.emplace(dist, rid);
        } else {
          // 如果堆已满，且当前距离比堆顶大，则替换堆顶
          if (dist < closest_queue.top().first) {
            closest_queue.pop();               // 移除堆顶
            closest_queue.emplace(dist, rid);  // 插入当前更近的向量
          }
        }
      }
    }
    // // 合并
    // std::priority_queue<DistanceAndRID, std::vector<DistanceAndRID>, CompareDistanceAndRID> closest_queue_merge;
    // for (int i = 0; i < cluster_ids.size(); i++) {
    //   while (!closest_queue[i].empty()) {
    //     float dist = closest_queue[i].top().first;
    //     RID   rid  = closest_queue[i].top().second;
    //     closest_queue[i].pop();

    //     // 如果全局堆的大小小于 limit，直接插入
    //     if (closest_queue_merge.size() < limit) {
    //       closest_queue_merge.emplace(dist, rid);
    //     } else {
    //       // 如果全局堆已满，且当前距离比堆顶小，则替换堆顶
    //       if (dist < closest_queue_merge.top().first) {
    //         closest_queue_merge.pop();               // 移除堆顶
    //         closest_queue_merge.emplace(dist, rid);  // 插入当前更近的向量
    //       }
    //     }
    //   }
    // }
    // 将小顶堆中的结果放入 closest_rids 中
    while (!closest_queue.empty()) {
      closest_rids.push_back(closest_queue.top().second);
      closest_queue.pop();
    }
    std::reverse(closest_rids.begin(), closest_rids.end());

    return closest_rids;  // 返回 limit 个最近的向量
  }

  void update_centroids()
  {
    kmeans.update_centroids(inverted_list, table_, offset_);
    std::unordered_map<int, std::vector<RID>> old_inverted_list = inverted_list;
    inverted_list.clear();
    Record record;
    for (auto &list : old_inverted_list) {
      for (auto &rid : list.second) {
        table_->get_record(rid, record);
        insert_entry(record, &rid, -1, nullptr);
      }
    }
  }

private:
  KMeans                                    kmeans;         // 用于对数据进行聚类
  std::unordered_map<int, std::vector<RID>> inverted_list;  // 倒排列表

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
