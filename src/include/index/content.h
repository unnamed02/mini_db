#include "common/config.h"

#define CONTENT_HEADER_SIZE = 16;

namespace mini_db{
    class Content{
        public:
        Content(){
            
        }

        inline duration_t GetStart(){return start_;}

        inline duration_t GetDuration(){return duration_;}

        inline page_id_t GetPageId(){return page_id_;}

        inline uint32_t GetLength(){return length_;}

        private:        
        duration_t start_;
        duration_t duration_;

        page_id_t  page_id_;
        
        uint32_t length_;
        
        char       content[0];
        
    };
}
