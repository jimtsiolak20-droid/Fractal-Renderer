#include "BoxCollider.h"

BoxCollider::BoxCollider(const int& x, const int& y, const int& w, const int& h, const bool& centered)
{
	this->width = w;
	this->height = h;
	this->centered = centered;
	this->xPos = x - w / 2 * centered;
	this->yPos = y - h / 2 * centered;
}

void BoxCollider::operator=(const BoxCollider& other)
{
	if (this == &other)
	{
		ErrorHandler::PopupAndExit("ALLOCATION ERROR", "BoxCollider object tried to copy itself.", -1);
	}

	this->xPos = other.xPos;
	this->yPos = other.yPos;
	this->width = other.width;
	this->height = other.height;
	this->centered = other.centered;
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Fix(MyWindow* window)
{
	if (xPos > window->GetWidth() || yPos > window->GetHeight())
	{
		xPos = 0;
		yPos = 0;
		width = 0;
		height = 0;
	}

	if (xPos < 0)
	{
		width += xPos;
		xPos = 0;
	}

	if (yPos < 0)
	{
		height += yPos;
		yPos = 0;
	}

	if (width < 0)
	{
		width = 0;
	}

	if (height < 0)
	{
		height = 0;
	}

	if (xPos + width > window->GetWidth())
	{
		width = window->GetWidth() - xPos;
	}

	if (yPos + height > window->GetHeight())
	{
		height = window->GetHeight() - yPos;
	}
}

bool BoxCollider::IsMouseOn(Keymouse& events)
{
	float clickX = (float)events.MouseX();
	float clickY = (float)events.MouseY();

	if (clickX >= xPos && clickX <= xPos + width && clickY >= yPos && clickY <= yPos + height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BoxCollider::CollidesWith(const BoxCollider& other)
{
	int otherX = other.xPos;
	int otherY = other.yPos;
	int otherW = other.width;
	int otherH = other.height;

	if (xPos + width >= otherX && otherX + otherW >= xPos && yPos + height >= otherY && otherY + otherH >= yPos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int BoxCollider::GetX()
{
	return xPos;
}

int BoxCollider::GetY()
{
	return yPos;
}

int BoxCollider::GetWidth()
{
	return width;
}

int BoxCollider::GetHeight()
{
	return height;
}

bool BoxCollider::isCentered()
{
	return centered;
}