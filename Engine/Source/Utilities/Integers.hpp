#pragma once

#include <cstdint>
#include <cstddef>

namespace ygg
{

using Int8   = std::int8_t;
using Int16  = std::int16_t;
using Int32  = std::int32_t;
using Int64  = std::int64_t;
using Uint8  = std::uint8_t;
using Uint16 = std::uint16_t;
using Uint32 = std::uint32_t;
using Uint64 = std::uint64_t;
using Size   = std::size_t;

constexpr Int8  MIN_INT8  = INT8_MIN;
constexpr Int16 MIN_INT16 = INT16_MIN;
constexpr Int32 MIN_INT32 = INT16_MIN;
constexpr Int64 MIN_INT64 = INT64_MIN;

constexpr Int8   MAX_INT8   = INT8_MAX;
constexpr Int16  MAX_INT16  = INT16_MAX;
constexpr Int32  MAX_INT32  = INT16_MAX;
constexpr Int64  MAX_INT64  = INT64_MAX;
constexpr Uint8  MAX_UINT8  = UINT8_MAX;
constexpr Uint16 MAX_UINT16 = UINT16_MAX;
constexpr Uint32 MAX_UINT32 = UINT16_MAX;
constexpr Uint64 MAX_UINT64 = UINT64_MAX;
constexpr Size   MAX_SIZE   = SIZE_MAX;

} // namespace ygg
