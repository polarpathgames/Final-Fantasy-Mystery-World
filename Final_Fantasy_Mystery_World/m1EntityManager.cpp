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

	if (!textures_loaded) {
		texture.reserve((uint)TextureType::NONE);

		static_assert(e1Entity::EntityType::NO_TYPE == (e1Entity::EntityType)14, "add the new texture in the enum and here");


		texture[(uint)TextureType::WARRIOR] = App->tex->Load("assets/sprites/Warrior.png");
		texture[(uint)TextureType::ARCHER] = App->tex->Load("assets/sprites/ArcherSpritesheet.png");
		texture[(uint)TextureType::MAGE] = App->tex->Load("assets/sprites/MageSpritesheet.png");
		texture[(uint)TextureType::CARNIVOROUS_PLANT] = App->tex->Load("assets/sprites/Carnivorous Plant.png");
		texture[(uint)TextureType::STRANGE_FROG] = App->tex->Load("assets/sprites/Frog.png");
		texture[(uint)TextureType::BLUE_DOG] = App->tex->Load("assets/sprites/Dog.png");
		texture[(uint)TextureType::STATIC_ENTITIES] = App->tex->Load("assets/maps/static_objects_tileset.png");
		texture[(uint)TextureType::STATIC_ENTITIES] = App->tex->Load("assets/maps/static_objects_tileset.png");
		texture[(uint)TextureType::PARTICLE] = App->tex->Load("assets/sprites/Particles.png");
		texture[(uint)TextureType::DAUGHTER] = App->tex->Load("assets/sprites/Little_Girl.png");
		textures_loaded = true;
	}
	
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
	DrawEntities(draw_entities, dt);

	if (App->scene->player != nullptr && App->scene->player->movement_type == Movement_Type::InLobby)
		App->render->SmoothCamera(App->scene->player->position);
	else if (App->scene->player != nullptr && App->scene->player->movement_type == Movement_Type::InQuest)
		App->render->SmoothCamera(App->scene->player->position);

	return true;
}

void m1EntityManager::DrawEntities(std::vector<e1Entity *> &draw_entities, float dt)
{
	BROFILER_CATEGORY("Sort&DrawEntities", Profiler::Color::Aqua);

	std::sort(draw_entities.begin(), draw_entities.end(), m1EntityManager::SortByYPos);

	for (std::vector<e1Entity*>::iterator item = draw_entities.begin(); item != draw_entities.end(); ++item) {
		if ((*item) != nullptr) {
			if ((*item)->type == e1Entity::EntityType::PLAYER) {
				switch (App->scene->player_type) {
				case PlayerType::WARRIOR:
					(*item)->Draw(texture[(uint)TextureType::WARRIOR], dt);
					break;
				case PlayerType::ARCHER:
					(*item)->Draw(texture[(uint)TextureType::ARCHER], dt);
					break;
				case PlayerType::MAGE:
					(*item)->Draw(texture[(uint)TextureType::MAGE], dt);
					break;
				}
			}
			else if ((*item)->type == e1Entity::EntityType::ENEMY) {
				e1Enemy *enemy = (e1Enemy*)(*item);
				switch (enemy->enemy_type) {
				case e1Enemy::EnemyType::CARNIVOROUS_PLANT:
					(*item)->Draw(texture[(uint)TextureType::CARNIVOROUS_PLANT], dt);
					break;
				case e1Enemy::EnemyType::BLUE_DOG:
					(*item)->Draw(texture[(uint)TextureType::BLUE_DOG], dt);
					break;
				case e1Enemy::EnemyType::STRANGE_FROG:
					(*item)->Draw(texture[(uint)TextureType::STRANGE_FROG], dt);
					break;
				}
			}
			else if ((*item)->type == e1Entity::EntityType::NPC)
			{
				e1NPC *npc = (e1NPC*)(*item);
				switch (npc->npc_type) {
				case e1NPC::NPCType::DAUGHTER:
					(*item)->Draw(texture[(uint)TextureType::DAUGHTER], dt);
					break;
				}
			}
			else if ((*item)->type == e1Entity::EntityType::STATIC)
				(*item)->Draw(texture[(uint)TextureType::STATIC_ENTITIES], dt);
			else if ((*item)->type == e1Entity::EntityType::PARTICLE)
				(*item)->Draw(texture[(uint)TextureType::PARTICLE], dt);

			App->render->DrawCircle((*item)->position.x + (*item)->pivot.x, (*item)->position.y + (*item)->pivot.y, 3, 255, 255, 255);
		}
	}
}

void m1EntityManager::UpdateEntities(float dt, std::vector<e1Entity *> &draw_entities)
{
	BROFILER_CATEGORY("UpdateEntityM", Profiler::Color::Aqua);

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			LOG("Updating %i", (int)(*item)->type);
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

	static_assert(e1Entity::EntityType::NO_TYPE == (e1Entity::EntityType)14, "code needs update");
	e1Entity* ret = nullptr;
	switch (type) {

	//case e1Entity::EntityType::PLAYER: ret = DBG_NEW e1Player(PositionX, PositionY); break;
	case e1Entity::EntityType::ENEMY: ret = DBG_NEW e1Enemy(PositionX, PositionY); break;
	case e1Entity::EntityType::STATIC: ret = DBG_NEW e1StaticEntity(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::ROCK: ret = DBG_NEW e1Rock(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::DROP: ret = DBG_NEW e1Drop(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::CARNIVOROUS_PLANT: ret = DBG_NEW e1CarnivorousPlant(PositionX, PositionY); break;
	case e1Entity::EntityType::BLUE_DOG: ret = DBG_NEW e1BlueDog(PositionX, PositionY); break;
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

	
	return ret;
}

bool m1EntityManager::Save(pugi::xml_node& save) const
{
	bool ret = true;
	
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