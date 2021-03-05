#include "index/polynomial_index.h"
#include "page/page.h"

namespace mini_db{

page_id_t PolynomialIndex::WriteSlice(const duration_t duration,char* const content){
    
}

page_id_t PolynomialIndex::GetPage(const duration_t duration){

}

PolynomialIndex::PolynomialIndex(DiskManager* disk_manager,time_scale_t scale,uint32_t max_pages,uint32_t buffer_size):
Index(disk_manager,scale,max_pages,buffer_size){
    
}

PolynomialIndex::~PolynomialIndex(){

}

}