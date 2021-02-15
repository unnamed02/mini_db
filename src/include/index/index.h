#pragma once

#include <string>
#include <assert.h>
#include "disk/disk_manager.h"
#include "page/frame.h"
#include "common/config.h"

namespace mini_db{

class Index{
    public:

    Index(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size);

    virtual ~Index();

    page_id_t AllocNewPage();

    virtual page_id_t GetPage(duration_t duration) = 0;

    virtual page_id_t WriteSlice(duration_t duration,char* content);

    size_t GetSliceLength(duration_t duration);

    int32_t GetSlice(duration_t duration,char* dst);
    
    farme_id_t GetFrame(duration_t duration);


    protected:

    DiskManager* disk_manager_ptr_; 

    //max number of pages
    uint32_t max_pages_;

    //current number of pages,since disk_manager's page id keep growing
    //the largest page is the curent page
    page_id_t cur_page_;
    
    //mp4 time scale
    time_scale_t scale_;

    duration_t cur_duration_;

    uint32_t buffer_size_;

    Frame* buffer_;
    
    private:
    //index shouldn't be copy able
    Index(const Index&);
    Index& operator=(const Index&);
};

}