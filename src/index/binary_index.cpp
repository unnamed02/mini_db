#include "index/binary_index.h"
#include "page/page.h"
namespace mini_dbm{

page_id_t BinaryIndex::WriteSlice(const duration_t duration,char* const content){
    // use Index::WriteSlice(duration,content) to do the real job
    // you can keep a record of cur_page_id and once its return value does not equal to that
    // you update your datastruct
    page_id_t before_page_id = cur_page_id_;
    duration_t before_duration = cur_duration_;
    
    page_id_t update_page_id = Index::WriteSlice(duration,content);
    if(update_page_id != INVALID_PAGE_ID){
        if(update_page_id != before_page_id){
            end_time_list_for_pages_.push_back(before_duration);
        }
    }
    return update_page_id;
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

    if(duration >= end_time_list_for_pages_.back() || duration < 0){
        // out of the content
        return INVALID_PAGE_ID;
    }else{
        //just return std::upper_bound(end_time_list_for_pages_.begin(),end_time_list_for_pages_.end(),duration)-end_time_list_for_pages_.begin() -1  is ok
        page_id_t low = 0, high = end_time_list_for_pages_.size()-1, mid;
	    while (low <= high)
	    {
		    mid = (low + high) / 2;
		    if (this->end_time_list_for_pages_[mid] > duration)
		    {
                if(mid > 0 && end_time_list_for_pages_[mid-1] > duration)
                {
                    high = mid - 1;
                }else{
                    return mid;
                }
		    }
			else{
                low = mid + 1;
            }
	    }
        return low;
    }
}


BinaryIndex::BinaryIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
    Index(disk_manager,scale,max_pages,buffer_size),
    end_time_list_for_pages_(8){
    
}

BinaryIndex::~BinaryIndex(){
}

}