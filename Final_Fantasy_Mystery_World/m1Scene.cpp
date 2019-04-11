#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "m1GUI.h"
#include "m1Collisions.h"
#include "m1Audio.h"
#include "p2ChangeControls.h"
#include "m1Render.h"
#include "m1FadeToBlack.h"
#include "m1Window.h"
#include "m1Map.h"
#include "e1Player.h"
#include "m1EntityManager.h"
#include "m1Scene.h"
#include "m1MainMenu.h"
#include <string>
#include "u1UI_Element.h"
#include "u1Button.h"
#include "u1Label.h"
#include "u1Image.h"
#include "u1Slider.h"
#include "u1CheckBox.h"
#include "Brofiler/Brofiler.h"
#include "m1Input.h"

m1Scene::m1Scene() : m1Module()
{
	name.assign("scene");

}

// Destructor
m1Scene::~m1Scene()
{}

// Called before render is available
bool m1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool m1Scene::Start()
{
	if (App->GetPause())
		App->ChangePause();

	if (App->GetInventory())
		App->ChangeInventory();

	App->gui->ShowCursor(false);
  
	return true;
}

// Called each loop iteration
bool m1Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateScene", Profiler::Color::Orange);

	return true;
}

// Called each loop iteration
bool m1Scene::Update(float dt)
{
	BROFILER_CATEGORY("UpdateScene", Profiler::Color::Aqua);

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		if (debug_screen == nullptr) {
			CreateDebugScreen();
		}
		else {
			DestroyDebugScreen();
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
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
		App->map->grid = !App->map->grid;

	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
		App->fade_to_black->FadeToBlack(Maps::LOBBY);
	}
		
	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		App->fade_to_black->FadeToBlack(Maps::TUTORIAL);
	}

	if (App->input->GetKey(SDL_SCANCODE_KP_1) == KEY_DOWN) {
		App->win->scale = 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_KP_2) == KEY_DOWN) {
		App->win->scale = 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_KP_3) == KEY_DOWN) {
		App->win->scale = 3;
	}
		
	App->map->Draw();
	
	switch (menu_state) {
	case StatesMenu::NO_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN) {
			if (App->ChangePause()) {
				CreatePauseMenu();
				player->BlockControls(true);
			}
			else {
				DestroyPauseMenu();
				player->BlockControls(false);
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_X) == KEY_DOWN) {
			if (App->ChangeInventory()) {
				CreateInventory();
				player->BlockControls(true);
			}
			else {
				DestroyInventory();
				player->BlockControls(false);
			}
		}
		break;
	case StatesMenu::INVENTORY_MENU:
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_X) == KEY_DOWN) {
			if (App->ChangeInventory()) {
				CreateInventory();
				player->BlockControls(true);
			}
			else {
				DestroyInventory();
				player->BlockControls(false);
			}
		}
		break;
	case StatesMenu::PAUSE_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN) {
			App->ChangePause();
			DestroyPauseMenu();
			menu_state = StatesMenu::NO_MENU;
			player->BlockControls(false);
		}
		break;
	case StatesMenu::OPTIONS_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN) {
			CreatePauseMenu();
			DestroyOptionsMenu();
			player->BlockControls(true);
		}
		break;
	case StatesMenu::CONTROLS_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN) {
			CreateOptionsMenu();
			DestroyControlsMenu();
		}
		if (control_to_change != nullptr && !control_to_change->Update()) {
			delete control_to_change;
			control_to_change = nullptr;
		}
		break;
	}

	if (debug_screen != nullptr) {
		UpdateDebugScreen();
	}

	//if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	//	App->audio->VolumeDown(-1);

	//if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	//	App->audio->VolumeUp(-1);

	//if (!App->audio->mute_volume) Mix_VolumeMusic(slider_music_volume->GetValue());
	//if (!App->audio->mute_fx) App->audio->SliderVolumeFx(slider_fx_volume->GetValue());
	//App->audio->volume = slider_music_volume->GetValue(); This crashes
	//App->audio->volume_fx = slider_fx_volume->GetValue(); This crashes

	return true;
}

// Called each loop iteration
bool m1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateScene", Profiler::Color::Purple);

	bool ret = true;

	/*iPoint mouse;
	app->input->GetMousePosition(mouse.x, mouse.y);
	app->render->ScreenToWorld(mouse.x, mouse.y);
	iPoint tile = app->map->WorldToMap(mouse.x, mouse.y);*/
	//LOG("Tile: %i, %i", tile.x, tile.y);

	return ret;
}

// Called before quitting
bool m1Scene::CleanUp()
{
	LOG("Freeing scene");

	//delete control_to_change;
	//labels_control.clear();

	return true;
}

void m1Scene::CreateEntities()
{
	//iterate all objects of map made with Tiled to find entities

	for (std::list<ObjectLayer*>::iterator position = App->map->data.objects.begin(); position != App->map->data.objects.end(); position++) {
		if ((*position)->name == "player") {
			if (player == nullptr) {
				if ((*position)->ent_type == "default") { // start position
					player = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::PLAYER, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
					App->render->CenterCameraOnPlayer(player->position);
				}
			}
			else {
				if ((*position)->ent_type == "shop" && App->map->last_map == Maps::SHOP) { // position after leaving shop
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "home" && App->map->last_map == Maps::HOME){ // position after leaving home
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "in_shop") { // position in the shop
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "in_home" && player->state != State::DEATH) { // position in the home
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "after_death" && player->state == State::DEATH) { // position in the home
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "default" && App->map->last_map == Maps::TUTORIAL) {
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
			}
		}
		else if ((*position)->ent_type == "static") {
			App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
		}
		else if ((*position)->ent_type == "enemy") {
			App->entity_manager->CreateEntity(e1Entity::EntityType::ENEMY, App->map->TiledToWorld((*position)->coll_x , (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
		}
		else if ((*position)->name == "collider") { // COLLIDERS
			if ((*position)->properties.FindNameValue("shop")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_SHOP, nullptr);
			}
			else if ((*position)->properties.FindNameValue("home")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_HOME, nullptr);
			}
		}
		else {
			LOG("There isn't any entity with name %s and type %s", (*position)->name.data(), (*position)->ent_type.data());
		}
	}
}

void m1Scene::CreateInventory()
{
	inventory_panel = App->gui->AddImage(0, 0, { 1024, 1536, 228, 384 }, this, App->gui->screen, true, false, false, false);
	inventory_panel->SetPosRespectParent(RIGHT_CENTERED);

	player_name = App->gui->AddLabel(80, 7, "Marche", inventory_panel, BLACK, FontType::FF64, nullptr, false); // This shall change when we have different characters

	hp_potion_button = App->gui->AddButton(73, 72, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, this, inventory_panel, true, false, true, true);
	hp_potion_button->AddListener(this);
	hp_potion_image = App->gui->AddImage(85, 80, { 1058, 1952, 33, 47 }, this, inventory_panel, true, false, false, false);
	hp_potion_label = App->gui->AddLabel(50, -10, "x 0", hp_potion_image, BLACK, FontType::FF64, nullptr, false); // This shall change when enemies drop money and we have the shop

	mana_potion_button = App->gui->AddButton(73, 135, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, { 1097, 1608, 125, 61 }, this, inventory_panel, true, false, true, true);
	mana_potion_button->AddListener(this);
	mana_potion_image = App->gui->AddImage(85, 140, {1091, 1952, 33, 51}, this, inventory_panel, true, false, false, false);
	mana_potion_label = App->gui->AddLabel(50, -10, "x 0", mana_potion_image, BLACK, FontType::FF64, nullptr, false); // This shall change when enemies drop money and we have the shop

	coin_image = App->gui->AddImage(45, 225, { 1024, 1952, 34, 34 }, this, inventory_panel, true, false, false, false);
	money_label = App->gui->AddLabel(50, -20, "x 0", coin_image, BLACK, FontType::FF64, nullptr, false); // This shall change when enemies drop money and we have the shop

	level_name_label = App->gui->AddLabel(76, 267, "Level:", inventory_panel, BLACK, FontType::FF64, nullptr, false);
	level_number_label = App->gui->AddLabel(65, 0, "1", level_name_label, BLACK, FontType::FF64, nullptr, false); // This shall change when enemies drop exp

	exp_name_label = App->gui->AddLabel(55, 307, "Exp:", inventory_panel, BLACK, FontType::FF64, nullptr, false);
	exp_number_label = App->gui->AddLabel(50, 0, "0/100", exp_name_label, BLACK, FontType::FF64, nullptr, false); // This shall change when enemies drop exp



	menu_state = StatesMenu::INVENTORY_MENU;
}

void m1Scene::DestroyInventory()
{
	App->gui->DeleteUIElement(inventory_panel);
	App->gui->ShowCursor(false);
	menu_state = StatesMenu::NO_MENU;
}

void m1Scene::CreatePotionMenu(u1GUI* potion_button)
{
	if (potion_button == hp_potion_button)
	{
		potion_panel = App->gui->AddImage(-170, 50, { 1878, 1536, 170, 101 }, this, inventory_panel, true, false, false, false);

		use_hp_button = App->gui->AddButton(30, 0, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, this, potion_panel, false, false, true, true);
		use_hp_button->AddListener(this);
		use_label = App->gui->AddLabel(50, -5, "Use", potion_panel, BLACK, FontType::FF64, nullptr, false);

		cancel_button = App->gui->AddButton(30, 43, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, this, potion_panel, false, false, true, true);
		cancel_button->AddListener(this);
		cancel_label = App->gui->AddLabel(50, 38, "Cancel", potion_panel, BLACK, FontType::FF64, nullptr, false);

		App->gui->FocusButton(use_hp_button);
	}

	if (potion_button == mana_potion_button)
	{
		potion_panel = App->gui->AddImage(-170, 100, { 1878, 1536, 170, 101 }, this, inventory_panel, true, false, false, false);

		use_mana_button = App->gui->AddButton(30, 0, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, this, potion_panel, false, false, true, true);
		use_mana_button->AddListener(this);
		use_label = App->gui->AddLabel(50, -5, "Use", potion_panel, BLACK, FontType::FF64, nullptr, false);

		cancel_button = App->gui->AddButton(30, 43, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, { 10, 10, 60, 50 }, this, potion_panel, false, false, true, true);
		cancel_button->AddListener(this);
		cancel_label = App->gui->AddLabel(50, 38, "Cancel", potion_panel, BLACK, FontType::FF64, nullptr, false);

		App->gui->FocusButton(use_mana_button);
	}

	menu_state = StatesMenu::POTION_MENU;
}

void m1Scene::DeletePotionMenu()
{
	App->gui->DeleteUIElement(potion_panel);
	menu_state = StatesMenu::INVENTORY_MENU;
}

void m1Scene::CreatePauseMenu()
{
	pause_panel = App->gui->AddImage(0, 0, { 1252,1536,313,428 }, this, App->gui->screen, true, false, false, false);
	pause_panel->SetPosRespectParent(CENTERED);

	button_resume = App->gui->AddButton(50, 50, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true, true);
	label_resume = App->gui->AddLabel(0, 0, "Continue", button_resume, BLACK, FontType::FF48, nullptr, false);
	label_resume->SetPosRespectParent(CENTERED);

	button_main_menu = App->gui->AddButton(50, 350, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true, true);
	label_main_menu = App->gui->AddLabel(0, 0, "Return to main menu", button_main_menu, BLACK, FontType::FF48, nullptr, false);
	label_main_menu->SetPosRespectParent(CENTERED);

	button_abort_quest = App->gui->AddButton(50, 250, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true, true);
	label_abort_quest = App->gui->AddLabel(0, 0, "Abort quest", button_abort_quest, BLACK, FontType::FF48, nullptr, false);
	label_abort_quest->SetPosRespectParent(CENTERED);


	button_options = App->gui->AddButton(50, 150, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true,true);
	label_options = App->gui->AddLabel(0, 0, "Options", button_options, BLACK, FontType::FF48, nullptr,false);
	label_options->SetPosRespectParent(CENTERED);

	menu_state = StatesMenu::PAUSE_MENU;
}

void m1Scene::DestroyPauseMenu()
{
	App->gui->DeleteUIElement(pause_panel);
	App->gui->ShowCursor(false);
}

void m1Scene::CreateOptionsMenu()
{
	options_panel = App->gui->AddImage(0, 0, { 1024,768,1024,768 }, this, App->gui->screen, true, false, false, false);
	options_panel->SetPosRespectParent(CENTERED);
	
	button_general_volume = App->gui->AddButton(491, 168, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_general_volume = App->gui->AddLabel(0, 0, "General Volume", button_general_volume, BLACK, FontType::FF48, nullptr, false);
	label_general_volume->SetPosRespectParent(LEFT_CENTERED);

	button_music_volume = App->gui->AddButton(491, 246, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_music_volume = App->gui->AddLabel(0, 0, "Music Volume", button_music_volume, BLACK, FontType::FF48, nullptr, false);
	label_music_volume->SetPosRespectParent(LEFT_CENTERED);

	button_fx_volume = App->gui->AddButton(491, 326, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_fx_volume = App->gui->AddLabel(0, 0, "FX Volume", button_fx_volume, BLACK, FontType::FF48, nullptr,false);
	label_fx_volume->SetPosRespectParent(LEFT_CENTERED);
	
	slider_general_volume = App->gui->AddSlider(680, 183, { 1566,1536,191,22 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, true, options_panel, this);
	//slider_music_volume->SetValue(app->audio->max_volume); why crashes�?

	slider_music_volume = App->gui->AddSlider(680, 263, { 1566,1536,191,22 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, true, options_panel, this);
	slider_music_volume->SetValue(App->audio->volume);

	slider_fx_volume = App->gui->AddSlider(680, 343, { 1566,1536,191,22 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, true, options_panel, this);
	slider_fx_volume->SetValue(App->audio->volume_fx);

	label_fps = App->gui->AddLabel(491, 413, "FPS Caps",  options_panel, BLACK, FontType::FF48, nullptr, false);
	checkbox_fps = App->gui->AddCheckBox(760, 413, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fps->is_option = true;
	checkbox_fps->draggable = false;
	checkbox_fps->drawable = true;
	checkbox_fps->interactable = true;
	checkbox_fps->AddListener(this);

	label_fullscreen = App->gui->AddLabel(491, 503, "Fullscreen", options_panel, BLACK, FontType::FF48, nullptr, false);
	checkbox_fullscreen = App->gui->AddCheckBox(760, 503, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fullscreen->is_option = true;
	checkbox_fullscreen->draggable = false;
	checkbox_fullscreen->drawable = true;
	checkbox_fullscreen->interactable = true;
	checkbox_fullscreen->AddListener(this);

	button_controls = App->gui->AddButton(491, 595, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_controls = App->gui->AddLabel(0, 0, "Controls", button_controls, BLACK, FontType::FF48, nullptr, false);
	label_controls->SetPosRespectParent(LEFT_CENTERED);

	button_retun = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	label_return = App->gui->AddLabel(0, 0, "Return", button_retun, BLACK, FontType::FF48, nullptr, false);
	label_return->SetPosRespectParent(CENTERED);

	menu_state = StatesMenu::OPTIONS_MENU;
}

void m1Scene::DestroyOptionsMenu()
{
	App->gui->DeleteUIElement(options_panel);
}

void m1Scene::CreateControlsMenu()
{
	controls_panel = App->gui->AddImage(0, 0, { 1024,768,1024,768 }, this, App->gui->screen, true, false, false,false);
	controls_panel->SetPosRespectParent(CENTERED);


	button_retun_to_options = App->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	label_return_to_options = App->gui->AddLabel(0, 0, "Return", button_retun_to_options, BLACK, FontType::FF48, nullptr, false);
	label_return_to_options->SetPosRespectParent(CENTERED);

	// Actions

	int actions_offset_x = 200;
	label_up =				App->gui->AddLabel(actions_offset_x, 300, "Move Up", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_right =			App->gui->AddLabel(actions_offset_x, 330, "Move Right", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_left =			App->gui->AddLabel(actions_offset_x, 360, "Move Left", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_down =			App->gui->AddLabel(actions_offset_x, 390, "Move Down", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_diagonals =		App->gui->AddLabel(actions_offset_x, 420, "Use Diagonals", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_direction_up =	App->gui->AddLabel(actions_offset_x, 450, "Change Direction Up", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_direction_right = App->gui->AddLabel(actions_offset_x, 480, "Change Direction Right", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_direction_left =	App->gui->AddLabel(actions_offset_x, 510, "Change Direction Left", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_direction_down =	App->gui->AddLabel(actions_offset_x, 540, "Change Direction Down", controls_panel, BLACK, FontType::FF48, nullptr, false);
	label_basic_attack =	App->gui->AddLabel(actions_offset_x, 565, "Basic Attack", controls_panel, BLACK, FontType::FF48, nullptr, false);

	// KEYS/BUTTONS
	int offset_between_y = 35;
	// KEYBOARD
	int keyboard_offset_x = 450;

	keyboard = App->gui->AddLabel(keyboard_offset_x, 265, "KEYBOARD", controls_panel, BLACK, FontType::FF48, nullptr,false);

	button_up = App->gui->AddButton(keyboard_offset_x, 295, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true, true);
	label_to_show_how_up = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.UP, button_up, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_up->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_up);

	button_right = App->gui->AddButton(keyboard_offset_x, button_up->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true, true);
	label_to_show_how_right = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.RIGHT, button_right, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_right->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_right);

	button_left = App->gui->AddButton(keyboard_offset_x, button_right->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	label_to_show_how_left = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.LEFT, button_left, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_left->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_left);
	
	button_down = App->gui->AddButton(keyboard_offset_x, button_left->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	label_to_show_how_down = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DOWN, button_down, BLACK, FontType::FF32, nullptr,true);
	label_to_show_how_down->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_down);

	button_diagonals = App->gui->AddButton(keyboard_offset_x, button_down->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	label_to_show_how_diagonals = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIAGONALS, button_diagonals, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_diagonals->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_diagonals);

	button_direction_up = App->gui->AddButton(keyboard_offset_x, button_diagonals->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	label_to_show_how_direction_up = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECTION_UP, button_direction_up, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_direction_up->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_direction_up);

	button_direction_right = App->gui->AddButton(keyboard_offset_x, button_direction_up->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	label_to_show_how_direction_right = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT, button_direction_right, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_direction_right->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_direction_right);

	button_direction_left = App->gui->AddButton(keyboard_offset_x, button_direction_right->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	label_to_show_how_direction_left = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECTION_LEFT, button_direction_left, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_direction_left->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_direction_left);

	button_direction_down = App->gui->AddButton(keyboard_offset_x, button_direction_left->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	label_to_show_how_direction_down = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN,  button_direction_down, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_direction_down->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_direction_down);

	button_basic_attack = App->gui->AddButton(keyboard_offset_x, button_direction_down->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	label_to_show_how_basic_attack = App->gui->AddLabel(0, 0, App->input->keyboard_buttons.buttons_char.BASIC_ATTACK, button_basic_attack, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_basic_attack->SetPosRespectParent(CENTERED);
	labels_control.push_back(label_to_show_how_basic_attack);


	// CONTROLLER
	int controller_offset_x = 690;

	controller = App->gui->AddLabel(700, 265, "CONTROLLER", controls_panel, BLACK, FontType::FF48, nullptr,false);

	Cbutton_up = App->gui->AddButton(controller_offset_x, 295, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true, true);
	Clabel_to_show_how_up = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.UP, Cbutton_up, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_up->SetPosRespectParent(CENTERED);

	Cbutton_right = App->gui->AddButton(controller_offset_x, Cbutton_up->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true, true);
	Clabel_to_show_how_right = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.RIGHT, Cbutton_right, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_right->SetPosRespectParent(CENTERED);

	Cbutton_left = App->gui->AddButton(controller_offset_x, Cbutton_right->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true, true);
	Clabel_to_show_how_left = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.LEFT, Cbutton_left, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_left->SetPosRespectParent(CENTERED);

	Cbutton_down = App->gui->AddButton(controller_offset_x, Cbutton_left->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true, true);
	Clabel_to_show_how_down = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DOWN, Cbutton_down, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_down->SetPosRespectParent(CENTERED);

	Cbutton_diagonals = App->gui->AddButton(controller_offset_x, Cbutton_down->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true, true);
	Clabel_to_show_how_diagonals = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIAGONALS, Cbutton_diagonals, BLACK, FontType::FF32, nullptr, false);
	Clabel_to_show_how_diagonals->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_diagonals);

	Cbutton_direction_up = App->gui->AddButton(controller_offset_x, Cbutton_diagonals->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Clabel_to_show_how_direction_up = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECTION_UP,  Cbutton_direction_up, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_direction_up->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_direction_up);

	Cbutton_direction_right = App->gui->AddButton(controller_offset_x, Cbutton_direction_up->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Clabel_to_show_how_direction_right = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECCTION_RIGHT, Cbutton_direction_right, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_direction_right->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_direction_right);

	Cbutton_direction_left = App->gui->AddButton(controller_offset_x, Cbutton_direction_right->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Clabel_to_show_how_direction_left = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECTION_LEFT, Cbutton_direction_left, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_direction_left->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_direction_left);

	Cbutton_direction_down = App->gui->AddButton(controller_offset_x, Cbutton_direction_left->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Clabel_to_show_how_direction_down = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.DIRECCTION_DOWN,  Cbutton_direction_down, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_direction_down->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_direction_down);

	Cbutton_basic_attack = App->gui->AddButton(controller_offset_x, Cbutton_direction_down->position.y + offset_between_y, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Clabel_to_show_how_basic_attack = App->gui->AddLabel(0, 0, App->input->controller_Buttons.buttons_char.BASIC_ATTACK, Cbutton_basic_attack, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_basic_attack->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_basic_attack);

	

	

	menu_state = StatesMenu::CONTROLS_MENU;
}

void m1Scene::DestroyControlsMenu()
{
	control_to_change = nullptr;
	App->gui->DeleteUIElement(controls_panel);

	labels_control.clear();
	Clabels_control.clear();

}

void m1Scene::CreateDebugScreen()
{
	debug_screen = App->gui->AddImage(0, 0, App->gui->screen->section, nullptr, App->gui->screen, false, false, false, false);

	SDL_Color debug_background = { 0,0,0,150 };
	project_name = App->gui->AddLabel(0, 0, App->GetTitle(), debug_screen, WHITE, FontType::PMIX16, nullptr, false, 0U, true, debug_background);
	version = App->gui->AddLabel(0, project_name->section.h, std::string(std::string("Version: ") + App->GetVersion()).data(), debug_screen, WHITE, FontType::PMIX16, nullptr, false, 0U, true, debug_background);
	fps = App->gui->AddLabel(0, version->position.y + version->section.h, "fps: ", project_name, WHITE, FontType::PMIX16, nullptr, false, 0U, true, debug_background);

	map = App->gui->AddLabel(0, fps->position.y + fps->section.h*2, "map:\nnumber of layers: %i\nnumber of tilesets: %i\nmap id: %i\nwidth: %i | height: %i\ntile width: %i | tile height: %i\ntiles drawn: %i",
		debug_screen, WHITE, FontType::PMIX16, nullptr, false, App->gui->screen->section.w*0.3, true, debug_background);

	player_label = App->gui->AddLabel(0, map->position.y + map->section.h * 2, "player:\nposition: %i\ntile: %i\n movement type: %i\ndirection: %i\n state: %i",
		debug_screen, WHITE, FontType::PMIX16, nullptr, false, App->gui->screen->section.w*0.3, true, debug_background);

}

void m1Scene::DestroyDebugScreen()
{
	App->gui->DeleteUIElement(debug_screen);

	debug_screen = nullptr;
	project_name = nullptr;
	fps = nullptr;
	mouse = nullptr;
}

void m1Scene::UpdateDebugScreen()
{
	BROFILER_CATEGORY("UpdateDebugScreen", Profiler::Color::Orange);

	if (debug_screen != nullptr) {
		fps->SetText(std::string("fps: " + std::to_string(App->GetFps())).data());

		map->SetTextWrapped(std::string("map:\nnumber of layers: " + std::to_string(App->map->data.layers.size()) + "\nnumber of tilesets: " + std::to_string(App->map->data.tilesets.size()) +
			"\nmap id: " + std::to_string((int)App->map->actual_map) + "\nwidth: " + std::to_string(App->map->data.width) + " | height: " + std::to_string(App->map->data.height) + "\ntile width: "
			+ std::to_string(App->map->data.tile_width) + "\ntile height: " + std::to_string(App->map->data.tile_height) + "\ntiles drawn: " + std::to_string(App->map->last_tiles_drawn)).data());

		player_label->SetTextWrapped(std::string("player:\nposition: (" + std::to_string(player->position.x) + ", " + std::to_string(player->position.y) +
			")\ntile: (" + std::to_string(player->actual_tile.x) + ", " + std::to_string(player->actual_tile.y) + ")\nmovement type: " + std::to_string((int)player->movement_type) +
			"\ndirection: " + std::to_string((int)player->direction) + "\nstate: " + std::to_string((int)player->state)).data());
	}
}

bool m1Scene::Interact(u1GUI* interact)
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
			player->BlockControls(false);
			menu_state = StatesMenu::NO_MENU;
		}
		if (interact == button_main_menu)
		{
			App->gui->DeleteAllUIElements();
			App->entity_manager->Disable();
			App->map->Disable();
			active = false; //desactivates main menu
			App->main_menu->Enable();
			DestroyDebugScreen();
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
	case StatesMenu::INVENTORY_MENU:
		if (interact == hp_potion_button) {
			DeletePotionMenu();
			CreatePotionMenu(hp_potion_button);
		}
		if (interact == mana_potion_button) {
			DeletePotionMenu();
			CreatePotionMenu(mana_potion_button);
		}
		break;
	case StatesMenu::POTION_MENU:
		if (interact == use_hp_button) {
			LOG("HP POTION USED");
		}
		if (interact == use_mana_button) {
			LOG("MANA POTION USED");
		}
		if (interact == cancel_button) {
			DeletePotionMenu();
			menu_state = StatesMenu::INVENTORY_MENU;
		}
		break;
	case StatesMenu::OPTIONS_MENU:
		if (interact == button_retun) {
			if (App->main_menu->active) {
				App->main_menu->CreateMainMenu();
				DestroyOptionsMenu();
			}
			else {
				CreatePauseMenu();
				DestroyOptionsMenu();
			}
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
			control_to_change = new ChangeControls(label_to_show_how_up, &App->input->keyboard_buttons.buttons_code.UP, &App->input->keyboard_buttons.buttons_char.UP, false);
		}
		if (interact == button_right) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_right, &App->input->keyboard_buttons.buttons_code.RIGHT, &App->input->keyboard_buttons.buttons_char.RIGHT, false);
		}
		if (interact == button_left) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_left, &App->input->keyboard_buttons.buttons_code.LEFT, &App->input->keyboard_buttons.buttons_char.LEFT, false);
		}
		if (interact == button_down) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_down, &App->input->keyboard_buttons.buttons_code.DOWN, &App->input->keyboard_buttons.buttons_char.DOWN, false);
		}
		if (interact == button_diagonals) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_diagonals, &App->input->keyboard_buttons.buttons_code.DIAGONALS, &App->input->keyboard_buttons.buttons_char.DIAGONALS, false);
		}
		if (interact == button_direction_up) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_up, &App->input->keyboard_buttons.buttons_code.DIRECTION_UP, &App->input->keyboard_buttons.buttons_char.DIRECTION_UP, false);
		}
		if (interact == button_direction_right) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_right, &App->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT, &App->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT, false);
		}
		if (interact == button_direction_left) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_left, &App->input->keyboard_buttons.buttons_code.DIRECTION_LEFT, &App->input->keyboard_buttons.buttons_char.DIRECTION_LEFT, false);
		}
		if (interact == button_direction_down) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_down, &App->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN, &App->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN, false);
		}
		if (interact == button_basic_attack) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_basic_attack, &App->input->keyboard_buttons.buttons_code.BASIC_ATTACK, &App->input->keyboard_buttons.buttons_char.BASIC_ATTACK, false);
		}
		if (interact == Cbutton_direction_up) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_direction_up, &App->input->controller_Buttons.buttons_code.DIRECTION_UP, &App->input->controller_Buttons.buttons_char.DIRECTION_UP, true);
		}
		if (interact == Cbutton_direction_right) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_direction_right, &App->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT, &App->input->controller_Buttons.buttons_char.DIRECCTION_RIGHT, true);
		}
		if (interact == Cbutton_direction_left) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_direction_left, &App->input->controller_Buttons.buttons_code.DIRECTION_LEFT, &App->input->controller_Buttons.buttons_char.DIRECTION_LEFT, true);
		}
		if (interact == Cbutton_direction_down) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_direction_down, &App->input->controller_Buttons.buttons_code.DIRECCTION_DOWN, &App->input->controller_Buttons.buttons_char.DIRECCTION_DOWN, true);
		}
		if (interact == Cbutton_diagonals) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_diagonals, &App->input->controller_Buttons.buttons_code.DIAGONALS, &App->input->controller_Buttons.buttons_char.DIAGONALS, true);
		}
		if (interact == Cbutton_basic_attack) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_basic_attack, &App->input->controller_Buttons.buttons_code.BASIC_ATTACK, &App->input->controller_Buttons.buttons_char.BASIC_ATTACK, true);
		}
		break;
	}
	
	if (interact == checkbox_fps)
	{
		checkbox_fps->Clicked();
		if (App->capactivated) {
			App->capactivated = false;
		}
		else {
			App->capactivated = true;
		}
		//App->GetFrameRate();
	}

	if (interact == checkbox_fullscreen)
	{
		checkbox_fullscreen->Clicked();
		
		if (App->win->fullscreen) {
			App->win->fullscreen = false;
			SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_SHOWN);
		}
		else {
			App->win->fullscreen = true;
			SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_FULLSCREEN);
		}
	}

	return ret;
}

StatesMenu m1Scene::GetMenuState()
{
	return menu_state;
}