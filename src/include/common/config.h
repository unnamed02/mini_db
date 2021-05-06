#pragma once
#include <stdint.h>
#include <stddef.h>
namespace mini_dbm {

static const int PAGE_SIZE = 1024 * 512;
static const int INVALID_PAGE_ID = -1;
static const int INVALID_FRAME_ID = -1;

static const char LEAF_PAGE = 1;
static const char ROOT_PAGE = 2;

using page_id_t = int32_t;     // page id type
static const int PAGE_ID_SIZE = sizeof(page_id_t);

using frame_id_t = int32_t;     //frame id type

//since mp4 has 4 bytes of duration and 4 bytes of time_scale 
//we use uint32_t to represent them
using duration_t = uint32_t;
static const int DURATION_SIZE = sizeof(duration_t);

using time_scale_t = uint32_t;

using page_offset_t = int32_t;
static const int PAGE_OFFSET_SIZE = sizeof(page_offset_t);

static const int32_t SLOT_SIZE = DURATION_SIZE + PAGE_OFFSET_SIZE;

static const size_t NOT_FOUND_OFFSET = -1; 

}  // namespace bustub
