#include "Sensor.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1EntityManager.h"
#include "p2Log.h"
#include "j1FadeToBlack.h"
#include "j1Scene.h"
#include "j1Map.h"
#include <string>
#include "Player.h"

Sensor::Sensor(const int & x, const int & y, const SensorType &sensor_type) : StaticEntity(x,y,"")
{
	ground = App->tex->Load("textures/sensor_pos.png");

	type = Entity::EntityType::SENSOR;
	has_turn = false;
	this->sensor_type = sensor_type;
	actual_tile = App->map->WorldToMap(position.x, position.y);
}

Sensor::~Sensor()
{
}

bool Sensor::Update(float dt)
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

bool Sensor::CleanUp()
{
	App->tex->UnLoad(ground);
	return true;
}
