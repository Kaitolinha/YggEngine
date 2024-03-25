#include "Core/Engine.hpp"

auto main(int argc, char** argv) -> int
{
	try
	{
		Engine engine;
		engine.Run();
	}
	catch (const std::runtime_error& error)
	{
		std::cerr << "Runtime Error! " << error.what() << '\n';
		return -1;
	}

	return 0;
}