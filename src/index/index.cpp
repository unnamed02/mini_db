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
    if(buffer_size_ == 0){
        buffer_size_ = 1;
    }
    buffer_ = new Frame[buffer_size_];
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
    if(duration >= buffer_[0].GetStart()){
        auto pg = reinterpret_cast<Page*>(buffer_[0].GetData());
        if(pg->Find(duration,&start,&length)){
            // LOG_DEBUG("start : %d length : %d",start,length);
            char *dst = (char*)malloc(length);
            memmove(dst,pg->content_ + start,length);
            return dst;
        }
        return nullptr;
    }else if (buffer_size_ > 1){
        frame_id_t frame_id = this->GetFrame(duration);
        if(frame_id != INVALID_FRAME_ID){
            auto pg = reinterpret_cast<Page*>(buffer_[frame_id].GetData());
            if(pg->Find(duration,&start,&length)){
                char *dst = (char*)malloc(length);
                memmove(dst,pg->content_ + start,length);
                return dst; 
            }
            LOG_ERROR("shouldn't get here, checkout GetFrame");
            abort();
        }
        
        page_id_t page_id = this->GetPage(duration);
        if(page_id == INVALID_PAGE_ID){
            return nullptr;
        }
        frame_id_t free_frame = this->GetFree();
        disk_manager_ptr_->ReadPage(page_id,buffer_[free_frame].GetData());
        auto pg = reinterpret_cast<Page*>(buffer_[free_frame].GetData());
        if(pg->Find(duration,&start,&length)){
            char *dst = (char*)malloc(length);
            memmove(dst,pg->content_ + start,length);
            return dst;
        }
        LOG_ERROR("shoud't get here,checkout GetPage");
        abort();
    }else{
        page_id_t page_id = this->GetPage(duration);
        if(page_id == INVALID_PAGE_ID){
            return nullptr;
        }
        char temp_buffer[PAGE_SIZE];
        disk_manager_ptr_->ReadPage(page_id,temp_buffer);
        auto pg = reinterpret_cast<Page*>(temp_buffer);
        if(pg->Find(duration,&start,&length)){
            char *dst = (char*)malloc(length);
            memmove(dst,pg->content_ + start,length);
            return dst;
        }
        LOG_ERROR("shoud't get here,checkout GetPage");
        abort();
    }
    return nullptr;
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
frame_id_t Index::GetFrame(const duration_t duration){
    for(int i = 1;i<buffer_size_;i++){
        
    }
}


frame_id_t Index::GetFree(){

}

Index::~Index(){
    delete []buffer_;
}

}
