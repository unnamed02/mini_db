#include "page/page.h"
#include "iostream"
namespace mini_db{

    bool Page::Append(const duration_t duration,char* const slice){
        size_t length = strlen(slice);
        // LOG_DEBUG("content + length : %d catalogue_offset - SLOT_SIZE : %d",(int)(content_offset_ + length),(int)(catalogue_offset_ - SLOT_SIZE));
        if(content_offset_ + length > catalogue_offset_ - SLOT_SIZE){
            return false;
        }
        else{
            memmove(content_ + content_offset_,slice,length);

            catalogue_offset_ -= SLOT_SIZE;
            auto duration_ptr = reinterpret_cast<duration_t*>(content_ + catalogue_offset_);
            *duration_ptr = duration_;
            
            auto offset_ptr = reinterpret_cast<page_offset_t*>(content_ + catalogue_offset_ + DURATION_SIZE);
            *offset_ptr = content_offset_;

            content_offset_ += length;
            duration_ += duration;
            return true;
        }
    }

    bool Page::Find(const duration_t duration,page_offset_t * const start,page_offset_t * const length){
        // LOG_DEBUG("MAX_CONTENT_SIZE : %d catalogue_offset : %d",MAX_CONTENT_SIZE,this->catalogue_offset_);
        if(catalogue_offset_ == MAX_CONTENT_SIZE){
            return false;
        }
        page_offset_t min = 1;
        page_offset_t max = (MAX_CONTENT_SIZE - catalogue_offset_)/SLOT_SIZE;
        while(max > min){
            page_offset_t mid = (min + max + 1)>>1;
            auto duration_ptr = reinterpret_cast<duration_t*>(content_ + MAX_CONTENT_SIZE - (mid * SLOT_SIZE));
            if(*duration_ptr <= duration){
                min = mid;
            }else{
                max = mid - 1;
            }
        }
        page_offset_t offset = MAX_CONTENT_SIZE-(min*SLOT_SIZE);
    
        auto offset_ptr = reinterpret_cast<page_offset_t*>(content_ + offset + DURATION_SIZE);
        *start = *offset_ptr;
        offset_ptr -= SLOT_SIZE/PAGE_OFFSET_SIZE;
        // LOG_DEBUG("offset:%d calalogue_offset_%d",offset,catalogue_offset_);
        if(offset  == catalogue_offset_){
            if(duration_ <= duration){
                return false;
            }
            *length = content_offset_ - (*start);
        }else{
            auto duration_ptr = reinterpret_cast<page_offset_t*>(content_ + offset - SLOT_SIZE);
            if(*duration_ptr <= duration){
                return false;
            }
            *length = (*offset_ptr)-(*start);
        }
        return true;
    }
}