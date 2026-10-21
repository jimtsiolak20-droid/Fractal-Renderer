#include "FontText.h"

FontText::FontText(const std::string& filepath, MyRenderer* renderer, const int& size)
{
	this->font = TTF_OpenFont(filepath.c_str(), size);
	if (font == nullptr)
	{
		ErrorHandler::PopupAndExit("FONT ERROR", TTF_GetError(), -1);
	}

	this->filepath = filepath;
	this->size = size;
	this->renderer = renderer;
}

FontText::FontText(const FontText& other)
{
	this->font = TTF_OpenFont(other.filepath.c_str(), other.size);
	if (font == nullptr)
	{
		ErrorHandler::PopupAndExit("FONT ERROR", TTF_GetError(), -1);
	}

	this->filepath = other.filepath;
	this->size = other.size;
	this->renderer = other.renderer;
}

FontText::FontText(FontText&& other) noexcept
{
	this->font = other.font;
	this->filepath = other.filepath;
	this->size = other.size;
	this->renderer = other.renderer;

	other.font = nullptr;
	other.filepath = "";
	other.size = NULL;
	other.renderer = nullptr;
}

void FontText::operator=(const FontText& other)
{
	if (this == &other)
	{
		ErrorHandler::PopupAndExit("ALLOCATION ERROR", "FontText object tried to copy itself.", -1);
	}

	TTF_CloseFont(font);

	this->font = TTF_OpenFont(other.filepath.c_str(), other.size);
	if (font == nullptr)
	{
		ErrorHandler::PopupAndExit("FONT ERROR", TTF_GetError(), -1);
	}

	this->filepath = other.filepath;
	this->size = other.size;
	this->renderer = other.renderer;
}

void FontText::operator=(FontText&& other) noexcept
{
	if (this == &other)
	{
		ErrorHandler::PopupAndExit("ALLOCATION ERROR", "FontText object tried to move itself.", -1);
	}

	TTF_CloseFont(font);

	this->font = other.font;
	this->filepath = other.filepath;
	this->size = other.size;
	this->renderer = other.renderer;

	other.font = nullptr;
	other.filepath = "";
	other.size = NULL;
	other.renderer = nullptr;
}

FontText::~FontText()
{
	if (font != nullptr)
	{
		TTF_CloseFont(font);
	}
}

void FontText::Draw(const std::string& text, const int& x, const int& y, const SDL_Color& colour, const bool& centered)
{
	SDL_Surface* temporary = TTF_RenderText_Blended(font, text.c_str(), colour);
	if (temporary == nullptr)
	{
		ErrorHandler::PopupAndExit("FONT ERROR", TTF_GetError(), -1);
	}

	SDL_Texture* renderable = SDL_CreateTextureFromSurface(renderer->GetSdlRenderer(), temporary);
	if (renderable == nullptr)
	{
		ErrorHandler::PopupAndExit("FONT ERROR", TTF_GetError(), -1);
	}

	renderer->DrawTexture(renderable, x, y, 1, centered);

	SDL_FreeSurface(temporary);
	SDL_DestroyTexture(renderable);
}

SDL_Texture* FontText::RenderText(const std::string& text, const SDL_Color& colour)
{
	SDL_Surface* temporary = TTF_RenderText_Blended(font, text.c_str(), colour);
	if (temporary == nullptr)
	{
		ErrorHandler::PopupAndExit("FONT ERROR", TTF_GetError(), -1);
	}

	SDL_Texture* renderable = SDL_CreateTextureFromSurface(renderer->GetSdlRenderer(), temporary);
	if (renderable == nullptr)
	{
		ErrorHandler::PopupAndExit("FONT ERROR", TTF_GetError(), -1);
	}

	SDL_FreeSurface(temporary);

	return renderable;
}

TTF_Font* FontText::GetFont()
{
	return font;
}

std::string FontText::GetFilepath()
{
	return filepath;  
}

int FontText::GetSize()
{
	return size;
}

MyRenderer* FontText::GetRenderer()
{
	return renderer;
}