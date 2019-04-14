#include "e1CarnivorousPlant.h"
#include "e1Enemy.h"

e1CarnivorousPlant::e1CarnivorousPlant(const int & x, const int & y) : e1Enemy(x, y)
{
	LoadEntityData("assets/entities/CarnivorousPlant.tsx");


	position.x += 8;
	position.y -= 22;

	target_position = position;
	initial_position = position;
}

e1CarnivorousPlant::~e1CarnivorousPlant()
{
}

bool e1CarnivorousPlant::PreUpdate()
{

	return true;
}

bool e1CarnivorousPlant::Update(float dt)
{

	return true;
}

bool e1CarnivorousPlant::PostUpdate()
{

	return true;
}

bool e1CarnivorousPlant::CleanUp()
{

	return true;
}

void e1CarnivorousPlant::IdAnimToEnum()
{

	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 0:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 4:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 7:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;
		case 10:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 13:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 16:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 19:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 22:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 24:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 33:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 27:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 30:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		case 36:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN;
			break;
		case 39:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP;
			break;
		case 42:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_LEFT;
			break;
		case 54:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_RIGHT;
			break;
		case 60:
			data.animations[i].animType = AnimationState::DEATH_DOWN_LEFT;
			break;
		case 63:
			data.animations[i].animType = AnimationState::DEATH_UP_LEFT;
			break;
		case 66:
			data.animations[i].animType = AnimationState::DEATH_DOWN_RIGHT;
			break;
		case 69:
			data.animations[i].animType = AnimationState::DEATH_UP_RIGHT;
			break;
		}

	}

}
