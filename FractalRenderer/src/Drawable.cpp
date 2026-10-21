#include "Drawable.h"

Spritesheet::Spritesheet(const std::string& filepath, MyRenderer* renderer, const int& frame_width, const int& frame_height)
{
	this->filepath = filepath;
	this->renderer = renderer;
	this->frame_width = frame_width;
	this->frame_height = frame_height;

	SDL_Surface* temporary = IMG_Load(filepath.c_str());

	if (temporary == nullptr)
	{
		ErrorHandler::PopupAndExit("TEXTURE ERROR", SDL_GetError(), -1);
	}
	
	spritesheet = SDL_CreateTextureFromSurface(renderer->GetSdlRenderer(), temporary);

	if (spritesheet == nullptr)
	{
		ErrorHandler::PopupAndExit("TEXTURE ERROR", SDL_GetError(), -1);
	}

	SDL_FreeSurface(temporary);
}

Spritesheet::Spritesheet(const Spritesheet& other)
{
	this->filepath = other.filepath;
	this->renderer = other.renderer;
	this->frame_width = other.frame_width;
	this->frame_height = other.frame_height;
	
	SDL_Surface* temporary = IMG_Load(filepath.c_str());

	if (temporary == nullptr)
	{
		ErrorHandler::PopupAndExit("TEXTURE ERROR", SDL_GetError(), -1);
	}

	spritesheet = SDL_CreateTextureFromSurface(renderer->GetSdlRenderer(), temporary);

	if (spritesheet == nullptr)
	{
		ErrorHandler::PopupAndExit("TEXTURE ERROR", SDL_GetError(), -1);
	}

	SDL_FreeSurface(temporary);
}

Spritesheet::Spritesheet(Spritesheet&& other) noexcept
{
	this->spritesheet = other.spritesheet;
	this->filepath = other.filepath;
	this->renderer = other.renderer;
	this->frame_width = other.frame_width;
	this->frame_height = other.frame_height;

	other.spritesheet = nullptr;
	other.filepath = "";
	other.renderer = nullptr;
	other.frame_width = NULL;
	other.frame_height = NULL;
}

void Spritesheet::operator=(const Spritesheet& other)
{
	if (this == &other)
	{
		ErrorHandler::PopupAndExit("ALLOCATION ERROR", "Spritesheet object tried to copy itself.", -1);
	}

	SDL_Surface* temporary = IMG_Load(filepath.c_str());

	if (temporary == nullptr)
	{
		ErrorHandler::PopupAndExit("TEXTURE ERROR", SDL_GetError(), -1);
	}

	spritesheet = SDL_CreateTextureFromSurface(renderer->GetSdlRenderer(), temporary);

	if (spritesheet == nullptr)
	{
		ErrorHandler::PopupAndExit("TEXTURE ERROR", SDL_GetError(), -1);
	}

	SDL_FreeSurface(temporary);

	this->filepath = other.filepath;
	this->renderer = other.renderer;
	this->frame_width = other.frame_width;
	this->frame_height = other.frame_height;
}

void Spritesheet::operator=(Spritesheet&& other) noexcept
{
	if (this == &other)
	{
		ErrorHandler::PopupAndExit("ALLOCATION ERROR", "Spritesheet object tried to move itself.", -1);
	}

	SDL_DestroyTexture(spritesheet);

	this->spritesheet = other.spritesheet;
	this->filepath = other.filepath;
	this->renderer = other.renderer;
	this->frame_width = other.frame_width;
	this->frame_height = other.frame_height;

	other.spritesheet = nullptr;
	other.filepath = "";
	other.renderer = nullptr;
	other.frame_height = NULL;
	other.frame_height = NULL;
}

Spritesheet::~Spritesheet()
{
	SDL_DestroyTexture(spritesheet);
}

void Spritesheet::Draw(const int& frame_x, const int& frame_y, const int& x, const int& y, const double& scale, const bool& centered)
{
	SDL_Texture* temporary = SDL_CreateTexture(renderer->GetSdlRenderer(), SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, frame_width, frame_height);
	SDL_SetTextureBlendMode(temporary, SDL_BLENDMODE_BLEND);

	SDL_Rect clip;
	clip.x = frame_x * frame_width;
	clip.y = frame_y * frame_height;
	clip.w = frame_width;
	clip.h = frame_height;

	SDL_SetRenderTarget(renderer->GetSdlRenderer(), temporary);
	SDL_RenderCopy(renderer->GetSdlRenderer(), spritesheet, &clip, nullptr);
	SDL_SetRenderTarget(renderer->GetSdlRenderer(), nullptr);
	renderer->DrawTexture(temporary, x, y, scale, centered);

	SDL_DestroyTexture(temporary);
}

SDL_Texture* Spritesheet::GetSprite(const int& frame_x, const int& frame_y)
{
	SDL_Texture* sprite = SDL_CreateTexture(renderer->GetSdlRenderer(), SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, frame_width, frame_height);
	SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);

	SDL_Rect clip;
	clip.x = frame_x * frame_width;
	clip.y = frame_y * frame_height;
	clip.w = frame_width;
	clip.h = frame_height;

	SDL_SetRenderTarget(renderer->GetSdlRenderer(), sprite);
	SDL_RenderCopy(renderer->GetSdlRenderer(), spritesheet, &clip, nullptr);
	SDL_SetRenderTarget(renderer->GetSdlRenderer(), nullptr);

	return sprite;
}

SDL_Texture* Spritesheet::GetTexture()
{
	return spritesheet;
}

std::string Spritesheet::GetFilepath()
{
	return filepath;
}

int Spritesheet::GetWidth()
{
	return frame_width;
}

int Spritesheet::GetHeight()
{
	return frame_height;
}

MyRenderer* Spritesheet::GetRenderer()
{
	return renderer;
}






SimpleTexture::SimpleTexture(SDL_Texture* texture, MyRenderer* renderer)
{
	this->texture = texture;
	this->renderer = renderer;
}

SimpleTexture::SimpleTexture(const SimpleTexture& other)
{
	this->renderer = other.renderer;
	
	int w, h;
	SDL_QueryTexture(other.texture, nullptr, nullptr, &w, &h);
	this->texture = SDL_CreateTexture(renderer->GetSdlRenderer(), SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, w, h);

	SDL_SetRenderTarget(renderer->GetSdlRenderer(), texture);
	SDL_RenderCopy(renderer->GetSdlRenderer(), other.texture, nullptr, nullptr);
	SDL_SetRenderTarget(renderer->GetSdlRenderer(), nullptr);

	if (texture == nullptr)
	{
		ErrorHandler::PopupAndExit("TEXTURE ERROR", SDL_GetError(), -1);
	}
}

SimpleTexture::SimpleTexture(SimpleTexture&& other) noexcept
{
	this->renderer = other.renderer;
	this->texture = other.texture;

	other.renderer = nullptr;
	other.texture = nullptr;
}

void SimpleTexture::operator=(const SimpleTexture& other)
{
	if (this == &other)
	{
		ErrorHandler::PopupAndExit("ALLOCATION ERROR", "TextureManager object tried to copy itself.", -1);
	}

	SDL_DestroyTexture(texture);

	this->renderer = other.renderer;

	int w, h;
	SDL_QueryTexture(other.texture, nullptr, nullptr, &w, &h);
	this->texture = SDL_CreateTexture(renderer->GetSdlRenderer(), SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, w, h);

	SDL_SetRenderTarget(renderer->GetSdlRenderer(), texture);
	SDL_RenderCopy(renderer->GetSdlRenderer(), other.texture, nullptr, nullptr);
	SDL_SetRenderTarget(renderer->GetSdlRenderer(), nullptr);

	if (texture == nullptr)
	{
		ErrorHandler::PopupAndExit("TEXTURE ERROR", SDL_GetError(), -1);
	}
}

void SimpleTexture::operator=(SimpleTexture&& other) noexcept
{
	if (this == &other)
	{
		ErrorHandler::PopupAndExit("ALLOCATION ERROR", "TextureManager object tried to move itself.", -1);
	}

	SDL_DestroyTexture(texture);

	this->renderer = other.renderer;
	this->texture = other.texture;

	other.renderer = nullptr;
	other.texture = nullptr;
}

SimpleTexture::~SimpleTexture()
{
	SDL_DestroyTexture(texture);
}

void SimpleTexture::Draw(const int& x, const int& y, const double& scale, const bool& centered)
{
	renderer->DrawTexture(texture, x, y, scale, centered);
}

SDL_Texture* SimpleTexture::GetTexture()
{
	return texture;
}

MyRenderer* SimpleTexture::GetRenderer()
{
	return renderer;
}