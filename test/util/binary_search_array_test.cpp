#include <gtest/gtest.h>
#include "util/binary_search_array.h"
#include "util/linked_header.h"
// #include "util/array_block.h"
#include "common/config.h"


TEST(BINARY_SEARCH_ARRAY,BASIC_TEST){
    mini_db::LinkedHeader<mini_db::duration_t,mini_db::ArrayBlock*> link_list_header;
    mini_db::BinarySearchArray<mini_db::duration_t,mini_db::ArrayBlock*> array_header(&link_list_header);

    mini_db::BinarySearchArray<mini_db::duration_t,mini_db::page_id_t> array(&array_header);
}

