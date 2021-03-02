#include "index/binary_index.h"
#include "index/index.h"
#include <gtest/gtest.h>

TEST(BINARY_INDEX_TEST,BASIC_TEST){
    auto disk_manager_ptr = new mini_db::DiskManager("test.db");
    mini_db::Index* index_ptr = new mini_db::BinaryIndex(disk_manager_ptr,10,10,6);
    
    char str[] = "123456";
    index_ptr->WriteSlice(12,str);
    
    char * dst = index_ptr->GetSlice(13);
    ASSERT_EQ(dst,nullptr);

    dst = index_ptr->GetSlice(11);
    for(int i = 0;i<6;i++){
        ASSERT_EQ(dst[i],str[i]);
    }
    index_ptr->FreeSlice(dst);

    delete index_ptr;
    delete disk_manager_ptr;
}