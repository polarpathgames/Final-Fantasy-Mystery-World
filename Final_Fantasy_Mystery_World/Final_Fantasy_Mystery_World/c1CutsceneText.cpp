#include "App.h"
#include "c1CutsceneText.h"
#include "m1GUI.h"
#include "u1Label.h"
#include "m1Fonts.h"

c1CutsceneText::c1CutsceneText(int pos_x, int pos_y, std::string text, uint size, bool image)
{
	this->text = App->gui->AddLabel(pos_x,pos_y,text.data(),App->gui->screen,BLACK,FontType::FF48,nullptr,false);
	this->text->drawable = image;
}

c1CutsceneText::~c1CutsceneText()
{
	App->gui->DeleteUIElement(text);
}

void c1CutsceneText::ChangeState(bool active)
{
	text->drawable = active;
}
