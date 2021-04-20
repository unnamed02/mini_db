#pragma once

#include "common/config.h"
#include <utility>

namespace mini_db{

using std::pair;

static const int32_t CONTENT_SIZE = PAGE_SIZE - BLOCK_OFFSET_SIZE;

template<typename KeyType>
class ArrayBlock{
    private:
    
    block_offset_t offset_;

    char content_[CONTENT_SIZE];

    static inline int32_t CONTENT_NUM(){
        return CONTENT_SIZE / sizeof(KeyType);
    }

    public:


    inline KeyType& operator[](block_offset_t n){
        auto dst_ptr = reinterpret_cast<KeyType*>(content_ + n * sizeof(KeyType));
        return *dst_ptr;
    }

    inline bool PushBack(const KeyType& key){
        if(offset_ != CONTENT_NUM()){
            auto dst_ptr = reinterpret_cast<KeyType*>(content_ + offset_ * sizeof(KeyType));
            *dst_ptr = key;
            offset_++;
            return true;
        }
        return false;
    }

    block_offset_t Find(const KeyType& key);

};

template<typename KeyType>
block_offset_t ArrayBlock<KeyType>::Find(const KeyType& key){
    block_offset_t left = 0;
    block_offset_t right = offset_ - 1;
    
    while(right > left){
        block_offset_t mid = (left + right) >> 1;
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