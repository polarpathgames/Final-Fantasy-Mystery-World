#ifndef __m1Collisions_H__
#define __m1Collisions_H__

#define MAX_COLLIDERS 500

#include "m1Module.h"
#include "SDL/include/SDL_rect.h"
#include "p2Line.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE,
	COLLIDER_PLAYER,
	COLLIDER_SHOP,
	COLLIDER_HOME,
	COLLIDER_NEXT_A,
	COLLIDER_NEXT_B,
	COLLIDER_LAST_A,
	COLLIDER_LAST_B,


	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	iLine line;

	bool to_delete = false;
	bool CanBeDeleted = false;
	COLLIDER_TYPE type;
	m1Module* callback = nullptr;
	mutable iPoint collided_point{ 0,0 };
	bool enable = true;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, m1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	Collider(iLine line, COLLIDER_TYPE type, m1Module* callback = nullptr) :
		line(line),
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

class m1Collision :	public m1Module
{
public:
	m1Collision();
	~m1Collision();

	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, m1Module* callback = nullptr);


	void DebugDraw();
	bool debug = false;

private:

	Collider * colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];

	

};

#endif
