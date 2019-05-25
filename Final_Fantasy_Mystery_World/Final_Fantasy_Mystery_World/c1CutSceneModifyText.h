#ifndef _C1CUTSCENEMODIFYTEXT_H
#define _C1CUTSCENEMODIFYTEXT_H

#include "c1CutsceneAction.h"
#include <string>

enum ActionType {
	DEFAULT = -1,
	ACTIVATE,
	DEACTIVATE,
	CHANGE
};

class c1CutsceneText;


class c1CutsceneModifyText :public c1CutsceneAction
{
public:
	c1CutsceneModifyText(uint start, uint duration, std::string name, std::string action, std::string text = "");
	~c1CutsceneModifyText();

	void Execute(float dt);

private:
	c1CutsceneText * element = nullptr;
	ActionType			type = DEFAULT;
	std::string			text;
	std::string			name;

};

#endif // !_C1CUTSCENEMODIFYTEXT_H


