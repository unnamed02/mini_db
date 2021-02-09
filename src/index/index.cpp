#include "index/index.h"

namespace mini_db{

Index::Index(DiskManager* disk_manager_ptr,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
    disk_manager_ptr_(disk_manager_ptr),
    scale_(scale),
    max_pages_(max_pages),
    cur_pages_(0),
    cur_duration_(0){
        buffer_ = new Page[buffer_size];    
}

page_id_t Index::AllocNewPage(){
    this->cur_pages_ = this->disk_manager_ptr_ -> AllocatePage();
    assert(cur_pages_ < max_pages_);
    return cur_pages_;
}

Index::~Index(){
    delete []buffer_;
}

}
