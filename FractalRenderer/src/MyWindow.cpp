#include "MyWindow.h"

void MyWindow::Initialize(const std::string& title, const int& width, const int& height)
{
	this->width = width;
	this->height = height;

	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	screen_w = dm.w;
	screen_h = dm.h;

	if (((double)height / (double)width) > ((double)screen_h / (double)screen_w))
	{
		ErrorHandler::PopupAndExit("SDL INIT ERROR", "Window size not appropriate.", -1);
	}

	equalizer = (double)screen_w / (double)width;
	yoffset = (int)ceil((double)((screen_h - (height * equalizer)) / 2.0));

	sdlWindow = SDL_CreateWindow(title.c_str(), 0, 0, screen_w, screen_h, 0);
	if (sdlWindow == nullptr)
	{
		ErrorHandler::PopupAndExit("SDL WINDOW ERROR", SDL_GetError(), -1);
	}
}

MyWindow::~MyWindow()
{
	SDL_DestroyWindow(sdlWindow);
}

int MyWindow::GetWidth()
{
	return width;
}

int MyWindow::GetHeight()
{
	return height;
}

int MyWindow::GetScreenWidth()
{
	return screen_w;
}

int MyWindow::GetScreenHeight()
{
	return screen_h;
}

int MyWindow::GetYoffset()
{
	return yoffset;
}

double MyWindow::GetEqualizer()
{
	return equalizer;
}

SDL_Window* MyWindow::GetSdlWindow()
{
	return sdlWindow;
}