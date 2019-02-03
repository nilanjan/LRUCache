/*
 * Simple LRU software cache model
 * Date: 3rd February, 2019
 * Author: Nilanjan Goswami
 */

#include "lru_cache.hpp"

void LRUCache::SelfTest(uint64_t test_size) {
    draw_id_t dataset_size = test_size/10;

    srand(seed_);

    for (uint64_t idx=0; idx<test_size; ++idx) {
        uint64_t data_idx = rand()%dataset_size;
        std::tuple<bool, bool, bool> stat = Get(data_idx);
    }

    CheckSanity();

    std::cout<<"Hit count: "<<GetHitCount()<<std::endl;
    std::cout<<"Miss count: "<<GetMissCount()<<std::endl;
    std::cout<<"Full count: "<<GetFullCount()<<std::endl;
}
