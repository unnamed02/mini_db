#include "index/index.h"
#include "index/content.h"
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

int32_t Index::GetSlice(duration_t duration,char** dst){
    //should find the page first 
    //and then you find the slice from that page via content.Find()
    if(duration > buffer_[0].start_){
        auto ctnt = reinterpret_cast<Content*>(buffer_[0].GetData());
        if(ctnt->Find(duration) > 0){
            memmove(*dst,ctnt->content_+ctnt->Find(duration),strlen(*dst));
            return true;
        }
        return false;
    }
    
}

Index::~Index(){
    delete []buffer_;
}

}
