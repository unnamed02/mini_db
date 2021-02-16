#include <gtest/gtest.h>
#include "disk/disk_manager.h"
#include "page/page.h"
#include "iostream"

TEST(page_test,basic_test){
    auto disk_manager_ptr = new mini_db::DiskManager("test.db");
    mini_db::page_id_t page_id = disk_manager_ptr->AllocatePage();
    
    char buffer[mini_db::PAGE_SIZE];
    auto page_ptr = reinterpret_cast<mini_db::Page*>(buffer);
    page_ptr->Init(0,page_id);
    
    char hello[6] = "hello";
    for(int i = 0;i < 100;i++){
        page_ptr->Append(12,hello);
    }

    disk_manager_ptr->WritePage(page_ptr->GetPageId(),buffer);

    memset(buffer,0,mini_db::PAGE_SIZE);


    disk_manager_ptr->ReadPage(page_id,buffer);
    page_ptr = reinterpret_cast<mini_db::Page*>(buffer);
    ASSERT_EQ(page_ptr->GetOffset(),500);
    ASSERT_EQ(page_ptr->GetCatalogueOffset(),mini_db::MAX_CONTENT_SIZE-600);

}