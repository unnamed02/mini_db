#include "page/page.h"
#include "iostream"
namespace mini_db{
    bool Page::Append(duration_t duration,char* slice){
        size_t length = strlen(slice);
        if(content_offset_ + length >= catalogue_offset_ - 6){
            return false;
        }
        else{
            memmove(content_+content_offset_,slice,length);

            catalogue_offset_ -= 6;
            auto duration_ptr = reinterpret_cast<duration_t*>(content_+catalogue_offset_);
            *duration_ptr = duration_;
            
            auto offset_ptr = reinterpret_cast<int16_t*>(content_+catalogue_offset_+4);
            *offset_ptr = content_offset_;

            content_offset_ += length;
            duration_ += duration;
            return true;
        }
    }

    bool Page::Find(const duration_t duration,int16_t * const start,int16_t * const end){\
        if(content_offset_ == MAX_CONTENT_SIZE){
            return false;
        }
        int16_t min = 1;
        int16_t max = (MAX_CONTENT_SIZE - catalogue_offset_)/6;
        while(max > min){
            int16_t mid = (min + max + 1)>>1;
            auto duration_ptr = reinterpret_cast<duration_t*>(content_ + MAX_CONTENT_SIZE - (mid * 6));
            if(*duration_ptr <= duration){
                min = mid;
            }else{
                max = mid - 1;
            }
        }
        int16_t offset = MAX_CONTENT_SIZE-(min*6);
        auto offset_ptr = reinterpret_cast<int16_t*>(content_ + offset + 4);
        *start = *offset_ptr;
        offset_ptr = reinterpret_cast<int16_t*>(content_ + offset - 2);
        *end = *offset_ptr;
        return true;
    }
}