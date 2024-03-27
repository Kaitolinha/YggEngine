#pragma once

#include "../Tree.hpp"

namespace ygg
{
namespace detail
{

class Engine;

} // namespace detail

class Branch;

class Root: public Tree
{
private:
	enum FlowType: Uint8
	{
		FLOW_INPUT,
		FLOW_FEED,
		FLOW_FIXED_FEED,
		FLOW_VIEW,
		FLOW_REFRESH
	};

	struct FlowHandler;

public:
	Root() YGG_EXCEPT;
	~Root() YGG_NOEXCEPT;
	
	auto ChangeTrunk(Pointer<Branch>&& trunk) YGG_NOEXCEPT -> void;

	friend class detail::Engine;

private:

	Pointer<Branch> currentTrunk;

	auto Flow(FlowType flow) const YGG_EXCEPT -> void;
};

} // namespace ygg
