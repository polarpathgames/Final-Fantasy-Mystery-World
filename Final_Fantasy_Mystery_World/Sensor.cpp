#include "Sensor.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1EntityManager.h"
#include "j1Map.h"
#include <string>
#include "Player.h"

Sensor::Sensor(const int & x, const int & y, const SensorType &sensor_type) : StaticEntity(x,y)
{
	ground = App->tex->Load("textures/sensor_pos.png");

	this->sensor_type = sensor_type;
}

Sensor::~Sensor()
{
}

bool Sensor::Update(float dt)
{

	App->render->Blit(ground, position.x, position.y, NULL);
	return true;
}

bool Sensor::CleanUp()
{
	App->tex->UnLoad(ground);
	return true;
}
