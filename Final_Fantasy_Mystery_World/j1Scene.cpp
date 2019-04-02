#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Pathfinding.h"
#include "j1UIManager.h"
#include "j1Collisions.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "ChangeControls.h"
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
#include "GUI_CheckBox.h"
#include "Sensor.h"
#include "Brofiler/Brofiler.h"
#include "j1Input.h"

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
	
	switch (menu_state) {
	case StatesMenu::NO_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			(App->ChangePause()) ? CreatePauseMenu() : DestroyPauseMenu();
		}
		break;
	case StatesMenu::CONTROLS_MENU:
		if (control_to_change != nullptr) {
			if (!control_to_change->Update()) {
				delete control_to_change;
				control_to_change = nullptr;
			}	
		}
		break;
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
	//LOG("Tile: %i, %i", tile.x, tile.y);

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	//delete control_to_change;
	//labels_control.clear();

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
	button_options->AddListener((j1Module*)App->scene);
	label_options = App->ui_manager->AddLabel(0, 0, "Options", 50, button_options, BLACK, "fonts/Munro.ttf", nullptr);
	label_options->SetPosRespectParent(CENTERED);

	menu_state = StatesMenu::PAUSE_MENU;
}

void j1Scene::DestroyPauseMenu()
{


	/*if(pause_panel != nullptr)
	App->ui_manager->DeleteUIElement(pause_panel);*/

	App->ui_manager->DeleteUIElement(pause_panel);
}

void j1Scene::CreateOptionsMenu()
{
	options_panel = App->ui_manager->AddImage(0, 0, { 1024,768,1024,768 }, this, App->ui_manager->screen, true, false, true);
	options_panel->SetPosRespectParent(CENTERED);
	
	button_general_volume = App->ui_manager->AddButton(491, 168, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true);
	button_general_volume->AddListener(this);
	label_general_volume = App->ui_manager->AddLabel(0, 0, "General Volume", 50, button_general_volume, BLACK, "fonts/Munro.ttf", nullptr);
	label_general_volume->SetPosRespectParent(LEFT_CENTERED);

	button_general_volume = App->ui_manager->AddButton(491, 246, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true);
	button_general_volume->AddListener(this);
	label_music_volume = App->ui_manager->AddLabel(0, 0, "Music Volume", 50, button_general_volume, BLACK, "fonts/Munro.ttf", nullptr);
	label_music_volume->SetPosRespectParent(LEFT_CENTERED);

	button_fx_volume = App->ui_manager->AddButton(491, 326, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true);
	button_fx_volume->AddListener(this);
	label_fx_volume = App->ui_manager->AddLabel(0, 0, "FX Volume", 50, button_fx_volume, BLACK, "fonts/Munro.ttf", nullptr);
	label_fx_volume->SetPosRespectParent(LEFT_CENTERED);
	
	label_fps = App->ui_manager->AddLabel(491, 413, "FPS Caps", 50, options_panel, BLACK, "fonts/Munro.ttf", nullptr);
	checkbox_fps = App->ui_manager->AddCheckBox(760, 413, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fps->is_option = true;
	checkbox_fps->draggable = false;
	checkbox_fps->drawable = true;
	checkbox_fps->interactable = true;
	checkbox_fps->AddListener(this);

	label_fullscreen = App->ui_manager->AddLabel(491, 503, "Fullscreen", 50, options_panel, BLACK, "fonts/Munro.tff", nullptr);
	checkbox_fullscreen = App->ui_manager->AddCheckBox(760, 503, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fullscreen->is_option = true;
	checkbox_fullscreen->draggable = false;
	checkbox_fullscreen->drawable = true;
	checkbox_fullscreen->interactable = true;
	checkbox_fullscreen->AddListener(this);

	button_controls = App->ui_manager->AddButton(491, 595, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true);
	button_controls->AddListener((j1Module*)App->scene);
	label_controls = App->ui_manager->AddLabel(0, 0, "Controls", 50, button_controls, BLACK, "fonts/Munro.ttf", nullptr);
	label_controls->SetPosRespectParent(LEFT_CENTERED);

	button_retun = App->ui_manager->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true);
	button_retun->AddListener((j1Module*)App->scene);
	label_return = App->ui_manager->AddLabel(0, 0, "Return", 50, button_retun, BLACK, "fonts/Munro.ttf", nullptr);
	label_return->SetPosRespectParent(CENTERED);

	menu_state = StatesMenu::OPTIONS_MENU;
}

void j1Scene::DestroyOptionsMenu()
{
	App->ui_manager->DeleteUIElement(options_panel);

}

void j1Scene::CreateControlsMenu()
{
	controls_panel = App->ui_manager->AddImage(0, 0, { 1024,768,1024,768 }, this, App->ui_manager->screen, true, false, true);
	controls_panel->SetPosRespectParent(CENTERED);

	keyboard = App->ui_manager->AddLabel(350, 265, "KEYBOARD", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);

	button_retun_to_options = App->ui_manager->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_retun_to_options->AddListener((j1Module*)App->scene);
	label_return_to_options = App->ui_manager->AddLabel(0, 0, "Return", 50, button_retun_to_options, BLACK, "fonts/Munro.ttf", nullptr);
	label_return_to_options->SetPosRespectParent(CENTERED);

	button_up = App->ui_manager->AddButton(340, 295, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_up->AddListener(this);
	label_to_show_how_up = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.UP, 50, button_up, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_up->SetPosRespectParent(CENTERED);
	label_up = App->ui_manager->AddLabel(300, 300, "Move Up", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_up);

	button_right = App->ui_manager->AddButton(340, 325, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_right->AddListener(this);
	label_to_show_how_right = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.RIGHT, 50, button_right, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_right->SetPosRespectParent(CENTERED);
	label_right = App->ui_manager->AddLabel(300, 330, "Move Right", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_right);

	button_left = App->ui_manager->AddButton(340, 355, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_left->AddListener(this);
	label_to_show_how_left = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.LEFT, 50, button_left, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_left->SetPosRespectParent(CENTERED);
	label_left = App->ui_manager->AddLabel(300, 360, "Move Left", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_left);

	button_down = App->ui_manager->AddButton(340, 385, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_left->AddListener(this);
	label_to_show_how_down = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DOWN, 50, button_down, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_down->SetPosRespectParent(CENTERED);
	label_down = App->ui_manager->AddLabel(300, 390, "Move Down", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_down);

	button_diagonals = App->ui_manager->AddButton(340, 415, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_diagonals->AddListener(this);
	label_to_show_how_diagonals = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIAGONALS, 50, button_diagonals, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_diagonals->SetPosRespectParent(CENTERED);
	label_diagonals = App->ui_manager->AddLabel(300, 420, "Use Diagonals", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_diagonals);

	button_direction_up = App->ui_manager->AddButton(340, 445, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_direction_up->AddListener(this);
	label_to_show_how_direction_up = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECTION_UP, 50, button_direction_up, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_direction_up->SetPosRespectParent(CENTERED);
	label_direction_up = App->ui_manager->AddLabel(300, 450, "Change Direction Up", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_direction_up);

	button_direction_right = App->ui_manager->AddButton(340, 475, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_direction_right->AddListener(this);
	label_to_show_how_direction_right = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT, 50, button_direction_right, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_direction_right->SetPosRespectParent(CENTERED);
	label_direction_right = App->ui_manager->AddLabel(300, 480, "Change Direction Right", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_direction_right);

	button_direction_left = App->ui_manager->AddButton(340, 505, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_direction_left->AddListener(this);
	label_to_show_how_direction_left = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECTION_LEFT, 50, button_direction_left, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_direction_left->SetPosRespectParent(CENTERED);
	label_direction_left = App->ui_manager->AddLabel(300, 510, "Change Direction Left", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_direction_left);

	button_direction_down = App->ui_manager->AddButton(340, 535, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_direction_down->AddListener(this);
	label_to_show_how_direction_down = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN, 50, button_direction_down, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_direction_down->SetPosRespectParent(CENTERED);
	label_direction_down = App->ui_manager->AddLabel(300, 540, "Change Direction Down", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_direction_down);

	button_basic_attack = App->ui_manager->AddButton(340, 560, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true);
	button_basic_attack->AddListener(this);
	label_to_show_how_basic_attack = App->ui_manager->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.BASIC_ATTACK, 50, button_basic_attack, BLACK, "fonts/Munro.ttf", nullptr);
	label_to_show_how_basic_attack->SetPosRespectParent(CENTERED);
	label_basic_attack = App->ui_manager->AddLabel(300, 565, "Basic Attack", 50, controls_panel, BLACK, "fonts/Munro.ttf", nullptr);
	labels_control.push_back(label_to_show_how_basic_attack);

	menu_state = StatesMenu::CONTROLS_MENU;
}

void j1Scene::DestroyControlsMenu()
{
	App->ui_manager->DeleteUIElement(controls_panel);

	labels_control.clear();


}

bool j1Scene::Interact(GUI* interact)
{
	bool ret = true;
	switch (menu_state) {
	case StatesMenu::PAUSE_MENU:
		if (interact == button_resume)
		{
			DestroyPauseMenu();
			if (App->GetPause())
				App->ChangePause();
			ret = false;
			menu_state = StatesMenu::NO_MENU;
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
			menu_state = StatesMenu::NO_MENU;
		}
		if (interact == button_options)
		{
			CreateOptionsMenu();
			DestroyPauseMenu();
			ret = false;
		}
		break;
	case StatesMenu::OPTIONS_MENU:
		if (interact == button_retun) {
			CreatePauseMenu();
			DestroyOptionsMenu();
		}
		if (interact == button_controls) {
			CreateControlsMenu();
			DestroyOptionsMenu();
		}
		break;
	case StatesMenu::CONTROLS_MENU:
		if (interact == button_retun_to_options) {
			CreateOptionsMenu();
			DestroyControlsMenu();
		}
		if (interact == button_up) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_up, &App->input->keyboard_buttons.buttons_code.UP, &App->input->keyboard_buttons.buttons_char.UP);
		}
		if (interact == button_right) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_right, &App->input->keyboard_buttons.buttons_code.RIGHT, &App->input->keyboard_buttons.buttons_char.RIGHT);
		}
		if (interact == button_left) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_left, &App->input->keyboard_buttons.buttons_code.LEFT, &App->input->keyboard_buttons.buttons_char.LEFT);
		}
		if (interact == button_down) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_down, &App->input->keyboard_buttons.buttons_code.DOWN, &App->input->keyboard_buttons.buttons_char.DOWN);
		}
		if (interact == button_diagonals) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_diagonals, &App->input->keyboard_buttons.buttons_code.DIAGONALS, &App->input->keyboard_buttons.buttons_char.DIAGONALS);
		}
		if (interact == button_direction_up) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_up, &App->input->keyboard_buttons.buttons_code.DIRECTION_UP, &App->input->keyboard_buttons.buttons_char.DIRECTION_UP);
		}
		if (interact == button_direction_right) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_right, &App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT, &App->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT);
		}
		if (interact == button_direction_left) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_left, &App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT, &App->input->keyboard_buttons.buttons_char.DIRECTION_LEFT);
		}
		if (interact == button_direction_down) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_down, &App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN, &App->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN);
		}
		if (interact == button_basic_attack) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_basic_attack, &App->input->keyboard_buttons.buttons_code.BASIC_ATTACK, &App->input->keyboard_buttons.buttons_char.BASIC_ATTACK);
		}
		break;
	}
	
	if (interact == checkbox_fps)
	{
		checkbox_fps->Clicked();
		//App->GetFrameRate();
	}

	//if (interact == checkbox_fullscreen)
	//{
	//	checkbox_fullscreen->Clicked();
	//	
	//	if (App->win->fullscreen) {
	//		App->win->fullscreen = false;
	//		SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_SHOWN);
	//		break;
	//	}
	//	else {
	//		App->win->fullscreen = true;
	//		SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_FULLSCREEN);
	//		break;
	//	}
	//}

	return ret;
}