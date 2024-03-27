#pragma once

#include "Reference.hpp"

namespace ygg
{

template<typename Type>
inline Reference<Type>::Reference(std::nullptr_t) YGG_NOEXCEPT
	: detail::Allocator<Type>()
{}

template<typename Type>
inline Reference<Type>::Reference(Pointer<Type>& pointer) YGG_NOEXCEPT
	: detail::Allocator<Type>(pointer.buffer)
{}

template<typename Type>
inline auto Reference<Type>::operator*() const YGG_EXCEPT -> Type&
{
	Assert(static_cast<bool>(*this), "Cannot access an invalid Reference.");
	return *this->buffer->raw;
}

template<typename Type>
inline auto Reference<Type>::operator->() const YGG_EXCEPT -> Type*
{
	Assert(static_cast<bool>(*this), "Cannot access an invalid Reference.");
	return this->buffer->raw;
}

template<typename Type>
inline auto Reference<Type>::operator=(std::nullptr_t) YGG_NOEXCEPT -> Reference&
{
	this->Decrement();

	return *this;
}

template<typename Type>
inline auto Reference<Type>::operator=(Pointer<Type>& pointer) YGG_NOEXCEPT -> Reference&
{
	this->buffer = pointer.buffer;
	this->Increment();

	return *this;
}

template<typename Type>
inline Reference<Type>::operator bool() const YGG_NOEXCEPT
{
	return this->buffer ? this->buffer->raw : false;
}

} // namespace ygg