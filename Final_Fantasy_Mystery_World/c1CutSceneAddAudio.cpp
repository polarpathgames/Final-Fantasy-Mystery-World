#include "App.h"
#include "m1CutScene.h"
#include "c1CutSceneAddAudio.h"
#include "m1Audio.h"
#include "p2Log.h"

c1CutSceneAddAudio::c1CutSceneAddAudio(uint start, uint duration, std::string name, std::string path) : c1CutsceneAction(start, duration)
{
	names = name;
	paths = path;
	fx = App->audio->LoadFx(paths.c_str());
}
c1CutSceneAddAudio::~c1CutSceneAddAudio()
{
	LOG("DO UNLOAD FX IMPORTANT 19/04/2019 18:02");
}

void c1CutSceneAddAudio::Execute(float dt)
{
	if (strcmp(names.data(), "daughter") == 0)
	{
		App->audio->PlayFx(fx);
	}
}