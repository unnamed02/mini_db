#include "page/page.h"

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
}