#include "ChangeControls.h"
#include "GUI.h"
#include "GUI_Label.h"
#include "j1App.h"
#include "j1Scene.h"
#include "j1Input.h"

ChangeControls::ChangeControls(GUI_Label * label, int * code)
{
	this->label = label;
	code_to_change = code;

	text_before = label->GetText();



	label->SetText(TEXT_WAITING_INPUT);

}

ChangeControls::~ChangeControls()
{
	if (label->GetText() == TEXT_WAITING_INPUT || label->GetText() == TEXT_TWO_CONTROLS_SAME) {
		label->SetText(text_before.data());
	}
}

bool ChangeControls::Update(float dt)
{
	bool ret = true;

	ret = ChangeControl();


	return ret;
}

bool ChangeControls::ChangeControl()
{
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("F")) {
			label->SetText("F");
			*code_to_change = SDL_SCANCODE_F;
			return false;
		}
	}


	return true;
}

bool ChangeControls::LookForOtherControlsBeSame(const char *control)
{
	bool ret = true;

	std::list<GUI_Label*>::iterator item = App->scene->labels_control.begin();

	for (; item != App->scene->labels_control.end(); ++item) {
		if ((*item)->GetText() == control) {
			label->SetText(TEXT_TWO_CONTROLS_SAME);
			ret = false;
			break;
		}
	}

	return ret;
}
