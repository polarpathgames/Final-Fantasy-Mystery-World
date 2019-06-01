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

	e1NPC(const int &x, const int &y, const char* name);

	virtual ~e1NPC();

	virtual bool PreUpdate() { return true; };

	virtual bool Update(float dt) { return true; };

	virtual bool PostUpdate() { return true; };

	virtual bool Load(pugi::xml_node&);

	virtual bool Save(pugi::xml_node&) const;

	virtual bool CleanUp();
	
public:
	NPCType npc_type = NPCType::NONE;
	std::vector<uint> dialog_id;
};


#endif

