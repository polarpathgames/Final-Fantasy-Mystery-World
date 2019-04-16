#include "e1Particles.h"
#include "App.h"
#include "m1Map.h"

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

	position.x -= 160 * dt;
	position.y += 80 * dt;

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
			GoDownLeft.PushBack({ 70,122,85,86 });
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
