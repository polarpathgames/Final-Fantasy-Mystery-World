#include "e1Sensor.h"
#include "m1Input.h"
#include "App.h"
#include "m1Render.h"
#include "m1Textures.h"
#include "m1Audio.h"
#include "m1EntityManager.h"
#include "p2Log.h"
#include "m1FadeToBlack.h"
#include "m1Scene.h"
#include "m1Map.h"
#include <string>
#include "e1Player.h"

e1Sensor::e1Sensor(const int & x, const int & y, const SensorType &sensor_type) : e1StaticEntity(x,y,"")
{
	ground = App->tex->Load("textures/sensor_pos.png");

	type = e1Entity::EntityType::SENSOR;
	has_turn = false;
	this->sensor_type = sensor_type;
	actual_tile = App->map->WorldToMap(position.x, position.y);
}

e1Sensor::~e1Sensor()
{
}

bool e1Sensor::Update(float dt)
{

	if (App->scene->player->actual_tile == actual_tile) {
		switch (sensor_type) {
		case SensorType::TO_LOBBY:
			App->fade_to_black->FadeToBlack(Maps::LOBBY);
			break;
		default:
			LOG("This sensor has no type...");
			break;
		}
	}

	App->render->Blit(ground, App->map->MapToWorld(actual_tile.x, actual_tile.y).x, App->map->MapToWorld(actual_tile.x, actual_tile.y).y);


	return true;
}

bool e1Sensor::CleanUp()
{
	App->tex->UnLoad(ground);
	return true;
}
