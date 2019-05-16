#include "p1Follow.h"
#include "p1Particle.h"
#include "m1Render.h"
#include "App.h"
#include "p2Log.h"

p1Follow::p1Follow(e1Entity* element, iPoint* object, SDL_Rect initial_rect, iPoint area, iPoint timelife, int num_textures, int num_particles, bool active, bool mouse, const iPoint& offset):
	area(area), number_particles(num_particles), isMouse(mouse),timelife(timelife),n_textures(num_textures),size_rect(initial_rect.w), offset(offset)
{
	if (element != nullptr)
	{
		pos.x = element->GetPosition().x + offset.x;
		pos.y = element->GetPosition().y + offset.y;
		element_to_follow = element;
		object_follow = nullptr;
	}
	else
	{
		pos.x = object->x + offset.x;
		pos.y = object->y + offset.y;
		object_follow = object;
		element_to_follow = nullptr;
	}

	for (int i = 0; i < num_particles; i++)
	{
		p1Particle* temp = DBG_NEW p1Particle(pos, area, timelife, fPoint(0,0), P_NON, initial_rect, size_rect, num_textures, active);
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
		pos.x = element_to_follow->GetPosition().x + offset.x;
		pos.y = element_to_follow->GetPosition().y + offset.y;
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
		pos.x = element->x + offset.x;
		pos.y = element->y + offset.y;
	}
	else
	{
		pos.x = element->x + offset.x - App->render->camera.x * 0.5F;
		pos.y = element->y + offset.y - App->render->camera.y * 0.5F;
	}

}

void p1Follow::SetEntityToFollow(e1Entity * ent)
{
	object_follow = nullptr;
	element_to_follow = ent;
}

void p1Follow::SetObjectToFollow(iPoint * obj)
{
	object_follow = obj;
	element_to_follow = nullptr;
}
