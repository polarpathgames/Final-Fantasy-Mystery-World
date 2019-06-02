#include "e1NPC.h"
#include "App.h"
#include "m1Render.h"
#include "m1Textures.h"
#include "m1Audio.h"
#include "m1EntityManager.h"
#include "Brofiler/Brofiler.h"
#include "p2Log.h"
#include <string>

e1NPC::e1NPC(const int &x, const int &y, const char* name) : e1DynamicEntity(x, y)
{
	LoadNPC(name);
	type = e1Entity::EntityType::NPC;
	current_animation = &anim.IdleDownLeft;
	SetPivot(10, 30);
	allow_turn = false;
	direction = Direction::DOWN_LEFT;
}

bool e1NPC::LoadNPC(const char * name)
{
	bool ret = true;

	this->name.assign(name);

	static pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("assets/xml/p2NPC.xml");

	if (result == NULL)
	{
		LOG("Could not load map xml file p2NPC.xml. pugi error: %s", result.description());
		ret = false;
	}

	if (ret) {
		pugi::xml_node node = doc.child("data");
		for (node = node.child("npc"); node; node = node.next_sibling()) {
			if (strcmp(node.attribute("name").as_string(), name) == 0)
				break;
		}

		if (!node) {
			LOG("Node %s not found", name);
			ret = false;
		}
		else {

			npc_type = (NPCType)node.attribute("id").as_int(-1);

			if (node.child("tsx") != nullptr) {
				LoadEntityData(node.child("tsx").attribute("path").as_string());
			}
			else {
				pugi::xml_node n_anim = node.child("animation");
				pugi::xml_node frame;
				Animation* temp_anim = nullptr;
				for (; n_anim; n_anim = n_anim.next_sibling()) {

					temp_anim = GetAnim((AnimationState)n_anim.attribute("id").as_int());

					for (frame = n_anim.child("frame"); frame; frame = frame.next_sibling()) {
						temp_anim->PushBack(SDL_Rect{ frame.attribute("x").as_int(),frame.attribute("y").as_int(),
							frame.attribute("width").as_int(), frame.attribute("height").as_int() });
					}
				}
			}

			pugi::xml_node n_data = node.child("data");

			if (n_data.child("init").attribute("anim_id") != nullptr) {
				current_animation = GetAnim((AnimationState)n_data.child("init").attribute("anim_id").as_int(-1));
			}
			else {
				ChangeAnimation((Direction)n_data.child("init").attribute("direction").as_int(-1), (State)n_data.child("init").attribute("state").as_int(-1));
			}

			
		}


		doc.reset();
	}

	return ret;
}

e1NPC::~e1NPC()
{
}

bool e1NPC::Load(pugi::xml_node &)
{
	return true;
}

bool e1NPC::Save(pugi::xml_node &) const
{
	return true;
}

bool e1NPC::CleanUp()
{
	return true;
}

