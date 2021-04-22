#pragma once
#include <vector>
#include <algorithm>
#include "util/array_header.h"



namespace mini_dbm{

using std::vector;
using std::make_pair;
using std::upper_bound;

template<typename KeyType,typename ValueType>
class VectorHeader : public ArrayHeader<KeyType,ValueType>{
    private:
    vector<pair<KeyType,ValueType>> vector_;

    public:
    VectorHeader(DiskManager* disk_manager_ptr):
    ArrayHeader<KeyType,ValueType>(disk_manager_ptr){

    };

    inline pair<KeyType,ValueType>& operator[](size_t i){
        return vector_[i];
    }

    size_t Find(const KeyType& key){
        size_t upper_bound = upper_bound()
    };

    bool inline PushBack(const KeyType& key,const ValueType& value){
        vector_.push_back(make_pair(key,value));
    }

    bool Persist(){};

    size_t inline Size(){
        return vector_.size();
    }

};
}