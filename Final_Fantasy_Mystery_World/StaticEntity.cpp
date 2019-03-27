#include "StaticEntity.h"
#include "j1App.h"
#include "j1Render.h"

StaticEntity::StaticEntity(int x, int y, const char * name):Entity(x,y)
{
	if (strcmp(name, "flower")) {
		type = StaticEntity::Type::FLOWER;
		frame = { 94,184,35,40 };
	}
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
