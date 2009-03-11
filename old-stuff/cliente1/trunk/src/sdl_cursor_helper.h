#ifndef _SDL_CURSOR_HELPER_H
#define _SDL_CURSOR_HELPER_H
#include "SDL.h"

enum Cursor_Id
{
	Cursor_Arrow = 0,
	Cursor_Cruz
};

SDL_Cursor *init_system_cursor(unsigned int cursor_id);

#endif // _SDL_CURSOR_HELPER_H
