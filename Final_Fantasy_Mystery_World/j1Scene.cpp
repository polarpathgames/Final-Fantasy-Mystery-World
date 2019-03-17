#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Pathfinding.h"
#include "j1Input.h"
#include "j1UIManager.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "EntityManager.h"
#include "j1Scene.h"
#include "MainMenu.h"
#include <string>

j1Scene::j1Scene() : j1Module()
{
	name.assign("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	//std::string map("iso_walk.tmx");
	
	App->map->Load("iso_walk2.tmx");
	/*SDL_Rect background_rect = { 0, 0, 1024, 768 };
	background = App->ui_manager->AddImage(0, 0, &background_rect, nullptr, this, nullptr);*/


	int w, h;
	uchar* data = NULL;
	if (App->map->CreateWalkabilityMap(w, h, &data))
		App->pathfinding->SetMap(w, h, data);

	CreateEntities();

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------


	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (first_update)
	{
		App->main_menu->Start();
		App->main_menu->active = true;
		App->entity_manager->active = false;
		first_update = false;
	}

	if (App->main_menu->active == true)
	{
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			App->ui_manager->DestroyUI();
			App->main_menu->active = false;
			App->entity_manager->active = true;
		 }
	}

	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 300 * dt;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 300 * dt;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 300 * dt;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 300 * dt;
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		App->map->Grid = !App->map->Grid;
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		int x = 0, y = 0;
		App->input->GetMousePosition(x, y);
		App->entity_manager->CreateEntity(Entity::EntityType::PLAYER, x, y, std::string());
	}
	//if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	//	App->entity_manager->CreateEnemy();
	/*if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		mock_image_ui = App->ui_manager->AddImage(0, 0, &mock_image_rect, nullptr, this, nullptr);*/

	App->map->Draw();



	

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);
	//App->render->ScreenToWorld(mouse.x, mouse.y);
	iPoint tile = App->map->WorldToMap(mouse.x, mouse.y);
	LOG("Tile: %i, %i", tile.x, tile.y);

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::CreateEntities()
{
	//iterate all objects of map made with Tiled to find entities

	for (std::list<ObjectLayer*>::iterator position = App->map->data.objects.begin(); position != App->map->data.objects.end(); position++) {
		if ((*position)->name == "player") {
			App->entity_manager->CreateEntity(Entity::EntityType::PLAYER, (*position)->coll_x, (*position)->coll_y, (*position)->name);
		}
		else if ((*position)->ent_type == "static") {
			//App->entity_manager->CreateEntity(Entity::EntityType::STATIC, (*position)->coll_x, (*position)->coll_y, (*position)->name);

		}
		else if ((*position)->ent_type == "enemy") {
			App->entity_manager->CreateEntity(Entity::EntityType::ENEMY, (*position)->coll_x, (*position)->coll_y, (*position)->name);
		}
		else {
			LOG("There isn't any entity with name %s and type %s", (*position)->name.data(), (*position)->ent_type.data());
		}
	}
}
