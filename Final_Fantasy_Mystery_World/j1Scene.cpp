#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Pathfinding.h"
#include "j1Input.h"
#include "j1UIManager.h"
#include "j1Collisions.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1FadeToBlack.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "j1Scene.h"
#include "MainMenu.h"
#include <string>
#include "GUI.h"
#include "GUI_Button.h"
#include "GUI_Label.h"
#include "GUI_Image.h"
#include "Sensor.h"
#include "Brofiler/Brofiler.h"

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
	
	//App->map->Load("iso_walk2.tmx");
	/*SDL_Rect background_rect = { 0, 0, 1024, 768 };
	background = App->ui_manager->AddImage(0, 0, &background_rect, nullptr, this, nullptr);*/
	if (App->GetPause())
		App->ChangePause();


	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateScene", Profiler::Color::Orange);
	// debug pathfing ------------------


	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("UpdateScene", Profiler::Color::Aqua);

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

	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
		App->fade_to_black->FadeToBlack(Maps::LOBBY);
	}
		
	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		App->fade_to_black->FadeToBlack(Maps::TUTORIAL);
	}
		
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && create_options == false) {
		(App->ChangePause()) ? CreatePauseMenu() : DestroyPauseMenu();
	}
	

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateScene", Profiler::Color::Purple);

	bool ret = true;

	//if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	//	ret = false;

	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);
	//App->render->ScreenToWorld(mouse.x, mouse.y);
	iPoint tile = App->map->WorldToMap(mouse.x, mouse.y);
//	LOG("Tile: %i, %i", tile.x, tile.y);

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
			App->entity_manager->CreateEntity(Entity::EntityType::PLAYER, App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y - 8).x, App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y - 8).y, (*position)->name);
		}
		else if ((*position)->ent_type == "static") {
			//App->entity_manager->CreateEntity(Entity::EntityType::STATIC, (*position)->coll_x, (*position)->coll_y, (*position)->name);

		}
		else if ((*position)->ent_type == "enemy") {
			App->entity_manager->CreateEntity(Entity::EntityType::ENEMY, App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y -8).x, App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y - 8).y, (*position)->name);
		}
		else if ((*position)->name == "sensor") {
			if ((*position)->ent_type == "ToLobby") {
				App->entity_manager->CreateEntity(Entity::EntityType::SENSOR, App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y - 8).x, App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y - 8).y, (*position)->name, Sensor::SensorType::TO_LOBBY);
			}
		}
		else if ((*position)->name == "collider") { // COLLIDERS
			if ((*position)->properties.FindNameValue("shop")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y - 8).x,App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y - 8).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_SHOP, nullptr);
			}
			else if ((*position)->properties.FindNameValue("home")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y - 8).x,App->map->TiledToWorld((*position)->coll_x + 1, (*position)->coll_y - 8).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_HOME, nullptr);
			}
		}
		else {
			LOG("There isn't any entity with name %s and type %s", (*position)->name.data(), (*position)->ent_type.data());
		}
	}
}

void j1Scene::CreatePauseMenu()
{
	pause_panel = App->ui_manager->AddImage(0, 0, { 1252,1536,313,428 }, this,App->ui_manager->screen, true,false,true);
	pause_panel->SetPosRespectParent(CENTERED);
	button_resume = App->ui_manager->AddButton(50, 50, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 },this, pause_panel, true,false,true);
	button_resume->AddListener(this);
	label_resume = App->ui_manager->AddLabel(0,0,"Continue",50, button_resume, BLACK, "fonts/Munro.ttf", nullptr);
	label_resume->SetPosRespectParent(CENTERED);

	button_main_menu = App->ui_manager->AddButton(50, 350, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true);
	button_main_menu->AddListener(this);
	label_main_menu = App->ui_manager->AddLabel(0, 0, "Return to main menu", 50, button_main_menu, BLACK, "fonts/Munro.ttf", nullptr);
	label_main_menu->SetPosRespectParent(CENTERED);

	button_abort_quest = App->ui_manager->AddButton(50, 250, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true);
	button_abort_quest->AddListener(this);
	label_abort_quest = App->ui_manager->AddLabel(0, 0, "Abort quest", 50, button_abort_quest, BLACK, "fonts/Munro.ttf", nullptr);
	label_abort_quest->SetPosRespectParent(CENTERED);

	button_options = App->ui_manager->AddButton(50, 150, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true);
	button_options->AddListener(this);
	label_options = App->ui_manager->AddLabel(0, 0, "Options", 50, button_options, BLACK, "fonts/Munro.ttf", nullptr);
	label_options->SetPosRespectParent(CENTERED);
}

void j1Scene::DestroyPauseMenu()
{
	
	if (App->GetPause())
		App->ChangePause();

	/*if(pause_panel != nullptr)
	App->ui_manager->DeleteUIElement(pause_panel);*/

	App->ui_manager->DeleteUIElement(pause_panel);
}

void j1Scene::CreateOptionsMenu()
{
	options_panel = App->ui_manager->AddImage(0, 0, { 1024,768,1024,768 }, this, App->ui_manager->screen, true, false, true);
	options_panel->SetPosRespectParent(CENTERED);
	
	button_general_volume = App->ui_manager->AddButton(491, 168, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, true, false, true);
	button_general_volume->AddListener(this);
	label_general_volume = App->ui_manager->AddLabel(0, 0, "General Volume", 50, button_general_volume, BLACK, "fonts/Munro.ttf", nullptr);
	label_general_volume->SetPosRespectParent(CENTERED);

	button_general_volume = App->ui_manager->AddButton(491, 246, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, true, false, true);
	button_general_volume->AddListener(this);
	label_music_volume = App->ui_manager->AddLabel(0, 0, "Music Volume", 50, button_general_volume, BLACK, "fonts/Munro.ttf", nullptr);
	label_music_volume->SetPosRespectParent(CENTERED);

	button_fx_volume = App->ui_manager->AddButton(491, 326, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, true, false, true);
	button_fx_volume->AddListener(this);
	label_fx_volume = App->ui_manager->AddLabel(0, 0, "FX Volume", 50, button_fx_volume, BLACK, "fonts/Munro.ttf", nullptr);
	label_fx_volume->SetPosRespectParent(CENTERED);
	
	label_fps = App->ui_manager->AddLabel(491, 413, "FPS Caps", 50, options_panel, BLACK, "fonts/Munro.ttf", nullptr);

	button_controls = App->ui_manager->AddButton(491, 495, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, true, false, true);
	button_controls->AddListener(this);
	label_controls = App->ui_manager->AddLabel(0, 0, "Controls", 50, button_controls, BLACK, "fonts/Munro.ttf", nullptr);
	label_controls->SetPosRespectParent(CENTERED);

	button_retun = App->ui_manager->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, true, false, true);
	button_retun->AddListener(this);
	label_return = App->ui_manager->AddLabel(0, 0, "Return", 50, button_retun, BLACK, "fonts/Munro.ttf", nullptr);
	label_return->SetPosRespectParent(CENTERED);

	create_options = true;
}

void j1Scene::DestroyOptionsMenu()
{
	App->ui_manager->DeleteUIElement(options_panel);

	create_options = false;
}

bool j1Scene::Interact(GUI* interact)
{
	bool ret = true;
	if (interact == button_resume)
	{
		DestroyPauseMenu();
		ret = false;
	}
	if (interact == button_main_menu)
	{
	
		/*App->fade_to_black->FadeToBlack(this, App->main_menu, 3.0f);*/
		App->ui_manager->DeleteAllUIElements();
		App->render->ResetCamera();
		App->entity_manager->active = false;
		App->entity_manager->CleanUp();
		App->map->active = false;
		App->map->CleanUp();
		this->active = false; //desactivates main menu
		App->main_menu->active = true;
		App->main_menu->Start();
		ret = false;
	}
	if (interact == button_options)
	{
		DestroyPauseMenu();
		CreateOptionsMenu();
		ret = false;
	}

	return ret;
}