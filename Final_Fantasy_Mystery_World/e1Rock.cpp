#include "e1Rock.h"
#include "App.h"
#include "m1Map.h"

e1Rock::e1Rock(const int &x, const int &y, const char* name) : e1StaticEntity(x, y, name)
{
	if (strcmp(name, "rock") == 0) {
		actual_tile = { x,y };
		frame = { 1030,4,28,12 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		position = App->map->MapToWorld(actual_tile.x, actual_tile.y);
		current_animation = idle;
	}
}
e1Rock::~e1Rock()
{
}

void e1Rock::GetHitted()
{

}