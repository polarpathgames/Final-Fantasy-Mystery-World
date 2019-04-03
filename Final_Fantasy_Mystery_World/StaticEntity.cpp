#include "StaticEntity.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"

StaticEntity::StaticEntity(int x, int y, const char * name):Entity(x,y)
{
	if (strcmp(name,"flower") == 0) {
		static_type = StaticEntity::Type::FLOWER;
		frame = { 128,96,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree1") == 0) {
		static_type = StaticEntity::Type::FLOWER;
		frame = { 128,96,32,32 };
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree2") == 0) {
		static_type = StaticEntity::Type::FLOWER;
		frame = { 128,96,32,32 };
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree3") == 0) {
		static_type = StaticEntity::Type::FLOWER;
		frame = { 128,96,32,32 };
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "barrel") == 0) {
		static_type = StaticEntity::Type::BARREL;
		frame = { 32,96,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else {
		LOG("Doesn't have any entity with name %s", name);
	}

	
	type = Entity::EntityType::STATIC;
}

StaticEntity::~StaticEntity()
{
}

void StaticEntity::Draw(SDL_Texture * tex, float dt)
{
	App->render->Blit(tex, position.x, position.y, &frame, true);
}

void StaticEntity::SetRect(int x, int y, int w, int h)
{
	frame = { x,y,w,h };
}
