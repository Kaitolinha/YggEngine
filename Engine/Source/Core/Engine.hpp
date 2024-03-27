#pragma once

#include "../Utilities/Utility.hpp"

namespace ygg
{
namespace detail
{

constexpr const char*  ENGINE_WINDOW_NAME{"Ygg Engine"};
constexpr unsigned int ENGINE_INITIAL_WINDOW_WIDTH{800u};
constexpr unsigned int ENGINE_INITIAL_WINDOW_HEIGHT{600u};

class Engine
{
public:
	Engine() YGG_EXCEPT;
	~Engine() YGG_NOEXCEPT;

	auto Run() YGG_EXCEPT -> void;

private:
	bool isRunning;

	struct Implementation;
	Implementation* implementation;
};

} // namespace detail
} // namespace ygg