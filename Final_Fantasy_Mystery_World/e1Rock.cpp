#include "e1Rock.h"
#include "App.h"
#include "m1Map.h"
#include "m1Render.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "m1Audio.h"

e1Rock::e1Rock(const int &x, const int &y, const char* name) : e1StaticEntity(x, y, name)
{
	if (strcmp(name, "rock") == 0) {
		original_pos = { x,y };
		frame = { 755,91,40,37 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = App->map->WorldToMap(x, y);
		actual_tile += {1, 1};
		position.y -= 5;
		position.x -= 2;
		static_type = e1StaticEntity::Type::BREAKABLE_ROCK;
		rock_type = RockType::NORMAL_ROCK;
	}
	else if (strcmp(name, "white_rock") == 0) {
		original_pos = { x,y };
		frame = { 755,187,40,37 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = App->map->WorldToMap(x, y);
		actual_tile += {1, 1};
		position.y -= 5;
		position.x -= 2;
		static_type = e1StaticEntity::Type::BREAKABLE_ROCK;
		rock_type = RockType::WHITE_ROCK;
	}
	else if (strcmp(name, "grey_rock") == 0) {
		original_pos = { x,y };
		frame = { 755,140,40,37 };
		SetPivot(frame.w*0.35F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = App->map->WorldToMap(x, y);
		actual_tile += {1, 1};
		position.y -= 5;
		position.x -= 2;
		static_type = e1StaticEntity::Type::BREAKABLE_ROCK;
		rock_type = RockType::GREY_ROCK;
	}
	else if (strcmp(name, "breakable_barrel") == 0) {
		original_pos = { x,y };
		frame = { 438,122,35,31 };
		SetPivot(frame.w*0.5F, frame.h*0.8F);
		size.create(frame.w, frame.h);
		actual_tile = App->map->WorldToMap(x, y);
		actual_tile += {1, 1}; 
		position.y -= 5;
		position.x -= 2;
		static_type = e1StaticEntity::Type::BREAKABLE_ROCK;
		rock_type = RockType::BREAKABLE_BARREL;
	}
}
e1Rock::~e1Rock()
{
}

void e1Rock::GetHitted()
{
	if (!hitted) {
		App->render->CameraTremble(0.59F, 1.3F);
		App->audio->PlayFx(App->scene->fx_rock);
		has_animation = true;
		idle = DBG_NEW Animation();
		current_animation = idle;
		if (rock_type == RockType::NORMAL_ROCK) {
			idle->PushBack({ 795,91,32,37 });
			idle->PushBack({ 835,91,32,37 });
			idle->PushBack({ 875,91,32,37 });
			idle->PushBack({ 915,91,32,37 });
			idle->PushBack({ 955,91,32,37 });
		}
		else if (rock_type == RockType::WHITE_ROCK) {
			idle->PushBack({ 795,187,32,37 });
			idle->PushBack({ 835,187,32,37 });
			idle->PushBack({ 875,187,32,37 });
			idle->PushBack({ 915,187,32,37 });
			idle->PushBack({ 955,187,32,37 });
		}
		else if (rock_type == RockType::GREY_ROCK) {
			idle->PushBack({ 438,122,35,31 });
			idle->PushBack({ 835,140,32,37 });
			idle->PushBack({ 875,140,32,37 });
			idle->PushBack({ 915,140,32,37 });
			idle->PushBack({ 955,140,32,37 });
		}
		else if (rock_type == RockType::BREAKABLE_BARREL) {
			idle->PushBack({ 473,122,35,31 });
			idle->PushBack({ 508,122,35,31 });
			idle->PushBack({ 543,122,35,31 });
			idle->PushBack({ 578,122,35,31 });
			idle->PushBack({ 613,122,35,31 });
		}
		idle->loop = false;
		idle->speed = 10;
		hitted = true;
		App->map->data.no_walkables.remove(actual_tile + iPoint{ 0,-1 });
		App->map->quest_rooms->AddEntityToNotRepeat(original_pos);
	}
}
