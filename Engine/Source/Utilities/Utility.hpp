#pragma once

#include "Attributes.hpp"

#include <iostream>
#include <stdexcept>

namespace ygg
{

inline auto Print(const std::string& message) YGG_NOEXCEPT -> void
{
    std::cout << "-> " << message << '\n';
}

inline auto Warning(const std::string& message) YGG_NOEXCEPT -> void
{
    std::cerr << "[Warning] " << message << '\n';
}

inline auto Error(const std::string& message) YGG_EXCEPT -> void
{
    throw std::runtime_error("[Error] " + message);
}

inline auto Assert(bool condition, const std::string& message) YGG_EXCEPT -> void
{
    if (!condition) { throw std::runtime_error("[Error] " + message); }
}

} // namespace ygg