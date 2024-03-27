#pragma once

#include "../Utilities/Utility.hpp"
#include "../Utilities/Memory/Pointer.hpp"
#include "../Utilities/Memory/Reference.hpp"

namespace ygg
{

class Tree
{
public:
	Tree() YGG_NOEXCEPT = default;
	virtual ~Tree() YGG_NOEXCEPT = default;
};

} // namespace ygg