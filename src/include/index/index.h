#pragma once

#include <string>
#include <assert.h>
#include "disk/disk_manager.h"
#include "page/frame.h"
#include "common/config.h"
#include "common/logger.h"
namespace mini_db{
class Index{
    public:

    Index(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size);

    virtual ~Index();

    page_id_t AllocNewPage();

    virtual page_id_t GetPage(const duration_t) = 0;
    
    virtual page_id_t WriteSlice(const duration_t,char* const content);

    size_t GetSliceLength(const duration_t);

    /* 
    since getSlice return a dynamic alloced char*,you should free that memory after use.
    that free function is as follow.
    the reason why we use GetSlice and FreeSlice instead of 
    using GetLength and GetSlice style api that allows you manage the memmory by yourself is that
    the page is stored in a lru buffer
    and if use that GetLength style api it will neither lead to swapout/swapin or holding
    that page for a long time which will definetedly make it way too slow 
    */
    char* GetSlice(const duration_t);

    //free function
    inline void FreeSlice(char* const content){
        free(content);
    }
    


    protected:


    DiskManager* disk_manager_ptr_; 

    //max number of pages
    uint32_t max_pages_;

    //current page id,since disk_manager's page id just increase one per alloc
    //the largest page id is the curent page id 
    page_id_t cur_page_id_;
    
    //mp4 time scale
    time_scale_t scale_;

    duration_t cur_duration_;

    uint32_t buffer_size_;

    Frame* buffer_;

    frame_id_t GetFrame(const duration_t);
    
    frame_id_t GetFree();
    
    private:
    

    //index shouldn't be copiable
    //and you are NOT allowed to use its default construct function
    Index(const Index&);

    Index& operator=(const Index&);
    
    Index();
};

}