/*
 * Simple LRU software cache model
 * Date: 3rd February, 2019
 * Author: Nilanjan Goswami
 */

#include "lru_cache_template.hpp"

typedef uint64_t draw_id_t;

class LRUCache : public LRUCacheTemplate<draw_id_t> {
private:
    uint32_t         seed_;
    void SelfTest(uint64_t test_size);

public:
    LRUCache(uint32_t seed, uint32_t cache_size, uint64_t test_size) :
        LRUCacheTemplate<draw_id_t>(cache_size),
        seed_(seed)
    {
        SelfTest(test_size);
    }

    virtual ~LRUCache() {}
};
