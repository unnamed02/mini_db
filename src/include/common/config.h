//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// config.h
//
// Identification: src/include/common/config.h
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <atomic>
#include <chrono>  // NOLINT
#include <cstdint>

namespace mini_db {

static constexpr int PAGE_SIZE = 4096;  

using page_id_t = int32_t;     // page id type

//since mp4 has 4 bytes of duration and 4 bytes of time_scale 
//we use uint32_t to represent them
using duration_t = uint32_t;
using time_scale_t = uint32_t;

}  // namespace bustub
