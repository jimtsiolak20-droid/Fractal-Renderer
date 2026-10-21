#pragma once

#include <SDL.h>

#include <map>

#include "MyWindow.h"
#include "ErrorHandler.h"

class Keymouse
{
public:
	Keymouse();
	Keymouse(MyWindow* window);
	~Keymouse();

	void Process();
	bool KeyPressed(SDL_Keycode key);
	int MouseX();
	int MouseY();
	bool MouseButtonDown();
	bool QuitEvent();
private:
	std::map<int, bool> keyboard;
	int mouseX;
	int mouseY;
	bool mouseButtonDown;
	bool quitEvent;
	MyWindow* window;
};