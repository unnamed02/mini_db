#include "page/page.h"
#include "iostream"
namespace mini_db{

    bool Page::Append(duration_t duration,char* const slice){
        size_t length = strlen(slice);
        if(content_offset_ + length >= catalogue_offset_ - SLOT_SIZE){
            return false;
        }
        else{
            memmove(content_ + content_offset_,slice,length);

            catalogue_offset_ -= SLOT_SIZE;
            auto duration_ptr = reinterpret_cast<duration_t*>(content_ + catalogue_offset_);
            *duration_ptr = duration_;
            
            auto offset_ptr = reinterpret_cast<int16_t*>(content_ + catalogue_offset_ + 4);
            *offset_ptr = content_offset_;

            content_offset_ += length;
            duration_ += duration;
            return true;
        }
    }

    bool Page::Find(const duration_t duration,int16_t * const start,int16_t * const length){
        if(catalogue_offset_ == MAX_CONTENT_SIZE){
            return false;
        }
        int16_t min = 1;
        int16_t max = (MAX_CONTENT_SIZE - catalogue_offset_)/SLOT_SIZE;
        while(max > min){
            int16_t mid = (min + max + 1)>>1;
            auto duration_ptr = reinterpret_cast<duration_t*>(content_ + MAX_CONTENT_SIZE - (mid * SLOT_SIZE));
            if(*duration_ptr <= duration){
                min = mid;
            }else{
                max = mid - 1;
            }
        }
        int16_t offset = MAX_CONTENT_SIZE-(min*SLOT_SIZE);
        auto offset_ptr = reinterpret_cast<int16_t*>(content_ + offset + 4);
        *start = *offset_ptr;
        offset_ptr -= 3;
        LOG_DEBUG("offset:%d calalogue_offset_%d",offset,catalogue_offset_);
        if(offset  == catalogue_offset_){
            *length = content_offset_ - (*start);
        }else{
            *length = (*offset_ptr)-(*start);
        }
        return true;
    }
}