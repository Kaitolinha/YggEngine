#include "Branch.hpp"

#include <typeinfo>

namespace ygg
{

Branch::Branch() YGG_NOEXCEPT
	: Tree()
	, name{std::string(typeid(*this).name()).substr(11ui64)}
	, receivers{RECEIVER_ALL}
	, twigs{}
{
	Print("Branch grew: " + this->name);
}

Branch::~Branch() YGG_NOEXCEPT
{
	Print("Branch broke: " + this->name);
}

} // namespace ygg