#include "p1Fire.h"
#include "p1Particle.h"
#include "App.h"
#include "m1Render.h"
#include "m1Window.h"

p1Fire::p1Fire(e1Entity* element, iPoint* object, iPoint position_static, SDL_Rect initial_rect, iPoint area_, iPoint timelife_, fPoint speed_particle, P_Direction p_direction, int num_particles, int num_textures, bool active_, Wind dir, const iPoint &offset)
	:offset(offset)
{
	if (element != nullptr)
	{
		pos.x = element->position.x + offset.x;
		pos.y = element->position.y + offset.y;
		element_to_follow = element;
		object = nullptr;
	}
	else if (object != nullptr)
	{
		pos.x = object->x + offset.x;
		pos.y = object->y + offset.y;
		object_follow = object;
		element_to_follow = nullptr;
	}
	else
	{
		pos.x = position_static.x + offset.x;
		pos.y = position_static.y + offset.y;
		object_follow = nullptr;
		element_to_follow = nullptr;
	}

	speed = speed_particle;

	if (dir != W_NON)
		wind_speed = true;
	else
		wind_speed = false;

	area = area_;
	timelife = timelife_;
	dir_wind = dir;
	number_particles = num_particles;
	godelete = false;
	active = active_;
	n_textures = num_textures;
	size_rect = initial_rect.w;
	for (int i = 0; i < num_particles; i++)
	{
		p1Particle* temp = DBG_NEW p1Particle(pos, area, timelife, speed, p_direction, initial_rect, size_rect, n_textures, true);
		particle.push_back(temp);
	}
}

p1Fire::~p1Fire()
{
}

bool p1Fire::Update(float dt)
{
	if (element_to_follow != nullptr && object_follow == nullptr)
	{
		pos.x = element_to_follow->position.x + offset.x;
		pos.y = element_to_follow->position.y + offset.y;
	}
	else if (element_to_follow == nullptr && object_follow != nullptr)
	{
		Update_position(object_follow);
	}

	MoveParticles();


	return true;
}

bool p1Fire::PostUpdate()
{
	render(pos);
	return true;
}

void p1Fire::render(fPoint pos)
{
	if (active)
	{
		//Check if the particle dead
		for (int i = 0; i < number_particles; i++)
		{
			if (particle[i]->isDead())
			{
				particle[i]->Modify(pos, area, timelife, iPoint(0, n_textures));
			}
		}
	}

	//Draw particles
	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->render();
	}
}

void p1Fire::MoveParticles()
{
	for (int i = 0; i < number_particles; i++)
	{
		float temp = App->GetDeltaTime();
		particle[i]->Move(fPoint(particle[i]->GetSpeed().x * temp, particle[i]->GetSpeed().y * temp), dir_wind, wind_speed);
	}
}

void p1Fire::Update_position(iPoint* element)
{
	pos.x = element->x - App->render->camera.x / App->win->GetScale();
	int scale = App->win->GetScale();
	int temp = App->render->camera.y / scale;
	pos.y = element->y - temp;
}