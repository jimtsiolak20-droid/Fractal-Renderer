#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include "MyRenderer.h"
#include "ErrorHandler.h"

class Spritesheet
{
public:
	Spritesheet() = default;
	Spritesheet(const std::string& filepath, MyRenderer* renderer, const int& frame_width, const int& frame_height);
	Spritesheet(const Spritesheet& other);
	Spritesheet(Spritesheet&& other) noexcept;
	void operator=(const Spritesheet& other);
	void operator=(Spritesheet&& other) noexcept;
	~Spritesheet();

	void Draw(const int& frame_x, const int& frame_y, const int& x, const int& y, const double& scale, const bool& centered);
	SDL_Texture* GetSprite(const int& frame_x, const int& frame_y); // not responsible for deleting

	SDL_Texture* GetTexture();
	std::string GetFilepath();
	int GetWidth();
	int GetHeight();
	MyRenderer* GetRenderer();
private:
	SDL_Texture* spritesheet;
	std::string filepath;
	MyRenderer* renderer;
	int frame_width;
	int frame_height;
};

class SimpleTexture
{
public:
	SimpleTexture() = default;
	SimpleTexture(SDL_Texture* texture, MyRenderer* renderer);
	SimpleTexture(const SimpleTexture& other);
	SimpleTexture(SimpleTexture&& other) noexcept;
	void operator=(const SimpleTexture& other);
	void operator=(SimpleTexture&& other) noexcept;
	~SimpleTexture();

	void Draw(const int& x, const int& y, const double& scale, const bool& centered);

	SDL_Texture* GetTexture();
	MyRenderer* GetRenderer();
private:
	SDL_Texture* texture;
	MyRenderer* renderer;
};