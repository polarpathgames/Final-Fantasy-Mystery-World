#include "App.h"
#include "m1Input.h"
#include "m1Render.h"
#include "m1Collisions.h"

#include "Brofiler/Brofiler.h"

m1Collision::m1Collision()
{
	name.assign("collisions");

	matrix[COLLIDER_PLAYER][COLLIDER_SHOP] = true;
	matrix[COLLIDER_SHOP][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_QUEST_FIRE] = true;
	matrix[COLLIDER_QUEST_FIRE][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_QUEST_ICE] = true;
	matrix[COLLIDER_QUEST_ICE][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_BED] = true;
	matrix[COLLIDER_BED][COLLIDER_PLAYER] = true;

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

	matrix[COLLIDER_PLAYER][COLLIDER_MENU_QUEST] = true;
	matrix[COLLIDER_MENU_QUEST][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_CUTSCENE_BRIDGE] = true;
	matrix[COLLIDER_CUTSCENE_BRIDGE][COLLIDER_PLAYER] = true;
}

// Destructor
m1Collision::~m1Collision()
{}

bool m1Collision::PreUpdate()
{
	BROFILER_CATEGORY("Collisions: PreUpdate", Profiler::Color::Magenta);
	// Remove all colliders scheduled for deletion
	/*for (std::vector<Collider*>::iterator item = colliders.begin(); item != colliders.end(); ++item)
	{
		if (*item != nullptr && (*item)->to_delete == true)
		{
			delete *item;
			*item = nullptr;
			colliders.erase(item);
		}
	}*/

	// Test all collisions
	Collider* c1 = nullptr;
	Collider* c2 = nullptr;
	
	for (uint i = 0; i < colliders.size(); ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];
		
		// avoid checking collisions already checked
		for (uint k = i + 1; k < colliders.size(); ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback) {
					switch (c1->info)
					{
					case ColliderInfo::ENTER:
						c1->callback->OnCollisionEnter(c1, c2);
						c1->collisions.push_back(c2);
						c1->info = ColliderInfo::STAY;
						break;
					case ColliderInfo::STAY:
						c1->callback->OnCollision(c1, c2);
						break;
					default:
						c1->callback->OnCollision(c1, c2);
						break;
					}
				}
				if (matrix[c2->type][c1->type] && c2->callback) {
					switch (c2->info)
					{
					case ColliderInfo::ENTER:
						c2->callback->OnCollisionEnter(c2, c1);
						c2->collisions.push_back(c1);
						c2->info = ColliderInfo::STAY;
						break;
					case ColliderInfo::STAY:
						c2->callback->OnCollision(c2, c1);
						break;
					default:
						c2->callback->OnCollision(c2, c1);
						break;
					}
				}
			}
			else {
				if (c1->info == ColliderInfo::STAY && matrix[c1->type][c2->type] && c1->callback) {
					if (std::find(c1->collisions.begin(), c1->collisions.end(), c2) != c1->collisions.end()) {
						c1->callback->OnCollisionExit(c1, c2);
						c1->info = ColliderInfo::ENTER;
						c1->collisions.remove(c2);
					}
				}
				if (c2->info == ColliderInfo::STAY && matrix[c2->type][c1->type] && c2->callback) {
					if (std::find(c2->collisions.begin(), c2->collisions.end(), c1) != c2->collisions.end()) {
						c2->callback->OnCollisionExit(c2, c1);
						c2->info = ColliderInfo::ENTER;
						c2->collisions.remove(c1);
					}
				}
					
			}
		}
	}

	return true;
}

// Called before render is available
bool m1Collision::Update(float dt)
{
	BROFILER_CATEGORY("Collisions: Update", Profiler::Color::Magenta);
	if (App->debug)
		DebugDraw();

	return true;
}

void m1Collision::DebugDraw()
{

	Uint8 alpha = 80;
	for (std::vector<Collider*>::iterator item = colliders.begin(); item != colliders.end(); ++item)
	{
		if (*item == nullptr)
			continue;

		switch ((*item)->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad((*item)->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_PLAYER: // white
			App->render->DrawQuad((*item)->rect, 255, 0, 255, alpha);
			break;
		case COLLIDER_SHOP: // white
			App->render->DrawQuad((*item)->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_HOME: // white
			App->render->DrawQuad((*item)->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_NEXT_A: // white
			App->render->DrawQuad((*item)->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_LAST_A: // white
			App->render->DrawQuad((*item)->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_NEXT_B: // white
			App->render->DrawQuad((*item)->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_LAST_B: // white
			App->render->DrawQuad((*item)->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_MENU_QUEST: // white
			App->render->DrawQuad((*item)->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_CUTSCENE_BRIDGE: // white
			App->render->DrawQuad((*item)->rect, 0, 255, 255, alpha);
			break;
		}

	}
}

// Called before quitting
bool m1Collision::CleanUp()
{
	std::vector<Collider*>::iterator item = colliders.begin();
	while (item != colliders.end()) {
		if ((*item) != nullptr) {
			delete (*item);
			(*item) = nullptr;
			item = colliders.erase(item);
		}
		else ++item;
	}
	colliders.clear();

	return true;
}

Collider* m1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, m1Module* callback)
{
	Collider* ret = DBG_NEW Collider(rect, type, callback);
	colliders.push_back(ret);

	return ret;
}

bool m1Collision::DeleteCollider(Collider* col)
{
	bool ret = false;
	std::vector<Collider*>::iterator item = colliders.begin();
	for (; item != colliders.end();++item) {
		if ((*item) == col) {
			delete (*item);
			(*item) = nullptr;
			item = colliders.erase(item);
			ret = true;
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

std::vector<Collider*> m1Collision::GetColliders()
{
	return colliders;
}
