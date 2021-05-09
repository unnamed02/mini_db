#include "index/binary_index.h"
// #include "index/b_plus_tree_index.h"
// #include "index/polynomial_index.h"
#include "index/linear_index.h"
#include "page/page.h"
#include "index/index.h"
#include <gtest/gtest.h>
#include <stdlib.h>

TEST(INDEX_TEST,BASIC_TEST){
    auto disk_manager_ptr = new mini_dbm::DiskManager("test.db");

    int t;
    mini_dbm::Index* index_ptr = nullptr;
    printf("index type ? \n1 stand for binary index,2 for b plus tree index,3 for polynomial index\n");
    scanf("%d",&t);
    switch (t){
    case 1:
        index_ptr = new mini_dbm::BinaryIndex(disk_manager_ptr,10,10,6);
        break;
    // case 2:
    //     index_ptr = new mini_dbm::BPlusTreeIndex(disk_manager_ptr,10,10,6);
    //     break;
    // case 3:
    //     index_ptr = new mini_dbm::PolynomialIndex(disk_manager_ptr,10,10,6);
    case 4:
        index_ptr = new mini_dbm::LinearIndex(disk_manager_ptr,10,10,6);
        break;
    default:
        printf("invalid input\n");
        return;
    }
    char str[] = "123456";
    index_ptr->WriteSlice(12,str);
    
    char * dst = index_ptr->GetSlice(12);
    ASSERT_EQ(dst,nullptr);

    dst = index_ptr->GetSlice(0);
    ASSERT_NE(dst,nullptr);
    if(dst){
        for(int i = 0;i<6;i++){
            ASSERT_EQ(dst[i],str[i]);
        }
        index_ptr->FreeSlice(dst);
    }

    delete index_ptr;
    delete disk_manager_ptr;
}

TEST(INDEX_TEST,CHANGE_PAGE_TEST){
    auto disk_manager_ptr = new mini_dbm::DiskManager("test.db");

    int t;
    mini_dbm::Index* index_ptr = nullptr;
    printf("index type ? \n1 stand for binary index,2 for b plus tree index,3 for polynomial index\n");
    scanf("%d",&t);
    switch (t){
    case 1:
        index_ptr = new mini_dbm::BinaryIndex(disk_manager_ptr,10,10,6);
        break;
    // case 2:
    //     index_ptr = new mini_dbm::BPlusTreeIndex(disk_manager_ptr,10,10,6);
    //     break;
    // case 3:
    //     index_ptr = new mini_dbm::PolynomialIndex(disk_manager_ptr,10,10,6);
    case 4:
        index_ptr = new mini_dbm::LinearIndex(disk_manager_ptr,10,10,6);
        break;
    default:
        printf("invalid input\n");
        return;
    }

    int n = mini_dbm::MAX_CONTENT_SIZE;
    char str[] = "12345678";
    n /= (8+mini_dbm::LEAF_SLOT_SIZE);
    
    auto pg_id = index_ptr->WriteSlice(12,str);
  
    for(int i = 1;i<n;i++){
        auto res = index_ptr->WriteSlice(12,str);
        ASSERT_EQ(res,pg_id);
    }
    
    auto res = index_ptr->WriteSlice(12,str);
    ASSERT_NE(res,pg_id);

    // index_ptr->GetSlice(0);

    delete index_ptr;
    delete disk_manager_ptr;
}

TEST(INDEX_TEST,GET_PAGE_TEST){

    auto disk_manager_ptr = new mini_dbm::DiskManager("test.db");

    int t;
    mini_dbm::Index* index_ptr = nullptr;

    index_ptr = new mini_dbm::LinearIndex(disk_manager_ptr,10,10,6);
    int n = mini_dbm::MAX_CONTENT_SIZE;
    char str[] = "12345678";
    n /= (8+mini_dbm::LEAF_SLOT_SIZE);

    for(int i = 0;i<6*n;i++){
        auto res = index_ptr->WriteSlice(12,str);
    }

    auto pg_id = index_ptr->WriteSlice(12,str);
    // int temp = rand();
    // printf("temp = %d\n",temp);
    // ASSERT_EQ(index_ptr->GetPage(180), 0);
    // ASSERT_EQ(index_ptr->GetPage(9.5*rand()), 4);
    // ASSERT_EQ(index_ptr->GetPage(rand()), 3);
    // ASSERT_EQ(index_ptr->GetPage(4*rand()), 5);

    ASSERT_EQ(index_ptr->GetPage(12*n+1),1);
    // ASSERT_EQ(index_pt)


    // index_ptr->GetSlice(0);

    delete index_ptr;
    delete disk_manager_ptr;
}