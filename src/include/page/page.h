#include "common/config.h"
#include "common/logger.h"
#include <cstring>
namespace mini_db{

static const int32_t CONTENT_HEADER_SIZE = 16;
static const int32_t MAX_CONTENT_SIZE = PAGE_SIZE - CONTENT_HEADER_SIZE;
static const int32_t SLOT_SIZE = DURATION_SIZE + PAGE_OFFSET_SIZE;

class Page{

    friend class Index;
    
    public:

    inline duration_t GetStart(){return start_;}

    inline duration_t GetDuration(){return duration_;}
    
    inline page_id_t GetPageId(){return page_id_;}

    inline void Init(const duration_t start,const page_id_t page_id){
        start_ = start,
        page_id_ = page_id,
        duration_ = 0,
        content_offset_ = 0,
        catalogue_offset_ = MAX_CONTENT_SIZE;
    };

    virtual ~Page();

    inline int32_t GetOffset(){return content_offset_;}
    
    inline int32_t GetCatalogueOffset(){return catalogue_offset_;}

    
    bool Append(const duration_t duration,char* const slice);
    
    bool Find(const duration_t duration,page_offset_t * const start,page_offset_t * const length);
    
    private:        
    
    duration_t     start_;
    duration_t     duration_;

    page_id_t      page_id_;
        
    page_offset_t       content_offset_;
    page_offset_t       catalogue_offset_;
        
    char           content_[0];    
    };
}
