#ifndef __J1ENTITYMANAGER_H__
#define __J1ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Animation.h"
#include "Entity.h"
#include "Sensor.h"
#include <vector>

class Player;
class Enemy;



class Entity;

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();



	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	Entity* CreateEntity(Entity::EntityType type, int PositionX, int PositionY, std::string name, Sensor::SensorType sensor_type = Sensor::SensorType::NONE);
	//Player* CreatePlayer();
	//Enemy* CreateEnemy();

	void DeleteEntities();
	void DeleteEntitiesNoPlayer();
	void DeleteEntity(Entity* entity_to_delete);

	const std::vector<Entity*> GetEntities();

	static bool SortByYPos(const Entity * ent1, const Entity * ent2);

private:

	std::vector<Entity*> entities;
	std::vector<SDL_Texture*> texture;

};

#endif

