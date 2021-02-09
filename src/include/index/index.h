#pragma once

#include <string>
#include "disk/disk_manager.h"

namespace mini_db{

class Index{
    public:

    Index(DiskManager* disk_manager);

    virtual ~Index();

    page_id_t AllocNewPage();

    virtual page_id_t GetPage(duration_t duration) = 0;

    virtual bool WritePage(Page page) = 0;
    
    protected:

    DiskManager* disk_manager_ptr; 

    //max number of pages
    uint32_t max_pages;

    //current number of pages,since disk_manager's page id keep growing
    //we record the max number of current used page
    page_id_t cur_pages;

    
    
};

}