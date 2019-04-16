#ifndef __J1ENTITYMANAGER_H__
#define __J1ENTITYMANAGER_H__

#include "m1Module.h"
#include "p2Animation.h"
#include "e1Entity.h"
#include <vector>

enum class TextureType {
	WARRIOR,
	MAGE,
	ARCHER,
	CARNIVOROUS_PLANT,
	BLUE_DOG,
	STRANGE_FROG,
	STATIC_ENTITIES,

	NONE // NONE must be the last one
};



class m1EntityManager : public m1Module
{
public:

	m1EntityManager();
	~m1EntityManager();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	void DrawEntities(std::vector<e1Entity *> &draw_entities, float dt);

	void UpdateEntities(float dt, std::vector<e1Entity *> &draw_entities);

	bool PostUpdate();

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);
	void OnCollisionEnter(Collider* c1, Collider* c2);
	void OnCollisionExit(Collider* c1, Collider* c2);

	e1Entity* CreateEntity(e1Entity::EntityType type, int PositionX, int PositionY, std::string name);

	void DeleteEntities();
	void DeleteEntitiesNoPlayer();
	void DeleteEntity(e1Entity* entity_to_delete);

	const std::vector<e1Entity*> GetEntities();
	const std::vector<SDL_Texture*> GetTextures();

	static bool SortByYPos(const e1Entity * ent1, const e1Entity * ent2);

	uint entities_drawn = 0u;

private:

	std::vector<e1Entity*> entities;
	std::vector<SDL_Texture*> texture;
	
	bool textures_loaded = false;
};

#endif