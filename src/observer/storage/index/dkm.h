#pragma once

// only included in case there's a C++11 compiler out there that doesn't support `#pragma once`
#ifndef DKM_KMEANS_H
#define DKM_KMEANS_H

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <random>
#include <tuple>
#include <type_traits>
#include <vector>
#include "immintrin.h"

/*
DKM - A k-means implementation that is generic across variable data dimensions.
*/


namespace dkm {

/*
These functions are all private implementation details and shouldn't be referenced outside of this
file.
*/
namespace details {

/*
Calculate the square of the distance between two points.
*/
template <typename T, size_t N>
T distance_squared(const std::vector<T>& a, const std::vector<T>& b) {
  assert(a.size() == b.size());
	T dist = T();
  switch(N) {
    case 0: { // l2_distance
      // for (int i = 0; i < point_a.size(); ++i) {
      //   T diff = point_a[i] - point_b[i];
      //   dist += diff * diff;
      // }
      // dist = std::sqrt(dist);
      size_t size = a.size();
      __m256 sum = _mm256_setzero_ps(); // 初始化为 0

      // 处理完整的 8 元素块
      size_t i = 0;
      for (; i + 7 < size; i += 8) {
          __m256 v1 = _mm256_loadu_ps(&a[i]);
          __m256 v2 = _mm256_loadu_ps(&b[i]);
          __m256 diff = _mm256_sub_ps(v1, v2);
          __m256 sq = _mm256_mul_ps(diff, diff);
          sum = _mm256_add_ps(sum, sq);
      }
      // 处理剩余的元素
      T scalarSum = 0.0f;
      for (; i < size; ++i) {
          float diff = a[i] - b[i];
          scalarSum += diff * diff;
      }

      // 处理最后的结果
      T result[8];
      _mm256_storeu_ps(result, sum);
      dist = std::sqrt(scalarSum + result[0] + result[1] + result[2] + result[3] + result[4] + result[5] + result[6] + result[7]);
    }break;
    case 1: { // cosine_distance
      // T inner_p = 0.0;
      // T mod_1   = 0.0;
      // T mod_2   = 0.0;
      // for (int i = 0; i < a.size(); i++) {
      //   inner_p += a[i] * b[i];
      //   mod_1 += a[i] * b[i];
      //   mod_2 += a[i] * b[i];
      // }
      // mod_1 = sqrtf(mod_1);
      // mod_2 = sqrtf(mod_2);
      // dist =  (1 - (inner_p / (mod_1 * mod_2)));
      size_t size = a.size();
      __m256 sumInner = _mm256_setzero_ps(); // 用于内积
      __m256 sumMod1 = _mm256_setzero_ps();   // 用于模1
      __m256 sumMod2 = _mm256_setzero_ps();   // 用于模2

      int i = 0;
      // 处理完整的8元素块
      for (; i + 7 < size; i += 8) {
          __m256 vecA = _mm256_loadu_ps(&a[i]); // 加载8个元素
          __m256 vecB = _mm256_loadu_ps(&b[i]); // 加载8个元素

          // 计算内积
          __m256 mul = _mm256_mul_ps(vecA, vecB);
          sumInner = _mm256_add_ps(sumInner, mul);

          // 计算模
          sumMod1 = _mm256_add_ps(sumMod1, _mm256_mul_ps(vecA, vecA));
          sumMod2 = _mm256_add_ps(sumMod2, _mm256_mul_ps(vecB, vecB));
      }

      // 处理剩余元素
      T inner_p = 0.0f;
      T mod_1 = 0.0f;
      T mod_2 = 0.0f;
      for (; i < size; ++i) {
          inner_p += a[i] * b[i];
          mod_1 += a[i] * a[i];
          mod_2 += b[i] * b[i];
      }

      // 收集 AVX 计算结果
      T innerArr[8];
      _mm256_storeu_ps(innerArr, sumInner);
      for (int j = 0; j < 8; ++j) {
          inner_p += innerArr[j];
      }

      T mod1Arr[8];
      _mm256_storeu_ps(mod1Arr, sumMod1);
      for (int j = 0; j < 8; ++j) {
          mod_1 += mod1Arr[j];
      }

      T mod2Arr[8];
      _mm256_storeu_ps(mod2Arr, sumMod2);
      for (int j = 0; j < 8; ++j) {
          mod_2 += mod2Arr[j];
      }

      // 计算平方根
      mod_1 = sqrtf(mod_1);
      mod_2 = sqrtf(mod_2);

      dist = (1 - (inner_p / (mod_1 * mod_2)));
    } break;
    case 2: { // inner product
      // T f_result = 0.0;
      // for (int i = 0; i < a.size(); i++) {
      //   f_result += a[i] * b[i];
      // }
      // dist = f_result;
      size_t size = a.size();
      __m256 sum = _mm256_setzero_ps(); // 初始化为 0

      int i = 0;
      // 处理完整的8元素块
      for (; i + 7 < size; i += 8) {
          __m256 vecA = _mm256_loadu_ps(&a[i]); // 加载8个元素
          __m256 vecB = _mm256_loadu_ps(&b[i]); // 加载8个元素

          // 计算乘积并累加
          __m256 mul = _mm256_mul_ps(vecA, vecB);
          sum = _mm256_add_ps(sum, mul);
      }

      // 处理剩余元素
      T result = 0.0f;
      for (; i < size; ++i) {
          result += a[i] * b[i];
      }

      // 收集 AVX 计算结果
      T temp[8];
      _mm256_storeu_ps(temp, sum);
      for (int j = 0; j < 8; ++j) {
          result += temp[j];
      }
      dist = result;
    } break;
    default:
      break;
  };
	// for (typename std::vector<T>::size_type i = 0; i < N; ++i) {
	// 	auto delta = point_a[i] - point_b[i];
	// 	d_squared += delta * delta;
	// }
	// return d_squared;
  return dist;
}



template <typename T, size_t N>
T distance(const std::vector<T>& point_a, const std::vector<T>& point_b) {
	// return std::sqrt(distance_squared(point_a, point_b));
  return distance_squared<T, N>(point_a, point_b);
}

/*
Calculate the smallest distance between each of the data points and any of the input means.
*/
template <typename T, size_t N>
std::vector<T> closest_distance(
	const std::vector<std::vector<T>>& means, const std::vector<std::vector<T>>& data) {
	std::vector<T> distances;
	distances.reserve(data.size());
	for (auto& d : data) {
		T closest = distance_squared<T, N>(d, means[0]);
		for (auto& m : means) {
			T distance = distance_squared<T, N>(d, m);
			if (distance < closest)
				closest = distance;
		}
		distances.push_back(closest);
	}
	return distances;
}

/*
This is an alternate initialization method based on the [kmeans++](https://en.wikipedia.org/wiki/K-means%2B%2B)
initialization algorithm.
*/
template <typename T, size_t N>
std::vector<std::vector<T>> random_plusplus(const std::vector<std::vector<T>>& data, uint32_t k, uint64_t seed) {
	assert(k > 0);
	assert(data.size() > 0);
	using input_size_t = typename std::vector<T>::size_type;
	std::vector<std::vector<T>> means;
	// Using a very simple PRBS generator, parameters selected according to
	// https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
	std::linear_congruential_engine<uint64_t, 6364136223846793005, 1442695040888963407, UINT64_MAX> rand_engine(seed);

	// Select first mean at random from the set
	{
		std::uniform_int_distribution<input_size_t> uniform_generator(0, data.size() - 1);
		means.push_back(data[uniform_generator(rand_engine)]);
	}

	for (uint32_t count = 1; count < k; ++count) {
		// Calculate the distance to the closest mean for each data point
		auto distances = details::closest_distance<T, N>(means, data);
		// Pick a random point weighted by the distance from existing means
		// TODO: This might convert floating point weights to ints, distorting the distribution for small weights
#if !defined(_MSC_VER) || _MSC_VER >= 1900
		std::discrete_distribution<input_size_t> generator(distances.begin(), distances.end());
#else  // MSVC++ older than 14.0
		input_size_t i = 0;
		std::discrete_distribution<input_size_t> generator(distances.size(), 0.0, 0.0, [&distances, &i](double) { return distances[i++]; });
#endif
		means.push_back(data[generator(rand_engine)]);
	}
	return means;
}

/*
Calculate the index of the mean a particular data point is closest to (euclidean distance)
*/
template <typename T, size_t N>
uint32_t closest_mean(const std::vector<T>& point, const std::vector<std::vector<T>>& means) {
	assert(!means.empty());
	T smallest_distance = distance_squared<T, N>(point, means[0]);
	typename std::vector<T>::size_type index = 0;
	T distance;
	for (size_t i = 1; i < means.size(); ++i) {
		distance = distance_squared<T, N>(point, means[i]);
		if (distance < smallest_distance) {
			smallest_distance = distance;
			index = i;
		}
	}
	return index;
}

/*
Calculate the index of the mean each data point is closest to (euclidean distance).
*/
template <typename T, size_t N>
std::vector<uint32_t> calculate_clusters(
	const std::vector<std::vector<T>>& data, const std::vector<std::vector<T>>& means) {
	std::vector<uint32_t> clusters;
	for (auto& point : data) {
		clusters.push_back(closest_mean<T, N>(point, means));
	}
	return clusters;
}

/*
Calculate means based on data points and their cluster assignments.
*/
template <typename T, size_t N>
std::vector<std::vector<T>> calculate_means(const std::vector<std::vector<T>>& data,
	const std::vector<uint32_t>& clusters,
	const std::vector<std::vector<T>>& old_means,
	uint32_t k) {
	std::vector<std::vector<T>> means(k, std::vector<T>(data[0].size()));
	std::vector<T> count(k);
	for (size_t i = 0; i < std::min(clusters.size(), data.size()); ++i) {
		auto& mean = means[clusters[i]];
		count[clusters[i]] += 1;
		for (size_t j = 0; j < std::min(data[i].size(), mean.size()); ++j) {
			mean[j] += data[i][j];
		}
	}
	for (size_t i = 0; i < k; ++i) {
		if (count[i] == 0) {
			means[i] = old_means[i];
		} else {
			for (size_t j = 0; j < means[i].size(); ++j) {
				means[i][j] /= count[i];
			}
		}
	}
	return means;
}

template <typename T, size_t N>
std::vector<T> deltas(
	const std::vector<std::vector<T>>& old_means, const std::vector<std::vector<T>>& means)
{
	std::vector<T> distances;
	distances.reserve(means.size());
	assert(old_means.size() == means.size());
	for (size_t i = 0; i < means.size(); ++i) {
		distances.push_back(distance<T, N>(means[i], old_means[i]));
	}
	return distances;
}

template <typename T>
bool deltas_below_limit(const std::vector<T>& deltas, T min_delta) {
	for (T d : deltas) {
		if (d > min_delta) {
			return false;
		}
	}
	return true;
}

} // namespace details

/*
clustering_parameters is the configuration used for running the kmeans_lloyd algorithm.

It requires a k value for initialization, and can subsequently be configured with your choice
of optional parameters, including:
* Maximum iteration count; the algorithm will terminate if it reaches this iteration count
  before converging on a solution. The results returned are the means and cluster assignments 
  calculated in the last iteration before termination.
* Minimum delta; the algorithm will terminate if the change in position of all means is
  smaller than the specified distance.
* Random seed; if present, this will be used in place of `std::random_device` for kmeans++
  initialization. This can be used to ensure reproducible/deterministic behavior.
*/
template <typename T>
class clustering_parameters {
public:
	explicit clustering_parameters(uint32_t k) :
	_k(k),
	_has_max_iter(false), _max_iter(),
	_has_min_delta(false), _min_delta(),
	_has_rand_seed(false), _rand_seed()
	{}

	void set_max_iteration(uint64_t max_iter)
	{
		_max_iter = max_iter;
		_has_max_iter = true;
	}

	void set_min_delta(T min_delta)
	{
		_min_delta = min_delta;
		_has_min_delta = true;
	}

	void set_random_seed(uint64_t rand_seed)
	{
		_rand_seed = rand_seed;
		_has_rand_seed = true;
	}

	bool has_max_iteration() const { return _has_max_iter; }
	bool has_min_delta() const { return _has_min_delta; }
	bool has_random_seed() const { return _has_rand_seed; }

	uint32_t get_k() const { return _k; };
	uint64_t get_max_iteration() const { return _max_iter; }
	T get_min_delta() const { return _min_delta; }
	uint64_t get_random_seed() const { return _rand_seed; }

private:
	uint32_t _k;
	bool _has_max_iter;
	uint64_t _max_iter;
	bool _has_min_delta;
	T _min_delta;
	bool _has_rand_seed;
	uint64_t _rand_seed;
};

/*
Implementation of k-means generic across the data type and the dimension of each data item. Expects
the data to be a vector of fixed-size arrays. Generic parameters are the type of the base data (T)
and the dimensionality of each data point (N). All points must have the same dimensionality.

e.g. points of the form (X, Y, Z) would be N = 3.

Takes a `clustering_parameters` struct for algorithm configuration. See the comments for the
`clustering_parameters` struct for more information about the configuration values and how they
affect the algorithm.

Returns a std::tuple containing:
  0: A vector holding the means for each cluster from 0 to k-1.
  1: A vector containing the cluster number (0 to k-1) for each corresponding element of the input
	 data vector.

Implementation details:
This implementation of k-means uses [Lloyd's Algorithm](https://en.wikipedia.org/wiki/Lloyd%27s_algorithm)
with the [kmeans++](https://en.wikipedia.org/wiki/K-means%2B%2B)
used for initializing the means.

*/
template <typename T, size_t N>
std::tuple<std::vector<std::vector<T>>, std::vector<uint32_t>> kmeans_lloyd(
	const std::vector<std::vector<T>>& data, const clustering_parameters<T>& parameters) {
	static_assert(std::is_arithmetic<T>::value && std::is_signed<T>::value,
		"kmeans_lloyd requires the template parameter T to be a signed arithmetic type (e.g. float, double, int)");
	assert(parameters.get_k() > 0); // k must be greater than zero
	assert(data.size() >= parameters.get_k()); // there must be at least k data points
	std::random_device rand_device;
	uint64_t seed = parameters.has_random_seed() ? parameters.get_random_seed() : rand_device();
	std::vector<std::vector<T>> means = details::random_plusplus<T, N>(data, parameters.get_k(), seed);

	std::vector<std::vector<T>> old_means;
	std::vector<std::vector<T>> old_old_means;
	std::vector<uint32_t> clusters;
	// Calculate new means until convergence is reached or we hit the maximum iteration count
	uint64_t count = 0;
	do {
		clusters = details::calculate_clusters<T, N>(data, means);
		old_old_means = old_means;
		old_means = means;
		means = details::calculate_means<T, N>(data, clusters, old_means, parameters.get_k());
		++count;
	} while (means != old_means && means != old_old_means
		&& !(parameters.has_max_iteration() && count == parameters.get_max_iteration())
		&& !(parameters.has_min_delta() && details::deltas_below_limit<T>(details::deltas<T, N>(old_means, means), parameters.get_min_delta())));

	return std::tuple<std::vector<std::vector<T>>, std::vector<uint32_t>>(means, clusters);
}

/*
This overload exists to support legacy code which uses this signature of the kmeans_lloyd function.
Any code still using this signature should move to the version of this function that uses a
`clustering_parameters` struct for configuration.
*/
template <typename T, size_t N>
std::tuple<std::vector<std::vector<T>>, std::vector<uint32_t>> kmeans_lloyd(
	const std::vector<std::vector<T>>& data, uint32_t k,
	uint64_t max_iter = 0, T min_delta = -1.0) {
	clustering_parameters<T> parameters(k);
	if (max_iter != 0) {
		parameters.set_max_iteration(max_iter);
	}
	if (min_delta != 0) {
		parameters.set_min_delta(min_delta);
	}
	return kmeans_lloyd<T, N>(data, parameters);
}

} // namespace dkm

#endif /* DKM_KMEANS_H */