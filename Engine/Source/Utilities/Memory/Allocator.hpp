#pragma once

#include "../Attributes.hpp"

namespace ygg
{
namespace detail
{

template<typename Type>
class Allocator
{
public:
	Allocator() YGG_NOEXCEPT;
	virtual ~Allocator() YGG_NOEXCEPT;

protected:
	struct Buffer;

	Allocator(Buffer* buffer) YGG_NOEXCEPT;

	Buffer* buffer;

	auto Increment() YGG_NOEXCEPT -> void;
	auto Decrement() YGG_NOEXCEPT -> void;
};

} // namespace detail
} // namespace ygg

#include "Allocator.inl"