#include "App.h"
#include "p2Defs.h"
#include "u1Image.h"

u1Image::u1Image(const int & pos_x, const int & pos_y, const SDL_Rect & image, u1GUI * parent, bool draw, bool inter, bool drag, bool focus)
	:u1GUI(IMAGE, pos_x, pos_y, parent, image, draw, inter, drag, focus) {}