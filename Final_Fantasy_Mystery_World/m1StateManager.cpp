#include "m1StateManager.h"
#include "App.h"
#include "m1Scene.h"

m1StateManager::m1StateManager()
{
	name.assign("state_manager");
}

m1StateManager::~m1StateManager()
{
}

bool m1StateManager::PostUpdate()
{
	if(App->scene)
	return false;
}
