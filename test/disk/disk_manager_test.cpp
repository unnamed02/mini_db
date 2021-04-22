#include "disk/disk_manager.h"
#include <gtest/gtest.h>

TEST(DISK_MANAGER_TEST,BASIC_TEST){
   auto disk_manager_ptr = new mini_dbm::DiskManager("test.db");
   mini_dbm::page_id_t p_id = disk_manager_ptr->AllocatePage();

   char hello_str[mini_dbm::PAGE_SIZE] = "hello new page";
   
   disk_manager_ptr->WritePage(p_id,hello_str);
   char buffer[mini_dbm::PAGE_SIZE];
   disk_manager_ptr->ReadPage(p_id,buffer);
   ASSERT_EQ(*buffer,*hello_str);


   delete disk_manager_ptr;
}
