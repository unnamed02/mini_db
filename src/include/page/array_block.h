#pragma once

#include "common/config.h"
#include "common/logger.h"
#include <utility>

namespace mini_dbm{

using std::pair;

static const int32_t CONTENT_SIZE = PAGE_SIZE - sizeof(size_t);

template<typename KeyType>
class ArrayBlock{
    private:
    
    size_t offset_;

    char content_[CONTENT_SIZE];

    static inline int32_t CONTENT_NUM(){
        return CONTENT_SIZE / sizeof(KeyType);
    }

    public:


    inline KeyType& operator[](size_t n){
        auto dst_ptr = reinterpret_cast<KeyType*>(content_ + n * sizeof(KeyType));
        return *dst_ptr;
    }

    inline bool PushBack(const KeyType& key){
        if(offset_ != CONTENT_NUM()){
            auto dst_ptr = reinterpret_cast<KeyType*>(content_ + offset_ * sizeof(KeyType));
            *dst_ptr = key;
            offset_++;
            LOG_DEBUG("pushing back %d",key);
            return true;
        }
        return false;
    }

    size_t Find(const KeyType& key);

};

template<typename KeyType>
size_t ArrayBlock<KeyType>::Find(const KeyType& key){
    size_t left = 0;
    size_t right = offset_ - 1;
    
    while(right > left){
        size_t mid = (left + right) >> 1;
        auto dst_ptr = reinterpret_cast<KeyType*>(content_ + mid * sizeof(KeyType));
        if(*dst_ptr >= key){
            right = mid;
        }else{
            left = mid + 1;
        }
    }

    auto dst_ptr = reinterpret_cast<KeyType*>(content_ + left * sizeof(KeyType));
    if(*dst_ptr >= key){
        return left;
    }

    return NOT_FOUND_OFFSET;
}

}