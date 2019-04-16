#include "e1ShopKeeperDaughter.h"
#include "e1NPC.h"


e1ShopKeeperDaughter::e1ShopKeeperDaughter(const int &x, const int &y) : e1NPC(x, y)
{
	LoadEntityData("assets/entities/Little_Girl.tsx");
	npc_type = NPCType::DAUGHTER;
	current_animation = &GoUpRight;
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



void e1ShopKeeperDaughter::IdAnimToEnum() //Assign every id animation to enum animation
{
	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 1:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 0:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;
		case 3:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 4:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 6:
			data.animations[i].animType = AnimationState::WALKING_DOWN_RIGHT;
			break;
		case 7:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;
		case 9:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 10:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 12:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 13:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 15:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 16:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 18:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 19:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 21:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 22:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		}
	}
}