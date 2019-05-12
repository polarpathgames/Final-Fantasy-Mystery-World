#ifndef _E1PARTICLES_H_
#define _E1PARTICLES_H_

#define MAX_ARROW 4
#define FIREBALL_ELEVATED_POS 190

#include "e1DynamicEntity.h"

#include <list>

class e1Particles : public e1DynamicEntity {

public:

	enum class ParticleType {
		ARROW,
		FIREBALL,

		NONE
	};

	e1Particles(const int &x, const int &y);
	virtual ~e1Particles();

	bool PreUpdate();
	bool Update(float dt);

	bool CleanUp();

	bool Load(pugi::xml_node&) { return true; };
	bool Save(pugi::xml_node&) const { return true; };

	void SetParticle(const ParticleType & particle_type, const Direction &dir);

private:

	void SetArrow();
	void MoveArrow(float dt);
	void LookForEnemyCollision();
	void LookForRocks();

	void SetFireBall();
	void MoveFireBall(float dt);
	void FireBallExplosionCollision();

public:

	ParticleType particle_type = ParticleType::NONE;

	iPoint arrow_tile = { 0,0 };
	iPoint max_arrow_distance = { 0,0 };
	iPoint fireball_tile_objective = { 0,0 };

	float arrow_time = 0;

	Animation* shadow_fire_ball = nullptr;

};

#endif // !_E1PARTICLES_H_