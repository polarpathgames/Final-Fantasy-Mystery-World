#ifndef __e1NPC_H__
#define __e1NPC_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "e1DynamicEntity.h"
#include "p2PerfTimer.h"
#include <vector>

class u1Image;

class e1NPC : public e1DynamicEntity
{
public:
	enum class NPCType {
		DAUGHTER,
		DOG,

		NONE = -1
	};
	enum class MovementType {
		STATIC,
		RANDOM,
		QUEUE,

		NONE = -1
	};

	struct NPC_move {
		int num_tiles = 0;
		Direction direction = Direction::NONE;
		float speed = 0.f;
	};

	e1NPC(const int &x, const int &y, const char* name);

	virtual ~e1NPC();

	bool LoadNPC(const char* name);

	void LoadInteraction(pugi::xml_node &node);

	void LoadMovement(pugi::xml_node &node);

	void LoadBasicData(pugi::xml_node &node);

	void LoadGraphics(pugi::xml_node &node);

	virtual bool PreUpdate() { return true; };

	virtual bool Update(float dt);

	virtual bool PostUpdate() { return true; };

	virtual bool Load(pugi::xml_node&);

	virtual bool Save(pugi::xml_node&) const;

	virtual bool CleanUp();

	iPoint CalculateDestination(const Direction & dir, const int num_tiles);
	
public:
	NPCType npc_type = NPCType::NONE;
	std::list<uint> dialog_id;

	MovementType move_type = MovementType::NONE;
	std::vector<NPC_move> move_vector;
	iPoint destination = { 0,0 };
	std::vector<NPC_move>::const_iterator move_it;
	float lerp_by = 0.f;

	u1Image* button_interact = nullptr;

	bool interactable = false;
	bool look_to_player = false;
	bool start_run = false;
};


#endif

