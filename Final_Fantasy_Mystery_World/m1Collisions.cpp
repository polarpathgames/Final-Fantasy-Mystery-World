#include "App.h"
#include "m1Input.h"
#include "m1Render.h"
#include "m1Collisions.h"

#include "Brofiler/Brofiler.h"

m1Collision::m1Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_PLAYER][COLLIDER_SHOP] = true;
	matrix[COLLIDER_SHOP][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_HOME] = true;
	matrix[COLLIDER_HOME][COLLIDER_PLAYER] = true;


	matrix[COLLIDER_PLAYER][COLLIDER_NEXT_A] = true;
	matrix[COLLIDER_NEXT_A][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_NEXT_B] = true;
	matrix[COLLIDER_NEXT_B][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_LAST_A] = true;
	matrix[COLLIDER_LAST_A][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_LAST_B] = true;
	matrix[COLLIDER_LAST_B][COLLIDER_PLAYER] = true;

}

// Destructor
m1Collision::~m1Collision()
{}

bool m1Collision::PreUpdate()
{
	BROFILER_CATEGORY("Collisions: PreUpdate", Profiler::Color::Magenta);
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Test all collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

// Called before render is available
bool m1Collision::Update(float dt)
{
	BROFILER_CATEGORY("Collisions: Update", Profiler::Color::Magenta);
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;
	DebugDraw();


	return true;
}

void m1Collision::DebugDraw()
{

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_PLAYER: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_SHOP: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_HOME: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_NEXT_A: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_LAST_A: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_NEXT_B: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_LAST_B: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		}

	}

}



// Called before quitting
bool m1Collision::CleanUp()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* m1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, m1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}