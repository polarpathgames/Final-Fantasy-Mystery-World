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

	if (NextTileFree(direction)) {
		position.x += floor(160 * dt);
		position.y -= floor(80 * dt);
	}
	else {
		to_delete = true;
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
		switch (direction) {
		case Direction::DOWN_LEFT:
			//GoDownLeft.PushBack({ 16,29,20,20 });
			GoDownLeft.PushBack({ 37,8,20,20 });
			size.create(20, 20);
			current_animation = &GoDownLeft;
			break;
		}
		break;
	default:
		break;
	}
	position = App->map->MapToWorld(position.x, position.y);
}
