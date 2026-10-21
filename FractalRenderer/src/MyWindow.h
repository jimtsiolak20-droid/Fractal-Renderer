 #pragma once

#include <SDL.h>

#include <string>

#include "ErrorHandler.h"

class MyWindow
{
public:
	MyWindow() = default;
	void Initialize(const std::string& title, const int& width, const int& height);
	~MyWindow();

	int GetWidth();
	int GetHeight();
	int GetScreenWidth();
	int GetScreenHeight();
	int GetYoffset();
	double GetEqualizer();
	SDL_Window* GetSdlWindow();
private:
	int width, height;
	int screen_w, screen_h;
	int yoffset;
	double equalizer;
	SDL_Window* sdlWindow;
};