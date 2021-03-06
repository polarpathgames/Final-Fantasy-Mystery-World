#include "App.h"
#include "m1Render.h"
#include "m1EntityManager.h"
#include "m1Textures.h"
#include "e1Entity.h"
#include "e1Spider.h"
#include "m1Audio.h"
#include "e1Cassio.h"
#include "m1MenuManager.h"
#include "e1StrangeFrog.h"
#include "e1MegaEye.h"
#include "e1Drop.h"
#include "m1Window.h"
#include "e1StaticEntity.h"
#include "e1Mage.h"
#include "e1SuperPurpleFrog.h"
#include "e1Archer.h"
#include "p2Log.h"
#include "e1BlueSlime.h"
#include "e1AmazingDragon.h"
#include "e1BabyDrake.h"
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
#include "e1State.h"
#include "e1Frozen.h"
#include "e1Bomberman.h"
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
	
	// Delete entities to_delete = true
	std::vector<e1Entity*>::iterator item = entities.begin();
	while (item != entities.end()) {
		if ((*item) != nullptr && (*item)->to_delete) {
			if (entity_turn == *item)
				entity_turn = nullptr;
			delete (*item);
			(*item) = nullptr;
			item = entities.erase(item);
		}
		else
			++item;
	}

	// Turn system ============================================================
	if (turns_active) {
		if (entity_turn == nullptr || entity_turn->turn_done) {
			item = std::find(entities.begin(), entities.end(), entity_turn);
			bool changed = false;
			for (; item != entities.end(); ++item) {
				if ((*item) != nullptr && entity_turn != *item && (*item)->allow_turn) {
					changed = true;
					if (entity_turn != nullptr) {
						entity_turn->turn_done = false;
						entity_turn->turn_count++;
					}
					entity_turn = *item;
					break;
				}
			}
			if (!changed) {
				item = entities.begin();
				for (; item != entities.end(); ++item) {
					if ((*item) != nullptr && entity_turn != *item && (*item)->allow_turn) {
						changed = true;
						if (entity_turn != nullptr) {
							entity_turn->turn_done = false;
							entity_turn->turn_count++;
						}
						entity_turn = *item;
						break;
					}
				}
			}
			if (!changed) {
				if (entity_turn != nullptr) {
					entity_turn->turn_done = false;
					entity_turn->turn_count++;
				}
			}
		}
		else {
			entity_turn->PreUpdate();
			item = entities.begin();
			for (; item != entities.end(); ++item) {
				if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY && static_cast<e1DynamicEntity*>(*item)->state != State::WALKING && App->scene->player->turn_done && !(*item)->turn_done && (*item)->allow_turn && !static_cast<e1Enemy*>(*item)->IsPlayerNextTile()) {
					(*item)->PreUpdate();
				}
			}
		}
	}
	

	//====================================================================

	// Create entities
	
	item = entities_to_create.begin();
	for (; item != entities_to_create.end(); ++item) {
		entities.push_back(*item);
	}
	entities_to_create.clear();

	return true;
}

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
	BROFILER_CATEGORY("CreateEntity", Profiler::Color::Blue);
	static_assert(e1Entity::EntityType::NO_TYPE == (e1Entity::EntityType)24, "code needs update");
	e1Entity* ret = nullptr;
	switch (type) {

	//case e1Entity::EntityType::PLAYER: ret = DBG_NEW e1Player(PositionX, PositionY); break;
	case e1Entity::EntityType::ENEMY: ret = DBG_NEW e1Enemy(PositionX, PositionY); break;
	case e1Entity::EntityType::STATIC: ret = DBG_NEW e1StaticEntity(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::ROCK: ret = DBG_NEW e1Rock(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::DROP: ret = DBG_NEW e1Drop(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::CARNIVOROUS_PLANT: ret = DBG_NEW e1CarnivorousPlant(PositionX, PositionY); break;
	case e1Entity::EntityType::BLUE_DOG: ret = DBG_NEW e1BlueDog(PositionX, PositionY); break;
	case e1Entity::EntityType::AMAZING_DRAGON: ret = DBG_NEW e1AmazingDragon(PositionX, PositionY); break;
	case e1Entity::EntityType::BLUE_SLIME: ret = DBG_NEW e1BlueSlime(PositionX, PositionY); break;
	case e1Entity::EntityType::FROZEN: ret = DBG_NEW e1Frozen(PositionX, PositionY); break;
	case e1Entity::EntityType::MEGA_EYE: ret = DBG_NEW e1MegaEye(PositionX, PositionY); break;
	case e1Entity::EntityType::SPIDER: ret = DBG_NEW e1Spider(PositionX, PositionY); break;
	case e1Entity::EntityType::WARRIOR: ret = DBG_NEW e1Warrior(PositionX, PositionY); break;
	case e1Entity::EntityType::ARCHER: ret = DBG_NEW e1Archer(PositionX, PositionY); break;
	case e1Entity::EntityType::MAGE: ret = DBG_NEW e1Mage(PositionX, PositionY); break;
	case e1Entity::EntityType::STRANGE_FROG: ret = DBG_NEW e1StrangeFrog(PositionX, PositionY); break;
	case e1Entity::EntityType::CASSIO: ret = DBG_NEW e1Cassio(PositionX, PositionY); break;
	case e1Entity::EntityType::BABY_DRAKE: ret = DBG_NEW e1BabyDrake(PositionX, PositionY); break;
	case e1Entity::EntityType::SUPER_PURPLE_FROG: ret = DBG_NEW e1SuperPurpleFrog(PositionX, PositionY); break;
	case e1Entity::EntityType::BOMBERMAN: ret = DBG_NEW e1Bomberman(PositionX, PositionY); break;
	case e1Entity::EntityType::PARTICLE: ret = DBG_NEW e1Particles(PositionX, PositionY); break;
	case e1Entity::EntityType::NPC: ret = DBG_NEW e1NPC(PositionX, PositionY, name.data()); break;
	case e1Entity::EntityType::DAUGHTER: ret = DBG_NEW e1ShopKeeperDaughter(PositionX, PositionY); break;
	case e1Entity::EntityType::EVENT: ret = DBG_NEW e1State(PositionX, PositionY, name.data()); break;
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

void m1EntityManager::SpawnRupees(const int & x, const int & y, const int & number, const int & range, const int & gold_per, const int & red_per, const int& blue_per, const int & green_per)
{
	BROFILER_CATEGORY("SpawnRupees", Profiler::Color::BlueViolet);
	e1Drop* drop = nullptr;
	iPoint destination = { 0,0 };
	std::vector<iPoint> positions;
	int random_rupee = 0;
	int gold = 0;

	std::vector<std::pair<int,const char*>> per;
	per.push_back(std::make_pair(gold_per, "gold_rupee"));
	per.push_back(std::make_pair(red_per, "red_rupee"));
	per.push_back(std::make_pair(blue_per, "blue_rupee"));
	per.push_back(std::make_pair(green_per, "green_rupee"));
	std::sort(per.begin(), per.end());
	std::vector<std::pair<int, const char*>>::iterator per_item = per.begin();
	int value = 0;
	while (per_item+1 != per.end()) {
		value = (*per_item).first;
		(*(++per_item)).first += value;
	}
	per_item = per.begin();

	if (FindFreeTileAround({ x,y }, range, &positions))
		for (int i = 0; i < number; ++i) {
			random_rupee = App->random.Generate(1, per.back().first);
			if (IN_RANGE(random_rupee, 0, (*per_item).first)) {
				drop = (e1Drop*)CreateEntity(e1Entity::EntityType::DROP, x, y, (*per_item).second);
			}
			else if (IN_RANGE(random_rupee, (*per_item).first, (*++per_item).first)) {
				drop = (e1Drop*)CreateEntity(e1Entity::EntityType::DROP, x, y, (*per_item).second);
			}
			else if (IN_RANGE(random_rupee, (*per_item).first, (*++per_item).first)) {
				drop = (e1Drop*)CreateEntity(e1Entity::EntityType::DROP, x, y, (*per_item).second);
			}
			else if (IN_RANGE(random_rupee, (*per_item).first, (*++per_item).first)) {
				drop = (e1Drop*)CreateEntity(e1Entity::EntityType::DROP, x, y, (*per_item).second);
			}
			
			if ((*per_item).second == "gold_rupee")
				gold = App->random.Generate(GOLD_RUPEE_YELLOW);
			else if ((*per_item).second == "red_rupee")
				gold = App->random.Generate(GOLD_RUPEE_RED);
			else if ((*per_item).second == "green_rupee")
				gold = App->random.Generate(GOLD_RUPEE_GREEN);
			else if ((*per_item).second == "blue_rupee")
				gold = App->random.Generate(GOLD_RUPEE_BLUE);

			drop->SetGold(gold);
			destination = positions[App->random.Generate(0, positions.size() - 1)];
			std::vector<iPoint>::iterator item = positions.begin();
			for (; item != positions.end(); ++item) {
				if ((*item) == destination) {
					positions.erase(item);
					break;
				}
			}
			drop->moving_pos = drop->actual_tile = destination;
			destination = App->map->MapToWorldCentered(destination.x, destination.y) - drop->pivot;
			App->easing_splines->CreateSpline(&drop->position.x, destination.x + App->map->data.tile_width / 2, 2000, TypeSpline::EASE, std::bind(&e1Drop::FinishSpline, drop));
			App->easing_splines->CreateSpline(&drop->position.y, destination.y - destination.DistanceTo(drop->position)*0.7f,
				1000, TypeSpline::EASE_OUT_CUBIC, std::bind(&e1Drop::SetSplineToFall, drop));
			drop->moving = true;
			if (positions.empty()) break;
			per_item = per.begin();
		}
}

bool m1EntityManager::FindFreeTileAround(const iPoint & tile, const uint & range, std::vector<iPoint> * list_to_fill)
{
	iPoint destination_tile = tile - iPoint{(int)range, (int)range};
	bool ret = false;
	for (uint i = 0; i <= 2 * range; i++) {
		for (uint j = 0; j <= 2 * range; j++) {
			if (destination_tile != tile)
				if (IsWalkable(destination_tile))
					list_to_fill->push_back(destination_tile);
			destination_tile.x++;
		}
		destination_tile.x = tile.x - range;
		destination_tile.y++;
	}
	
	if (!list_to_fill->empty())
		return true;

	return false;
}

iPoint m1EntityManager::FindRandomFreeTileAround(const iPoint & tile, const uint & range)
{
	BROFILER_CATEGORY("FindRandomFreeTileAround", Profiler::Color::Violet);
	iPoint destination_tile = tile - iPoint{ (int)range, (int)range };
	std::vector<iPoint> positions;

	for (uint i = 0; i < 2 * range; i++) {
		for (uint j = 0; j < 2 * range; j++) {
			destination_tile.x++;
			if (destination_tile != tile)
				if (IsWalkable(destination_tile)) {
					positions.push_back(destination_tile);
				}
		}
		destination_tile.x = tile.x - range;
		destination_tile.y++;
	}

	if (positions.size() > 0) {
		return positions[App->random.Generate(0, positions.size() - 1)];
	}

	return tile;
}

iPoint m1EntityManager::FindFirstFreeTileOnRange(const iPoint & tile, const uint & range)
{
	iPoint destination_tile = tile;

	destination_tile.y -= range;
	destination_tile.x -= range;
	for (uint i = 0; i < 2 * range; i++) { //first row
		if (IsWalkable(destination_tile))
			return destination_tile;

		destination_tile.x++;
	}

	destination_tile.y = tile.y + range;
	destination_tile.x = tile.x - range;
	for (uint i = 0; i < 2 * range; i++) { //second row
		if (IsWalkable(destination_tile))
			return destination_tile;

		destination_tile.x++;
	}

	destination_tile.y = tile.y - range;
	destination_tile.x = tile.x - range;
	for (uint i = 0; i < 2 * range; i++) { //first column
		if (IsWalkable(destination_tile))
			return destination_tile;

		destination_tile.y++;
	}

	destination_tile.y = tile.y - range;
	destination_tile.x = tile.x + range;
	for (uint i = 0; i < 2 * range; i++) { //second column
		if (IsWalkable(destination_tile))
			return destination_tile;

		destination_tile.y++;
	}

	//FindFirstFreeTileOnRange(tile,range-1) ===================== recursive

	return tile;
}

iPoint m1EntityManager::FindRandomFreeTileOnRange(const iPoint & tile, const uint & range)
{
	iPoint destination_tile = tile;
	std::vector<iPoint> positions;

	destination_tile.y -= range;
	destination_tile.x -= range;
	for (uint i = 0; i < 2 * range; i++) { //first row
		if (IsWalkable(destination_tile))
			positions.push_back(destination_tile);

		destination_tile.x++;
	}

	destination_tile.y = tile.y + range;
	destination_tile.x = tile.x - range;
	for (uint i = 0; i < 2 * range; i++) { //second row
		if (IsWalkable(destination_tile))
			positions.push_back(destination_tile);

		destination_tile.x++;
	}

	destination_tile.y = tile.y - range;
	destination_tile.x = tile.x - range;
	for (uint i = 0; i < 2 * range; i++) { //first column
		if (IsWalkable(destination_tile))
			positions.push_back(destination_tile);

		destination_tile.y++;
	}

	destination_tile.y = tile.y - range;
	destination_tile.x = tile.x + range;
	for (uint i = 0; i < 2 * range; i++) { //second column
		if (IsWalkable(destination_tile))
			positions.push_back(destination_tile);

		destination_tile.y++;
	}

	if (positions.size() > 0) {
		return positions[App->random.Generate(0, positions.size()-1)];
	}

	return tile;
}

bool m1EntityManager::IsWalkable(const iPoint & destination_tile) {

	for (std::vector<e1Entity*>::iterator item = entities.begin(); item != entities.end(); ++item) {
		if ((*item)->actual_tile == destination_tile) {
			return false;
		}
	}

	return App->map->IsWalkable(destination_tile, false);
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
	for (; item != entities_to_create.cend(); ++item)
	{
		if ((*item)->type == e1Entity::EntityType::MAGE || (*item)->type == e1Entity::EntityType::ARCHER || (*item)->type == e1Entity::EntityType::WARRIOR || (*item)->type == e1Entity::EntityType::PLAYER)
		{
			(*item)->Load(load);
			break;
		}
	}
	App->menu_manager->CreateHUD();
	App->menu_manager->EnableHUD(false);
	App->audio->StopMusic(-4);
	App->scene->player->actual_tile.x += 1;
	App->scene->player->actual_tile.y += 1;
	App->scene->player->CenterOnTile();
	App->globals.Ability3PanelShowed = true;
	
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

bool m1EntityManager::IsInEntitiesVector(e1Entity * entity)
{
	return (std::find(entities.begin(), entities.end(), entity) != entities.end());
}

bool m1EntityManager::ThereIsEntity(const char * name)
{
	bool ret = false;

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item)
	{
		if ((*item) != nullptr && (*item)->name.compare(name) == 0) {
			ret = true;
			break;
		}
	}
	return ret;
}

bool m1EntityManager::CheckForBarrelsAndSnowMan(const iPoint &act_tile, const Direction &direction)
{
	std::vector<e1Entity*>::const_iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr) {
			if ((*item)->type == e1Entity::EntityType::STATIC) {
				bool has_succeeded = false;
				e1StaticEntity* ent = (e1StaticEntity*)*item;
				if (ent->static_type == e1StaticEntity::Type::BREAKABLE_ROCK && (static_cast<e1Rock*>(ent)->rock_type == RockType::BREAKABLE_BARREL || static_cast<e1Rock*>(ent)->rock_type == RockType::BREAKABLE_SNOWMAN)) {
					iPoint origin = act_tile;
					iPoint destination = (*item)->actual_tile;

					switch (direction) {
					case Direction::DOWN:
						origin += {1, 1};
						if (destination == origin)
							has_succeeded = true;
						break;
					case Direction::UP:
						origin += {-1, -1};
						if (destination == origin)
							has_succeeded = true;
						break;
					case Direction::LEFT:
						origin += {-1, 1};
						if (destination == origin)
							has_succeeded = true;
						break;
					case Direction::RIGHT:
						origin += {1, -1};
						if (destination == origin)
							has_succeeded = true;
						break;
					case Direction::DOWN_LEFT:
						origin += {0, 1};
						if (destination == origin)
							has_succeeded = true;
						break;
					case Direction::DOWN_RIGHT:
						origin += {1, 0};
						if (destination == origin)
							has_succeeded = true;
						break;
					case Direction::UP_LEFT:
						origin += {-1, 0};
						if (destination == origin)
							has_succeeded = true;
						break;
					case Direction::UP_RIGHT:
						origin += {0, -1};
						if (destination == origin)
							has_succeeded = true;
						break;
					}

					if (has_succeeded) {
						static_cast<e1Rock*>(*item)->GetHitted();
						if (static_cast<e1Rock*>(*item)->rock_type == RockType::BREAKABLE_SNOWMAN)
							return true;
					}
				}

			}
		}
	}
	return false;
}

e1Entity * m1EntityManager::FindEntity(e1Entity::EntityType type)
{
	e1Entity* ret = nullptr;

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item)
	{
		if ((*item) != nullptr && (*item)->type == type) {
			ret = *item;
			break;
		}
	}
	return ret;
}

e1Entity * m1EntityManager::FindEntity(const char * name)
{
	e1Entity* ret = nullptr;

	std::vector<e1Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item)
	{
		if ((*item) != nullptr && (*item)->name.compare(name) == 0) {
			ret = *item;
			break;
		}
	}
	return ret;
}

bool m1EntityManager::IsPlayerPoisonedOrBurned()
{
	for (std::vector<e1Entity*>::iterator item = entities.begin(); item != entities.end(); ++item)
	{
		if ((*item)->type == e1Entity::EntityType::EVENT) {
			e1State* event = static_cast<e1State*>(*item);
			if ((event->state == EventStates::POISON || event->state == EventStates::FIRE) && event->target == App->scene->player) {
					return true;
			}
		}
	}
	return false;
}
