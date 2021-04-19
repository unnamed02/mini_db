#pragma once

#include "common/config.h"
#include "util/array_block.h"

namespace mini_db{

template<typename KeyType,typename ValueType>
class ArrayHeader{

    public:

    virtual pair<KeyType,ValueType>& operator[](int32_t i);

    virtual ValueType binary_search(KeyType key) = 0;

    virtual bool push_back(KeyType key,ValueType value);

    virtual bool persist();
    
};

}