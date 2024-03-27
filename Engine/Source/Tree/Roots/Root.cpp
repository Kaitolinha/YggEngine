#include "Root.hpp"

#include "../Branches/Branch.hpp"

namespace ygg
{

struct Root::FlowHandler
{
	static auto Input(Branch& branch) YGG_EXCEPT -> void
	{
		// Todo.
	}
	
	static auto Feed(Branch& branch, float delta) YGG_EXCEPT -> void
	{
		if (!branch.IsReceiving(Branch::RECEIVER_ENERGY & Branch::RECEIVER_FEED)) { return; }

		branch.Feed(delta);

		for (const auto& twig : branch.twigs)
		{
			Feed(*twig.second, delta);
		}
	}

	static auto FixedFeed(Branch& branch, float delta) YGG_EXCEPT -> void
	{
		if (branch.IsReceiving(Branch::RECEIVER_ENERGY & Branch::RECEIVER_FIXED_FEED)) { return; }

		branch.FixedFeed(delta);

		for (const auto& twig : branch.twigs)
		{
			FixedFeed(*twig.second, delta);
		}
	}
	
	static auto View(Branch& branch) YGG_EXCEPT -> void
	{
		if (!branch.IsReceiving(Branch::RECEIVER_ENERGY & Branch::RECEIVER_VIEW)) { return; }

		branch.View();

		for (const auto& twig : branch.twigs)
		{
			View(*twig.second);
		}
	}

	static auto Refresh(Branch& branch) YGG_EXCEPT -> void
	{
		// Todo.
	}
};

Root::Root() YGG_EXCEPT
	: currentTrunk{nullptr}
{
	Print("Root created!");

	this->ChangeTrunk(Pointer<Branch>::New());
}

Root::~Root() YGG_NOEXCEPT
{
	this->currentTrunk = nullptr;
	Print("Root Broke.");
}

auto Root::ChangeTrunk(Pointer<Branch>&& trunk) YGG_NOEXCEPT -> void
{
	this->currentTrunk.Move(trunk);
	Print("New Trunk to the Root: " + this->currentTrunk->name);
}

auto Root::Flow(FlowType flow) const YGG_EXCEPT -> void
{
	if (!this->currentTrunk) { return; }

	switch (flow)
	{
	case FLOW_INPUT:
		FlowHandler::Input(*this->currentTrunk);
		break;

	case FLOW_FEED:
		FlowHandler::Feed(*this->currentTrunk, 0.016f);
		break;

	case FLOW_FIXED_FEED:
		FlowHandler::FixedFeed(*this->currentTrunk, 0.016f);
		break;

	case FLOW_VIEW:
		FlowHandler::View(*this->currentTrunk);
		break;

	case FLOW_REFRESH:
		FlowHandler::Refresh(*this->currentTrunk);
		break;
	}
}

} // namespace ygg