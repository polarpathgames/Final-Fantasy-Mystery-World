#ifndef _E1PARTICLES_H_
#define _E1PARTICLES_H_

#include "e1DynamicEntity.h"

class e1Particles : public e1DynamicEntity {

public:

	enum class ParticleType {
		ARROW,

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

public:

	ParticleType particle_type = ParticleType::NONE;

};



#endif // !_E1PARTICLES_H_

