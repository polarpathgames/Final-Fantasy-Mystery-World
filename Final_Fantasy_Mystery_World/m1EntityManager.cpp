#include "App.h"
#include "m1Render.h"
#include "m1EntityManager.h"
#include "m1Textures.h"
#include "e1Entity.h"
#include "m1Audio.h"
#include "e1StrangeFrog.h"
#include "e1Drop.h"
#include "m1Window.h"
#include "e1StaticEntity.h"
#include "e1Mage.h"
#include "e1Archer.h"
#include "p2Log.h"
#include "e1BlueSlime.h"
#include "e1BlueDog.h"
#include "m1Map.h"
#include "e1CarnivorousPlant.h"
#include "e1NPC.h"
#include "e1ShopKeeperDaughter.h"
#include "e1Rock.h"
#include "m1Scene.h"
#include "e1Particles.h"
#include "e1Player.h"
#include "e1Warrior.h"
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
	
	return ret;
}

bool m1EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateEntityM", Profiler::Color::Orange);
	
	std::vector<e1Entity*>::iterator item = entities.begin();
	while (item != entities.end()) {
		if ((*item) != nullptr && (*item)->to_delete) {
			delete (*item);
			(*item) = nullptr;
			item = entities.erase(item);
		}
		else
			++item;
	}

	item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->has_turn) {
			(*item)->PreUpdate();
		}
	}
	
	item = entities_to_create.begin();
	for (; item != entities_to_create.end(); ++item) {
		entities.push_back(*item);
	}
	entities_to_create.clear();

	return true;
}

// Called before render is available
bool m1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntityM", Profiler::Color::Aqua);

	std::vector<e1Entity*> draw_entities;

	UpdateEntities(dt, draw_entities);
	entities_drawn = draw_entities.size();
	SortEntities(draw_entities);
	DrawEntities(draw_entities, dt);

	if (App->scene->player != nullptr)
		App->render->SmoothCamera(App->scene->player->position);

	return true;
}

void m1EntityManager::SortEntities(std::vector<e1Entity *> &entities_to_sort)
{
	BROFILER_CATEGORY("Sort TO Draw Entities", Profiler::Color::Aqua);
	std::sort(entities_to_sort.begin(), entities_to_sort.end(), m1EntityManager::SortByYPos);
}

void m1EntityManager::SortAllEntities()
{
	BROFILER_CATEGORY("Sort All Entities", Profiler::Color::Aqua);
	std::sort(entities.begin(), entities.end(), m1EntityManager::SortByYPos);
}

void m1EntityManager::DrawEntities(std::vector<e1Entity *> &draw_entities, float dt)
{
	BROFILER_CATEGORY("DrawEntities", Profiler::Color::Aqua);

	for (std::vector<e1Entity*>::iterator item = draw_entities.begin(); item != draw_entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->Draw(dt);

			if (App->debug)
				App->render->DrawCircle((*item)->position.x + (*item)->pivot.x, (*item)->position.y + (*item)->pivot.y, 3, 255, 255, 255);
		}
	}
}

void m1EntityManager::UpdateEntities(float dt, std::vector<e1Entity *> &draw_entities)
{
	BROFILER_CATEGORY("UpdateEntities", Profiler::Color::Aqua);

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->Update(dt);

			if (App->render->IsOnCamera((*item)->position.x, (*item)->position.y, (*item)->size.x, (*item)->size.y)) {
				draw_entities.push_back(*item);
			}
		}

	}
}

bool m1EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateEntity", Profiler::Color::Purple);

	/*std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr)
				(*item)->PostUpdate();

	}*/
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
		}
	}
	entities.clear();
	App->scene->player = nullptr;

	for (std::vector<SDL_Texture*>::iterator item_tx = texture.begin(); item_tx != texture.end(); ++item_tx) {
		App->tex->UnLoad(*item_tx);
		*item_tx = nullptr;
	}
	texture.clear();

	return true;
}

void m1EntityManager::OnCollision(Collider * c1, Collider * c2)
{
	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->GetCollider() == c1) {
			(*item)->OnCollision(c2);
		}
	}

}

void m1EntityManager::OnCollisionEnter(Collider * c1, Collider * c2)
{
	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->GetCollider() == c1) {
			(*item)->OnCollisionEnter(c2);
		}
	}
}

void m1EntityManager::OnCollisionExit(Collider * c1, Collider * c2)
{
	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->GetCollider() == c1) {
			(*item)->OnCollisionExit(c2);
		}
	}
}


//e1Entity Factory
e1Entity* m1EntityManager::CreateEntity(e1Entity::EntityType type, int PositionX, int PositionY, std::string name)
{

	static_assert(e1Entity::EntityType::NO_TYPE == (e1Entity::EntityType)15, "code needs update");
	e1Entity* ret = nullptr;
	switch (type) {

	//case e1Entity::EntityType::PLAYER: ret = DBG_NEW e1Player(PositionX, PositionY); break;
	case e1Entity::EntityType::ENEMY: ret = DBG_NEW e1Enemy(PositionX, PositionY); break;
	case e1Entity::EntityType::STATIC: ret = DBG_NEW e1StaticEntity(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::ROCK: ret = DBG_NEW e1Rock(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::DROP: ret = DBG_NEW e1Drop(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::CARNIVOROUS_PLANT: ret = DBG_NEW e1CarnivorousPlant(PositionX, PositionY); break;
	case e1Entity::EntityType::BLUE_DOG: ret = DBG_NEW e1BlueDog(PositionX, PositionY); break;
	case e1Entity::EntityType::BLUE_SLIME: ret = DBG_NEW e1BlueSlime(PositionX, PositionY); break;
	case e1Entity::EntityType::WARRIOR: ret = DBG_NEW e1Warrior(PositionX, PositionY); break;
	case e1Entity::EntityType::ARCHER: ret = DBG_NEW e1Archer(PositionX, PositionY); break;
	case e1Entity::EntityType::MAGE: ret = DBG_NEW e1Mage(PositionX, PositionY); break;
	case e1Entity::EntityType::STRANGE_FROG: ret = DBG_NEW e1StrangeFrog(PositionX, PositionY); break;
	case e1Entity::EntityType::PARTICLE: ret = DBG_NEW e1Particles(PositionX, PositionY); break;
	//case e1Entity::EntityType::NPC: ret = new ent_NPC(PositionX, PositionY, name); break;
	case e1Entity::EntityType::NPC: ret = DBG_NEW e1NPC(PositionX, PositionY); break;
	case e1Entity::EntityType::DAUGHTER: ret = DBG_NEW e1ShopKeeperDaughter(PositionX, PositionY); break;
	default:
		LOG("Cannot find any entity with that type");
		break;
	}
	if (ret != nullptr) {
		entities_to_create.push_back(ret);
		//ret->Start();
	}

	return ret;
}

void m1EntityManager::DeleteEntities()
{

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			delete *item;
			*item = nullptr;
		}
	}
	entities.clear();
	App->scene->player = nullptr;

}

void m1EntityManager::DeleteEntitiesNoPlayer()
{

	std::vector<e1Entity*>::iterator item = entities.begin();
	while (item != entities.end()) {
		if ((*item) != nullptr && (*item)->type != e1Entity::EntityType::PLAYER) {
			(*item)->CleanUp();
			delete *item;
			*item = nullptr;
			item = entities.erase(item);
		}
		else
			++item;
	}

}

void m1EntityManager::DeleteEntity(e1Entity* entity_to_delete)
{

	std::vector<e1Entity*>::iterator item = entities.begin();

	while (item != entities.end()) {
		if ((*item) != nullptr && (*item) == entity_to_delete) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
			item = entities.erase(item);
			break;
		}
		else
			++item;
	}



}

const std::vector<e1Entity*> m1EntityManager::GetEntities()
{
	return entities;
}

const std::vector<SDL_Texture*> m1EntityManager::GetTextures()
{
	return texture;
}

bool m1EntityManager::SortByYPos(const e1Entity * ent1, const e1Entity * ent2)
{
	return ent1->pivot.y + ent1->position.y < ent2->pivot.y + ent2->position.y;
}

bool m1EntityManager::Load(pugi::xml_node& load)
{
	bool ret = true;
	App->scene->CreateEntitiesFromXML(load);
	std::vector<e1Entity*>::const_iterator item = entities_to_create.cbegin();
	for (; item != entities.cend(); ++item)
	{
		if ((*item)->type == e1Entity::EntityType::MAGE || (*item)->type == e1Entity::EntityType::ARCHER || (*item)->type == e1Entity::EntityType::WARRIOR || (*item)->type == e1Entity::EntityType::PLAYER)
		{
			(*item)->Load(load);
			break;
		}
	}
	App->scene->CreateHUD();
	App->scene->ShowHUD(false);
	App->scene->player->actual_tile.x += 1;
	App->scene->player->actual_tile.y += 1;
	App->scene->player->CenterOnTile();
	
	return ret;
}

bool m1EntityManager::Save(pugi::xml_node& save) const
{
	bool ret = true;
	std::vector<e1Entity*>::const_iterator item = entities.cbegin();
	for (; item != entities.cend(); ++item)
	{
		if ((*item)->type == e1Entity::EntityType::MAGE || (*item)->type == e1Entity::EntityType::ARCHER || (*item)->type == e1Entity::EntityType::WARRIOR || (*item)->type == e1Entity::EntityType::PLAYER)
		{
			(*item)->Save(save);
			break;
		}
	}

	return ret;
}

bool m1EntityManager::ThereAreEnemies()
{
	bool ret = false;

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item)
	{
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY) {
			ret = true;
			break;
		}			
	}
	return ret;
}

bool m1EntityManager::ThereIsEntity(e1Entity::EntityType type)
{
	bool ret = false;

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item)
	{
		if ((*item) != nullptr && (*item)->type == type) {
			ret = true;
			break;
		}
	}
	return ret;
}