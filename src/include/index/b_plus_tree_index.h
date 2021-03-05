#include "index/index.h"

namespace mini_db{
    class B_PLUS_Binary_Index : public Index{
        
        public:
        B_PLUS_Binary_Index(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size);

        ~B_PLUS_Binary_Index();
        
        page_id_t WriteSlice(const duration_t,char * const content);

        page_id_t GetPage(const duration_t);

        private:

    };
}