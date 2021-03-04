#include "index/binary_index.h"
#include "page/page.h"
namespace mini_db{

page_id_t BinaryIndex::WriteSlice(const duration_t duration,char* const content){
    // use Index::WriteSlice(duration,content) to do the real job
    // you can keep a record of cur_page_id and once its return value does not equal to that
    // you update your datastruct
    this->cur_page_id_;
    
    Index::WriteSlice(duration,content);
}

page_id_t BinaryIndex::GetPage(const duration_t duration){
    //an example of how you could get a page
    //read page 1
    
    //make sure your finding algorithm is accurate
    //so that you NEEDN'T do disk IO

    // page_id_t page_to_read = 1; 
    // char temp_buffer[PAGE_SIZE];
    // this->disk_manager_ptr_->ReadPage(page_to_read,temp_buffer);
    // auto pg_ptr = reinterpret_cast<Page*>(temp_buffer);

    //and now you can use pg_ptr to get that page's data 

}


BinaryIndex::BinaryIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
Index(disk_manager,scale,max_pages,buffer_size){
    
}

BinaryIndex::~BinaryIndex(){

}

}