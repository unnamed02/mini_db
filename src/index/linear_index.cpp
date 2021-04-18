#include "index/linear_index.h"
#include "page/page.h"

namespace mini_db{

page_id_t LinearIndex::WriteSlice(const duration_t duration,char* const content){
    
    // record the current page_id and duration
    page_id_t before_page_id = cur_page_id_;
    duration_t before_duration = cur_duration_;
    
    page_id_t update_page_id = Index::WriteSlice(duration,content);
    if(update_page_id != INVALID_PAGE_ID){
        if(update_page_id != before_page_id){
            end_time_list_for_pages_.push_back(before_duration);
            average_duration_ = (average_duration_ * (end_time_list_for_pages_.size() -1) + before_duration) / end_time_list_for_pages_.size();
        }
    }
    return update_page_id;
}

page_id_t LinearIndex::GetPage(const duration_t duration_stamp){

    page_id_t page_to_read = duration_stamp / average_duration_; 
    char temp_buffer[PAGE_SIZE];
    this->disk_manager_ptr_->ReadPage(page_to_read,temp_buffer);
    auto pg_ptr = reinterpret_cast<Page*>(temp_buffer);

    // down-search
    while (pg_ptr->GetStart() > duration_stamp && page_to_read>0)
    {
        page_to_read--;
        this->disk_manager_ptr_->ReadPage(page_to_read,temp_buffer);
        pg_ptr = reinterpret_cast<Page*>(temp_buffer);
    }
    // up-search
    while (pg_ptr->GetStart() + pg_ptr->GetDuration() < duration_stamp && page_to_read < end_time_list_for_pages_.size()-1)
    {
        page_to_read++;
        this->disk_manager_ptr_->ReadPage(page_to_read,temp_buffer);
        pg_ptr = reinterpret_cast<Page*>(temp_buffer);
    }
    return page_to_read;
}

duration_t LinearIndex::CalcAverageDuration_(std::vector<duration_t> &end_time_list_for_pages_){
    
    duration_t sum=0;
    for(auto i=end_time_list_for_pages_.begin(); i!=end_time_list_for_pages_.end(); i++){
        sum += *i;
    }
    return sum / end_time_list_for_pages_.size();
}


LinearIndex::LinearIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
    Index(disk_manager,scale,max_pages,buffer_size),
    end_time_list_for_pages_(0),
    average_duration_(0){
    
}

LinearIndex::~LinearIndex(){

}

}