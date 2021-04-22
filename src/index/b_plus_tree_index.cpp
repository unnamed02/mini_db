#include "index/b_plus_tree_index.h"
#include "page/page.h"
namespace mini_dbm{

page_id_t BPlusTreeIndex::WriteSlice(const duration_t duration,char* const content){
    
}

page_id_t BPlusTreeIndex::GetPage(const duration_t duration){

}


BPlusTreeIndex::BPlusTreeIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
Index(disk_manager,scale,max_pages,buffer_size,true,true){
    
}

BPlusTreeIndex::~BPlusTreeIndex(){

}

}