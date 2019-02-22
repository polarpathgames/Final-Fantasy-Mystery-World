#ifndef __DYNAMICENTITY_H__
#define __DYNAMICENTITY_H__

#include "p2Point.h"
#include <string>
#include "p2Animation.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1PerfTimer.h"


enum EntityType;
struct SDL_Texture;

class DynamicEntity 
{
public:

	DynamicEntity();
	virtual ~DynamicEntity();
	
	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt);
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
	virtual bool Awake(pugi::xml_node&) { return true; };
	virtual void Draw(SDL_Texture* tex, float dt);
	
	virtual bool Load(pugi::xml_node&) { return true; };
	virtual bool Save(pugi::xml_node&) const { return true; };

	void LoadXML(std::string name_xml_file);
	Animation LoadPushbacks(pugi::xml_node&, std::string NameAnim) const;

public:

	EntityType type;

	iPoint position;

	Animation* current_animation = nullptr;
	Animation GoLeft;
	Animation GoRight;
	Animation GoDown;
	Animation GoUp;
	Animation IdleLeft;
	Animation IdleRight;
	Animation IdleUp;
	Animation IdleDown;


	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		node;

};

#endif
