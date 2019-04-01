#include "ChangeControls.h"
#include "GUI.h"
#include "GUI_Label.h"
#include "j1Input.h"
#include <conio.h>


ChangeControls::ChangeControls(GUI_Label * label)
{
	this->label = label;

	text_before = label->GetText();

	label->SetText("Click the button you want");

}

ChangeControls::~ChangeControls()
{
}

bool ChangeControls::Update(float dt)
{
	bool ret = true;
	/*if (_kbhit() != 0) {
		char 
	}
	*/




	return ret;
}
