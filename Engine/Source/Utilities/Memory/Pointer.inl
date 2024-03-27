#pragma once

#include "Pointer.hpp"

#include <utility>

namespace ygg
{

template<typename Type>
inline Pointer<Type>::Pointer(std::nullptr_t) YGG_NOEXCEPT
	: detail::Allocator<Type>(nullptr)
{}

template<typename Type>
inline Pointer<Type>::Pointer(Pointer&& other) YGG_NOEXCEPT
	: detail::Allocator<Type>(std::exchange(other.buffer, nullptr))
{}

template<typename Type>
inline Pointer<Type>::~Pointer() YGG_NOEXCEPT
{
	this->Clean();
}

template<typename Type>
inline auto Pointer<Type>::Release() YGG_NOEXCEPT -> Type*
{
	Type* raw{std::exchange(this->buffer->raw, nullptr)};
	this->Decrement();

	return raw;
}

template<typename Type>
inline auto Pointer<Type>::Swap(Pointer& other) YGG_NOEXCEPT -> void
{
	std::swap(this->buffer, other.buffer);
}

template<typename Type>
inline auto Pointer<Type>::Move(Pointer& other) YGG_NOEXCEPT -> void
{
	*this = std::move(other);
}

template<typename Type>
inline auto Pointer<Type>::operator*() const YGG_EXCEPT -> Type&
{
	Assert(static_cast<bool>(*this), "Cannot access an invalid Pointer.");
	return *this->buffer->raw;
}

template<typename Type>
inline auto Pointer<Type>::operator->() const YGG_EXCEPT -> Type*
{
	Assert(static_cast<bool>(*this), "Cannot access an invalid Pointer.");
	return this->buffer->raw;
}

template<typename Type>
inline auto Pointer<Type>::operator=(std::nullptr_t) YGG_NOEXCEPT -> Pointer&
{
	this->Clean();
	this->Decrement();

	return *this;
}

template<typename Type>
inline auto Pointer<Type>::operator=(Pointer&& other) YGG_NOEXCEPT -> Pointer&
{
	if (this != &other)
	{
		if (this->buffer != other.buffer)
		{
			this->Clean();
			this->Decrement();
			this->buffer = std::move(other.buffer);
		}

		other.buffer = nullptr;
	}

	return *this;
}

template<typename Type>
inline Pointer<Type>::operator bool() const YGG_NOEXCEPT
{
	return this->buffer ? this->buffer->raw : false;
}

template<typename Type>
inline Pointer<Type>::Pointer(Type*&& raw) YGG_NOEXCEPT
	: detail::Allocator<Type>(new typename detail::Allocator<Type>::Buffer{std::move(raw), 0u})
{}

template<typename Type>
inline auto Pointer<Type>::Clean() YGG_NOEXCEPT -> void
{
	if (!this->buffer || !this->buffer->raw) { return; }

	delete this->buffer->raw;
	this->buffer->raw = nullptr;
}

template<typename Type>
template<typename ...Types>
inline auto Pointer<Type>::New(Types&&... arguments) YGG_NOEXCEPT -> Pointer
{
	return Pointer(new Type(std::forward<Types>(arguments)...));
}

} // namespace ygg