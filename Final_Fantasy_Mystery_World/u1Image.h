#ifndef _u1Image_H__ 
#define _u1Image_H__

#include "u1UI_Element.h"


class u1Image : public u1GUI
{
public:
	u1Image() : u1GUI(IMAGE, 0, 0, nullptr, { 0,0,0,0 },false,false,false) {}
	u1Image(const int& pos_x,const int& pos_y, const SDL_Rect &image, u1GUI* parent, bool draw = true, bool inter = true, bool drag = false, bool focus = false, Animation* anim = nullptr, SDL_Rect* clip_zone = NULL);
	~u1Image();

	void InnerDraw();

	void SetClipZone(const SDL_Rect& clip_zone);
	void ResetClipZone();

public:

	Animation * img_anim = nullptr;
	SDL_Rect* clip_zone = NULL;

private:

	bool new_clip = false;

};
#endif //_u1Image_H__
