#include "common/config.h"
namespace mini_db{

static const int32_t CONTENT_HEADER_SIZE = 16;
static const int32_t MAX_CONTENT_SIZE = PAGE_SIZE - CONTENT_HEADER_SIZE;

class Page{

    friend class Index;
    
    public:

    inline duration_t GetStart(){return start_;}

    inline duration_t GetDuration(){return duration_;}
    
    inline page_id_t GetPageId(){return page_id_;}

    inline int32_t GetOffset(){return content_offset_;}
    
    inline int32_t GetCatalogue(){return catalogue_;}
    
    bool Append(duration_t duration,char* slice);
    
    int16_t Find(duration_t duration);
    
    private:        
    
    duration_t     start_;
    duration_t     duration_;

    page_id_t      page_id_;
        
    int16_t       content_offset_;
    int16_t       catalogue_;
        
    char           content_[0];    
    };
}
