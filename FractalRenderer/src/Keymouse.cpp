#include "Keymouse.h"

Keymouse::Keymouse()
	:window(nullptr), mouseX(NULL), mouseY(NULL), mouseButtonDown(NULL), quitEvent(NULL)
{
}

Keymouse::Keymouse(MyWindow* window)
{
	this->window = window;
	mouseX = 0;
	mouseY = 0;
	mouseButtonDown = false;
	quitEvent = false;
}

Keymouse::~Keymouse()
{
}

void Keymouse::Process()
{
	SDL_Event tempEvent;
	while (SDL_PollEvent(&tempEvent))
	{
		switch (tempEvent.type)
		{
		case SDL_KEYDOWN:
			keyboard[tempEvent.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keyboard[tempEvent.key.keysym.sym] = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseButtonDown = true;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButtonDown = false;
			break;
		case SDL_QUIT:
			quitEvent = true;
		}
	}

	int tempMouseX;
	int tempMouseY;
	SDL_GetMouseState(&tempMouseX, &tempMouseY);
	mouseX = (int)(tempMouseX / window->GetEqualizer());
	mouseY = (int)((tempMouseY - window->GetYoffset()) / window->GetEqualizer());
	if (mouseY > window->GetHeight())
	{
		mouseY = -1;
	}
}

bool Keymouse::KeyPressed(SDL_Keycode key)
{
	return keyboard[key];
}

int Keymouse::MouseX()
{
	return mouseX;
}

int Keymouse::MouseY()
{
	return mouseY;
}

bool Keymouse::MouseButtonDown()
{
	return mouseButtonDown;
}

bool Keymouse::QuitEvent()
{
	return quitEvent;
}