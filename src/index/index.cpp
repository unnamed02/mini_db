#include "index/index.h"
#include "page/page.h"
namespace mini_db{

Index::Index(DiskManager* disk_manager_ptr,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
    disk_manager_ptr_(disk_manager_ptr),
    scale_(scale),
    max_pages_(max_pages),
    cur_page_(0),
    cur_duration_(0),
    buffer_size_(buffer_size){
        buffer_ = new Frame[buffer_size];    
}

page_id_t Index::AllocNewPage(){
    this->cur_page_ = this->disk_manager_ptr_ -> AllocatePage();
    assert(cur_page_ < max_pages_);
    buffer_[0].Init(cur_page_,cur_duration_,0);
    return cur_page_;
}

//should find in the buffer_[0],the last page
//and then find in the rest buffer
int32_t Index::GetSlice(duration_t duration,char* dst){
    if(duration > buffer_[0].GetStart()){
        auto pg = reinterpret_cast<Page*>(buffer_[0].GetData());
        if(pg->Find(duration) > 0){
            memmove(dst,pg->content_ + pg->Find(duration),strlen(dst));
            return true;
        }
        return false;
    }else{
        int32_t frame_id = this->GetFrame(duration);
        if(frame_id != INVALID_FRAME_ID){
            auto pg = reinterpret_cast<Page*>(buffer_[frame_id].GetData());
            if(pg->Find(duration) > 0){
                memmove(dst,pg->content_ + pg->Find(duration),strlen(dst));
                return true; 
            }
        }
        
        page_id_t page_id = this->GetPage(duration);
        if(page_id == INVALID_PAGE_ID){
            return false;
        }else{
            
        }

    }
    
}

page_id_t Index::WriteSlice(duration_t duration,char* content){

}

// TODO: use stl datastruct to record this
farme_id_t Index::GetFrame(duration_t duration){
    for(int i = 1;i<buffer_size_;i++){
        
    }
}

Index::~Index(){
    delete []buffer_;
}

}
