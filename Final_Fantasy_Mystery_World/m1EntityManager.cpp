#include "j1App.h"
#include "j1Render.h"
#include "j1EntityManager.h"
#include "j1Textures.h"
#include "Entity.h"
#include "j1Audio.h"
#include "j1Window.h"
#include "Sensor.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "Player.h"
#include "Enemy.h"
#include <algorithm>
#include "Brofiler/Brofiler.h"


j1EntityManager::j1EntityManager() : j1Module()
{
	name.assign("entity_manager");


}

// Destructor
j1EntityManager::~j1EntityManager()
{

}

bool j1EntityManager::Awake(pugi::xml_node& config)
{
	bool ret = true;


	return ret;
}

bool j1EntityManager::Start()
{
	bool ret = true;


	texture.push_back(App->tex->Load("assets/sprites/WarriorSpritesheet.png"));
	texture.push_back(App->tex->Load("assets/sprites/Enemy.png"));
	texture.push_back(App->tex->Load("maps/static_objects_tileset.png"));

	return ret;
}

bool j1EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateEntityM", Profiler::Color::Orange);
	
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
bool j1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntityM", Profiler::Color::Aqua);

	std::vector<Entity*> draw_entities;
	std::vector<Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->Update(dt);
			
			if (App->render->IsOnCamera((*item)->position.x, (*item)->position.y, (*item)->size.x, (*item)->size.y)) {
				draw_entities.push_back(*item);
			}
		}

	}

	std::sort(draw_entities.begin(), draw_entities.end(), j1EntityManager::SortByYPos);

	for (std::vector<Entity*>::iterator item = draw_entities.begin(); item != draw_entities.end(); ++item) {
		if ((*item) != nullptr) {
			if ((*item)->type == Entity::EntityType::PLAYER)
				(*item)->Draw(texture[0], dt);
			else if ((*item)->type == Entity::EntityType::ENEMY)
				(*item)->Draw(texture[1], dt);
			else if ((*item)->type == Entity::EntityType::STATIC)
				(*item)->Draw(texture[2], dt);

			App->render->DrawCircle((*item)->position.x + (*item)->pivot.x, (*item)->position.y + (*item)->pivot.y, 3, 255, 255, 255);
		}		
	}
	if (App->scene->player->movement_type == Movement_Type::InLobby && App->scene->player != nullptr)
		App->render->LobbyCamera(App->scene->player->position);
	return true;
}

bool j1EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateEntity", Profiler::Color::Purple);

	std::vector<Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
				(*item)->PostUpdate();

	}
	return true;
}


// Called before quitting
bool j1EntityManager::CleanUp()
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
	App->scene->player = nullptr;
	for (std::vector<SDL_Texture*>::iterator item_tx = texture.begin(); item_tx != texture.end(); ++item_tx) {
		App->tex->UnLoad(*item_tx);
	}
	texture.clear();

	return true;
}

void j1EntityManager::OnCollision(Collider * c1, Collider * c2)
{
	std::vector<Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr &&(*item)->GetCollider() == c1) {
			(*item)->OnCollision(c2);
		}
	}

}


//Entity Factory
Entity* j1EntityManager::CreateEntity(Entity::EntityType type, int PositionX, int PositionY, std::string name, Sensor::SensorType sensor_type)
{
	static_assert(Entity::EntityType::NO_TYPE == (Entity::EntityType)4, "code needs update");
	Entity* ret = nullptr;
	switch (type) {
	case Entity::EntityType::PLAYER: ret = new Player(PositionX, PositionY); break;
	case Entity::EntityType::ENEMY: ret = new Enemy(PositionX, PositionY); break;
	case Entity::EntityType::SENSOR: ret = new Sensor(PositionX, PositionY, sensor_type); break;
	case Entity::EntityType::STATIC: ret = new StaticEntity(PositionX, PositionY, name.data()); break;
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

void j1EntityManager::DeleteEntities()
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
	App->scene->player = nullptr;

}

void j1EntityManager::DeleteEntitiesNoPlayer()
{

	std::vector<Entity*>::iterator item = entities.begin();
	while (item != entities.end()) {
		if ((*item) != nullptr && (*item)->type != Entity::EntityType::PLAYER) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			item = entities.erase(item);
		}
		else 
			++item;
	}


}

void j1EntityManager::DeleteEntity(Entity* entity_to_delete)
{

	std::vector<Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item) == entity_to_delete) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			//entities.erase(item);
		}
	}


}

const std::vector<Entity*> j1EntityManager::GetEntities()
{
	return entities;
}

bool j1EntityManager::SortByYPos(const Entity * ent1, const Entity * ent2)
{
	return ent1->pivot.y + ent1->position.y < ent2->pivot.y + ent2->position.y;
}

bool j1EntityManager::Load(pugi::xml_node& load)
{
	bool ret = true;

	
	return ret;
}

bool j1EntityManager::Save(pugi::xml_node& save) const
{
	bool ret = true;
	
	return ret;
}






