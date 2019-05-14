#include "App.h"
#include "p2Log.h"
#include "m1Render.h"
#include "m1Fonts.h"
#include "m1GUI.h"
#include "m1EntityManager.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "m1MenuManager.h"
#include "m1Input.h"
#include "m1CutScene.h"
#include "c1CutsceneMoveCamera.h"
#include "c1CutsceneMoveEntity.h"
#include "c1CutsceneModifyText.h"
#include "c1CutsceneModifyImage.h"
#include "c1CutsceneEntity.h"
#include "c1CutsceneText.h"
#include "c1CutsceneImage.h"
#include "c1CutSceneDeleteEntity.h"
#include "c1CutSceneAddAudio.h"
#include "u1Bar.h"


m1CutScene::m1CutScene()
{
	name = "cutscene_manager";
}

bool m1CutScene::Awake(pugi::xml_node &config)
{
	LOG("Starting Cutscene Manager:");


	return true;
}

bool m1CutScene::Update(float dt)
{
	if (is_executing)
		ExecuteCutscene(dt);

	return true;
}

bool m1CutScene::CleanUp()
{

	return true;
}


void m1CutScene::PlayCutscene(std::string path)
{
	if (!is_executing)
	{
		LoadCutscene(path);
		SetExecuting(true);
		App->menu_manager->SkipMenu(true);
	}
}

bool m1CutScene::LoadCutscene(std::string path)
{
	//TODO 1: Iterate the differents cutscene. Save the cutscene in the cutscenes vector.

	bool ret = false;
	App->menu_manager->EnableHUD(false);
	App->scene->player->BlockControls(true);
	pugi::xml_parse_result result = cutscene_file.load_file(path.c_str());

	if (result == NULL)
		LOG("Could not load map xml file cutscene.xml. Pugi error: %s", result.description());
	else
	{
		ret = true;

		c1CutsceneAction* cutscene_action = nullptr;

		for (pugi::xml_node cutscene_action_node = cutscene_file.first_child().child("actions").child("cutscene"); cutscene_action_node; cutscene_action_node = cutscene_action_node.next_sibling())
		{
			std::string action = cutscene_action_node.attribute("action").as_string();

			uint start = cutscene_action_node.child("time").attribute("start").as_uint();
			uint duration = cutscene_action_node.child("time").attribute("duration").as_uint();

			if (action == "move_camera")
			{
				cutscene_action = DBG_NEW c1CutsceneMoveCamera(start, duration, 
					cutscene_action_node.child("time").attribute("origin_x").as_int(App->render->camera.x), cutscene_action_node.child("time").attribute("origin_y").as_int(App->render->camera.y),
					cutscene_action_node.child("time").attribute("destination_x").as_int(-1 * (App->scene->player->position.x - App->render->camera.w * 0.5F)), cutscene_action_node.child("time").attribute("destination_y").as_int(-1*(App->scene->player->position.y + App->render->camera.h * 0.5F)),
					cutscene_action_node.child("time").attribute("speed").as_float(), cutscene_action_node.child("time").attribute("stop_goal").as_bool(false));
			}
			else if (action == "move_entity")
			{
				cutscene_action = DBG_NEW c1CutsceneMoveEntity(start, duration,
					cutscene_action_node.child("time").attribute("speed_x").as_float(), cutscene_action_node.child("time").attribute("speed_y").as_float(),
					cutscene_action_node.attribute("entity").as_string());
			}
			else if (action == "modify_text")
			{
				cutscene_action = DBG_NEW c1CutsceneModifyText(start, duration,
					cutscene_action_node.attribute("name").as_string(),
					cutscene_action_node.child("time").attribute("type").as_string(),
					cutscene_action_node.child("time").attribute("text").as_string());
			}
			else if (action == "modify_image")
			{
				cutscene_action = DBG_NEW c1CutsceneModifyImage(start, duration,
					cutscene_action_node.attribute("name").as_string(),
					cutscene_action_node.child("time").attribute("type").as_string());
			}
			else if (action == "delete_entity")
			{
				cutscene_action = DBG_NEW c1CutSceneDeleteEntity(start, duration, cutscene_action_node.attribute("entity").as_string());

			}
			else if (action == "add_audio")
			{
				cutscene_action = DBG_NEW c1CutSceneAddAudio(start, duration, cutscene_action_node.attribute("entity").as_string(), cutscene_action_node.attribute("path").as_string());
			}
			actions.push_back(cutscene_action);
		}

		c1CutsceneElement* cutscene_element = nullptr;


		for (pugi::xml_node cutscene_element_node = cutscene_file.first_child().child("elements").child("element"); cutscene_element_node; cutscene_element_node = cutscene_element_node.next_sibling())
		{
			std::string type = cutscene_element_node.attribute("type").as_string();
			std::string name = cutscene_element_node.attribute("name").as_string();

			if (type == "entity")
			{
				cutscene_element = DBG_NEW c1CutsceneEntity(cutscene_element_node.attribute("pos_x").as_int(),
					cutscene_element_node.attribute("pos_y").as_int(),
					cutscene_element_node.attribute("name").as_string());
			}
			else if (type == "text")
			{
				cutscene_element = DBG_NEW c1CutsceneText(cutscene_element_node.attribute("pos_x").as_int(),
					cutscene_element_node.attribute("pos_y").as_int(),
					cutscene_element_node.attribute("txt").as_string(),
					cutscene_element_node.attribute("size").as_uint(),
					cutscene_element_node.attribute("active").as_bool(true)
				);
			}
			else if (type == "image")
			{
				cutscene_element = DBG_NEW c1CutsceneImage(cutscene_element_node.attribute("pos_x").as_int(),
					cutscene_element_node.attribute("pos_y").as_int(),
					{
						cutscene_element_node.attribute("rect_x").as_int(),
						cutscene_element_node.attribute("rect_y").as_int(),
						cutscene_element_node.attribute("rect_w").as_int(),
						cutscene_element_node.attribute("rect_h").as_int()
					},
					cutscene_element_node.attribute("active").as_bool(true));
			}

			cutscene_element->active = cutscene_element_node.attribute("active").as_bool(true);
			elements.insert(std::pair <std::string, c1CutsceneElement*>(name, cutscene_element));
		}
	}

	return ret;
}

void m1CutScene::ExecuteCutscene(float dt)
{
	if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && !skip_cutscene) || (App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_A) == KEY_REPEAT && !skip_cutscene)) {
		if (App->menu_manager->br_skipper->current_width >= App->menu_manager->br_skipper->max_width)
		{
			skip_cutscene = true;
		}
		App->menu_manager->br_skipper->UpdateBar(300*dt, UIType::SKIPBAR);
	}
	else {
		App->menu_manager->br_skipper->UpdateBar(-300*dt, UIType::SKIPBAR);
	}
	if (is_executing)
	{
		if (start) {
			cutscene_timer.Start();

			item = actions.begin();
			start = false;
		}

		if ((cutscene_timer.ReadMs() - (*item)->start_time) > (*item)->duration_time)
		{
			++item;
		}

		if (item != actions.end())
		{
			if (cutscene_timer.ReadMs() > (*item)->start_time || (*item)->duration_time == 0)
				(*item)->Execute(dt);
		}
		else
		{
			is_executing = false;
			start = true;
			ClearCutscene();
			App->menu_manager->SkipMenu(false);
		}
	}
	if (skip_cutscene)
	{
		int cont = 0;
		for (pugi::xml_node cutscene_action_node = cutscene_file.first_child().child("actions").child("cutscene"); cutscene_action_node; cutscene_action_node = cutscene_action_node.next_sibling())
		{
			std::string action = cutscene_action_node.attribute("action").as_string();
			if (action == "delete_entity")
				actions[cont]->Execute(dt);

			cont++;
		}
		is_executing = false;
		start = true;
		ClearCutscene();
		skip_cutscene = false;
		App->menu_manager->SkipMenu(false);
	}
		

}

void m1CutScene::ClearCutscene()
{
	for (std::vector<c1CutsceneAction*>::iterator it = actions.begin(); it != actions.end(); ++it)
	{
		delete (*it);
		*it = nullptr;
	}

	actions.clear();
	
	for (std::map<std::string, c1CutsceneElement*>::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
	cutscene_file.reset();
	elements.clear();
	App->menu_manager->EnableHUD(true);
	App->scene->player->BlockControls(false);
}

double m1CutScene::GetTimer()
{
	return cutscene_timer.ReadMs();
}

void m1CutScene::SetExecuting(bool executing)
{
	is_executing = executing;
}
