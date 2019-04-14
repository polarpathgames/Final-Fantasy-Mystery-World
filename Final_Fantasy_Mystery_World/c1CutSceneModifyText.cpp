#include "App.h"
#include "m1Cutscene.h"
#include "c1CutsceneModifyText.h"
#include "c1CutsceneText.h"
#include "u1Label.h"

c1CutsceneModifyText::c1CutsceneModifyText(uint start, uint duration, std::string name, std::string action, std::string text) :c1CutsceneAction(start, duration)
{
	this->name = name;

	if (action == "activate")
	{
		type = ACTIVATE;
	}
	else if (action == "deactivate")
	{
		type = DEACTIVATE;
	}
	else if (action == "change")
	{
		type = CHANGE;
		this->text = text;
	}
}

c1CutsceneModifyText::~c1CutsceneModifyText()
{
}

void c1CutsceneModifyText::Execute(float dt)
{
	element = (c1CutsceneText*)App->cutscene_manager->elements.find(name)->second;

	switch (type)
	{
	case ACTIVATE:
		element->ChangeState(true);
		break;
	case DEACTIVATE:
		element->ChangeState(false);
		break;
	case CHANGE:
		element->text->SetText(text.data());
		break;
	default:
		break;
	}

}

