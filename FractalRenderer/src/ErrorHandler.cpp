#include "ErrorHandler.h"

void ErrorHandler::PopupAndExit(const char* title, const char* message, const int& exitcode)
{
	SDL_Quit();
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
	exit(exitcode);
}