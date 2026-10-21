#include "MyRenderer.h"

void MyRenderer::Initialize(MyWindow* window)
{
	this->window = window;
	sdlRenderer = SDL_CreateRenderer(window->GetSdlWindow(), -1, SDL_RENDERER_SOFTWARE);
	if (sdlRenderer == nullptr)
	{
		ErrorHandler::PopupAndExit("SDL RENDERER ERROR", SDL_GetError(), -1);
	}

	SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
}

MyRenderer::~MyRenderer()
{
	SDL_DestroyRenderer(sdlRenderer);
}

void MyRenderer::DrawRect(const int& x, const int& y, const int& w, const int& h, const SDL_Color& colour, const bool& centered)
{
	SDL_Rect rectangle;
	rectangle.x = (int)((x - ((double)w / 2.0 * centered)) * window->GetEqualizer());
	rectangle.y = (int)((y - ((double)h / 2.0 * centered)) * window->GetEqualizer() + window->GetYoffset());
	rectangle.w = (int)(w * window->GetEqualizer());
	rectangle.h = (int)(h * window->GetEqualizer());

	if (rectangle.w <= 0)
	{
		rectangle.w = 1;
	}

	if (rectangle.h <= 0)
	{
		rectangle.h = 1;
	}

	SDL_SetRenderDrawColor(sdlRenderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(sdlRenderer, &rectangle);
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
}

void MyRenderer::DrawTexture(SDL_Texture* texture, const int& x, const int& y, const double& scale, const bool& centered)
{
	int texture_width;
	int texture_height;
	SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);

	SDL_Rect srcrect;
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = texture_width;
	srcrect.h = texture_height;

	SDL_Rect dstrect;
	dstrect.x = (int)((x - ((double)centered * (double)scale * (double)texture_width / 2.0)) * (double)window->GetEqualizer());
	dstrect.y = (int)((y - ((double)centered * (double)scale * (double)texture_height / 2.0)) * (double)window->GetEqualizer() + (double)window->GetYoffset());
	dstrect.w = (int)((double)texture_width * scale * window->GetEqualizer());
	dstrect.h = (int)((double)texture_height * scale * window->GetEqualizer());

	SDL_RenderCopy(sdlRenderer, texture, &srcrect, &dstrect);
}

void MyRenderer::Present()
{
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);

	SDL_Rect rectangle;
	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = window->GetScreenWidth();
	rectangle.h = window->GetYoffset();

	SDL_RenderFillRect(sdlRenderer, &rectangle);

	rectangle.y = window->GetScreenHeight() - window->GetYoffset();

	SDL_RenderFillRect(sdlRenderer, &rectangle);

	SDL_RenderPresent(sdlRenderer);
}

void MyRenderer::Clear()
{
	SDL_RenderClear(sdlRenderer);
}

MyWindow* MyRenderer::GetWindow()
{
	return window;
}

SDL_Renderer* MyRenderer::GetSdlRenderer()
{
	return sdlRenderer;
}