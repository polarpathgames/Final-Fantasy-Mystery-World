#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Animation.h"
#include <list>

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

	Player* CreatePlayer();
	Enemy* CreateEnemy();

	void DeleteEntities();

	Player * GetPlayerData() const;

	const std::list<Entity*> GetEntities();

private:

	std::list<Entity*> entities;
	SDL_Texture* texture = nullptr;

public:


};

#endif

