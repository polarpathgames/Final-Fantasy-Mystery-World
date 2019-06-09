#include "App.h"
#include "m1Cutscene.h"
#include "c1CutsceneModifyImage.h"
#include "c1CutsceneImage.h"
#include "u1Label.h"

c1CutsceneModifyImage::c1CutsceneModifyImage(uint start, uint duration, std::string name, std::string action) :c1CutsceneAction(start, duration)
{
	this->name = name;

	if (action == "activate")
	{
		type = ACTIVATE_IMAGE;
	}
	else if (action == "deactivate")
	{
		type = DEACTIVATE_IMAGE;
	}

}

c1CutsceneModifyImage::~c1CutsceneModifyImage()
{
}

void c1CutsceneModifyImage::Execute(float dt)
{
	element = (c1CutsceneImage*)App->cutscene_manager->elements.find(name)->second;

	switch (type)
	{
	case ACTIVATE_IMAGE:
		element->ChangeState(true);
		break;
	case DEACTIVATE_IMAGE:
		element->ChangeState(false);
		break;
	default:
		break;
	}

}
