#ifndef _C1CUTSCENEELEMENT_H_
#define _C1CUTSCENEELEMENT_H_

#include <string>

class c1CutsceneElement
{
public:
	c1CutsceneElement() {};
	virtual ~c1CutsceneElement() {};

public:
	bool active = false;
	std::string path;
	std::string name;
};




#endif // !_CUTSCENE_ELEMENT_H_


