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
    auto old_page = reinterpret_cast<Page*>(temp_frame.GetData());
    // auto cur_page = reinterpret_cast<Page*>(buffer_[0].GetData()); 

    old_page->MoveHalfTo(cur_page);
    disk_manager_ptr_->WritePage(old_page->GetPageId(),temp_frame.GetData());
    cur_page->SetParentPageId(InsertIntoParent(old_page->GetParentPageId(),cur_page->GetStart(),new_page_id));

    return cur_page_id_;
}

page_id_t BPlusTreeIndex::InsertIntoParent(const page_id_t parent_page_id,const duration_t duration,const page_id_t child_page_id){
    Frame parent_frame;
    disk_manager_ptr_->ReadPage(parent_page_id,parent_frame->GetData());
    auto parent_page_ptr = reinterpret_cast<Page*>(parent_frame->GetData());

    if(parent_page_ptr->Append(duration,child_page_id)){
        return parent_page_ptr->GetPageId();
    }
    
    if(!parent_page_ptr->IsRootPage()){
        Frame new_frame;
        page_id_t new_page_id = AllocNewPage(false,false);
        auto new_page_ptr = reinterpret_cast<Page*>(new_frame->GetData());
        parent_page_ptr->MoveHalfTo(new_page_ptr);

        //TODO: could be buggy here,since InsertIntoParent may read this page again
        disk_manager_ptr_->WritePage(parent_page_id,parent_page_ptr->GetDat());
        new_page_ptr->SetParentPageId(InsertIntoParent(parent_page_id->GetParentPageId(),new_page_ptr->GetStart(),new_page_id));
        disk_manager_ptr_->WritePage(new_page_id,new_frame->GetData());
        return new_page_id;
    }else{
        
    }

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