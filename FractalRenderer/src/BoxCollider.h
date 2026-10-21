 #pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "MyWindow.h"
#include "Keymouse.h"
#include "ErrorHandler.h"

class BoxCollider
{
public:
	BoxCollider() = default;
	BoxCollider(const int& x, const int& y, const int& w, const int& h,const bool& centered);
	void operator=(const BoxCollider& other);
	~BoxCollider();

	void Fix(MyWindow* window);
	bool IsMouseOn(Keymouse& events);
	bool CollidesWith(const BoxCollider& other);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	bool isCentered();
private:
	int xPos, yPos;
	int width, height;
	bool centered;

	
};