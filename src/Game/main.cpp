#include "Game.h"

#include <SDL2/SDL_main.h>

#include <Library/Logger/Logger.hpp>

int main(int argc, char* args[])
{

	if(argc > 1 && std::string(args[1]) == "--no-debug")
		Logging::Settings::SetLevel(Logging::Level::Error);
	else
		Logging::Settings::SetLevel(Logging::Level::Debug);

	Game game;
	game.Run();

	return 0;
}
