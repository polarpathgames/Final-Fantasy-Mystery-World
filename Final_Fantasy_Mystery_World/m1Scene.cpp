#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "m1Pathfinding.h"
#include "m1GUI.h"
#include "m1Collisions.h"
#include "m1Textures.h"
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
	//std::string map("iso_walk.tmx");
	
	//app->map->Load("iso_walk2.tmx");
	/*SDL_Rect background_rect = { 0, 0, 1024, 768 };
	background = app->gui->AddImage(0, 0, &background_rect, nullptr, this, nullptr);*/
	if (app->GetPause())
		app->ChangePause();


	return true;
}

// Called each loop iteration
bool m1Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateScene", Profiler::Color::Orange);
	// debug pathfing ------------------


	return true;
}

// Called each loop iteration
bool m1Scene::Update(float dt)
{
	BROFILER_CATEGORY("UpdateScene", Profiler::Color::Aqua);

	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGame("save_game.xml");

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGame("save_game.xml");

	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y += 300 * dt;

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y -= 300 * dt;

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x += 300 * dt;

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x -= 300 * dt;
	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		app->map->Grid = !app->map->Grid;
	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		int x = 0, y = 0;
		app->input->GetMousePosition(x, y);
		app->entity_manager->CreateEntity(e1Entity::EntityType::PLAYER, x, y, std::string());
	}
	//if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	//	app->entity_manager->CreateEnemy();
	/*if(app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		mock_image_ui = app->gui->AddImage(0, 0, &mock_image_rect, nullptr, this, nullptr);*/

	app->map->Draw();

	if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
		app->fade_to_black->FadeToBlack(Maps::LOBBY);
	}
		
	if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		app->fade_to_black->FadeToBlack(Maps::TUTORIAL);
	}

	if (app->input->GetKey(SDL_SCANCODE_KP_1) == KEY_DOWN) {
		app->win->scale = 1;
	}
	if (app->input->GetKey(SDL_SCANCODE_KP_2) == KEY_DOWN) {
		app->win->scale = 2;
	}
	if (app->input->GetKey(SDL_SCANCODE_KP_3) == KEY_DOWN) {
		app->win->scale = 3;
	}
		

	
	switch (menu_state) {
	case StatesMenu::NO_MENU:
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			(app->ChangePause()) ? CreatePauseMenu() : DestroyPauseMenu();
		}
		break;
	case StatesMenu::PAUSE_MENU:
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			(app->ChangePause()) ? CreatePauseMenu() : DestroyPauseMenu();
		}
		break;
	case StatesMenu::OPTIONS_MENU:
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			CreatePauseMenu();
			DestroyOptionsMenu();
		}
		break;
	case StatesMenu::CONTROLS_MENU:
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			CreateOptionsMenu();
			DestroyControlsMenu();
		}
		if (control_to_change != nullptr) {
			if (!control_to_change->Update()) {
				delete control_to_change;
				control_to_change = nullptr;
			}	
		}
		break;
	}

	//if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	//	app->audio->VolumeDown(-1);

	//if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	//	app->audio->VolumeUp(-1);

	//if (!app->audio->mute_volume) Mix_VolumeMusic(slider_music_volume->GetValue());
	//if (!app->audio->mute_fx) app->audio->SliderVolumeFx(slider_fx_volume->GetValue());
	//app->audio->volume = slider_music_volume->GetValue(); This crashes
	//app->audio->volume_fx = slider_fx_volume->GetValue(); This crashes

	return true;
}

// Called each loop iteration
bool m1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateScene", Profiler::Color::Purple);

	bool ret = true;

	//if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	//	ret = false;

	iPoint mouse;
	app->input->GetMousePosition(mouse.x, mouse.y);
	//app->render->ScreenToWorld(mouse.x, mouse.y);
	iPoint tile = app->map->WorldToMap(mouse.x, mouse.y);
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

	for (std::list<ObjectLayer*>::iterator position = app->map->data.objects.begin(); position != app->map->data.objects.end(); position++) {
		if ((*position)->name == "player") {
			if (player == nullptr) {
				if ((*position)->ent_type == "default") { // start position
					player = (e1Player*)app->entity_manager->CreateEntity(e1Entity::EntityType::PLAYER, app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
			}
			else {
				if ((*position)->ent_type == "shop" && app->map->last_map == Maps::SHOP) { // position after leaving shop
					player->position.create(app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
				}
				else if ((*position)->ent_type == "home" && app->map->last_map == Maps::HOME){ // position after leaving home
					player->position.create(app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
				}
				else if ((*position)->ent_type == "in_shop") { // position in the shop
					player->position.create(app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
				}
				else if ((*position)->ent_type == "in_home") { // position in the home
					player->position.create(app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->CenterPlayerInTile();
				}
			}
		}
		else if ((*position)->ent_type == "static") {
			app->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);

		}
		else if ((*position)->ent_type == "enemy") {
			app->entity_manager->CreateEntity(e1Entity::EntityType::ENEMY, app->map->TiledToWorld((*position)->coll_x , (*position)->coll_y).x, app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
		}
		else if ((*position)->name == "collider") { // COLLIDERS
			if ((*position)->properties.FindNameValue("shop")) {
				app->collision->AddCollider({ app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_SHOP, nullptr);
			}
			else if ((*position)->properties.FindNameValue("home")) {
				app->collision->AddCollider({ app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,app->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_HOME, nullptr);
			}
		}
		else {
			LOG("There isn't any entity with name %s and type %s", (*position)->name.data(), (*position)->ent_type.data());
		}
	}
}

void m1Scene::CreatePauseMenu()
{
	pause_panel = app->gui->AddImage(0, 0, { 1252,1536,313,428 }, this, app->gui->screen, true, false, false, false);
	pause_panel->SetPosRespectParent(CENTERED);
	button_resume = app->gui->AddButton(50, 50, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true, true);
	button_resume->AddListener(this);
	label_resume = app->gui->AddLabel(0, 0, "Continue", button_resume, BLACK, FontType::FF48, nullptr, false);
	label_resume->SetPosRespectParent(CENTERED);

	button_main_menu = app->gui->AddButton(50, 350, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true, true);
	button_main_menu->AddListener(this);
	label_main_menu = app->gui->AddLabel(0, 0, "Return to main menu", button_main_menu, BLACK, FontType::FF48, nullptr, false);
	label_main_menu->SetPosRespectParent(CENTERED);

	button_abort_quest = app->gui->AddButton(50, 250, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true, true);
	button_abort_quest->AddListener(this);
	label_abort_quest = app->gui->AddLabel(0, 0, "Abort quest", button_abort_quest, BLACK, FontType::FF48, nullptr, false);
	label_abort_quest->SetPosRespectParent(CENTERED);


	button_options = app->gui->AddButton(50, 150, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, pause_panel, true, false, true,true);
	button_options->AddListener((m1Module*)app->scene);
	label_options = app->gui->AddLabel(0, 0, "Options", button_options, BLACK, FontType::FF48, nullptr,false);

	label_options->SetPosRespectParent(CENTERED);

	menu_state = StatesMenu::PAUSE_MENU;
}

void m1Scene::DestroyPauseMenu()
{


	/*if(pause_panel != nullptr)
	app->gui->DeleteUIElement(pause_panel);*/

	app->gui->DeleteUIElement(pause_panel);
}

void m1Scene::CreateOptionsMenu()
{
	options_panel = app->gui->AddImage(0, 0, { 1024,768,1024,768 }, this, app->gui->screen, true, false, false, false);
	options_panel->SetPosRespectParent(CENTERED);
	
	button_general_volume = app->gui->AddButton(491, 168, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	button_general_volume->AddListener(this);
	label_general_volume = app->gui->AddLabel(0, 0, "General Volume", button_general_volume, BLACK, FontType::FF32, nullptr, false);
	label_general_volume->SetPosRespectParent(LEFT_CENTERED);

	button_music_volume = app->gui->AddButton(491, 246, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	button_music_volume->AddListener(this);
	label_music_volume = app->gui->AddLabel(0, 0, "Music Volume", button_music_volume, BLACK, FontType::FF32, nullptr, false);
	label_music_volume->SetPosRespectParent(LEFT_CENTERED);

	button_fx_volume = app->gui->AddButton(491, 326, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	button_fx_volume->AddListener(this);
	label_fx_volume = app->gui->AddLabel(0, 0, "FX Volume", button_fx_volume, BLACK, FontType::FF32, nullptr,false);
	label_fx_volume->SetPosRespectParent(LEFT_CENTERED);
	
	slider_general_volume = app->gui->AddSlider(680, 183, { 1566,1536,191,22 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, true, options_panel, this);
	//slider_music_volume->SetValue(app->audio->max_volume); why crashes�?

	slider_music_volume = app->gui->AddSlider(680, 263, { 1566,1536,191,22 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, true, options_panel, this);
	slider_music_volume->SetValue(app->audio->volume);

	slider_fx_volume = app->gui->AddSlider(680, 343, { 1566,1536,191,22 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, { 1757,1536, 41,25 }, true, options_panel, this);
	slider_fx_volume->SetValue(app->audio->volume_fx);

	label_fps = app->gui->AddLabel(491, 413, "FPS Caps",  options_panel, BLACK, FontType::FF32, nullptr, false);
	checkbox_fps = app->gui->AddCheckBox(760, 413, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fps->is_option = true;
	checkbox_fps->draggable = false;
	checkbox_fps->drawable = true;
	checkbox_fps->interactable = true;
	checkbox_fps->AddListener(this);

	label_fullscreen = app->gui->AddLabel(491, 503, "Fullscreen", options_panel, BLACK, FontType::FF32, nullptr, false);
	checkbox_fullscreen = app->gui->AddCheckBox(760, 503, { 1659,1575,33,33 }, { 1659,1575,33,33 }, { 1566,1559,48,36 }, options_panel);
	checkbox_fullscreen->is_option = true;
	checkbox_fullscreen->draggable = false;
	checkbox_fullscreen->drawable = true;
	checkbox_fullscreen->interactable = true;
	checkbox_fullscreen->AddListener(this);

	button_controls = app->gui->AddButton(491, 595, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	button_controls->AddListener((m1Module*)app->scene);
	label_controls = app->gui->AddLabel(0, 0, "Controls", button_controls, BLACK, FontType::FF32, nullptr, false);
	label_controls->SetPosRespectParent(LEFT_CENTERED);

	button_retun = app->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, options_panel, false, false, true, true);
	button_retun->AddListener((m1Module*)app->scene);
	label_return = app->gui->AddLabel(0, 0, "Return", button_retun, BLACK, FontType::FF32, nullptr, false);
	label_return->SetPosRespectParent(CENTERED);

	menu_state = StatesMenu::OPTIONS_MENU;
}

void m1Scene::DestroyOptionsMenu()
{
	app->gui->DeleteUIElement(options_panel);

}

void m1Scene::CreateControlsMenu()
{
	controls_panel = app->gui->AddImage(0, 0, { 1024,768,1024,768 }, this, app->gui->screen, true, false, true,false);
	controls_panel->SetPosRespectParent(CENTERED);


	button_retun_to_options = app->gui->AddButton(810, 700, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_retun_to_options->AddListener((m1Module*)app->scene);
	label_return_to_options = app->gui->AddLabel(0, 0, "Return", button_retun_to_options, BLACK, FontType::FF32, nullptr, false);
	label_return_to_options->SetPosRespectParent(CENTERED);

	// KEYBOARD

	keyboard = app->gui->AddLabel(350, 265, "KEYBOARD", controls_panel, BLACK, FontType::FF32, nullptr,false);

	button_up = app->gui->AddButton(340, 295, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,false);
	button_up->AddListener(this);
	label_to_show_how_up = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.UP, button_up, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_up->SetPosRespectParent(CENTERED);
	label_up = app->gui->AddLabel(300, 300, "Move Up", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_up);

	button_right = app->gui->AddButton(340, 325, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_right->AddListener(this);
	label_to_show_how_right = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.RIGHT, button_right, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_right->SetPosRespectParent(CENTERED);
	label_right = app->gui->AddLabel(300, 330, "Move Right", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_right);

	button_left = app->gui->AddButton(340, 355, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_left->AddListener(this);
	label_to_show_how_left = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.LEFT, button_left, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_left->SetPosRespectParent(CENTERED);
	label_left = app->gui->AddLabel(300, 360, "Move Left", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_left);

	button_down = app->gui->AddButton(340, 385, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_left->AddListener(this);
	label_to_show_how_down = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.DOWN, button_down, BLACK, FontType::FF32, nullptr,true);
	label_to_show_how_down->SetPosRespectParent(CENTERED);
	label_down = app->gui->AddLabel(300, 390, "Move Down", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_down);

	button_diagonals = app->gui->AddButton(340, 415, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_diagonals->AddListener(this);
	label_to_show_how_diagonals = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.DIAGONALS, button_diagonals, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_diagonals->SetPosRespectParent(CENTERED);
	label_diagonals = app->gui->AddLabel(300, 420, "Use Diagonals", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_diagonals);

	button_direction_up = app->gui->AddButton(340, 445, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_direction_up->AddListener(this);
	label_to_show_how_direction_up = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.DIRECTION_UP, button_direction_up, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_direction_up->SetPosRespectParent(CENTERED);
	label_direction_up = app->gui->AddLabel(300, 450, "Change Direction Up", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_direction_up);

	button_direction_right = app->gui->AddButton(340, 475, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_direction_right->AddListener(this);
	label_to_show_how_direction_right = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT, button_direction_right, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_direction_right->SetPosRespectParent(CENTERED);
	label_direction_right = app->gui->AddLabel(300, 480, "Change Direction Right", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_direction_right);

	button_direction_left = app->gui->AddButton(340, 505, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_direction_left->AddListener(this);
	label_to_show_how_direction_left = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.DIRECTION_LEFT, button_direction_left, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_direction_left->SetPosRespectParent(CENTERED);
	label_direction_left = app->gui->AddLabel(300, 510, "Change Direction Left", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_direction_left);

	button_direction_down = app->gui->AddButton(340, 535, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_direction_down->AddListener(this);
	label_to_show_how_direction_down = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN,  button_direction_down, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_direction_down->SetPosRespectParent(CENTERED);
	label_direction_down = app->gui->AddLabel(300, 540, "Change Direction Down", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_direction_down);

	button_basic_attack = app->gui->AddButton(340, 560, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	button_basic_attack->AddListener(this);
	label_to_show_how_basic_attack = app->gui->AddLabel(0, 0, app->input->keyboard_buttons.buttons_char.BASIC_ATTACK, button_basic_attack, BLACK, FontType::FF32, nullptr,false);
	label_to_show_how_basic_attack->SetPosRespectParent(CENTERED);
	label_basic_attack = app->gui->AddLabel(300, 565, "Basic Attack", controls_panel, BLACK, FontType::FF32, nullptr,false);
	labels_control.push_back(label_to_show_how_basic_attack);


	// CONTROLLER

	controller = app->gui->AddLabel(700, 265, "CONTROLLER", controls_panel, BLACK, FontType::FF32, nullptr,false);

	Cbutton_direction_up = app->gui->AddButton(690, 445, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_direction_up->AddListener(this);
	Clabel_to_show_how_direction_up = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.DIRECTION_UP,  Cbutton_direction_up, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_direction_up->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_direction_up);

	Cbutton_direction_right = app->gui->AddButton(690, 475, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_direction_right->AddListener(this);
	Clabel_to_show_how_direction_right = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.DIRECCTION_RIGHT, Cbutton_direction_right, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_direction_right->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_direction_right);

	Cbutton_direction_left = app->gui->AddButton(690, 505, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_direction_left->AddListener(this);
	Clabel_to_show_how_direction_left = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.DIRECTION_LEFT, Cbutton_direction_left, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_direction_left->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_direction_left);

	Cbutton_direction_down = app->gui->AddButton(690, 535, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_direction_down->AddListener(this);
	Clabel_to_show_how_direction_down = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.DIRECCTION_DOWN,  Cbutton_direction_down, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_direction_down->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_direction_down);

	Cbutton_diagonals = app->gui->AddButton(690, 415, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_diagonals->AddListener(this);
	Clabel_to_show_how_diagonals = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.DIAGONALS, Cbutton_diagonals, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_diagonals->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_diagonals);

	Cbutton_basic_attack = app->gui->AddButton(690, 565, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_basic_attack->AddListener(this);
	Clabel_to_show_how_basic_attack = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.BASIC_ATTACK, Cbutton_basic_attack, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_basic_attack->SetPosRespectParent(CENTERED);
	Clabels_control.push_back(Clabel_to_show_how_basic_attack);

	Cbutton_up = app->gui->AddButton(690, 295, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_up->AddListener(this);
	Clabel_to_show_how_up = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.UP,  Cbutton_up, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_up->SetPosRespectParent(CENTERED);

	Cbutton_right = app->gui->AddButton(690, 325, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_right->AddListener(this);
	Clabel_to_show_how_right = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.RIGHT, Cbutton_right, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_right->SetPosRespectParent(CENTERED);

	Cbutton_left = app->gui->AddButton(690, 355, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_left->AddListener(this);
	Clabel_to_show_how_left = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.LEFT,  Cbutton_left, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_left->SetPosRespectParent(CENTERED);

	Cbutton_down = app->gui->AddButton(690, 385, { 1850,1637,198,50 }, { 1850,1637,198,50 }, { 1850,1637,198,50 }, this, controls_panel, false, false, true,true);
	Cbutton_down->AddListener(this);
	Clabel_to_show_how_down = app->gui->AddLabel(0, 0, app->input->controller_Buttons.buttons_char.DOWN,  Cbutton_down, BLACK, FontType::FF32, nullptr,false);
	Clabel_to_show_how_down->SetPosRespectParent(CENTERED);

	menu_state = StatesMenu::CONTROLS_MENU;
}

void m1Scene::DestroyControlsMenu()
{
	control_to_change = nullptr;
	app->gui->DeleteUIElement(controls_panel);

	labels_control.clear();
	Clabels_control.clear();

}

bool m1Scene::Interact(u1GUI* interact)
{
	bool ret = true;
	switch (menu_state) {
	case StatesMenu::PAUSE_MENU:
		if (interact == button_resume)
		{
			DestroyPauseMenu();
			if (app->GetPause())
				app->ChangePause();
			ret = false;
			menu_state = StatesMenu::NO_MENU;
		}
		if (interact == button_main_menu)
		{

			/*app->fade_to_black->FadeToBlack(this, app->main_menu, 3.0f);*/
			app->gui->DeleteAllUIElements();
			app->render->ResetCamera();
			app->entity_manager->active = false;
			app->entity_manager->CleanUp();
			app->map->active = false;
			app->map->CleanUp();
			this->active = false; //desactivates main menu
			app->main_menu->active = true;
			app->main_menu->Start();
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
			control_to_change = new ChangeControls(label_to_show_how_up, &app->input->keyboard_buttons.buttons_code.UP, &app->input->keyboard_buttons.buttons_char.UP, false);
		}
		if (interact == button_right) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_right, &app->input->keyboard_buttons.buttons_code.RIGHT, &app->input->keyboard_buttons.buttons_char.RIGHT, false);
		}
		if (interact == button_left) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_left, &app->input->keyboard_buttons.buttons_code.LEFT, &app->input->keyboard_buttons.buttons_char.LEFT, false);
		}
		if (interact == button_down) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_down, &app->input->keyboard_buttons.buttons_code.DOWN, &app->input->keyboard_buttons.buttons_char.DOWN, false);
		}
		if (interact == button_diagonals) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_diagonals, &app->input->keyboard_buttons.buttons_code.DIAGONALS, &app->input->keyboard_buttons.buttons_char.DIAGONALS, false);
		}
		if (interact == button_direction_up) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_up, &app->input->keyboard_buttons.buttons_code.DIRECTION_UP, &app->input->keyboard_buttons.buttons_char.DIRECTION_UP, false);
		}
		if (interact == button_direction_right) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_right, &app->input->keyboard_buttons.buttons_code.DIRECCTION_RIGHT, &app->input->keyboard_buttons.buttons_char.DIRECCTION_RIGHT, false);
		}
		if (interact == button_direction_left) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_left, &app->input->keyboard_buttons.buttons_code.DIRECTION_LEFT, &app->input->keyboard_buttons.buttons_char.DIRECTION_LEFT, false);
		}
		if (interact == button_direction_down) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_direction_down, &app->input->keyboard_buttons.buttons_code.DIRECCTION_DOWN, &app->input->keyboard_buttons.buttons_char.DIRECCTION_DOWN, false);
		}
		if (interact == button_basic_attack) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(label_to_show_how_basic_attack, &app->input->keyboard_buttons.buttons_code.BASIC_ATTACK, &app->input->keyboard_buttons.buttons_char.BASIC_ATTACK, false);
		}
		if (interact == Cbutton_direction_up) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_direction_up, &app->input->controller_Buttons.buttons_code.DIRECTION_UP, &app->input->controller_Buttons.buttons_char.DIRECTION_UP, true);
		}
		if (interact == Cbutton_direction_right) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_direction_right, &app->input->controller_Buttons.buttons_code.DIRECCTION_RIGHT, &app->input->controller_Buttons.buttons_char.DIRECCTION_RIGHT, true);
		}
		if (interact == Cbutton_direction_left) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_direction_left, &app->input->controller_Buttons.buttons_code.DIRECTION_LEFT, &app->input->controller_Buttons.buttons_char.DIRECTION_LEFT, true);
		}
		if (interact == Cbutton_direction_down) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_direction_down, &app->input->controller_Buttons.buttons_code.DIRECCTION_DOWN, &app->input->controller_Buttons.buttons_char.DIRECCTION_DOWN, true);
		}
		if (interact == Cbutton_diagonals) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_diagonals, &app->input->controller_Buttons.buttons_code.DIAGONALS, &app->input->controller_Buttons.buttons_char.DIAGONALS, true);
		}
		if (interact == Cbutton_basic_attack) {
			if (control_to_change != nullptr)
				delete control_to_change;
			control_to_change = new ChangeControls(Clabel_to_show_how_basic_attack, &app->input->controller_Buttons.buttons_code.BASIC_ATTACK, &app->input->controller_Buttons.buttons_char.BASIC_ATTACK, true);
		}
		break;
	}
	
	if (interact == checkbox_fps)
	{
		checkbox_fps->Clicked();
		if (app->capactivated) {
			app->capactivated = false;
		}
		else {
			app->capactivated = true;
		}
		//app->GetFrameRate();
	}

	if (interact == checkbox_fullscreen)
	{
		checkbox_fullscreen->Clicked();
		
		if (app->win->fullscreen) {
			app->win->fullscreen = false;
			SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_SHOWN);
		}
		else {
			app->win->fullscreen = true;
			SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN);
		}
	}

	return ret;
}