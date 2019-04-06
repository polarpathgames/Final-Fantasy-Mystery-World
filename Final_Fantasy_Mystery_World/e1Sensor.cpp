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
	ground = app->tex->Load("textures/sensor_pos.png");

	type = e1Entity::EntityType::SENSOR;
	has_turn = false;
	this->sensor_type = sensor_type;
	actual_tile = app->map->WorldToMap(position.x, position.y);
}

e1Sensor::~e1Sensor()
{
}

bool e1Sensor::Update(float dt)
{

	if (app->scene->player->actual_tile == actual_tile) {
		switch (sensor_type) {
		case SensorType::TO_LOBBY:
			app->fade_to_black->FadeToBlack(Maps::LOBBY);
			break;
		default:
			LOG("This sensor has no type...");
			break;
		}
	}

	app->render->Blit(ground, app->map->MapToWorld(actual_tile.x, actual_tile.y).x, app->map->MapToWorld(actual_tile.x, actual_tile.y).y);


	return true;
}

bool e1Sensor::CleanUp()
{
	app->tex->UnLoad(ground);
	return true;
}
