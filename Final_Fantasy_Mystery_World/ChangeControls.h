#ifndef __CHANGECONTROLS_H__
#define __CHANGECONTROLS_H__

#define TEXT_WAITING_INPUT "Click the button you want"
#define TEXT_TWO_CONTROLS_SAME "Two controls can't have the same input"

#include <string>


class GUI_Label;

class ChangeControls {

public:

	ChangeControls(GUI_Label* label, int * code, char ** save_new_char, bool controller);
	~ChangeControls();

	bool Update();
	

private:

	bool LookForOtherControlsBeSame(const char *control);
	void SetSaveText(char* tex);
	bool ChangeControl();
	bool ChangingController();
	bool ChangingKeyboard();

	GUI_Label * label = nullptr;
	std::string text_before;
	int * code_to_change = nullptr;
	char ** save_char = nullptr;
	bool is_changing_controller = false;
};




#endif
