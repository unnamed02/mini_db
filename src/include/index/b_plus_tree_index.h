#pragma once

#include "index/index.h"

namespace mini_db{

class BPlusTreeIndex : public Index{
        
    public:
    BPlusTreeIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size);

    ~BPlusTreeIndex();
        
    page_id_t WriteSlice(const duration_t,char * const content);

    page_id_t GetPage(const duration_t);

    private:

};

}