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
		MUFI,
		SNOWMAN_HATER,
		WISE,
		WORRIED_MAN,
		CASUAL_VILLAGER,
		CASUAL_VILLAGER2,
		CASUAL_VILLAGER3,
		POLAR_KNIGHT,


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

	~e1NPC();

	bool LoadNPC(const char* name);

	void LoadInteraction(pugi::xml_node &node);

	void LoadMovement(pugi::xml_node &node);

	void LoadBasicData(pugi::xml_node &node);

	void LoadGraphics(pugi::xml_node &node);

	virtual bool Update(float dt);

	void DoMovement(float dt);
	void DoInteraction();

	void DestroyInteractionButton();

	void CreateInteractionButton();

	void Draw(float dt);

	iPoint CalculateDestination(const Direction & dir, const int num_tiles);
	
public:
	NPCType npc_type = NPCType::NONE;
	std::list<uint> dialog_id;

	MovementType move_type = MovementType::NONE;
	std::vector<NPC_move> move_vector;
	iPoint destination = { 0,0 };
	fPoint new_position = { 0.f,0.f };
	std::vector<NPC_move>::const_iterator move_it;
	float lerp_by = 0.f;

	u1Image* button_interact = nullptr;
	int distance_to_interact = 0;
	bool has_directions = false;

	bool interactable = false;
	bool interacting = false;
	bool look_to_player = false;
	bool is_quest_npc = false;
};


#endif

