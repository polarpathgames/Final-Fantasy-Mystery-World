#ifndef __j1Collisions_H__
#define __j1Collisions_H__

#define MAX_COLLIDERS 500

#include "j1Module.h"
#include "SDL/include/SDL_rect.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	bool CanBeDeleted = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;
	bool enable = true;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	void SetShape(int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}

	void SetType(COLLIDER_TYPE type)
	{
		this->type = type;
	}
	bool CheckCollision(const SDL_Rect& r) const;
};

class j1Collision :
	public j1Module
{
public:
	j1Collision();
	~j1Collision();

	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);

	void DebugDraw();
	bool debug = false;

private:

	Collider * colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];

};

#endif
