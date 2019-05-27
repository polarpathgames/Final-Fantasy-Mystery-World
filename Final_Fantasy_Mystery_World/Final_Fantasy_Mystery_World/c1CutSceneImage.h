#ifndef _C1CUTSCENEIMAGE_H_
#define _C1CUTSCENEIMAGE_H_

#include "c1CutsceneElement.h"

class SDL_Rect;
class u1Image;

class c1CutsceneImage :public c1CutsceneElement
{
public:
	c1CutsceneImage(int pos_x, int pos_y, SDL_Rect rect, bool image);
	~c1CutsceneImage();

	void ChangeState(bool active);

private:
	u1Image * image = nullptr;
};


#endif // !_CUTSCENE_IMAGE_H_

