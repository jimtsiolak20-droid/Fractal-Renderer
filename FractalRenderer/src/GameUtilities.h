#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "FontText.h"
#include "Keymouse.h"
#include "BoxCollider.h"

namespace GameUtils
{
	class SimpleRectClickButton
	{
	public:
		SimpleRectClickButton() = delete;
		SimpleRectClickButton(const SimpleRectClickButton& other) = delete;
		void operator=(const SimpleRectClickButton& other) = delete;

		SimpleRectClickButton(FontText* font, Keymouse* events, MyRenderer* renderer); // not responsible for deleting
		~SimpleRectClickButton();

		void SetPosition(const int& x, const int& y);
		void SetDimensions(const int& width, const int& height);
		void SetButtonColours(const SDL_Color& idleColour, const SDL_Color& hoverColour);
		void SetText(const std::string& text, const SDL_Color& textColour, const double& textSize);

		void Update();
		void Render();

		FontText* GetFont();
		Keymouse* GetEvents();
		MyRenderer* GetRenderer();
		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();
		SDL_Color GetIdleColour();
		SDL_Color GetHoverColour();
		SDL_Color GetTextColour();
		std::string GetText();
		double GetTextSize();
		SDL_Texture* GetRendererdText();
		int GetState();
	private:
		FontText* font;
		Keymouse* events;
		MyRenderer* renderer;
		int xpos;
		int ypos;
		int width;
		int height;
		SDL_Color idleColour;
		SDL_Color hoverColour;
		SDL_Color textColour;
		std::string text;
		double textsize;
		SDL_Texture* rendererdText;
		int state; // 0 = nothing, 1 = hovered, 2 = clicked

		bool mouseButtonDown;
	};
}