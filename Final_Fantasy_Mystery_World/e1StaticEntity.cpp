#include "e1StaticEntity.h"
#include "p2Log.h"
#include "App.h"
#include "m1Render.h"

e1StaticEntity::e1StaticEntity(int x, int y, const char * name):e1Entity(x,y)
{
	if (strcmp(name,"flower") == 0) { // finished
		static_type = e1StaticEntity::Type::FLOWER;
		frame = { 128,96,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree1") == 0) { // finished
		static_type = e1StaticEntity::Type::TREE1;
		frame = { 128,0,32,64 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree2") == 0) { // finished
		static_type = e1StaticEntity::Type::TREE2;
		frame = { 96,64,32,64 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "tree3") == 0) { // finished
		static_type = e1StaticEntity::Type::TREE3;
		frame = { 64,64,32,64 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "barrel") == 0) { // finished
		static_type = e1StaticEntity::Type::BARREL;
		frame = { 32,96,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "streetlight") == 0) { // finished
		static_type = e1StaticEntity::Type::STREETLIGHT;
		frame = { 0,64,32,64 };
		SetPivot(frame.w*0.5F, frame.h*0.9F);
		size.create(frame.w, frame.h);
	}
	else if (strcmp(name, "plant1") == 0) {
		static_type = e1StaticEntity::Type::PLANT1;
		frame = { 32,96,32,32 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
	}
	else {
		LOG("Doesn't have any entity with name %s", name);
	}

	
	type = e1Entity::EntityType::STATIC;
}

e1StaticEntity::~e1StaticEntity()
{
}

void e1StaticEntity::Draw(SDL_Texture * tex, float dt)
{
	App->render->Blit(tex, position.x, position.y, &frame, true);
}

void e1StaticEntity::SetRect(int x, int y, int w, int h)
{
	frame = { x,y,w,h };
}
