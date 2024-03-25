#pragma once

#include <iostream>

class Engine
{
public:
	Engine();
	virtual ~Engine();

	auto Run() -> void;
	auto RuntimeError(const std::string& message) const -> void { throw std::runtime_error(message); }
	auto Log(const std::string& message) const -> void { std::cout << message << '\n'; }

private:
	bool isRunning;

	struct Context;
	Context* context;
};
