#include <cstring>
#include "common/config.h"

namespace mini_db{

class Page{

    public:
    Page(){ResetMemory();}

    ~Page() = default;

    inline char* GetContent(){return content_;}
    
    private:
    inline void ResetMemory() { memset(content_,0, PAGE_SIZE); }

    page_id_t page_id;

    duration_t duration;
    
    //the actual page content
    char content_[PAGE_SIZE];
};

}