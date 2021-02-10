#pragma once

#include <string>
#include <assert.h>
#include "disk/disk_manager.h"
#include "index/page.h"

namespace mini_db{

class Index{
    public:

    Index(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size);

    virtual ~Index();

    page_id_t AllocNewPage();

    virtual page_id_t GetPage(duration_t duration) = 0;

    virtual bool WriteSlice(duration_t duration,char* content) = 0;

    size_t GetSliceLength(duration_t duration);

    int32_t GetSlice(duration_t duration,char** dst);   


    protected:

    DiskManager* disk_manager_ptr_; 

    //max number of pages
    uint32_t max_pages_;

    //current number of pages,since disk_manager's page id keep growing
    //we record the max number of current used page
    page_id_t cur_pages_;
    
    //mp4 time scale
    time_scale_t scale_;

    duration_t cur_duration_;

    Page* buffer_;
    
    private:
    //index shouldn't be copy able
    Index(const Index&);
    Index& operator=(const Index&);
};

}