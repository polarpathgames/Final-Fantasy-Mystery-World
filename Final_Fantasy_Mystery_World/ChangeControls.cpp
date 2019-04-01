#include "ChangeControls.h"
#include "GUI.h"
#include "GUI_Label.h"
#include "j1Input.h"
#include <conio.h>


ChangeControls::ChangeControls(GUI_Label * label)
{
	this->label = label;

	text_before = label->GetText();

	label->SetText(TEXT_WAITING_INPUT);

}

ChangeControls::~ChangeControls()
{
}

bool ChangeControls::Update(float dt)
{
	bool ret = true;

	SDL_Event event;

	if (SDL_PollEvent(&event) != 0) {
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_F:
			label->SetText("F");
			ret = false;
			break;
		}
	}
	
	/*if (_kbhit() != 0) {
		char 
	}
	*/




	return ret;
}
