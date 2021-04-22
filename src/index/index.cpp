#include "index/index.h"
#include "page/page.h"

namespace mini_dbm{


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
    try{
        buffer_ = new Frame[buffer_size_];
    }catch(bad_alloc){
        LOG_ERROR("out of memmory");
        abort(); 
    }
    AllocNewPage();
}

Index::Index(DiskManager* disk_manager_ptr,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size,bool is_leaf,bool is_root):
    disk_manager_ptr_(disk_manager_ptr),
    scale_(scale),
    max_pages_(max_pages),
    cur_page_id_(0),
    cur_duration_(0),
    buffer_size_(buffer_size){
    if(buffer_size_ == 0){
        buffer_size_ = 1;
    }
    try{
        buffer_ = new Frame[buffer_size_];
    }catch(bad_alloc){
        LOG_ERROR("out of memmory");
        abort(); 
    }
    AllocNewPage(is_leaf,is_root);
}

page_id_t Index::AllocNewPage(){
    Alloc();

    auto pg_ptr = reinterpret_cast<Page*>(buffer_[0].GetData());
    pg_ptr->Init(cur_page_id_,cur_duration_);
    return cur_page_id_;
}

page_id_t Index::AllocNewPage(bool is_leaf,bool is_root){
    Alloc();

    auto pg_ptr = reinterpret_cast<Page*>(buffer_[0].GetData());
    pg_ptr->Init(cur_page_id_,cur_duration_,is_leaf,is_root);
    return cur_page_id_;
}

void Index::Alloc(){
    auto res = disk_manager_ptr_ -> AllocatePage();
    if(cur_page_id_ > max_pages_){
        LOG_ERROR("bad alloc: cur_page_id_ > max_pages");
        return;
    }
    buffer_[0].Init(cur_page_id_,cur_duration_,0);
    cur_page_id_ = res;
}


//should find in the buffer_[0],the last page
//and then find in the rest of buffer
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
        frame_id_t frame_id = GetFrame(duration);
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
        
        page_id_t page_id = GetPage(duration);
        if(page_id == INVALID_PAGE_ID){
            return nullptr;
        }
        frame_id_t free_frame = GetFree();
        disk_manager_ptr_->ReadPage(page_id,buffer_[free_frame].GetData());
        auto pg = reinterpret_cast<Page*>(buffer_[free_frame].GetData());

        buffer_[free_frame].Init(pg->GetPageId(),pg->GetStart(),pg->GetDuration());
        
        if(pg->Find(duration,&start,&length)){
            char *dst = (char*)malloc(length);
            memmove(dst,pg->content_ + start,length);
            return dst;
        }
        LOG_ERROR("shoud't get here,checkout GetPage");
        abort();
    }else{
        page_id_t page_id = GetPage(duration);
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
        LOG_DEBUG("changing page writing page : %d to disk",cur_page->GetPageId());
        disk_manager_ptr_->WritePage(cur_page->GetPageId(),buffer_[0].GetData());
        
        cur_page->Clear();
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
    
    auto cur_page = reinterpret_cast<Page*>(buffer_[0].GetData());
    disk_manager_ptr_->WritePage(cur_page->GetPageId(),buffer_[0].GetData());

    delete []buffer_;
}

}
