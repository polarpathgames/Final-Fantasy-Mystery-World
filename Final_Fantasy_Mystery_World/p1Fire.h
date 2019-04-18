#ifndef _P_FIRE_H_
#define _P_FIRE_H_

#include "m1ParticleManager.h"
#include "e1Entity.h"
#include <vector>

class p1Particle;

class p1Fire
{
public:
	p1Fire(e1Entity* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect = { 0,0,8,2 }, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4, bool active_ = false, Wind dir = W_NON, const iPoint &offset = { 0,0 });

	~p1Fire();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void Update_position(iPoint* pos);

	void MoveParticles();

public:
	std::vector<p1Particle*> particle;
	e1Entity* element_to_follow = nullptr;
	//Num of particles
	int number_particles;

	//test
	iPoint* object_follow = nullptr;

	//wind
	Wind dir_wind;
	bool wind_speed;
	iPoint timelife;

	//position
	fPoint pos;
	iPoint offset = { 0,0 };
	int size_rect;
	int n_textures;
	iPoint area;

	//velocity
	fPoint speed;
	bool active;

	bool godelete;

};
#endif /*_P_FIRE_H_*/