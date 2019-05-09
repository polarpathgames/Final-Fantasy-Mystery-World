#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "p2PerfTimer.h"
#include "p2Properties.h"
#include "p1Fire.h"
#include "p1Explosion.h"


struct SDL_Texture;
struct Collider;

enum class State {
	IDLE, WALKING, BEFORE_ATTACK, ATTACKING, AFTER_ATTACK, DEATH, MENU, SLEEPING, BEFORE_FLASH, FLASHING, AFTER_FLASH,NONE
};

enum class AnimationState {

	IDLE_UP, IDLE_UP_LEFT, IDLE_UP_RIGHT, IDLE_LEFT, IDLE_DOWN_LEFT, IDLE_DOWN, IDLE_DOWN_RIGHT, IDLE_RIGHT,
	WALKING_UP, WALKING_UP_LEFT, WALKING_UP_RIGHT, WALKING_LEFT, WALKING_DOWN_LEFT, WALKING_DOWN, WALKING_DOWN_RIGHT, WALKING_RIGHT,
	BASIC_ATTACK_UP, BASIC_ATTACK_UP_LEFT, BASIC_ATTACK_UP_RIGHT, BASIC_ATTACK_LEFT, BASIC_ATTACK_DOWN_LEFT, BASIC_ATTACK_DOWN, BASIC_ATTACK_DOWN_RIGHT, BASIC_ATTACK_RIGHT,
	DEATH_UP, DEATH_UP_LEFT, DEATH_UP_RIGHT, DEATH_LEFT, DEATH_DOWN_LEFT, DEATH_DOWN, DEATH_DOWN_RIGHT, DEATH_RIGHT,
	ABILITY_UP_1, ABILITY_UP_LEFT_1, ABILITY_UP_RIGHT_1, ABILITY_LEFT_1, ABILITY_DOWN_LEFT_1, ABILITY_DOWN_1, ABILITY_DOWN_RIGHT_1, ABILITY_RIGHT_1,
	ABILITY_UP_2, ABILITY_UP_LEFT_2, ABILITY_UP_RIGHT_2, ABILITY_LEFT_2, ABILITY_DOWN_LEFT_2, ABILITY_DOWN_2, ABILITY_DOWN_RIGHT_2, ABILITY_RIGHT_2,

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

class e1Entity
{
public:
	enum class EntityType
	{
		PLAYER,
		ENEMY,
		STATIC,
		DROP,
		CARNIVOROUS_PLANT,
		BLUE_DOG,
		STRANGE_FROG,
		WARRIOR,
		ARCHER,
		SUPER_PURPLE_FROG,
		MAGE,
		PARTICLE,
		NPC,
		DAUGHTER,
		ROCK,
		BLUE_SLIME,
		EVENT,
		CASSIO,
		FROZEN,

		NO_TYPE
	};

public:
	e1Entity(const int& x, const int& y);
	virtual ~e1Entity();

	bool LoadEntityData(const char*);
	void LoadProperties(pugi::xml_node&);
	virtual void IdAnimToEnum() {};

	virtual void PushBack() {};

	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
	virtual void Draw(float dt);
	virtual void OnCollision(Collider* c2) {};
	virtual void OnCollisionEnter(Collider* c2) {};
	virtual void OnCollisionExit(Collider* c2) {};
	const Collider * GetCollider() const;

	void SetPivot(const int &x, const int &y);
	void CenterOnTile();
	
	void CreateParticleFollow(e1Entity* element_to_follow, iPoint* object_follow, SDL_Rect initial_rect, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, int num_textures = 4, int num_particles = 20, bool active_ = false, bool isMouse = false, const iPoint & offset = { 0,0 });
	void CreateParticleFire(e1Entity* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4, bool active_ = false, Wind dir = W_NON, const iPoint &offset = { 0,0 });
	void CreateParticleExplosion(e1Entity* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, Explosion_Type type, iPoint perimeter = { 20, 20 }, iPoint timelife = { 20,10 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4, const fPoint& gravity = { 0.0f,5.0f });

	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };

	iPoint GetPosition() const;

	Animation LoadPushbacks(pugi::xml_node&, std::string NameAnim) const;

public:

	EntityType type = EntityType::NO_TYPE;
	EntityInfo data;

	iPoint position = { 0,0 };
	iPoint pivot = { 0, 0 };
	iPoint size = { 0,0 };

	Animation* current_animation = nullptr;

	pugi::xml_document	entity_file;
	pugi::xml_node		config;
	pugi::xml_node		node;

	bool drawable = true;
	bool allow_turn = false;
	bool turn_done = false;
	iPoint actual_tile;
	Collider* coll = nullptr;
	bool to_delete = false;
	iPoint velocity;

	uint turn_count = 0u;

	Properties<int> general_properties;
	std::string name;

	std::list<p1Follow*> particle_follow;
	std::list<p1Fire*> particle_fire;
	std::list<p1Explosion*> particle_explosion;
};

#endif

