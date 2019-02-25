#include "Entity.h"
#include "j1App.h"
#include "EntityManager.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "p2Log.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::Draw(SDL_Texture * tex, float dt)
{
	App->render->Blit(tex, position.x, position.y, &(current_animation->GetCurrentFrame(dt)));
}

void Entity::LoadXML(std::string name_xml_file)
{
	config = App->LoadConfig(config_file, name_xml_file.data());
	switch (type) {
	case PLAYER:
		node = config.child("player");
		break;
	default:
		LOG("Could not LoadXML");
		break;
	}
}

Animation Entity::LoadPushbacks(pugi::xml_node &config, std::string NameAnim) const
{
	std::string XML_NAME_ANIM;
	SDL_Rect rect;
	Animation anim;
	XML_NAME_ANIM = "Animations";

	for (pugi::xml_node frames = config.child(XML_NAME_ANIM.data()).child(NameAnim.data()).child("frame"); frames; frames = frames.next_sibling("frame")) {
		rect.x = frames.attribute("x").as_int();
		rect.y = frames.attribute("y").as_int();
		rect.w = frames.attribute("w").as_int();
		rect.h = frames.attribute("h").as_int();
		anim.PushBack({ rect.x,rect.y,rect.w,rect.h });
	}
	anim.speed = config.child(XML_NAME_ANIM.data()).child(NameAnim.data()).attribute("speed").as_float();
	anim.loop = config.child(XML_NAME_ANIM.data()).child(NameAnim.data()).attribute("loop").as_bool();

	return anim;
}
