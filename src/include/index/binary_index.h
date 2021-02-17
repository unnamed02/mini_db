#include "index/index.h"

namespace mini_db{
    class BinaryIndex : public Index{
        
        public:
        BinaryIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size);

        ~BinaryIndex();
        
        page_id_t WriteSlice(const duration_t duration,char * const content);

        page_id_t GetPage(const duration_t duration);

        private:

    };
}