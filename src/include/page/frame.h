#pragma once

#include "common/config.h"
#include <cstring>
namespace mini_db{

class Frame{

    public:
    Frame(){ResetMemory();}

    ~Frame() = default;

    inline char* GetData(){return data_;}

    inline duration_t GetDuration(){return duration_;}

    inline duration_t GetStart(){return start_;}

    inline void Init(page_id_t page_id,duration_t start,duration_t duration){
        page_id_ = page_id;
        start_ = start;
        duration_ = duration;
    }
    
    
    private:
    inline void ResetMemory() { memset(data_,0, PAGE_SIZE);}

    page_id_t page_id_;


    duration_t start_;

    duration_t duration_;
    
    //the actual page content
    char data_[PAGE_SIZE]{};
};

}