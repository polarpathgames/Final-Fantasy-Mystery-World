#include "j1App.h"
#include "j1UIManager.h"
#include "GUI.h"

j1UIManager::j1UIManager(): j1Module()
{
}

j1UIManager::~j1UIManager() {}

bool j1UIManager::Awake(pugi::xml_node &node)
{
	return true;
}

bool j1UIManager::Start()
{

	return true;
}

bool j1UIManager::PreUpdate()
{
	return true;
}

bool j1UIManager::Update(float dt)
{
	return true;
}

bool j1UIManager::PostUpdate()
{

	return true;
}

bool j1UIManager::CleanUp()
{
	return true;
}

const SDL_Texture* j1UIManager::GetAtlas() const
{
	return atlas;
}

//GUI* j1UIManager::AddImage(int x, int y, SDL_Rect* rect)
//{
//
//}


