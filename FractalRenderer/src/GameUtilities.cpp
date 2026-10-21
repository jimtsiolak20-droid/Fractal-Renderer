#include "GameUtilities.h"

namespace GameUtils
{
	SimpleRectClickButton::SimpleRectClickButton(FontText* font, Keymouse* events, MyRenderer* renderer)
	{
		this->font = font;
		this->events = events;
		this->renderer = renderer;
		this->xpos = 0;
		this->ypos = 0;
		this->width = 100;
		this->height = 50;
		this->idleColour = { 150, 150, 150, 255 }; 
		this->hoverColour = { 100, 100, 100, 255 };
		this->textColour = { 0, 0, 0, 255 };
		this->text = "hello world";
		this->textsize = 1;
		this->rendererdText = font->RenderText(text, textColour);
		this->state = 0;
		this->mouseButtonDown = true;
	}

	SimpleRectClickButton::~SimpleRectClickButton()
	{
		SDL_DestroyTexture(rendererdText);
	}

	void SimpleRectClickButton::SetPosition(const int& x, const int& y)
	{
		this->xpos = x;
		this->ypos = y;
	}

	void SimpleRectClickButton::SetDimensions(const int& width, const int& height)
	{
		this->width = width;
		this->height = height;
	}

	void SimpleRectClickButton::SetButtonColours(const SDL_Color& idleColour, const SDL_Color& hoverColour)
	{
		this->idleColour = idleColour;
		this->hoverColour = hoverColour;
	}

	void SimpleRectClickButton::SetText(const std::string& text, const SDL_Color& textColour, const double& textSize)
	{
		this->text = text;
		this->textColour = textColour;
		this->textsize = textSize;
		
		if (text != "")
		{
			SDL_DestroyTexture(rendererdText);
			rendererdText = font->RenderText(text, textColour);
		}
	}

	void SimpleRectClickButton::Update()
	{
		BoxCollider collider = BoxCollider(xpos, ypos, width, height, true);
		
		bool registerClick = events->MouseButtonDown() && !mouseButtonDown;
		mouseButtonDown = events->MouseButtonDown();

		if (collider.IsMouseOn(*events))
		{
			if (registerClick)
			{
				state = 2;
			}
			else
			{
				state = 1;
			}
		}
		else
		{
			state = 0;
		}
	}

	void SimpleRectClickButton::Render()
	{
		if (state == 0)
		{
			renderer->DrawRect(xpos, ypos, width, height, idleColour, true);
		}
		else if (state >= 1)
		{
			renderer->DrawRect(xpos, ypos, width, height, hoverColour, true);
		}
		
		if (text != "")
		{
			renderer->DrawTexture(rendererdText, xpos, ypos, textsize, true);
		}
	}

	FontText* SimpleRectClickButton::GetFont()
	{
		return font;
	}

	Keymouse* SimpleRectClickButton::GetEvents()
	{
		return events;
	}

	MyRenderer* SimpleRectClickButton::GetRenderer()
	{
		return renderer;
	}

	int SimpleRectClickButton::GetX()
	{
		return xpos;
	}

	int SimpleRectClickButton::GetY()
	{
		return ypos;
	}

	int SimpleRectClickButton::GetWidth()
	{
		return width;
	}

	int SimpleRectClickButton::GetHeight()
	{
		return height;
	}

	SDL_Color SimpleRectClickButton::GetIdleColour()
	{
		return idleColour;
	}

	SDL_Color SimpleRectClickButton::GetHoverColour()
	{
		return hoverColour;
	}

	SDL_Color SimpleRectClickButton::GetTextColour()
	{
		return textColour;
	}

	std::string SimpleRectClickButton::GetText()
	{
		return text;
	}

	double SimpleRectClickButton::GetTextSize()
	{
		return textsize;
	}

	SDL_Texture* SimpleRectClickButton::GetRendererdText()
	{
		return rendererdText;
	}

	int SimpleRectClickButton::GetState()
	{
		return state;
	}
}