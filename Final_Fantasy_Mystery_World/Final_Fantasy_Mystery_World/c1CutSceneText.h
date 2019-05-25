#ifndef _C1CUTSCENETEXT_H_
#define _C1CUTSCENETEXT_H_

#include "c1CutsceneElement.h"
#include "p2Defs.h"

class u1Label;

class c1CutsceneText :public c1CutsceneElement {
public:
	c1CutsceneText(int pos_x, int pos_y, std::string text, uint size, bool image);
	~c1CutsceneText();

	void ChangeState(bool active);

public:
	u1Label * text = nullptr;

};



#endif // !_CUTSCENE_TEXT_H_

