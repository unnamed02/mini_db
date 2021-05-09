#include <gtest/gtest.h>
#include "disk/disk_manager.h"
#include "page/page.h"

TEST(PAGE_TEST,BASIC_TEST){
    auto disk_manager_ptr = new mini_dbm::DiskManager("test.db");
    mini_dbm::page_id_t page_id = disk_manager_ptr->AllocatePage();
    
    char buffer[mini_dbm::PAGE_SIZE];
    auto page_ptr = reinterpret_cast<mini_dbm::Page*>(buffer);
    page_ptr->Init(0,page_id);
    
    char hello[6] = "hello";
    for(int i = 0;i < 100;i++){
        page_ptr->Append(12,hello);
    }

    disk_manager_ptr->WritePage(page_ptr->GetPageId(),buffer);

    memset(buffer,0,mini_dbm::PAGE_SIZE);

    disk_manager_ptr->ReadPage(page_id,buffer);
    page_ptr = reinterpret_cast<mini_dbm::Page*>(buffer);
    ASSERT_EQ(page_ptr->GetOffset(),500);
    ASSERT_EQ(page_ptr->GetCatalogueOffset(),mini_dbm::MAX_CONTENT_SIZE-100 * mini_dbm::LEAF_SLOT_SIZE);
    
    mini_dbm::page_offset_t start;
    mini_dbm::page_offset_t length;
    for(int i = 0;i<100;i++){
        page_ptr->Find(i*12+1,&start,&length);
        ASSERT_EQ(start,i*5);
        ASSERT_EQ(length,5);
        char dst[6];
        memmove(dst,page_ptr->GetContent()+start,length);
        for(int i = 0;i<sizeof(dst);i++){
            ASSERT_EQ(dst[i],hello[i]);
        }
    }

    delete disk_manager_ptr;
}

TEST(PAGE_TEST,MISS_FIND_TEST){
    auto disk_manager_ptr = new mini_dbm::DiskManager("test.db");
    mini_dbm::page_id_t page_id = disk_manager_ptr->AllocatePage();
    
    char buffer[mini_dbm::PAGE_SIZE];
    auto page_ptr = reinterpret_cast<mini_dbm::Page*>(buffer);
    page_ptr->Init(0,page_id);
    
    char hello[6] = "hello";
    for(int i = 0;i < 100;i++){
        page_ptr->Append(12,hello);
    }

    disk_manager_ptr->WritePage(page_ptr->GetPageId(),buffer);

    memset(buffer,0,mini_dbm::PAGE_SIZE);

    disk_manager_ptr->ReadPage(page_id,buffer);
    page_ptr = reinterpret_cast<mini_dbm::Page*>(buffer);

    mini_dbm::page_offset_t start;
    mini_dbm::page_offset_t length;
    bool res = page_ptr->Find(1201,&start,&length);
    ASSERT_EQ(res,false);
}

TEST(PAGE_TEST,MAX_INSERT_TEST){
    auto disk_manager_ptr = new mini_dbm::DiskManager("test.db");
    mini_dbm::page_id_t page_id = disk_manager_ptr->AllocatePage();
    
    char buffer[mini_dbm::PAGE_SIZE];
    auto page_ptr = reinterpret_cast<mini_dbm::Page*>(buffer);
    page_ptr->Init(0,page_id);

    char str[] = "123456";
    int max_size = mini_dbm::MAX_CONTENT_SIZE/((sizeof(str) + mini_dbm::LEAF_SLOT_SIZE - 1));

    for(int i = 0;i<max_size;i++){
        bool res = page_ptr->Append(12,str);
        ASSERT_EQ(res,true);
    }

    bool res = page_ptr->Append(12,str);
    ASSERT_EQ(res,false);

    disk_manager_ptr->WritePage(page_ptr->GetPageId(),buffer);

    disk_manager_ptr->ReadPage(page_id,buffer);
    page_ptr = reinterpret_cast<mini_dbm::Page*>(buffer);

    mini_dbm::page_offset_t start;
    mini_dbm::page_offset_t length;

    for(int i = 0;i<max_size;i++){
        page_ptr->Find(i*12+1,&start,&length);
        ASSERT_EQ(start,i*6);
        ASSERT_EQ(length,6);
        char dst[6];
        memmove(dst,page_ptr->GetContent()+start,length);
        for(int i = 0;i<sizeof(dst);i++){
            ASSERT_EQ(dst[i],str[i]);
        }
    }

    delete disk_manager_ptr;
}

