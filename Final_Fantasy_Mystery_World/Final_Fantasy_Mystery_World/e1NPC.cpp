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
	allow_turn = false;
}

bool e1NPC::Update(float dt) {

	return true;
}

bool e1NPC::LoadNPC(const char * name)
{
	bool ret = true;

	this->name.assign(name);

	static pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("assets/xml/NPC.xml");

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

			LoadGraphics(node);

			LoadBasicData(node);

			LoadMovement(node);

			LoadInteraction(node);
		}


		doc.reset();
	}

	return ret;
}

void e1NPC::LoadInteraction(pugi::xml_node &node)
{
	if (node.child("interaction") != nullptr) {
		interactable = node.child("interaction").attribute("value").as_bool("false");
		if (node.child("dialog_tree") != nullptr) {
			pugi::xml_node n_dialog = node.child("dialog_tree").child("dialog");
			for (; n_dialog; n_dialog = n_dialog.next_sibling()) {
				dialog_id.push_back(n_dialog.attribute("id").as_uint());
			}
		}
		look_to_player = node.child("interaction").attribute("look_to_player").as_bool("false");
	}
}

void e1NPC::LoadMovement(pugi::xml_node &node)
{
	move_type = (MovementType)node.child("move_type").attribute("id").as_int();
	if (move_type == MovementType::QUEUE) {
		pugi::xml_node n_move = node.child("move_type").child("move");
		for (; n_move; n_move = n_move.next_sibling()) {

			const char* dir = n_move.attribute("type").as_string();
			NPC_move tmp;

			if (strcmp(dir, "right") == 0)
				tmp.direction = Direction::RIGHT;
			else if (strcmp(dir, "left") == 0)
				tmp.direction = Direction::LEFT;
			else if (strcmp(dir, "up") == 0)
				tmp.direction = Direction::UP;
			else if (strcmp(dir, "down") == 0)
				tmp.direction = Direction::DOWN;

			tmp.num_tiles = n_move.attribute("num_tiles").as_int();

			move_vector.push_back(tmp);
		}
	}
}

void e1NPC::LoadBasicData(pugi::xml_node &node)
{
	pugi::xml_node n_data = node.child("data");

	direction = (Direction)n_data.child("init").attribute("direction").as_int(-1);
	state = (State)n_data.child("init").attribute("state").as_int(-1);

	if (n_data.child("init").attribute("anim_id") != nullptr) {
		current_animation = GetAnim((AnimationState)n_data.child("init").attribute("anim_id").as_int(-1));
	}
	else {
		ChangeAnimation(direction, state);
	}

	SetPivot(n_data.child("pivot").attribute("x").as_int(), n_data.child("pivot").attribute("y").as_int());

	size.create(n_data.child("size").attribute("width").as_int(), n_data.child("size").attribute("height").as_int());
}

void e1NPC::LoadGraphics(pugi::xml_node &node)
{
	if (node.child("tsx") != nullptr) {
		LoadEntityData(node.child("tsx").attribute("path").as_string());
	}
	else {
		pugi::xml_node n_anim = node.child("animations");
		data.tileset.texture = App->tex->Load(n_anim.attribute("texture").as_string());
		pugi::xml_node frame;
		for (n_anim = n_anim.child("animation"); n_anim; n_anim = n_anim.next_sibling()) {

			Animation* tmp_anim = GetAnim((AnimationState)n_anim.attribute("id").as_int());

			for (frame = n_anim.child("frame"); frame; frame = frame.next_sibling()) {
				tmp_anim->PushBack(SDL_Rect{ frame.attribute("x").as_int(),frame.attribute("y").as_int(),
					frame.attribute("width").as_int(), frame.attribute("height").as_int() });
			}
		}
	}
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

