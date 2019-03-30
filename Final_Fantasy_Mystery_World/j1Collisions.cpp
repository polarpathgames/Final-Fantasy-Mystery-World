#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collisions.h"

#include "Brofiler/Brofiler.h"

j1Collision::j1Collision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
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

			switch (c1->type) {
			case COLLIDER_PLAYER: {
				if (c1->CheckCollision(c2->line) == true) {
					c2->collided_point = c1->collided_point;
					if (matrix[c1->type][c2->type] && c1->callback)
						c1->callback->OnCollision(c1, c2);

					if (matrix[c2->type][c1->type] && c2->callback)
						c2->callback->OnCollision(c2, c1);
				}
			} break;
			default: {
				if (c1->CheckCollision(c2->rect) == true) {
					if (matrix[c1->type][c2->type] && c1->callback)
						c1->callback->OnCollision(c1, c2);

					if (matrix[c2->type][c1->type] && c2->callback)
						c2->callback->OnCollision(c2, c1);
				}
			} break;
			}
		}
	}

	return true;
}

// Called before render is available
bool j1Collision::Update(float dt)
{
	BROFILER_CATEGORY("Collisions: Update", Profiler::Color::Magenta);
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;
	DebugDraw();


	return true;
}

void j1Collision::DebugDraw()
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
		case COLLIDER_WALL: // white
			App->render->DrawLine(colliders[i]->line.x1, colliders[i]->line.y1, colliders[i]->line.x2, colliders[i]->line.y2, 0, 0, 0, alpha);
			break;
		}

	}

}



// Called before quitting
bool j1Collision::CleanUp()
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

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
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

Collider * j1Collision::AddCollider(iLine line, COLLIDER_TYPE type, j1Module * callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(line, type, callback);
			break;
		}
	}

	return ret;
}



// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	bool ret;

	if (!HasIntersection(r.x, r.y, r.x + r.w, r.y, line.x1, line.y1, line.x2, line.y2) && !HasIntersection(r.x, r.y, r.x, r.y + r.h, line.x1, line.y1, line.x2, line.y2)
		&& !HasIntersection(r.x + r.w, r.y, r.x + r.w, r.y + r.h, line.x1, line.y1, line.x2, line.y2) && !HasIntersection(r.x, r.y + r.h, r.x + r.w, r.y + r.h, line.x1, line.y1, line.x2, line.y2)) {
		ret = false;
	}
	else {
		ret = true;
	}

	return ret;
}

bool Collider::CheckCollision(const iLine & l) const
{
	bool ret;

	if (!HasIntersection(rect.x, rect.y, rect.x + rect.w, rect.y, l.x1, l.y1, l.x2, l.y2) && !HasIntersection(rect.x, rect.y, rect.x, rect.y + rect.h, l.x1, l.y1, l.x2, l.y2)
		&& !HasIntersection(rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h, l.x1, l.y1, l.x2, l.y2) && !HasIntersection(rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h, l.x1, l.y1, l.x2, l.y2)) {
		ret = false;
	}
	else {
		ret = true;
	}

	return ret;
}



bool Collider::HasIntersection(const int &x1_1, const int &y1_1, const int &x2_1, const int &y2_1, const int &x1_2, const int& y1_2, const int &x2_2, const int &y2_2) const
{
	iPoint pos1, pos2, pos3, pos4;
	if (x1_1 > x2_1 || y1_1 > y2_1) {
		pos1 = { x2_1,y2_1 };
		pos2 = { x1_1,y1_1 };
	}
	else {
		pos1 = { x1_1,y1_1 };
		pos2 = { x2_1,y2_1 };
	}
	if (x1_2 > x2_2 || y1_2 > y2_2) {
		pos3 = { x2_2,y2_2 };
		pos4 = { x1_2,y1_2 };
	}
	else {
		pos3 = { x1_2,y1_2 };
		pos4 = { x2_2,y2_2 };
	}



	float s1_x, s1_y, s2_x, s2_y, sn, tn, sd, td, t;
	s1_x = pos2.x - pos1.x;     s1_y = pos2.y - pos1.y;
	s2_x = pos4.x - pos3.x;     s2_y = pos4.y - pos3.y;

	sn = -s1_y * (pos1.x - pos3.x) + s1_x * (pos1.y - pos3.y);
	sd = -s2_x * s1_y + s1_x * s2_y;
	tn = s2_x * (pos1.y - pos3.y) - s2_y * (pos1.x - pos3.x);
	td = -s2_x * s1_y + s1_x * s2_y;

	if (sn >= 0 && sn <= sd && tn >= 0 && tn <= td)
	{
		// Collision detected
		t = tn / td;
		collided_point.x = pos1.x + (tn * s1_x);
		collided_point.y = pos1.y + (td * s1_y);
		return true;
	}

	return false; // No collision



	/*double Epsilon = 1e-10;

	iPoint p{ x1_1,y1_1 };
	iPoint p2{ x2_1,y2_1 };

	iPoint q{ x1_2,y1_2 };
	iPoint q2{ x2_2,y2_2 };

	iPoint r = p2 - p;
	iPoint s = q2 - q;
	int rxs = r.Cross(s);
	int qpxr = (q - p).Cross(r);
	
	if (abs(rxs) < Epsilon && abs(qpxr) < Epsilon)
		return false;

	int t = (q - p).Cross(s) / rxs;


	int u = (q - p).Cross(r) / rxs;

	if (abs(rxs) < Epsilon && (0 <= t && t <= 1) && (0 <= u && u <= 1))
	{
		collided_point.x = p.x + t * r.x;
		collided_point.y = p.y + t * r.y;
		return true;
	}
	return false;

	*/




	/*

	float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;

	s10_x = x2_1 - x1_1;
	s10_y = y2_1 - y1_1;
	s02_x = x1_1 - x1_2;
	s02_y = y1_1 - y1_2;

	s_numer = s10_x * s02_y - s10_y * s02_x;
	if (s_numer < 0)
		return false; // No collision

	s32_x = x2_2 - x1_2;
	s32_y = y2_2 - y1_2;
	t_numer = s32_x * s02_y - s32_y * s02_x;
	if (t_numer < 0)
		return false; // No collision

	denom = s10_x * s32_y - s32_x * s10_y;
	if (s_numer > denom || t_numer > denom)
		return false; // No collision

				  // Collision detected
	t = t_numer / denom;

		collided_point.x = x1_1 + (t * s10_x);

		collided_point.y = y1_1 + (t * s10_y);

	return true;
	*/


	


}
