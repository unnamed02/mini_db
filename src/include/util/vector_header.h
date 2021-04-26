#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
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
        size_t header_offset = upper_bound(vector_.begin(),vector_.end(),key,[](const KeyType& key,auto to_compare)->bool{
            return (key > to_compare.first);
        }) - vector_.begin() - 1;
        if(header_offset >= 0){
            return NOT_FOUND_OFFSET;
        }
        return header_offset;
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