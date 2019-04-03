#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1PerfTimer.h"
#include "StaticEntity.h"



class Sensor : public StaticEntity
{
public:

	enum class SensorType {

		TO_LOBBY,
		TO_QUEST_TUTORIAL,

		NONE
	};

public:

	Sensor(const int &x, const int &y, const SensorType &sensor_type);
	virtual ~Sensor();

	bool Update(float dt);

	bool CleanUp();

	bool Load(pugi::xml_node&) { return true; };
	bool Save(pugi::xml_node&) const { return true; };

public:

	Animation Idle;
	SensorType sensor_type;
	SDL_Texture * ground = nullptr;

};

#endif


