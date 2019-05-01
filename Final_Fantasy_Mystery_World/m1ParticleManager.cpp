#include "m1ParticleManager.h"
#include "App.h"
#include "m1Render.h"
#include "m1Textures.h"
#include "e1Player.h"
#include "m1Audio.h"
#include "p2Timer.h"
#include "p1Follow.h"
#include "p1Fire.h"
#include "p1Explosion.h"
#include "p1Firework.h"

m1ParticleManager::m1ParticleManager()
{
	name.assign("particles");
}

m1ParticleManager::~m1ParticleManager()
{
}

bool m1ParticleManager::Awake()
{
	return true;
}

bool m1ParticleManager::Start()
{
	//texture
	atlas_particle = App->tex->Load("assets/sprites/atlas_particle.png");

	return true;
}

bool m1ParticleManager::PreUpdate()
{
	return true;
}

bool m1ParticleManager::Update(float dt)
{
	////SET FIRE
	//if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	//{
	//	Group_Fire.push_back(new P_Fire(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,2,2,0 }, iPoint(5, 2), iPoint(12, 4), fPoint(0, -60), P_NON, 65, 4, true, W_NON));
	//}
	////FIREWORK
	//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{
	//	Group_Firework.push_back(new P_Firework(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,8,2,0 }, iPoint(0, 2), fPoint(0, -400), P_NON, 20, 1, iPoint(1,1), iPoint(1, 4)));
	//}

	////EXPLOSIONS
	//if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
	//{
	//	Group_Explosion.push_back(new P_Explosion(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,4,2,0 }, CROSS, iPoint(20, 20), iPoint(10, 2), fPoint(60, 60), P_NON, 21));
	//}
	//if (App->input->GetMouseButtonDown(2) == KEY_DOWN)
	//{
	//	Group_Explosion.push_back(new P_Explosion(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,4,2,0 }, CIRCLE, iPoint(20, 20), iPoint(10, 2), fPoint(60, 60), P_RANDOM, 22));
	//}
	//if (App->input->GetMouseButtonDown(3) == KEY_DOWN)
	//{
	//	Group_Explosion.push_back(new P_Explosion(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,4,2,0 }, RANDOM, iPoint(20, 20), iPoint(20, 8), fPoint(200, -60), P_RANDOM_X, 21));
	//}

	//Iterate all list
	//Group FOLLOW -------------------------------------------------
	std::list<p1Follow*>::iterator item = Group_Follow.begin();
	while (item != Group_Follow.end())
	{
		item._Ptr->_Myval->Update(dt);
		item++;
	}

	//Group FIRE -------------------------------------------------
	std::list<p1Fire*>::iterator item_2 = Group_Fire.begin();
	while (item_2 != Group_Fire.end())
	{
		item_2._Ptr->_Myval->Update(dt);
		item_2++;
	}

	//Group EXPLOSION -------------------------------------------------
	std::list<p1Explosion*>::iterator item_3 = Group_Explosion.begin();
	while (item_3 != Group_Explosion.end())
	{
		if ((*item_3)->godelete)
		{
			for (std::vector<p1Particle*>::iterator particle = (*item_3)->particle.begin(); particle != (*item_3)->particle.end(); particle++) {
				RELEASE(*particle);
			}
			(*item_3)->particle.clear();
			RELEASE(*item_3);
		}
		else
		{
			item_3._Ptr->_Myval->Update(dt);
		}
		item_3++;
	}
	Group_Explosion.remove(nullptr);

	//Group FIREWORK -------------------------------------------------
	std::list<p1Firework*>::iterator item_4 = Group_Firework.begin();
	while (item_4 != Group_Firework.end())
	{
		if (item_4._Ptr->_Myval->godelete)
		{
			item_4._Ptr->_Myval->particle.clear();
			Group_Firework.erase(item_4);
		}
		else
		{
			item_4._Ptr->_Myval->Update(dt);
		}
		item_4++;
	}
	return true;
}

bool m1ParticleManager::PostUpdate()
{
	//Iterate all list
	//Group FOLLOW -------------------------------------------------
	std::list<p1Follow*>::iterator item = Group_Follow.begin();
	while (item != Group_Follow.end())
	{
		item._Ptr->_Myval->PostUpdate();
		item++;
	}
	//Group FRIE -------------------------------------------------
	std::list<p1Fire*>::iterator item_2 = Group_Fire.begin();
	while (item_2 != Group_Fire.end())
	{
		item_2._Ptr->_Myval->PostUpdate();
		item_2++;
	}
	//Group EXPLOSION -------------------------------------------------
	std::list<p1Explosion*>::iterator item_3 = Group_Explosion.begin();
	while (item_3 != Group_Explosion.end())
	{
		item_3._Ptr->_Myval->PostUpdate();
		item_3++;
	}
	//Group FIREWORK -------------------------------------------------
	std::list<p1Firework*>::iterator item_4 = Group_Firework.begin();
	while (item_4 != Group_Firework.end())
	{
		item_4._Ptr->_Myval->PostUpdate();
		item_4++;
	}


	return true;
}

bool m1ParticleManager::CleanUp()
{
	for (std::list<p1Follow*>::iterator item = Group_Follow.begin(); item != Group_Follow.end(); ++item) {
		for (std::vector<p1Particle*>::iterator item_p = (*item)->particle.begin(); item_p != (*item)->particle.end(); item_p++) {
			delete *item_p;
			*item_p = nullptr;
		}
		(*item)->particle.clear();

		delete *item;
		*item = nullptr;
	}
	Group_Follow.remove(nullptr);

	for (std::list<p1Fire*>::iterator item = Group_Fire.begin(); item != Group_Fire.end(); ++item) {
		for (std::vector<p1Particle*>::iterator item_p = (*item)->particle.begin(); item_p != (*item)->particle.end(); item_p++) {
			delete *item_p;
			*item_p = nullptr;
		}
		(*item)->particle.clear();

		delete *item;
		*item = nullptr;
	}
	Group_Fire.remove(nullptr);

	for (std::list<p1Explosion*>::iterator item = Group_Explosion.begin(); item != Group_Explosion.end(); ++item) {
		for (std::vector<p1Particle*>::iterator item_p = (*item)->particle.begin(); item_p != (*item)->particle.end(); item_p++) {
			delete *item_p;
			*item_p = nullptr;
		}
		(*item)->particle.clear();

		delete *item;
		*item = nullptr;
	}
	Group_Explosion.remove(nullptr);

	for (std::list<p1Firework*>::iterator item = Group_Firework.begin(); item != Group_Firework.end(); ++item) {
		for (std::vector<p1Particle*>::iterator item_p = (*item)->particle.begin(); item_p != (*item)->particle.end(); item_p++) {
			delete *item_p;
			*item_p = nullptr;
		}
		(*item)->particle.clear();

		delete *item;
		*item = nullptr;
	}
	Group_Firework.remove(nullptr);

	SDL_assert(Group_Explosion.size() == 0 && Group_Follow.size() == 0 && Group_Fire.size() == 0 && Group_Firework.size() == 0);

	return Group_Explosion.size() == 0 && Group_Follow.size() == 0 && Group_Fire.size() == 0 && Group_Firework.size() == 0;
}

//CREATE GROUPS -------------------------------------------------------------------------------------------------------------------------------------

p1Follow* m1ParticleManager::CreateFollow(e1Entity* element_to_follow, iPoint* object_follow, SDL_Rect initial_rect, iPoint area, iPoint timelife, int num_textures, int num_particles, bool active, bool isMouse, const iPoint & offset)
{
	p1Follow* ret = DBG_NEW p1Follow(element_to_follow, object_follow, initial_rect, area, timelife, num_textures, num_particles, active, isMouse, offset);
	Group_Follow.push_back(ret);
	return ret;
}

p1Fire* m1ParticleManager::CreateFire(e1Entity* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint area, iPoint timelife, fPoint speed, P_Direction p_direction, int num_particles, int num_textures, bool active, Wind w_dir, const iPoint &offset)
{
	p1Fire* ret = DBG_NEW p1Fire(element_to_follow, object_follow, position_static, initial_rect, area, timelife, speed, p_direction, num_particles, num_textures, active, w_dir, offset);
	Group_Fire.push_back(ret);
	return ret;
}

p1Explosion* m1ParticleManager::CreateExplosion(e1Entity* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, Explosion_Type type, iPoint perimeter, iPoint timelife, fPoint speed, P_Direction p_direction, int num_particles, int num_textures, const fPoint& gravity)
{
	p1Explosion* ret = DBG_NEW p1Explosion(element_to_follow, object_follow, position_static, initial_rect, type, perimeter, timelife, speed, p_direction, num_particles, num_textures, gravity);
	Group_Explosion.push_back(ret);
	return ret;
}

p1Firework* m1ParticleManager::CreateFirework(e1Entity* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint timelife, fPoint speed, P_Direction p_direction, int num_particles, int num_textures, iPoint next_textures, iPoint last_textures)
{
	p1Firework* ret = DBG_NEW p1Firework(element_to_follow, object_follow, position_static, initial_rect, timelife, speed, p_direction, num_particles, num_textures, next_textures, last_textures);
	Group_Firework.push_back(ret);
	return ret;
}


//DELETE GROUPS -------------------------------------------------------------------------------------------------------------------------------------

bool m1ParticleManager::DeleteFollow_p(p1Follow* group)
{
	std::list<p1Follow*>::iterator item = Group_Follow.begin();
	std::vector<p1Particle*>::iterator part;
	while (item != Group_Follow.end())
	{
		if ((*item) == group)
		{
			for (part = (*item)->particle.begin(); part != (*item)->particle.end(); part++) {
				delete *part;
				*part = nullptr;
			}
			(*item)->particle.clear();

			delete *item;
			*item = nullptr;
		}
		item++;
	}
	Group_Follow.remove(nullptr);
	return true;
}

bool m1ParticleManager::DeleteFire_p(p1Fire* group)
{
	std::list<p1Fire*>::iterator item = Group_Fire.begin();
	std::vector<p1Particle*>::iterator part;
	while (item != Group_Fire.end())
	{
		if ((*item) == group)
		{
			for (part = (*item)->particle.begin(); part != (*item)->particle.end(); part++) {
				delete *part;
				*part = nullptr;
			}
			(*item)->particle.clear();

			delete *item;
			*item = nullptr;
		}
		item++;
	}
	Group_Fire.remove(nullptr);
	return true;
}

bool m1ParticleManager::DeleteExplosion_p(p1Explosion* group)
{
	std::list<p1Explosion*>::iterator item = Group_Explosion.begin();
	std::vector<p1Particle*>::iterator part;
	while (item != Group_Explosion.end())
	{
		if ((*item) == group)
		{
			for (part = (*item)->particle.begin(); part != (*item)->particle.end(); part++) {
				delete *part;
				*part = nullptr;
			}
			(*item)->particle.clear();

			delete *item;
			*item = nullptr;
		}
		item++;
	}
	Group_Explosion.remove(nullptr);
	return true;
}

bool m1ParticleManager::DeleteFirework_p(p1Firework* group)
{
	std::list<p1Firework*>::iterator item = Group_Firework.begin();
	std::vector<p1Particle*>::iterator part;
	while (item != Group_Firework.end())
	{
		if ((*item) == group)
		{
			for (part = (*item)->particle.begin(); part != (*item)->particle.end(); part++) {
				delete *part;
				*part = nullptr;
			}
			(*item)->particle.clear();

			delete *item;
			*item = nullptr;
		}
		item++;
	}
	Group_Firework.remove(nullptr);
	return true;
}