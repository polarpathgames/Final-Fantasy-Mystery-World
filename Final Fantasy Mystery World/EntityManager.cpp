#include "j1App.h"
#include "j1Render.h"
#include "EntityManager.h"
#include "j1Textures.h"
#include "DynamicEntity.h"
#include "j1Audio.h"
#include "j1Window.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "Player.h"



EntityManager::EntityManager()
{
	name.assign("entity_manager");
	

}

// Destructor
EntityManager::~EntityManager()
{

}

bool EntityManager::Awake(pugi::xml_node& config)
{
	bool ret = true;
	std::list<DynamicEntity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) 
			(*item)->Awake(config);
	}

	return ret;
}

bool EntityManager::Start()
{
	bool ret = true;

	std::list<DynamicEntity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
			(*item)->Start();
	}

	texture = App->tex->Load("textures/characters.png");

	return ret;
}

bool EntityManager::PreUpdate()
{
	
	std::list<DynamicEntity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
			(*item)->PreUpdate();
	}
	

	return true;
}

// Called before render is available
bool EntityManager::Update(float dt)
{
	std::list<DynamicEntity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
			(*item)->Update(dt);
	}
	std::list<DynamicEntity*>::iterator item2 = entities.begin();
	for (; item2 != entities.end(); ++item2) {
		if ((*item2) != nullptr)
			(*item2)->Draw(texture, dt);
	}
	
	return true;
}

bool EntityManager::PostUpdate()
{
	std::list<DynamicEntity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
			(*item)->PostUpdate();
	}
	return true;
}


// Called before quitting
bool EntityManager::CleanUp()
{
	std::list<DynamicEntity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			//entities.erase(item);
		}
	}
	entities.clear();
	App->tex->UnLoad(texture);
	return true;
}




Player * EntityManager::CreatePlayer()
{
	Player* ret = nullptr;

	ret = new Player();
	ret->type = PLAYER;
	if (ret != nullptr)
		entities.push_back(ret);

	return ret;
}

void EntityManager::DeleteEntities()
{

	std::list<DynamicEntity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			//entities.erase(item);
		}
	}
	entities.clear();


}



bool EntityManager::Load(pugi::xml_node& load)
{
	bool ret = true;

	
	return ret;
}

bool EntityManager::Save(pugi::xml_node& save) const
{
	bool ret = true;
	
	return ret;
}






