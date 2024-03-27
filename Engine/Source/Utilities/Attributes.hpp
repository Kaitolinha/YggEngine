#pragma once

#define YGG_EXCEPT noexcept(false)
#define YGG_NOEXCEPT noexcept(true)
#define YGG_NOEXCEPT_IF(condition) noexcept(condition)

#define YGG_NODISCARD [[nodiscard("Are you sure you want to discard the return value?")]]
#define YGG_NODISCARD_MESSAGE(message) [[nodiscard(message)]]