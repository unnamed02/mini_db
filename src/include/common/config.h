#pragma once
#include <stdint.h>
namespace mini_db {

static const int PAGE_SIZE = 4096;  
static const int INVALID_PAGE_ID = -1;
static const int INVALID_FRAME_ID = -1;

using page_id_t = int32_t;     // page id type
using farme_id_t = int32_t;     //frame id type

//since mp4 has 4 bytes of duration and 4 bytes of time_scale 
//we use uint32_t to represent them
using duration_t = uint32_t;
static const int DURATION_SIZE = 4;

using time_scale_t = uint32_t;

using page_offset_t = int16_t;
static const int PAGE_OFFSET_SIZE = 2;

}  // namespace bustub
