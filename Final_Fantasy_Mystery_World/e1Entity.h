#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1PerfTimer.h"



struct SDL_Texture;
struct Collider;

enum class State {
	IDLE, WALKING, BEFORE_ATTACK, ATTACKING, AFTER_ATTACK, NONE
};

enum class AnimationState {

	IDLE_UP, IDLE_UP_LEFT, IDLE_UP_RIGHT, IDLE_LEFT, IDLE_DOWN_LEFT, IDLE_DOWN, IDLE_DOWN_RIGHT, IDLE_RIGHT,
	WALKING_UP, WALKING_UP_LEFT, WALKING_UP_RIGHT, WALKING_LEFT, WALKING_DOWN_LEFT, WALKING_DOWN, WALKING_DOWN_RIGHT, WALKING_RIGHT,
	BASIC_ATTACK_UP, BASIC_ATTACK_UP_LEFT, BASIC_ATTACK_UP_RIGHT, BASIC_ATTACK_LEFT, BASIC_ATTACK_DOWN_LEFT, BASIC_ATTACK_DOWN, BASIC_ATTACK_DOWN_RIGHT, BASIC_ATTACK_RIGHT,
	
	
	NONE
};



struct TileSetEntity {

	SDL_Rect GetTileRect(int id) const;

	std::string name;
	uint tilewidth = 0;
	uint tileheight = 0;
	uint spacing = 0;
	uint margin = 0;
	uint tilecount = 0;
	uint columns = 0;
	std::string imagePath;
	SDL_Texture* texture = nullptr;
	uint width = 0;
	uint height = 0;
};

struct EntityAnim {
	uint id = 0;
	uint num_frames = 0;
	SDL_Rect* frames = nullptr;
	int speed = 0;
	AnimationState animType = AnimationState::NONE;

	uint FrameCount(pugi::xml_node&);
};

struct EntityInfo {
	TileSetEntity tileset;
	EntityAnim* animations = nullptr;
	uint num_animations = 0;
};

class Entity
{
public:
	enum class EntityType
	{
		PLAYER,
		ENEMY,
		SENSOR,
		STATIC,


		NO_TYPE
	};

public:
	Entity(const int& x, const int& y);
	virtual ~Entity();

	bool LoadEntityData(const char*);
	//virtual void LoadProperties(pugi::xml_node&);
	virtual void IdAnimToEnum();

	virtual void PushBack() {};

	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
	virtual void Draw(SDL_Texture* tex, float dt);
	virtual void OnCollision(Collider* c2) {};
	const Collider * GetCollider() const;

	void SetPivot(const int &x, const int &y);

	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };

	void LoadXML(std::string name_xml_file);
	Animation LoadPushbacks(pugi::xml_node&, std::string NameAnim) const;

public:

	EntityType type = EntityType::NO_TYPE;
	EntityInfo data;

	iPoint position = { 0,0 };
	iPoint pivot = { 0, 0 };
	iPoint size = { 0,0 };

	Animation* current_animation = nullptr;

	pugi::xml_document	config_file;
	pugi::xml_document	entity_file;
	pugi::xml_node		config;
	pugi::xml_node		node;


	bool has_turn = true;
	iPoint actual_tile;
	Collider* coll = nullptr;
};

#endif

