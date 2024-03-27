#pragma once

#include "../Roots/Root.hpp"

#include <unordered_map>

namespace ygg
{

class Branch: public Tree
{
public:
	enum Receiver: Uint8
	{
		RECEIVER_ENERGY     = 0x01,
		RECEIVER_FEED       = 0x02,
		RECEIVER_FIXED_FEED = 0x04,
		RECEIVER_VIEW       = 0x08,
		RECEIVER_ALL        = 0xFF
	};

	Branch() YGG_NOEXCEPT;
	virtual ~Branch() YGG_NOEXCEPT;

	std::string name;

	auto SetReceiver(Uint8 receivers, bool enable) YGG_NOEXCEPT -> void { this->receivers = enable ? this->receivers | receivers : this->receivers & ~receivers; }
	auto IsReceiving(Uint8 receivers) const YGG_NOEXCEPT -> bool { return this->receivers & receivers; }

	friend class Root;

protected:
	auto virtual Grew() YGG_EXCEPT -> void {}
	auto virtual Feed(float delta) YGG_EXCEPT -> void {}
	auto virtual FixedFeed(float delta) YGG_EXCEPT -> void {}
	auto virtual View() YGG_EXCEPT -> void {}
	auto virtual Broke() YGG_EXCEPT -> void {}

private:
	Uint8 receivers;
	std::unordered_map<Size, Pointer<Branch>> twigs;
};

} // namespace ygg