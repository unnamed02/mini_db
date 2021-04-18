#include "index/index.h"
#include <vector>

namespace mini_db{
    
    class LinearIndex : public Index{
        
        public:
        LinearIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size);

        ~LinearIndex();
        
        page_id_t WriteSlice(const duration_t,char * const content);

        page_id_t GetPage(const duration_t);
        
        private:
        std::vector<duration_t> end_time_list_for_pages_;

        duration_t average_duration_;

        duration_t CalcAverageDuration_(std::vector<duration_t> &end_time_list_for_pages_);


    };
}