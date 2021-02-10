#include <cstring>
#include "common/config.h"

namespace mini_db{

class Page{
    friend class Index;
    public:
    Page(){ResetMemory();}

    ~Page() = default;

    inline char* GetData(){return data_;}

    inline duration_t GetDuration(){return duration_;}

    inline duration_t GetStartTime(){return start_;}
    
    private:
    inline void ResetMemory() { memset(data_,0, PAGE_SIZE);}

    page_id_t page_id_;


    duration_t start_;

    duration_t duration_;
    
    //the actual page content
    char data_[PAGE_SIZE]{};
};

}