#include "e1NPC.h"
#include "App.h"
#include "m1Render.h"
#include "m1Textures.h"
#include "m1Audio.h"
#include "m1EntityManager.h"
#include "Brofiler/Brofiler.h"
#include "p2Log.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "m1GUI.h"
#include "u1Image.h"
#include "m1Input.h"
#include "m1DialogSystem.h"
#include "m1Map.h"
#include "p2Math.h"
#include "m1Cutscene.h"
#include <string>

e1NPC::e1NPC(const int &x, const int &y, const char* name) : e1DynamicEntity(x, y)
{
	LoadNPC(name);
	type = e1Entity::EntityType::NPC;
	allow_turn = false;
}

bool e1NPC::Update(float dt) {

	if (interactable && !App->cutscene_manager->is_executing) {
		if (!is_quest_npc || (App->map->quest_rooms != nullptr && App->map->quest_rooms->actual_room != nullptr && !App->entity_manager->ThereAreEnemies())) {
			if (GetPosition().DistanceTo(App->scene->player->GetPosition()) <= distance_to_interact) {
				if (App->scene->GetMenuState() == StatesMenu::NO_MENU) {
					if (interacting == false) {
						CreateInteractionButton();
					}
					if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) {
						if (!dialog_id.empty()) {
							if (interacting) {
								if (App->dialog->end_dial)
									interacting = false;
							}
							else {
								App->scene->player->state = State::IDLE;
								App->scene->player->BlockControls(true);
								interacting = true;
								App->dialog->end_dial = false;
								App->audio->PlayFx(App->scene->fx_writting);
								DestroyInteractionButton();
								//Look to player
							}
							if (interacting) {
								uint id = *dialog_id.begin();
								App->dialog->PerformDialogue(id);
								if (dialog_id.size() > 1)
									dialog_id.pop_front();
							}
						}
						DoInteraction();
						state = State::IDLE;
						if (has_directions) {
							int tmp = (int)App->scene->player->direction;
							if (tmp >= 4) {
								tmp -= 4;
							}
							else {
								tmp += 4;
							}
							direction = (Direction)tmp;
						}
						ChangeAnimation(direction, state);
					}
				}
			}
			else {
				DestroyInteractionButton();
			}
		}
	}

	if (move_type == MovementType::QUEUE && interacting == false) {
		state = State::WALKING;
		DoMovement(dt);
		ChangeAnimation((*move_it).direction, state);
	}

	return true;
}

void e1NPC::DoMovement(float dt)
{
	if (position != destination || lerp_by < 1.0f) {
		lerp_by += (*move_it).speed * dt;
		new_position = lerp(initial_position, destination, lerp_by);
		position = new_position.AproximateToIntCast();
	}
	else {
		move_it++;
		if (move_it == move_vector.end()) {
			move_it = move_vector.begin();
		}
		lerp_by = 0.f;
		initial_position = position;
		destination = CalculateDestination((*move_it).direction, (*move_it).num_tiles);
	}
}

void e1NPC::DoInteraction() {
	switch (npc_type)
	{
	case e1NPC::NPCType::DAUGHTER:
		break;
	case e1NPC::NPCType::DOG:
		break;
	case e1NPC::NPCType::MUFI:
		break;
	case e1NPC::NPCType::WISE:
		break;
	case e1NPC::NPCType::SNOWMAN_HATER:
		break;
	case e1NPC::NPCType::WORRIED_MAN:
		break;
	case e1NPC::NPCType::CASUAL_VILLAGER:
		break;
	case e1NPC::NPCType::CASUAL_VILLAGER2:
		break;
	case e1NPC::NPCType::CASUAL_VILLAGER3:
		break;
	case e1NPC::NPCType::POLAR_KNIGHT:
		break;
	case e1NPC::NPCType::NONE:
		break;
	default:
		break;
	}
}

void e1NPC::DestroyInteractionButton()
{
	if (button_interact != nullptr) {
		App->gui->DeleteUIElement((u1GUI*)button_interact);
		button_interact = nullptr;
	}
}

void e1NPC::CreateInteractionButton()
{
	if (button_interact == nullptr) {
		button_interact = App->gui->AddImage(0, 0, { 1524,2052,31,31 }, nullptr, App->gui->screen, true, false, false, false);

		iPoint pos = App->gui->UIToGame({ App->scene->player->GetPosition().x, App->scene->player->position.y });

		pos.x -= button_interact->section.w*0.5F;
		pos.y -= button_interact->section.h;

		button_interact->SetPos(pos.x, pos.y);
	}
	else {
		iPoint pos = App->gui->UIToGame({ App->scene->player->GetPosition().x, App->scene->player->position.y });

		pos.x -= button_interact->section.w*0.5F;
		pos.y -= button_interact->section.h;

		button_interact->SetPos(pos.x, pos.y);
	}
}

void e1NPC::Draw(float dt) {
	if (drawable) {
		App->render->Blit(data.tileset.texture, new_position.x, new_position.y, &(current_animation->GetCurrentFrame(dt)), true);
	}
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
				tmp.direction = Direction::DOWN_RIGHT;
			else if (strcmp(dir, "left") == 0)
				tmp.direction = Direction::UP_LEFT;
			else if (strcmp(dir, "up") == 0)
				tmp.direction = Direction::UP_RIGHT;
			else if (strcmp(dir, "down") == 0)
				tmp.direction = Direction::DOWN_LEFT;

			tmp.num_tiles = n_move.attribute("num_tiles").as_int();
			tmp.speed = n_move.attribute("speed").as_float();

			move_vector.push_back(tmp);
		}
		move_it = move_vector.begin();
		if (move_it != move_vector.end()) {
			CalculateDestination((*move_it).direction, (*move_it).num_tiles);
		}
	}
}

iPoint e1NPC::CalculateDestination(const Direction & dir, const int num_tiles)
{
	actual_tile = App->map->WorldToMap(GetPosition().x, GetPosition().y);
	switch (dir)
	{
	case Direction::UP_LEFT:
		destination = actual_tile + iPoint{ -1, 0 } * num_tiles;
		break;
	case Direction::DOWN_LEFT:
		destination = actual_tile + iPoint{ 0, 1 } * num_tiles;
		break;
	case Direction::UP_RIGHT:
		destination = actual_tile + iPoint{ 0, -1 } * num_tiles;
		break;
	case Direction::DOWN_RIGHT:
		destination = actual_tile + iPoint{ 1, 0 } * num_tiles;
		break;
	default:
		LOG("No direction found");
		break;
	}
	destination = App->map->MapToWorldCentered(destination.x-1, destination.y) - pivot;
	return destination;
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
	distance_to_interact = n_data.child("distance_to_interact").attribute("value").as_int();
	is_quest_npc = n_data.child("is_quest").attribute("value").as_bool("false");
	has_directions = n_data.child("has_directions").attribute("value").as_bool();
	new_position = position.AproximateToFloat();
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
	if (button_interact != nullptr)
		App->gui->DeleteUIElement(button_interact);
}
