#include "e1Particles.h"

e1Particles::e1Particles(const int & x, const int & y) : e1DynamicEntity(x, y)
{
	
}

e1Particles::~e1Particles()
{
}

bool e1Particles::PreUpdate()
{
	return false;
}

bool e1Particles::Update(float dt)
{
	return false;
}

bool e1Particles::CleanUp()
{
	return false;
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
			current_animation = &GoDownLeft;
			break;
		}
		break;
	default:
		break;
	}
	position = App->
}
