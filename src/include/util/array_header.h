#pragma once

#include "common/config.h"
#include "page/array_block.h"

namespace mini_db{

template<typename KeyType,typename ValueType>
class ArrayHeader{

    public:

    virtual pair<KeyType,ValueType>& operator[](block_offset_t i);

    virtual block_offset_t Find(KeyType key) = 0;

    virtual bool PushBack(KeyType key,ValueType value);

    virtual bool Persist();
    
};

}