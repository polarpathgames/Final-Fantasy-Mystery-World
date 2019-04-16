#include "e1ShopKeeperDaughter.h"
#include "e1NPC.h"


e1ShopKeeperDaughter::e1ShopKeeperDaughter(const int &x, const int &y) : e1NPC(x, y)
{
	LoadEntityData("assets/entities/StrangeFrog.tsx");
	npc_type = NPCType::DAUGHTER;
	position.x;
	position.y;
}

e1ShopKeeperDaughter::~e1ShopKeeperDaughter()
{
}

bool e1ShopKeeperDaughter::PreUpdate()
{
	return true;
}

bool e1ShopKeeperDaughter::Update(float dt)
{
	return true;
}
