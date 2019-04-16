#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "m1Module.h"
#include "m1Scene.h"
#include "p2Point.h"

class e1Entity;

#define MAX_TIMELIFE 255
#define NORMAL_SPEED_Y 180

enum Wind { W_NON = 0, W_UP, W_DOWN, W_LEFT, W_RIGHT };

enum P_Direction { P_NON, P_UP, P_DOWN, P_LEFT, P_RIGHT, P_RANDOM_X, P_RANDOM_Y, P_RANDOM, P_RANDOM_FIREWORK };

enum Explosion_Type
{
	CIRCLE,				/**/
	CROSS,				/**/
	RANDOM				/**/
};


class p1Follow;
class p1Fire;
class p1Explosion;
class p1Firework;

class m1ParticleManager : public m1Module
{
public:

	m1ParticleManager();

	// Destructor
	~m1ParticleManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	virtual bool Update(float dt);

	// Called before all Updates
	virtual bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//FUNCTIONS TO CREATE

	//Create & Delete Follow Group
	void CreateFollow_P(e1Entity* element_to_follow, iPoint* object_follow, SDL_Rect initial_rect, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, int num_textures = 4, int num_particles = 20, bool active_ = false, bool isMouse = false);
	bool DeleteFollow_p(p1Follow* group);

	//Create & DeleteFire Group
	void CreateFire_Particle(e1Entity* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4, bool active_ = false, Wind dir = W_NON);
	bool DeleteFire_p(p1Fire* group);

	//Create & Delete Explosion Group
	void CreateExplosion_Particle(e1Entity* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, Explosion_Type type, iPoint perimeter = { 20, 20 }, iPoint timelife = { 20,10 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4);
	bool DeleteExplosion_p(p1Explosion* group);

	//Create & Delete Firework Group
	void CreateFirework_Particle(e1Entity* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4, iPoint next_textures = { 0, 4 }, iPoint last_textures = { 0, 4 });
	bool DeleteFirework_p(p1Firework* group);


public:

	std::list<p1Follow*> Group_Follow;
	std::list<p1Fire*> Group_Fire;
	std::list<p1Explosion*> Group_Explosion;
	std::list<p1Firework*> Group_Firework;

	SDL_Texture* atlas_particle = nullptr;

};

#endif // __PARTICLESYSTEM_H__