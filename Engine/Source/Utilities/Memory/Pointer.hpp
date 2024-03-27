#pragma once

#include "../Integers.hpp"
#include "../Attributes.hpp"
#include "Allocator.hpp"

namespace ygg
{

template<typename Type>
class Reference;

template<typename Type>
class Pointer: public detail::Allocator<Type>
{
public:
	Pointer(std::nullptr_t = nullptr) YGG_NOEXCEPT;
	Pointer(Pointer&& other) YGG_NOEXCEPT;
	~Pointer() YGG_NOEXCEPT;

	Pointer(const Pointer&) = delete;
	auto operator=(const Pointer&) -> Pointer& = delete;

	YGG_NODISCARD_MESSAGE("The value returned by Release() must not be discarded without use. Consider manually freeing the memory.")
	auto Release() YGG_NOEXCEPT -> Type*;

	auto Swap(Pointer& other) YGG_NOEXCEPT -> void;
	auto Move(Pointer& other) YGG_NOEXCEPT -> void;

	auto operator* () const YGG_EXCEPT -> Type&;
	auto operator->() const YGG_EXCEPT -> Type*;
	auto operator=(std::nullptr_t) YGG_NOEXCEPT -> Pointer&;
	auto operator=(Pointer&& other) YGG_NOEXCEPT -> Pointer&;

	explicit operator bool() const YGG_NOEXCEPT;

	template<typename... Types>
	static auto New(Types&&... arguments) YGG_NOEXCEPT -> Pointer;

	friend class Reference<Type>;

private:
	Pointer(Type*&& raw) YGG_NOEXCEPT;

	auto Clean() YGG_NOEXCEPT -> void;
};

} // namespace ygg

#include "Pointer.inl"