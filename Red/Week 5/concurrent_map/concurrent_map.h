#pragma once

#include <algorithm>
#include <future>
#include <map>
#include <vector>

using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
        mutex& m;
        V& ref_to_value;
        ~Access() {
			m.unlock();
        }
    };

    explicit ConcurrentMap(size_t bucket_count);

    Access operator[](const K& key);

    map<K, V> BuildOrdinaryMap();

private:
    struct Bucket {
        map<K,V> part_map_;
        mutex m;
    };
    vector<Bucket> buckets_;
};

template <typename K, typename V>
ConcurrentMap<K, V>::ConcurrentMap(size_t bucket_count) {
	buckets_ = vector<Bucket>(bucket_count);
}

template <typename K, typename V>
typename ConcurrentMap<K, V>::Access ConcurrentMap<K, V>::operator[](const K& key) {
	
    const size_t bucket_index = key % buckets_.size();
	buckets_[bucket_index].m.lock();

    if (buckets_[bucket_index].part_map_.count(key) == 0) {
		buckets_[bucket_index].part_map_[key] = V();
    }

	return Access { buckets_[bucket_index].m, buckets_[bucket_index].part_map_[key] };
}

template <typename K, typename V>
map<K, V> ConcurrentMap<K, V>::BuildOrdinaryMap() {
	
    map<K, V> full_map;
    for (size_t i = 0; i < buckets_.size(); ++i) {
		buckets_[i].m.lock();
		full_map.insert(buckets_[i].part_map_.begin(), buckets_[i].part_map_.end());
		buckets_[i].m.unlock();
    }

	return full_map;
}