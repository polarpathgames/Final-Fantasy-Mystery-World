#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Animation.h"
#include "Entity.h"
#include <vector>

class Player;
class Enemy;



class Entity;

class EntityManager : public j1Module
{
public:

	EntityManager();
	~EntityManager();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();



	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();


	Entity* CreateEntity(Entity::EntityType type, int PositionX, int PositionY, std::string name);
	//Player* CreatePlayer();
	//Enemy* CreateEnemy();

	void DeleteEntities();

	Player * GetPlayerData() const;

	const std::vector<Entity*> GetEntities();

	//static bool SortByYPos(const Entity * ent1, const Entity * ent2);

private:

	std::vector<Entity*> entities;
	SDL_Texture* texture = nullptr;

public:


};

#endif

