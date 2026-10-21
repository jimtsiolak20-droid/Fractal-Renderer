#pragma once

#include <SDL.h>

class ErrorHandler
{
public:
	ErrorHandler() = delete;

	static void PopupAndExit(const char* title, const char* message, const int& exitcode);
};