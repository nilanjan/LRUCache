/*
 * Simple LRU software cache model
 * Date: 3rd February, 2019
 * Author: Nilanjan Goswami
 */

#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <cassert>

template<typename KT> class LRUCacheTemplate {
private:
    typedef std::list<KT> queue_t;
    typename std::list<KT>::iterator queue_iter_t;

    queue_t                                                       deque_; // list of keys in a queue (maintains the access order)
    std::unordered_map<KT, typename std::list<KT>::iterator>      map_;   // map of key and list_iterators(deque)
    uint32_t                                                      size_;  // size of the cache

    //statistics
    uint64_t                                                      hit_count_;
    uint64_t                                                      miss_count_;
    uint64_t                                                      full_count_;
    uint64_t                                                      access_count_;

public:
    LRUCacheTemplate(uint32_t size):
        size_(size),
        hit_count_(0),
        miss_count_(0),
        full_count_(0),
        access_count_(0) { }

    // Reset the cache key structures
    // Statistics are kep intact
    // Cache size is unchanged
    void Reset() {
        deque_.clear();
        map_.clear();
    }

    std::tuple<bool, bool, bool> Get(KT key) {
        bool hit = false;
        bool miss = false;
        bool full = false;

        ++access_count_;

        // cache entry does not exists
        if(map_.find(key) == map_.end()) {
            ++miss_count_;
            miss = true;

            // Cache full so remove the last entry
            if(deque_.size() == size_) {
                ++full_count_;
                full = true;

                KT last_key = deque_.back();
                deque_.pop_back();
                map_.erase(last_key);
            }

            deque_.push_front(key);
            map_[key] = deque_.begin();
        } else { // cache entry exits
            hit = true;
            ++hit_count_;

            // remove the old entry from the queue
            deque_.erase(map_[key]);

            // move the same old entry to the front of the
            // queu to demark its most recently used
            deque_.push_front(key);
            map_[key] = deque_.begin();
        }

        return std::make_tuple(hit, miss, full);
    }

    uint32_t GetSize() {
        return size_;
    }

    void CheckSanity() {
        assert(hit_count_+miss_count_ == access_count_);
    }

    uint64_t GetHitCount() { return hit_count_; }
    uint64_t GetMissCount() { return miss_count_; }
    uint64_t GetFullCount() { return full_count_; }

    virtual ~LRUCacheTemplate() {}
};
