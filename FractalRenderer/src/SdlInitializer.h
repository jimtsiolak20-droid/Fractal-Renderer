#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "ErrorHandler.h"

class SdlInitializer
{
public:
	static void SdlInit();
	static void SdlQuit();
	static bool isInitialized();
private:
	static bool initialized;

	SdlInitializer() = delete;
};