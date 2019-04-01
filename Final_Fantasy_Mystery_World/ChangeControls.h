#ifndef __CHANGECONTROLS_H__
#define __CHANGECONTROLS_H__

#include <string>

class GUI_Label;

class ChangeControls {

public:

	ChangeControls(GUI_Label* label);
	~ChangeControls();

	bool Update(float dt);

private:

	GUI_Label * label = nullptr;
	std::string text_before;
	std::string text_after;

};




#endif
