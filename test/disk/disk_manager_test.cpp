#include "disk/disk_manager.h"
#include <gtest/gtest.h>

TEST(BufferPool,BasicTest){
   auto disk_manager_ptr = new mini_db::DiskManager("test.db");
   mini_db::page_id_t p_id = disk_manager_ptr->AllocatePage();


   char hello_str[mini_db::PAGE_SIZE] = "hello new page";
   
   disk_manager_ptr->WritePage(p_id,hello_str);
   char buffer[mini_db::PAGE_SIZE];
   disk_manager_ptr->ReadPage(p_id,buffer);
   ASSERT_EQ(*buffer,*hello_str);


   delete disk_manager_ptr;
}
