#include "page/page.h"
#include "iostream"
namespace mini_dbm{

    bool Page::Append(const duration_t duration,char* const slice){
        size_t length = strlen(slice);
        // LOG_DEBUG("content + length : %d catalogue_offset - LEAF_SLOT_SIZE : %d",(int)(content_offset_ + length),(int)(catalogue_offset_ - LEAF_SLOT_SIZE));
        if(content_offset_ + length >= catalogue_offset_ - LEAF_SLOT_SIZE){
            return false;
        }
        else{
            memmove(content_ + content_offset_,slice,length);

            catalogue_offset_ -= LEAF_SLOT_SIZE;
            auto duration_ptr = reinterpret_cast<duration_t*>(content_ + catalogue_offset_);
            *duration_ptr = duration_;
            
            auto offset_ptr = reinterpret_cast<page_offset_t*>(content_ + catalogue_offset_ + DURATION_SIZE);
            *offset_ptr = content_offset_;

            content_offset_ += length;
            duration_ += duration;
            return true;
        }
    }

    bool Page::Append(const duration_t duration,const page_id_t page_id){
        if(content_offset_ + INTERNAL_SLOT_SIZE >= MAX_CONTENT_SIZE){
            return false;
        }
        auto duration_ptr = reinterpret_cast<duration_t*>(content_ + content_offset_);
        *duration_ptr = duration;
    
        auto page_ptr = reinterpret_cast<page_id_t*>(++duration_ptr);
        *page_ptr = page_id;

        content_offset_ += INTERNAL_SLOT_SIZE;
        return true;
    }

    bool Page::Find(const duration_t duration,page_offset_t * const start_offset,page_offset_t * const length){
        // LOG_DEBUG("MAX_CONTENT_SIZE : %d catalogue_offset : %d",MAX_CONTENT_SIZE,this->catalogue_offset_);
        if(catalogue_offset_ == MAX_CONTENT_SIZE || duration >= duration_ + start_ || duration < start_){
            return false;
        }
        page_offset_t min = 1;
        page_offset_t max = (MAX_CONTENT_SIZE - catalogue_offset_)/LEAF_SLOT_SIZE;
        while(max > min){
            page_offset_t mid = (min + max + 1)>>1;
            auto duration_ptr = reinterpret_cast<duration_t*>(content_ + MAX_CONTENT_SIZE - (mid * LEAF_SLOT_SIZE));
            if(*duration_ptr <= duration){
                min = mid;
            }else{
                max = mid - 1;
            }
        }
        page_offset_t offset = MAX_CONTENT_SIZE - (min * LEAF_SLOT_SIZE);
    
        auto offset_ptr = reinterpret_cast<page_offset_t*>(content_ + offset + DURATION_SIZE);
        *start_offset = *offset_ptr;
        offset_ptr -= LEAF_SLOT_SIZE/PAGE_OFFSET_SIZE;
        // LOG_DEBUG("offset:%d calalogue_offset_%d",offset,catalogue_offset_);
        if(offset  == catalogue_offset_){
            *length = content_offset_ - (*start_offset);
        }else{
            *length = (*offset_ptr) - (*start_offset);
        }
        return true;
    }

    bool Page::Find(const duration_t,page_id_t* const page_id){

    }

    //TODO: remember to reset this page's start duration
    void Page::MoveHalfTo(Page* const target_page){
        if(IsLeafPage()){
            page_offset_t min = 1;
            page_offset_t max = (MAX_CONTENT_SIZE - catalogue_offset_)/LEAF_SLOT_SIZE;
            page_offset_t mid = (min + max + 1)>>1;

            page_offset_t offset = MAX_CONTENT_SIZE - (mid * LEAF_SLOT_SIZE);

            memmove(target_page->content_ + MAX_CONTENT_SIZE - offset + catalogue_offset_,content_ + catalogue_offset_,offset - catalogue_offset_);

            auto offset_ptr = reinterpret_cast<page_offset_t*>(content_ + offset + DURATION_SIZE);
            start
        }
    }


}