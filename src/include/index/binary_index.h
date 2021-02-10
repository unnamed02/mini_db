#include "index/index.h"

namespace mini_db{
    class BinaryIndex :public Index{
        
        public:

        page_id_t GetPage(duration_t duration);

        bool WriteSlice(duration_t duration,char* content);        

    };
}