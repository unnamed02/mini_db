#include "index/index.h"
#include "page/page.h"
namespace mini_db{

Index::Index(DiskManager* disk_manager_ptr,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
    disk_manager_ptr_(disk_manager_ptr),
    scale_(scale),
    max_pages_(max_pages),
    cur_page_id_(0),
    cur_duration_(0),
    buffer_size_(buffer_size){
    buffer_ = new Frame[buffer_size];
    AllocNewPage();
    auto pg = reinterpret_cast<Page*>(buffer_[0].GetData());
    pg->Init(0,cur_page_id_);
}

page_id_t Index::AllocNewPage(){
    this->cur_page_id_ = this->disk_manager_ptr_ -> AllocatePage();
    if(cur_page_id_ > max_pages_){
        return INVALID_PAGE_ID;
    }
    buffer_[0].Init(cur_page_id_,cur_duration_,0);
    return cur_page_id_;
}

//should find in the buffer_[0],the last page
//and then find in the rest buffer
char* Index::GetSlice(duration_t duration){
    int16_t start,length;
    if(duration > buffer_[0].GetStart()){
        auto pg = reinterpret_cast<Page*>(buffer_[0].GetData());
        if(pg->Find(duration,&start,&length)){
            char *dst = (char*)malloc(length);
            memmove(dst,pg->content_ + start,length);
            return dst;
        }
        LOG_DEBUG("hello");
        return nullptr;
    }else{
        int32_t frame_id = this->GetFrame(duration);
        if(frame_id != INVALID_FRAME_ID){
            auto pg = reinterpret_cast<Page*>(buffer_[frame_id].GetData());
            if(pg->Find(duration,&start,&length)){
                char *dst = (char*)malloc(length);
                memmove(dst,pg->content_ + start,length);
                return dst; 
            }
        }
        
        page_id_t page_id = this->GetPage(duration);
        if(page_id == INVALID_PAGE_ID){
            return nullptr;
        }else{
            
        }

    }
    
}



page_id_t Index::WriteSlice(const duration_t duration,char* slice){
    auto cur_page = reinterpret_cast<Page*>(buffer_[0].GetData());
    if(cur_page->Append(duration,slice)){
        cur_duration_ += duration;
        return cur_page->GetPageId();
    }else{
        disk_manager_ptr_->WritePage(cur_page->GetPageId(),buffer_[0].GetData());
        AllocNewPage();
        auto cur_page = reinterpret_cast<Page*>(buffer_[0].GetData());
        if(!cur_page->Append(duration,slice)){
            LOG_ERROR("slice is bigger than PAGE_SIZE");
            return INVALID_PAGE_ID;
        }
        cur_duration_ += duration;
        return cur_page->GetPageId();
    }
}

// TODO: use STL datastruct to record this
farme_id_t Index::GetFrame(const duration_t duration){
    for(int i = 1;i<buffer_size_;i++){
        
    }
}

Index::~Index(){
    delete []buffer_;
}

}
