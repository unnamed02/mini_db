#pragma once

#include "common/config.h"
#include "disk/disk_manager.h"
#include "page/array_block.h"

namespace mini_dbm{

template<typename KeyType,typename ValueType>
class ArrayHeader{

protected:
    size_t size_;

    DiskManager* disk_manager_ptr_;

public:

    ArrayHeader(DiskManager* disk_manager_ptr){
        disk_manager_ptr_ = disk_manager_ptr;
        size_ = 0;
    }

    virtual pair<KeyType,ValueType>& operator[](size_t i){};

    virtual size_t Find(const KeyType& key) = 0;

    virtual bool PushBack(KeyType key,ValueType value){};

    virtual bool Persist(){};

    virtual size_t Size(){
        return size_;
    };
    
};
}
