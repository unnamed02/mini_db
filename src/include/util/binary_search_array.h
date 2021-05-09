#pragma once

#include <stddef.h>
#include "common/config.h"
#include "common/logger.h"
#include "util/array_header.h"
#include "page/array_block.h"
#include "disk/disk_manager.h"

namespace mini_dbm{

template<typename KeyType>
class BinarySearchArray{
    private:
    ArrayHeader<KeyType,ArrayBlock<KeyType>*>* header_ptr_;

    ArrayBlock<KeyType>* cur_block_ptr_;

    DiskManager* disk_manager_ptr_;

    int32_t size_;

    public:
    BinarySearchArray(ArrayHeader<KeyType,ArrayBlock<KeyType>*>* header_ptr,DiskManager* disk_manager_ptr){
        header_ptr_ = header_ptr;
        disk_manager_ptr_ = disk_manager_ptr;

        auto new_block_ptr = new ArrayBlock<KeyType>();
        header_ptr->PushBack(0,new_block_ptr);
        cur_block_ptr_ = new_block_ptr;
    }

    size_t Find(KeyType key);

    KeyType& operator[](size_t offset);

    bool PushBack(KeyType start);

    void Persist();

    //TODO:BinarySearchArray should be copible，we will implement this later
    BinarySearchArray(const BinarySearchArray&) = delete;
    BinarySearchArray& operator=(const BinarySearchArray&) = delete;

};


template<typename KeyType>  
bool BinarySearchArray<KeyType>::PushBack(KeyType start){
    if(!cur_block_ptr_){
        LOG_ERROR("empty cur_block_ptr");
    }
    
    if(cur_block_ptr_->PushBack(start)){
        return true;
    }
    
    auto new_block_ptr = new ArrayBlock<KeyType>();

    if(new_block_ptr){
        header_ptr_->PushBack(start,new_block_ptr);
        cur_block_ptr_ = new_block_ptr;
        cur_block_ptr_->PushBack(start);
        return true;
    }
    return false;
}

template<typename KeyType>
size_t BinarySearchArray<KeyType>::Find(KeyType key){
    size_t head_offset = header_ptr_->Find(key);
    if(head_offset >= 0){
        pair<KeyType,void*> head_pair = (*header_ptr_)[head_offset];
        ArrayBlock<KeyType>* block_ptr = reinterpret_cast<ArrayBlock<KeyType>*>(head_pair.second());
        return head_offset * ArrayBlock<KeyType>::CONTENT_NUM()  + block_ptr->Find(key);
    }
    return -1;
}

template<typename KeyType>
KeyType& BinarySearchArray<KeyType>::operator[](size_t n){
    pair<KeyType,void*> head_pair = (*header_ptr_)[n / ArrayBlock<KeyType>::CONTENT_NUM()];
    if(head_pair.second()){
        ArrayBlock<KeyType>* block_ptr = reinterpret_cast<ArrayBlock<KeyType>*>(head_pair.second());
        return block_ptr[n % ArrayBlock<KeyType>::CONTENT_NUM()];
    }
    return pair<KeyType,void*>(NULL,nullptr);
}

template<typename KeyType>
void BinarySearchArray<KeyType>::Persist(){
    for(int i = 0;i<header_ptr_->Size();i++){
        auto char_ptr = reinterpret_cast<char*>((*header_ptr_)[i].second());
        this->disk_manager_ptr_->WritePage(i,char_ptr);
    }
}

}