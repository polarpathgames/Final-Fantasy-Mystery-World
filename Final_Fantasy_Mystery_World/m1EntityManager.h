#ifndef __J1ENTITYMANAGER_H__
#define __J1ENTITYMANAGER_H__

#include "m1Module.h"
#include "p2Animation.h"
#include "e1Entity.h"
#include "e1Sensor.h"
#include <vector>

class e1Player;
class e1Enemy;



class e1Entity;

class m1EntityManager : public m1Module
{
public:

	m1EntityManager();
	~m1EntityManager();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();



	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	e1Entity* CreateEntity(e1Entity::EntityType type, int PositionX, int PositionY, std::string name, e1Sensor::SensorType sensor_type = e1Sensor::SensorType::NONE);
	//e1Player* CreatePlayer();
	//e1Enemy* CreateEnemy();

	void DeleteEntities();
	void DeleteEntitiesNoPlayer();
	void DeleteEntity(e1Entity* entity_to_delete);

	const std::vector<e1Entity*> GetEntities();

	static bool SortByYPos(const e1Entity * ent1, const e1Entity * ent2);

private:

	std::vector<e1Entity*> entities;
	std::vector<SDL_Texture*> texture;

};

#endif