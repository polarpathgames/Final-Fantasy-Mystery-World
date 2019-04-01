#include "ChangeControls.h"
#include "GUI.h"
#include "GUI_Label.h"
#include "j1App.h"
#include "j1Scene.h"
#include "j1Input.h"

ChangeControls::ChangeControls(GUI_Label * label, int * code, char ** save_new_char)
{
	this->label = label;
	code_to_change = code;

	text_before = label->GetText();
	save_char = save_new_char;
	label->SetText(TEXT_WAITING_INPUT);

}

ChangeControls::~ChangeControls()
{
	if (label->GetText() == TEXT_WAITING_INPUT || label->GetText() == TEXT_TWO_CONTROLS_SAME) {
		label->SetText(text_before.data());
	}
}

bool ChangeControls::Update()
{
	bool ret = true;

	ret = ChangeControl();


	return ret;
}

bool ChangeControls::ChangeControl()
{
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("F")) {
			SetSaveText("F");
			*code_to_change = SDL_SCANCODE_F;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("Q")) {
			SetSaveText("Q");
			*code_to_change = SDL_SCANCODE_Q;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("W")) {
			SetSaveText("W");
			*code_to_change = SDL_SCANCODE_W;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("E")) {
			SetSaveText("E");
			*code_to_change = SDL_SCANCODE_E;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("R")) {
			SetSaveText("R");
			*code_to_change = SDL_SCANCODE_R;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("T")) {
			SetSaveText("T");
			*code_to_change = SDL_SCANCODE_F;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("Y")) {
			SetSaveText("Y");
			*code_to_change = SDL_SCANCODE_Y;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("U")) {
			SetSaveText("U");
			*code_to_change = SDL_SCANCODE_U;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("I")) {
			SetSaveText("I");
			*code_to_change = SDL_SCANCODE_I;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("O")) {
			SetSaveText("O");
			*code_to_change = SDL_SCANCODE_O;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("P")) {
			SetSaveText("P");
			*code_to_change = SDL_SCANCODE_P;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("A")) {
			SetSaveText("A");
			*code_to_change = SDL_SCANCODE_A;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("S")) {
			SetSaveText("S");
			*code_to_change = SDL_SCANCODE_S;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("D")) {
			SetSaveText("D");
			*code_to_change = SDL_SCANCODE_D;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("G")) {
			SetSaveText("G");
			*code_to_change = SDL_SCANCODE_G;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("H")) {
			SetSaveText("H");
			*code_to_change = SDL_SCANCODE_H;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("J")) {
			SetSaveText("J");
			*code_to_change = SDL_SCANCODE_J;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("K")) {
			SetSaveText("K");
			*code_to_change = SDL_SCANCODE_K;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("L")) {
			SetSaveText("L");
			*code_to_change = SDL_SCANCODE_L;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("Z")) {
			SetSaveText("Z");
			*code_to_change = SDL_SCANCODE_Z;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("X")) {
			SetSaveText("X");
			*code_to_change = SDL_SCANCODE_X;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("C")) {
			SetSaveText("C");
			*code_to_change = SDL_SCANCODE_C;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("V")) {
			SetSaveText("V");
			*code_to_change = SDL_SCANCODE_V;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("B")) {
			SetSaveText("B");
			*code_to_change = SDL_SCANCODE_B;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("N")) {
			SetSaveText("N");
			*code_to_change = SDL_SCANCODE_N;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("M")) {
			SetSaveText("M");
			*code_to_change = SDL_SCANCODE_M;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("1")) {
			SetSaveText("1");
			*code_to_change = SDL_SCANCODE_1;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("2")) {
			SetSaveText("2");
			*code_to_change = SDL_SCANCODE_2;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("3")) {
			SetSaveText("3");
			*code_to_change = SDL_SCANCODE_3;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("4")) {
			SetSaveText("4");
			*code_to_change = SDL_SCANCODE_4;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("5")) {
			SetSaveText("5");
			*code_to_change = SDL_SCANCODE_5;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("6")) {
			SetSaveText("6");
			*code_to_change = SDL_SCANCODE_6;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("7")) {
			SetSaveText("7");
			*code_to_change = SDL_SCANCODE_7;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("8")) {
			SetSaveText("8");
			*code_to_change = SDL_SCANCODE_8;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("9")) {
			SetSaveText("9");
			*code_to_change = SDL_SCANCODE_9;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("0")) {
			SetSaveText("0");
			*code_to_change = SDL_SCANCODE_0;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("LSHIFT")) {
			SetSaveText("LSHIFT");
			*code_to_change = SDL_SCANCODE_LSHIFT;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_RSHIFT) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("RSHIFT")) {
			SetSaveText("RSHIFT");
			*code_to_change = SDL_SCANCODE_RSHIFT;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("SPACE")) {
			SetSaveText("SPACE");
			*code_to_change = SDL_SCANCODE_SPACE;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_RCTRL) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("RCTRL")) {
			SetSaveText("RCTRL");
			*code_to_change = SDL_SCANCODE_RCTRL;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("LCTRL")) {
			SetSaveText("LCTRL");
			*code_to_change = SDL_SCANCODE_LCTRL;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("LALT")) {
			SetSaveText("LALT");
			*code_to_change = SDL_SCANCODE_LALT;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_RALT) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("RALT")) {
			SetSaveText("RALT");
			*code_to_change = SDL_SCANCODE_RALT;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("TAB")) {
			SetSaveText("TAB");
			*code_to_change = SDL_SCANCODE_TAB;
			return false;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_CAPSLOCK) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("CAPSLOCK")) {
			SetSaveText("CAPSLOCK");
			*code_to_change = SDL_SCANCODE_CAPSLOCK;
			return false;
		}
	}	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		if (LookForOtherControlsBeSame("RETURN")) {
			SetSaveText("RETURN");
			*code_to_change = SDL_SCANCODE_RETURN;
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

void ChangeControls::SetSaveText(char * tex)
{
	label->SetText(tex);
	*save_char = tex;
}
