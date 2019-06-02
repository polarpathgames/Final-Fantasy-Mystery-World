#ifndef __e1NPC_H__
#define __e1NPC_H__

#include "p2Animation.h"
#include "p2Point.h"
#include "e1DynamicEntity.h"
#include "p2PerfTimer.h"
#include <vector>

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
	
public:
	NPCType npc_type = NPCType::NONE;
	std::vector<uint> dialog_id;

	MovementType move_type = MovementType::NONE;
	std::vector<NPC_move> move_vector;

	bool interactable = false;
	bool look_to_player = false;
};


#endif

