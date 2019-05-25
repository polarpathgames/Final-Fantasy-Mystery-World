#pragma once
#ifndef _P_FOLLOW_H_
#define _P_FOLLOW_H_

#include "m1ParticleManager.h"
#include "e1Entity.h"
#include <vector>

class p1Particle;

class p1Follow
{
public:
	p1Follow(e1Entity* element_to_follow, iPoint* object_follow, SDL_Rect initial_rect = { 0,0,8,2 }, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, int num_textures = 4, int num_particles = 20, bool active_ = false, bool isMouse = false, const iPoint& offset = { 0,0 });
	~p1Follow();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void Update_position(iPoint* pos);

	void SetEntityToFollow(e1Entity* ent);
	void SetObjectToFollow(iPoint* obj);


public:

	std::vector<p1Particle*> particle;
	e1Entity* element_to_follow;
	iPoint* object_follow;

	//Num of particles
	int number_particles;

	//iPoints
	iPoint area;
	iPoint timelife;

	//position
	fPoint pos;
	int size_rect;
	int n_textures;
	iPoint offset = { 0,0 };

	//velocity
	//fPoint speed;
	bool active;
	bool isMouse;

	bool godelete;

};
#endif /*_P_FOLLOW_H_*/