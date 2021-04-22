#include <gtest/gtest.h>
#include "disk/disk_manager.h"
#include "util/array_header.h"
#include "util/vector_header.h"
#include "util/binary_search_array.h"
#include "page/array_block.h"
#include "page/page.h"

TEST(BINARY_SEARCH_ARRAY,BASIC_TEST){
    auto dmp_h1 = new mini_dbm::DiskManager("index_level_1.db");
    auto dmp_h2 = new mini_dbm::DiskManager("index_level_2.db");
    mini_dbm::ArrayHeader<mini_dbm::duration_t,mini_dbm::ArrayBlock<mini_dbm::duration_t>*>*array_head_ptr
        = new mini_dbm::VectorHeader<mini_dbm::duration_t,mini_dbm::ArrayBlock<mini_dbm::duration_t>*>(dmp_h1);

    mini_dbm::BinarySearchArray<mini_dbm::duration_t> array(array_head_ptr,dmp_h2);
}

