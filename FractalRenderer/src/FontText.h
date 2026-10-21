#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "MyRenderer.h"
#include "ErrorHandler.h"

class FontText
{
public:
	FontText() = default;
	FontText(const std::string& fontpath, MyRenderer* renderer, const int& size);
	FontText(const FontText& other);
	FontText(FontText&& other) noexcept;
	void operator=(const FontText& other);
	void operator=(FontText&& other) noexcept;
	~FontText();

	void Draw(const std::string& text, const int& x, const int& y, const SDL_Color& colour, const bool& centered);
	SDL_Texture* RenderText(const std::string& text, const SDL_Color& colour); // not responsible for deleting

	TTF_Font* GetFont();
	std::string GetFilepath();
	int GetSize();
	MyRenderer* GetRenderer();
private:
	TTF_Font* font;
	std::string filepath;
	int size;
	MyRenderer* renderer;
};