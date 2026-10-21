#pragma once

#include <SDL.h>

#include "MyWindow.h"
#include "ErrorHandler.h"

class MyRenderer
{
public:
	MyRenderer() = default;
	void Initialize(MyWindow* window);
	~MyRenderer();

	void DrawRect(const int& x, const int& y, const int& w, const int& h, const SDL_Color& colour, const bool& centered);
	void DrawTexture(SDL_Texture* texture, const int& x, const int& y, const double& scale, const bool& centered);
	void Present();
	void Clear();

	MyWindow* GetWindow();
	SDL_Renderer* GetSdlRenderer();
private:
	MyWindow* window;
	SDL_Renderer* sdlRenderer;
};