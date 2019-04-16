#include "p1Follow.h"
#include "p1Particle.h"
#include "m1Render.h"
#include "App.h"
#include "p2Log.h"

p1Follow::p1Follow(e1Entity* element, iPoint* object, SDL_Rect initial_rect, iPoint area_, iPoint timelife_, int num_textures, int num_particles, bool active_, bool mouse)
{
	if (element != nullptr)
	{
		pos.x = element->position.x + element->pivot.x;
		pos.y = element->position.y + element->pivot.y;
		element_to_follow = element;
		object_follow = nullptr;
	}
	else
	{
		pos.x = object->x;
		pos.y = object->y;
		object_follow = object;
		element_to_follow = nullptr;
	}

	area = area_;
	number_particles = num_particles;
	godelete = false;
	isMouse = mouse;
	active = active_;
	timelife = timelife_;
	n_textures = num_textures;
	size_rect = initial_rect.w;

	for (int i = 0; i < num_particles; i++)
	{
		p1Particle* temp = new p1Particle(pos, area, timelife, fPoint(0,0), P_NON, initial_rect, size_rect, num_textures, active_);
		particle.push_back(temp);
	}
}

p1Follow::~p1Follow()
{
}

bool p1Follow::Update(float dt)
{
	if (element_to_follow != nullptr)
	{
		pos.x = element_to_follow->GetPosition().x;
		pos.y = element_to_follow->GetPosition().y;
	}
	else
	{
		Update_position(object_follow);
	}

	return true;
}

bool p1Follow::PostUpdate()
{
	render(pos);
	return true;
}

void p1Follow::render(fPoint pos)
{
	if (active)
	{
		for (int i = 0; i < number_particles; i++)
		{
			if (particle[i]->isDead())
			{
				particle[i]->Modify(pos, area, timelife, iPoint(0, n_textures));
			}
		}
	}

	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->render();
	}
}

void p1Follow::Update_position(iPoint* element)
{
	if (isMouse == false)
	{
		pos.x = element->x;
		pos.y = element->y;
	}
	else
	{
		pos.x = element->x - App->render->camera.x / 2;
		pos.y = element->y - App->render->camera.y / 2;
	}

	LOG("%i - %i", element->x, element->y);
}