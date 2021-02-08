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

}  // namespace bustub
