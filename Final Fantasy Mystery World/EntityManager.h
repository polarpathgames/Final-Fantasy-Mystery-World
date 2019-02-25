#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Animation.h"
#include <list>

class Player;
class Enemy;

enum EntityType
{
	PLAYER,
	ENEMY,


	NO_TYPE
};

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

	Player* CreatePlayer();
	Enemy* CreateEnemy();

	void DeleteEntities();

	Player * GetPlayerData() const;


private:

	std::list<Entity*> entities;
	SDL_Texture* texture;

public:


};

#endif

