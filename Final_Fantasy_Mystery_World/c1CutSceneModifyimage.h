#ifndef _C1CUTSCENEMODIFYIMAGE_H
#define _C1CUTSCENEMODIFYIMAGE_H

#include "c1CutsceneAction.h"
#include <string>

enum ImageActionType {
	DEFAULT_IMAGE = -1,
	ACTIVATE_IMAGE,
	DEACTIVATE_IMAGE
};

class c1CutsceneImage;


class c1CutsceneModifyImage :public c1CutsceneAction
{
public:
	c1CutsceneModifyImage(uint start, uint duration, std::string name, std::string action);
	~c1CutsceneModifyImage();

	void Execute(float dt);

private:
	c1CutsceneImage * element = nullptr;
	ImageActionType		type = DEFAULT_IMAGE;
	std::string			name;

};

#endif // !_C1CUTSCENEMODIFYIMAGE_H


