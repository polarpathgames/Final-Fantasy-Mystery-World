#include "j1App.h"
#include "j1Render.h"
#include "EntityManager.h"
#include "j1Textures.h"
#include "Entity.h"
#include "j1Audio.h"
#include "j1Window.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "Player.h"
#include "Enemy.h"



EntityManager::EntityManager() : j1Module()
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


	return ret;
}

bool EntityManager::Start()
{
	bool ret = true;


	texture.push_back(App->tex->Load("textures/Animist.png"));
	texture.push_back(App->tex->Load("textures/Animist2.png"));

	return ret;
}

bool EntityManager::PreUpdate()
{
	
	std::vector<Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			if ((*item)->has_turn) {
				(*item)->PreUpdate();
			}
		}
	}
	
	return true;
}

// Called before render is available
bool EntityManager::Update(float dt)
{
	std::vector<Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
				(*item)->Update(dt);

	}
	item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			if ((*item)->type == Entity::EntityType::PLAYER)
				(*item)->Draw(texture[0], dt);
			else if((*item)->type == Entity::EntityType::ENEMY)
				(*item)->Draw(texture[1], dt);
		}
	}
	
	return true;
}

bool EntityManager::PostUpdate()
{
	std::vector<Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
				(*item)->PostUpdate();

	}
	return true;
}


// Called before quitting
bool EntityManager::CleanUp()
{
	std::vector<Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			//entities.erase(item);
		}
	}
	entities.clear();
	for (int i = 0; i < texture.size(); ++i) {
		App->tex->UnLoad(texture[i]);
	}
	return true;
}


//Entity Factory
Entity* EntityManager::CreateEntity(Entity::EntityType type, int PositionX, int PositionY, std::string name)
{
	static_assert(Entity::EntityType::NO_TYPE == (Entity::EntityType)2, "code needs update");
	Entity* ret = nullptr;
	switch (type) {
	case Entity::EntityType::PLAYER: ret = new Player(PositionX, PositionY); break;
	case Entity::EntityType::ENEMY: ret = new Enemy(PositionX, PositionY); break;
	//case Entity::EntityType::NPC: ret = new ent_NPC(PositionX, PositionY, name); break;
	default:
		LOG("Cannot find any entity with that type");
		break;
	}
	if (ret != nullptr) {
		entities.push_back(ret);
		//ret->Start();
	}

	return ret;
}

//Player * EntityManager::CreatePlayer()
//{
//	Player* ret = nullptr;
//
//	ret = new Player();
//	ret->type = Entity::EntityType::PLAYER;
//	ret->has_turn = true;
//	if (ret != nullptr)
//		entities.push_back(ret);
//
//	return ret;
//}
//
//Enemy * EntityManager::CreateEnemy()
//{
//	Enemy* ret = nullptr;
//
//	ret = new Enemy();
//	ret->type = Entity::EntityType::ENEMY;
//	ret->has_turn = false;
//	if (ret != nullptr)
//		entities.push_back(ret);
//
//	return ret;
//}

void EntityManager::DeleteEntities()
{

	std::vector<Entity*>::iterator item = entities.begin();
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

Player* EntityManager::GetPlayerData() const {

	std::vector<Entity*>::const_iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
		{
			if ((*item)->type == Entity::EntityType::PLAYER)
				return (Player*)(*item);
		}
	}

	return nullptr;
}

const std::vector<Entity*> EntityManager::GetEntities()
{
	return entities;
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






