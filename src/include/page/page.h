#include "common/config.h"
#include <cstring>
namespace mini_db{

static const int32_t CONTENT_HEADER_SIZE = 16;
static const int32_t MAX_CONTENT_SIZE = PAGE_SIZE - CONTENT_HEADER_SIZE;

class Page{

    friend class Index;
    
    public:

    inline duration_t GetStart(){return start_;}

    inline duration_t GetDuration(){return duration_;}
    
    inline page_id_t GetPageId(){return page_id_;}

    inline void Init(duration_t start,page_id_t page_id){
        start_ = start,
        page_id_ = page_id,
        duration_ = 0,
        content_offset_ = 0,
        catalogue_offset_ = MAX_CONTENT_SIZE;
    };

    virtual ~Page();

    inline int32_t GetOffset(){return content_offset_;}
    
    inline int32_t GetCatalogueOffset(){return catalogue_offset_;}

    
    bool Append(duration_t duration,char* slice);
    
    bool Find(duration_t duration,int16_t * const start,int16_t * const end);
    
    private:        
    
    duration_t     start_;
    duration_t     duration_;

    page_id_t      page_id_;
        
    int16_t       content_offset_;
    int16_t       catalogue_offset_;
        
    char           content_[0];    
    };
}
