#include "App.h"
#include "m1CutScene.h"
#include "c1CutSceneAddAudio.h"
#include "m1Audio.h"

c1CutSceneAddAudio::c1CutSceneAddAudio(uint start, uint duration, std::string name, std::string path) : c1CutsceneAction(start, duration)
{
	names = name;
	paths = path;
}
c1CutSceneAddAudio::~c1CutSceneAddAudio()
{

}

void c1CutSceneAddAudio::Execute(float dt)
{
	if (strcmp(names.data(), "daughter") == 0)
	{
		int help = App->audio->LoadFx(paths.c_str());
		App->audio->PlayFx(help);
	}
}