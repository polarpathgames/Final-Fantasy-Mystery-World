#include "e1Particles.h"
#include "App.h"
#include "m1Map.h"
#include "m1EntityManager.h"
#include "e1DynamicEntity.h"


e1Particles::e1Particles(const int & x, const int & y) : e1DynamicEntity(x, y)
{
	type = e1Entity::EntityType::PARTICLE;
}

e1Particles::~e1Particles()
{
}

bool e1Particles::PreUpdate()
{
	return true;
}

bool e1Particles::Update(float dt)
{
	actual_tile = App->map->WorldToMap(position.x, position.y);


	
	switch (particle_type)
	{
	case ParticleType::ARROW:
		if (NextTileFree(direction) && App->map->IsWalkable(actual_tile, false)) {
			switch (direction)
			{
			case Direction::UP:
				position.y -= floor(velocity.y * dt * 2);
				break;
			case Direction::DOWN:
				position.y += floor(velocity.y * dt * 2);
				break;
			case Direction::RIGHT:
				position.x += floor(velocity.x * dt);
				break;
			case Direction::LEFT:
				position.x -= floor(velocity.x * dt);
				break;
			case Direction::UP_LEFT:
				position.x -= floor(velocity.x * dt);
				position.y -= floor(velocity.y * dt);
				break;
			case Direction::DOWN_LEFT:
				position.x -= floor(velocity.x * dt);
				position.y += floor(velocity.y * dt);
				break;
			case Direction::UP_RIGHT:
				position.x += floor(velocity.x * dt);
				position.y -= floor(velocity.y * dt);
				break;
			case Direction::DOWN_RIGHT:
				position.x += floor(velocity.x * dt);
				position.y += floor(velocity.y * dt);
				break;
			default:
				break;
			}
		}
		else {
			to_delete = true;
		}
		break;
	default:
		break;
	}
	


	return true;
}

bool e1Particles::CleanUp()
{
	return true;
}

void e1Particles::SetParticle(const ParticleType & particle_type, const Direction & dir)
{
	this->particle_type = particle_type;
	direction = dir;
	switch (particle_type) {
	case ParticleType::ARROW:
		velocity.x = 160;
		velocity.y = 80;
		switch (direction) {
		case Direction::DOWN_LEFT:
			GoDownLeft.PushBack({ 16,29,20,20 });
			SetPivot(10, 10);
			size.create(20, 20);
			current_animation = &GoDownLeft;
			break;
		case Direction::UP_RIGHT:
			GoUpRight.PushBack({ 37,8,20,20 });
			SetPivot(10, 10);
			size.create(20, 20);
			current_animation = &GoUpRight;
			break;
		case Direction::UP_LEFT:
			GoUpLeft.PushBack({ 16,8,20,20 });
			SetPivot(10, 10);
			size.create(20, 20);
			current_animation = &GoUpLeft;
			break;
		case Direction::DOWN_RIGHT:
			GoDownRight.PushBack({ 37,29,20,20 });
			SetPivot(10, 10);
			size.create(20, 20);
			current_animation = &GoDownRight;
			break;
		case Direction::DOWN:
			GoDown.PushBack({ 8,8,8,27 });
			SetPivot(10, 10);
			size.create(20, 20);
			current_animation = &GoDown;
			break;
		case Direction::UP:
			GoUp.PushBack({ 0,8,8,27 });
			SetPivot(10, 10);
			size.create(20, 20);
			current_animation = &GoUp;
			break;
		case Direction::LEFT:
			GoLeft.PushBack({ 28,0,28,7 });
			SetPivot(10, 10);
			size.create(20, 20);
			current_animation = &GoLeft;
			break;
		case Direction::RIGHT:
			GoRight.PushBack({ 0,0,28,7 });
			SetPivot(10, 10);
			size.create(20, 20);
			current_animation = &GoRight;
			break;
		}
		break;
	default:
		break;
	}
	position = App->map->MapToWorld(position.x, position.y);
}
