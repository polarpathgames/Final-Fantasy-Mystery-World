#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Animation.h"
#include <list>

class Player;

enum EntityType
{
	PLAYER,


	NO_TYPE
};

class DynamicEntity;

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

	void DeleteEntities();


private:

	std::list<DynamicEntity*> entities;

public:


};

#endif

