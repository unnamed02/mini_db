#include "index/binary_index.h"
#include "page/page.h"
namespace mini_db{

page_id_t BinaryIndex::WriteSlice(duration_t duration,char* content){
    // use Index::WriteSlice(duration,content) to do the real job
    // you can keep a record of cur_page_id and once its return value does not equal to that
    // you update your datastruct
    
}

page_id_t BinaryIndex::GetPage(duration_t duration){
    //an example of how you could get a page

    // Frame frame;
    // disk_manager_ptr_->ReadPage(1,frame.GetData());
    // auto page = reinterpret_cast<Page*>(frame.GetData());
    // frame.Init(page->GetPageId(),page->GetStart(),page->GetDuration());


}

BinaryIndex::BinaryIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
Index(disk_manager,scale,max_pages,buffer_size){
    
}

BinaryIndex::~BinaryIndex(){

}

}