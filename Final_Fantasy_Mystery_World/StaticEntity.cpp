#include "StaticEntity.h"
#include "j1App.h"
#include "j1Render.h"

StaticEntity::StaticEntity(int x, int y, const char * name):Entity(x,y)
{
	if (strcmp(name, "flower")) {
		
	}

	static_type = StaticEntity::Type::FLOWER;
	frame = { 94,184,35,40 };
	size.create(35, 40);
	position.x = 0;
	position.y = 0;
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
