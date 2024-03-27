#include "Core/Engine.hpp"

auto main(int argc, char** argv) -> int
{
	try
	{
		ygg::detail::Engine engine;
		engine.Run();
	}
	catch (const std::runtime_error& error)
	{
		std::cerr << error.what() << '\n';
		return -1;
	}

	return 0;
}