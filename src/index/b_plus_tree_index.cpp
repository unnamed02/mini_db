#include "index/b_plus_tree_index.h"
#include "page/page.h"
namespace mini_dbm{

page_id_t BPlusTreeIndex::WriteSlice(const duration_t duration,char* const content){
    
    //B+ tree should behave like this,we can skip that since we can assume target_frame is always buffer[0]

    // page_id_t target_page_id = GetPage(duration);
    // Frame target_frame;
    // disk_manager_ptr_->ReadPage(target_page_id,target_frame.GetData());
    
    auto cur_page = reinterpret_cast<Page*>(buffer_[0].GetData());
    if(cur_page->Append(duration,content)){
        cur_duration_ += duration;
        return cur_page->GetPageId();
    }
    Frame temp_frame = buffer_[0];

    cur_page->Clear();
    page_id_t new_page_id = AllocNewPage(true,false);
    auto old_page = reinterpret_cast<Page*>(buffer_[0].GetData());
    auto cur_page = reinterpret_cast<Page*>(buffer_[0].GetData());
    cur_page->Init(new_page_id,0,0,old_page->GetParentPageId(),true,false);
    old_page->MoveHalfTo(cur_page);
    disk_manager_ptr_->WritePage(old_page->GetPageId(),temp_frame.GetData());

    t

    return cur_page_id;
}

page_id_t BPlusTreeIndex::GetPage(const duration_t duration){

}


BPlusTreeIndex::BPlusTreeIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
Index(disk_manager,scale,max_pages,buffer_size,false,true){
    root_page_id_ = cur_page_id_;
    page_id_t leaf_page_id = AllocNewPage(true,false);

    Frame temp_frame;
    disk_manager_ptr_->ReadPage(root_page_id_,temp_frame.GetData());
    auto root_page_ptr = reinterpret_cast<Page*>(temp_frame.GetData());
    root_page_ptr->Append(0,leaf_page_id);
    disk_manager_ptr_->WritePage(root_page_id_,temp_frame.GetData());

}

BPlusTreeIndex::~BPlusTreeIndex(){

}

}