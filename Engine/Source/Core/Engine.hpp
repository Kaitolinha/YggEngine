#pragma once

#include <iostream>

constexpr const char*  ENGINE_WINDOW_NAME{"Ygg Engine"};
constexpr unsigned int ENGINE_INITIAL_WINDOW_WIDTH{800u};
constexpr unsigned int ENGINE_INITIAL_WINDOW_HEIGHT{600u};

class Engine
{
public:
	Engine();
	virtual ~Engine();

	auto Run() -> void;
	auto Log(const std::string& message) const -> void { std::cout << "[LOG] " << message << '\n'; }

private:
	bool isRunning;

	struct Context;
	Context* context;
};
