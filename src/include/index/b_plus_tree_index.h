#pragma once

#include "index/index.h"

namespace mini_dbm{

class BPlusTreeIndex : public Index{
        
    public:
    BPlusTreeIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size);

    ~BPlusTreeIndex();
        
    page_id_t WriteSlice(const duration_t,char * const content);

    page_id_t GetPage(const duration_t);

    page_id_t InsertIntoParent(const page_id_t parent_page_id,const duration_t,const page_id_t child_page_id);

    private:
    page_id_t root_page_id_;

};

}