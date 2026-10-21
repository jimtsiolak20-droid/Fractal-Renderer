#include "SdlInitializer.h"

bool SdlInitializer::initialized = false;

void SdlInitializer::SdlInit()
{
	if (initialized)
	{
		ErrorHandler::PopupAndExit("SDL INIT ERROR", "SDL is already initialized.", -1);
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		ErrorHandler::PopupAndExit("SDL INIT ERROR", SDL_GetError(), -1);
	}

	if (TTF_Init() != 0)
	{
		ErrorHandler::PopupAndExit("SDL INIT ERROR", TTF_GetError(), -1);
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		ErrorHandler::PopupAndExit("SDL INIT ERROR", IMG_GetError(), -1);
	}

	initialized = true;
}

void SdlInitializer::SdlQuit()
{
	if (!initialized)
	{
		ErrorHandler::PopupAndExit("SDL INIT ERROR", "SDL is not initialized.", -1);
	}

	TTF_Quit();
	SDL_Quit();
	IMG_Quit();

	initialized = false;
}

bool SdlInitializer::isInitialized()
{
	return initialized;
}