#pragma once

#include "Pointer.hpp"

namespace ygg
{

template<typename Type>
class Reference: public detail::Allocator<Type>
{
public:
	explicit Reference(std::nullptr_t = nullptr) YGG_NOEXCEPT;
	Reference(Pointer<Type>& pointer) YGG_NOEXCEPT;
	~Reference() = default;

	auto operator* () const YGG_EXCEPT -> Type&;
	auto operator->() const YGG_EXCEPT -> Type*;
	auto operator=(std::nullptr_t) YGG_NOEXCEPT -> Reference&;
	auto operator=(Pointer<Type>& pointer) YGG_NOEXCEPT -> Reference&;

	explicit operator bool() const YGG_NOEXCEPT;
};

} // namespace ygg

#include "Reference.inl"