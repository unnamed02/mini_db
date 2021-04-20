#pragma once

#include "common/config.h"
#include "common/logger.h"
#include <cstring>
namespace mini_db{

static inline int32_t CONTENT_HEADER_SIZE(){
    int size = 0;
    size += 2 * DURATION_SIZE;

    if(size % PAGE_ID_SIZE == 0){
        size += PAGE_ID_SIZE * 2;
    }else{
        size = ((size/PAGE_ID_SIZE)+3)*PAGE_ID_SIZE;
    }

    if(size % PAGE_OFFSET_SIZE == 0){
        size += PAGE_OFFSET_SIZE * 2;
    }else{
        size = ((size/PAGE_OFFSET_SIZE)+3)*PAGE_OFFSET_SIZE;
    }

    size += 1;

    return size;
}

static const int32_t MAX_CONTENT_SIZE = PAGE_SIZE - CONTENT_HEADER_SIZE();

class Page{

    friend class Index;
    
    public:

    inline duration_t GetStart(){return start_;}

    inline duration_t GetDuration(){return duration_;}
    
    inline page_id_t GetPageId(){return page_id_;}

    inline bool IsLeafPage(){
        return perm_ & LEAF_PAGE;
    }

    //FOR TEST ONLY
    inline char* GetContent(){return content_;}

    inline void Init(const page_id_t page_id,const duration_t start,bool is_leaf,bool is_root){
        Init(page_id,start);
        if(is_leaf){
            perm_ |= LEAF_PAGE;
        }else{
            perm_ &= !LEAF_PAGE;
        }
        
        if(is_root){
            perm_ |= ROOT_PAGE;
        }else{
            perm_ &= !ROOT_PAGE;
        }
    };

    inline void Init(const page_id_t page_id,const duration_t start){
        start_ = start,
        page_id_ = page_id,
        duration_ = 0,
        content_offset_ = 0,
        catalogue_offset_ = MAX_CONTENT_SIZE;
    };

    inline void Clear(){
        memset(content_,0,PAGE_SIZE);
    }

    virtual ~Page();

    inline int32_t GetOffset(){return content_offset_;}
    
    inline int32_t GetCatalogueOffset(){return catalogue_offset_;}

    
    bool Append(const duration_t,char* const slice);

    bool Append(const duration_t,const page_id_t page_id);
    
    bool Find(const duration_t,page_offset_t * const start,page_offset_t * const length);

    bool Find(const duration_t,page_id_t* const page_id);
    
    private:        
    
    duration_t     start_;
    duration_t     duration_;

    page_id_t      page_id_;
    page_id_t      parent_page_id_;
        
    page_offset_t       content_offset_;
    page_offset_t       catalogue_offset_;
    
    char           perm_;

    char           content_[0]{};
    };
}
