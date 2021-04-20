#pragma once

#include <stddef.h>
#include "common/config.h"
#include "util/array_header.h"
#include "page/array_block.h"
#include "disk/disk_manager.h"

namespace mini_db{

template<typename KeyType>
class BinarySearchArray{
    private:
    ArrayHeader<KeyType,void*>* header_ptr_;

    ArrayBlock<KeyType>* cur_block_ptr_;

    DiskManager* disk_manager_ptr_;

    public:
    BinarySearchArray(ArrayHeader<KeyType,void*>* header_ptr,DiskManager* disk_manager_){
        header_ptr_ = header_ptr;
        disk_manager_ptr_ = disk_manager_ptr;
        auto new_block_ptr = new ArrayBlock<KeyType>();
        
    }

    block_offset_t Find(KeyType key);

    KeyType& operator[](block_offset_t offset);

    bool PushBack(KeyType start);

    bool Persist();

};


template<typename KeyType>  
bool BinarySearchArray<KeyType>::PushBack(KeyType start){
    if(cur_block_ptr_->PushBack(start)){
        return true;
    }
    
    auto new_block_ptr = new ArrayBlock<KeyType>();

    if(new_block_ptr){
        header_ptr_->PushBack(start,new_block_ptr);
        cur_block_ptr_ = new_block_ptr;
        cur_block_ptr_->pushBack(start);
        return true;
    }
    return false;
}

template<typename KeyType>
block_offset_t BinarySearchArray<KeyType>::Find(KeyType key){
    block_offset_t head_offset = header_ptr_->Find(key);
    if(head_offset >= 0){
        pair<KeyType,void*> head_pair = (*header_ptr_)[head_offset];
        ArrayBlock<KeyType>* block_ptr = reinterpret_cast<ArrayBlock<KeyType>*>(head_pair.second());
        return head_offset * ArrayBlock<KeyType>::CONTENT_NUM()  + block_ptr->Find(key);
    }
    return -1;
}

template<typename KeyType>
KeyType& BinarySearchArray<KeyType>::operator[](block_offset_t n){
    pair<KeyType,void*> head_pair = (*header_ptr_)[n / ArrayBlock<KeyType>::CONTENT_NUM()];
    if(head_pair.second()){
        ArrayBlock<KeyType>* block_ptr = reinterpret_cast<ArrayBlock<KeyType>*>(head_pair.second());
        return block_ptr[n % ArrayBlock<KeyType>::CONTENT_NUM()];
    }
    return pair<KeyType,void*>(NULL,nullptr);
}

template<typename KeyType>
bool BinarySearchArray<KeyType>::Persist(){

}

}