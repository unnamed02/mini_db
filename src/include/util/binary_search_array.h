#pragma once

#include "common/config.h"
#include "util/array_header.h"
#include "util/array_block.h"

namespace mini_db{

template<typename KeyType>
class BinarySearchArray{
    private:
    ArrayHeader<KeyType,ArrayBlock*>* _header_ptr;

    ArrayBlock<KeyType>* _cur_block_ptr;

    public:
    BinarySearchArray(ArrayHeader<KeyType,ArrayBlock*>* header_ptr){
        this->_header_ptr = header_ptr;
    }

    int32_t find(KeyType start);

    bool push_back(KeyType start);

    bool persist();

};

}