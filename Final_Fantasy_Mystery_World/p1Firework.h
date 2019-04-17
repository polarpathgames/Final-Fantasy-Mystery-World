#ifndef _P_FIREWORK_H_
#define _P_FIREWORK_H_

#include "m1ParticleManager.h"
#include "e1Entity.h"
#include <vector>

#define MULITFIREWORK 4

class p1Particle;

class p1Firework
{
public:
	p1Firework(e1Entity* element, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect = { 0,0,8,2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4, iPoint next_textures = { 0, 4 }, iPoint last_textures = { 0, 4 });
	~p1Firework();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void MoveParticles();

public:
	std::vector<p1Particle*> particle;
	e1Entity* element_to_follow;
	//Num of particles
	int number_particles;
	int number_multifirework;

	//iPoint object
	iPoint* object_follow;

	//timelife
	iPoint timelife;


	//textures
	iPoint next_textures;
	iPoint last_textures;

	//position
	fPoint pos;
	int size_rect;
	int n_textures;

	SDL_Rect i_rect;

	//velocity
	fPoint speed;

	bool godelete;

};


#endif /*_P_FIREWORK_H_*/