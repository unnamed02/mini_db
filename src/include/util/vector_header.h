#pragma once
#include "util/array_header.h"
#include <vector>

namespace mini_db{

using std::vector;
using std::make_pair;

template<typename KeyType,typename ValueType>
class VectorHeader : public ArrayHeader<KeyType,ValueType>{
    private:
    vector<pair<KeyType,ValueType>> vector_;

    public:
    VectorHeader(DiskManager* disk_manager_ptr):
    ArrayHeader<KeyType,ValueType>(disk_manager_ptr){

    };

    inline pair<KeyType,ValueType>& operator[](block_offset_t i){
        return vector_[i];
    }

    block_offset_t Find(const KeyType& key);

    bool Insert(const KeyType& key,const ValueType& value){
        vector_.push_back(make_pair(key,value));
    }

    bool Persist();

    inline size_t Size(){
        return vector_.size();
    }

};
}