#pragma once

#include "Allocator.hpp"

#include <atomic>

namespace ygg
{
namespace detail
{

template<typename Type>
struct Allocator<Type>::Buffer
{
	Type* raw;
	std::atomic<Uint32> count;
};

template<typename Type>
inline Allocator<Type>::Allocator() YGG_NOEXCEPT
	: buffer{nullptr}
{}

template<typename Type>
inline Allocator<Type>::Allocator(Buffer* buffer) YGG_NOEXCEPT
	: buffer{buffer}
{
	this->Increment();
}

template<typename Type>
inline Allocator<Type>::~Allocator() YGG_NOEXCEPT
{
	this->Decrement();
}

template<typename Type>
inline auto Allocator<Type>::Increment() YGG_NOEXCEPT -> void
{
	if (this->buffer) { ++this->buffer->count; }
}

template<typename Type>
inline auto Allocator<Type>::Decrement() YGG_NOEXCEPT -> void
{
	if (this->buffer)
	{
		if (--this->buffer->count == 0u) { delete this->buffer; }
		this->buffer = nullptr;
	}
}

} // namespace detail
} // namespace ygg