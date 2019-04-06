#include "App.h"
#include "m1Render.h"
#include "m1EntityManager.h"
#include "m1Textures.h"
#include "e1Entity.h"
#include "m1Audio.h"
#include "m1Window.h"
#include "e1Sensor.h"
#include "p2Log.h"
#include "m1Map.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "e1Enemy.h"
#include <algorithm>
#include "Brofiler/Brofiler.h"


m1EntityManager::m1EntityManager() : m1Module()
{
	name.assign("entity_manager");


}

// Destructor
m1EntityManager::~m1EntityManager()
{

}

bool m1EntityManager::Awake(pugi::xml_node& config)
{
	bool ret = true;


	return ret;
}

bool m1EntityManager::Start()
{
	bool ret = true;


	texture.push_back(app->tex->Load("assets/sprites/WarriorSpritesheet.png"));
	texture.push_back(app->tex->Load("assets/sprites/Enemy.png"));
	texture.push_back(app->tex->Load("maps/static_objects_tileset.png"));

	return ret;
}

bool m1EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateEntityM", Profiler::Color::Orange);
	
	std::vector<e1Entity*>::iterator item = entities.begin();
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
bool m1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntityM", Profiler::Color::Aqua);

	std::vector<e1Entity*> draw_entities;
	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->Update(dt);
			
			if (app->render->IsOnCamera((*item)->position.x, (*item)->position.y, (*item)->size.x, (*item)->size.y)) {
				draw_entities.push_back(*item);
			}
		}

	}

	std::sort(draw_entities.begin(), draw_entities.end(), m1EntityManager::SortByYPos);

	for (std::vector<e1Entity*>::iterator item = draw_entities.begin(); item != draw_entities.end(); ++item) {
		if ((*item) != nullptr) {
			if ((*item)->type == e1Entity::EntityType::PLAYER)
				(*item)->Draw(texture[0], dt);
			else if ((*item)->type == e1Entity::EntityType::ENEMY)
				(*item)->Draw(texture[1], dt);
			else if ((*item)->type == e1Entity::EntityType::STATIC)
				(*item)->Draw(texture[2], dt);

			app->render->DrawCircle((*item)->position.x + (*item)->pivot.x, (*item)->position.y + (*item)->pivot.y, 3, 255, 255, 255);
		}		
	}
	if (app->scene->player->movement_type == Movement_Type::InLobby && app->scene->player != nullptr)
		app->render->LobbyCamera(app->scene->player->position);
	return true;
}

bool m1EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateEntity", Profiler::Color::Purple);

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
				(*item)->PostUpdate();

	}
	return true;
}


// Called before quitting
bool m1EntityManager::CleanUp()
{
	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			//entities.erase(item);
		}
	}
	entities.clear();
	app->scene->player = nullptr;
	for (std::vector<SDL_Texture*>::iterator item_tx = texture.begin(); item_tx != texture.end(); ++item_tx) {
		app->tex->UnLoad(*item_tx);
	}
	texture.clear();

	return true;
}

void m1EntityManager::OnCollision(Collider * c1, Collider * c2)
{
	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr &&(*item)->GetCollider() == c1) {
			(*item)->OnCollision(c2);
		}
	}

}


//e1Entity Factory
e1Entity* m1EntityManager::CreateEntity(e1Entity::EntityType type, int PositionX, int PositionY, std::string name, e1Sensor::SensorType sensor_type)
{
	static_assert(e1Entity::EntityType::NO_TYPE == (e1Entity::EntityType)4, "code needs update");
	e1Entity* ret = nullptr;
	switch (type) {
	case e1Entity::EntityType::PLAYER: ret = new e1Player(PositionX, PositionY); break;
	case e1Entity::EntityType::ENEMY: ret = new e1Enemy(PositionX, PositionY); break;
	case e1Entity::EntityType::SENSOR: ret = new e1Sensor(PositionX, PositionY, sensor_type); break;
	case e1Entity::EntityType::STATIC: ret = new e1StaticEntity(PositionX, PositionY, name.data()); break;
	//case e1Entity::EntityType::NPC: ret = new ent_NPC(PositionX, PositionY, name); break;
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

//e1Player * EntityManager::CreatePlayer()
//{
//	e1Player* ret = nullptr;
//
//	ret = new e1Player();
//	ret->type = e1Entity::EntityType::PLAYER;
//	ret->has_turn = true;
//	if (ret != nullptr)
//		entities.push_back(ret);
//
//	return ret;
//}
//
//e1Enemy * EntityManager::CreateEnemy()
//{
//	e1Enemy* ret = nullptr;
//
//	ret = new e1Enemy();
//	ret->type = e1Entity::EntityType::ENEMY;
//	ret->has_turn = false;
//	if (ret != nullptr)
//		entities.push_back(ret);
//
//	return ret;
//}

void m1EntityManager::DeleteEntities()
{

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			//entities.erase(item);
		}
	}
	entities.clear();
	app->scene->player = nullptr;

}

void m1EntityManager::DeleteEntitiesNoPlayer()
{

	std::vector<e1Entity*>::iterator item = entities.begin();
	while (item != entities.end()) {
		if ((*item) != nullptr && (*item)->type != e1Entity::EntityType::PLAYER) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			item = entities.erase(item);
		}
		else 
			++item;
	}


}

void m1EntityManager::DeleteEntity(e1Entity* entity_to_delete)
{

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item) == entity_to_delete) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			//entities.erase(item);
		}
	}


}

const std::vector<e1Entity*> m1EntityManager::GetEntities()
{
	return entities;
}

bool m1EntityManager::SortByYPos(const e1Entity * ent1, const e1Entity * ent2)
{
	return ent1->pivot.y + ent1->position.y < ent2->pivot.y + ent2->position.y;
}

bool m1EntityManager::Load(pugi::xml_node& load)
{
	bool ret = true;

	
	return ret;
}

bool m1EntityManager::Save(pugi::xml_node& save) const
{
	bool ret = true;
	
	return ret;
}