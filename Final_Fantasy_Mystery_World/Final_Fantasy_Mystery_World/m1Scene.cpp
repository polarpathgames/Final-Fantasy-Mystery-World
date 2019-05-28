#include "m1Scene.h"
#include "p2Log.h"
#include "App.h"
#include "m1Audio.h"
#include "m1EntityManager.h"
#include "m1Map.h"
#include "m1MenuManager.h"
#include "m1GUI.h"
#include "m1Input.h"
#include "e1Player.h"
#include "m1FadeToBlack.h"
#include "m1Collisions.h"
#include "m1MenuManager.h"
#include "m1Cutscene.h"
#include "u1Button.h"
#include "u1Image.h"
#include "u1VerticalSlider.h"
#include "u1Bar.h"
#include "m1MainMenu.h"
#include "m1DialogSystem.h"
#include "m1Window.h"
#include "m1Render.h"

#include "Brofiler/Brofiler.h"

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

	menu_state = StatesMenu::NO_MENU;

	fx_writting = App->audio->LoadFx("assets/audio/sfx/LTTP_Text_Done.wav");
	fx_attack = App->audio->LoadFx("assets/audio/sfx/InBattle_Steps_on_Water1.wav");
	fx_frog_attack = App->audio->LoadFx("assets/audio/sfx/InBattle_anim.BasicAttack.wav");
	fx_dog_attack = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Door_Hit.wav");
	fx_plant_attack = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Punch1.wav");
	fx_ability_warrior = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Critical_Hit.wav");
	fx_ability_mage = App->audio->LoadFx("assets/audio/sfx/explosion_large_07.wav");
	fx_ability_mage_prepare = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Magic_Charge1.wav");
	fx_ability_archer = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Arrow3.wav");
	fx_ability_no_mana = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Not_Enough_Money.wav");
	fx_ability_screen = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Sparkle1.wav");
	fx_drop_pick_up = App->audio->LoadFx("assets/audio/sfx/retro_collect_pickup_coin_03.wav");
	fx_door_enter = App->audio->LoadFx("assets/audio/sfx/MC_Stairs_Up.wav");
	fx_potion = App->audio->LoadFx("assets/audio/sfx/Potion.wav");
	fx_denegated_potion = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Land_on_Wood.wav");
	fx_potion_menu = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_L1R1L2R2_Shifting.wav");
	fx_flash = App->audio->LoadFx("assets/audio/sfx/sci-fi_device_item_power_up_flash_01.wav");
	fx_die = App->audio->LoadFx("assets/audio/sfx/Hurt4.wav");
	fx_rock = App->audio->LoadFx("assets/audio/sfx/LTTP_Bomb_Drop.wav");
	fx_kill_enemy = App->audio->LoadFx("assets/audio/sfx/MC_Enemy_Kill.wav");
	fx_no_money = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Sit_Down.wav");
	fx_controller_conection = App->audio->LoadFx("assets/audio/sfx/ST_Passenger_Pleased.wav");
	fx_surprise = App->audio->LoadFx("assets/audio/sfx/MC_Shield.wav");
	fx_buy = App->audio->LoadFx("assets/audio/sfx/MainMenu_Cancel_Selection.wav");
	fx_buy_special = App->audio->LoadFx("assets/audio/sfx/song203.wav");
	fx_ability3 = App->audio->LoadFx("assets/audio/sfx/Ability3.wav");
	fx_ability3_hit = App->audio->LoadFx("assets/audio/sfx/Ability3_hit.wav");
	fx_burn = App->audio->LoadFx("assets/audio/sfx/burn.wav");
	fx_poison = App->audio->LoadFx("assets/audio/sfx/posion.wav");
	fx_pick_up_poti = App->audio->LoadFx("assets/audio/sfx/pick_up_poti.wav");
  
	mus_game_over = App->audio->LoadMusic("assets/audio/music/35.Final Fantasy TA - Judge.ogg");

	if (App->fast_start) {
		if (player == nullptr) {
			player_type = PlayerType::WARRIOR;
			App->globals.player_name.assign("Oriol :D");
			App->scene->player = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::WARRIOR, -100, -100, "warrior");
			App->map->Enable();
			App->menu_manager->CreateHUD();
		}
	}

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
		if (App->menu_manager->debug_screen.debug_screen == nullptr) {
			App->menu_manager->CreateDebugScreen();
		}
		else {
			App->menu_manager->DestroyDebugScreen();
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		App->map->grid = !App->map->grid;
	}

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		App->globals.ability1_gained = true;
		App->globals.ability2_gained = true;
		App->globals.ability3_gained = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		e1Player* swap = nullptr;
		iPoint new_pos = App->map->MapToWorld(player->actual_tile.x, player->actual_tile.y);
		switch(player_type) {
		case PlayerType::WARRIOR:
			player_type = PlayerType::ARCHER;
			swap = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::ARCHER, new_pos.x, new_pos.y, "");
			break;
		case PlayerType::ARCHER:
			player_type = PlayerType::MAGE;
			swap = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::MAGE, new_pos.x, new_pos.y, "");
			break;
		case PlayerType::MAGE:
			player_type = PlayerType::WARRIOR;
			swap = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::WARRIOR, new_pos.x, new_pos.y, "");
			break;
		}
		if (swap != nullptr) {
			swap->position = player->GetPosition() - swap->pivot;
			App->entity_manager->DeleteEntity(player);
			player = swap;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN && !App->fade_to_black->IsFading()) {
		if (App->map->actual_map != Maps::SHOP && App->map->actual_map != Maps::NONE && App->map->actual_map != Maps::HOME && App->map->actual_map != Maps::LOBBY) {
			if (App->input->GetKey(SDL_SCANCODE_LSHIFT)) {
				App->map->quest_rooms->ChangeRoom(COLLIDER_TYPE::COLLIDER_NEXT_B, true);
			}
			else {
				App->map->quest_rooms->ChangeRoom(COLLIDER_TYPE::COLLIDER_NEXT_A, true);
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN && !App->fade_to_black->IsFading()) {
		if (App->map->actual_map != Maps::SHOP && App->map->actual_map != Maps::NONE && App->map->actual_map != Maps::HOME && App->map->actual_map != Maps::LOBBY) {
			if (App->input->GetKey(SDL_SCANCODE_LSHIFT)) {
				App->map->quest_rooms->ChangeRoom(COLLIDER_TYPE::COLLIDER_LAST_B, true);
			}
			else {
				App->map->quest_rooms->ChangeRoom(COLLIDER_TYPE::COLLIDER_LAST_A, true);
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) {
		App->input->ControllerVibration(0.3F, 1000);
		App->entity_manager->CreateEntity(e1Entity::EntityType::EVENT, 0, 0, "blizzard");
	}

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		App->debug = !App->debug;
	}

	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		App->scene->player->god_mode = !App->scene->player->god_mode;
		App->menu_manager->GodModeIndicator(App->scene->player->god_mode);
	}

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		player->GetHitted(50);
	}

	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN) {
		App->fade_to_black->FadeToBlack(Maps::LOBBY);
		App->menu_manager->EnableHUD(false);
	}
		
	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN) {
		App->fade_to_black->FadeToBlack(Maps::TUTORIAL);
	}

	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN) {
		App->fade_to_black->FadeToBlack(Maps::QUEST2);
	}
	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		App->fade_to_black->FadeToBlack(Maps::FINAL_QUEST);
	}

	App->map->Draw();
	
	switch (menu_state) {
	case StatesMenu::NO_MENU:
		if ((App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN) && player->state == State::IDLE && App->dialog->end_dial && !App->cutscene_manager->is_executing && !player->turn_done && App->entity_manager->entity_turn == player) {
			if (App->menu_manager->pause.pause_panel == nullptr && App->ChangePause() && !App->cutscene_manager->is_executing) {
				App->audio->PlayFx(App->gui->fx_pause);
				App->menu_manager->CreatePauseMenu();
				player->BlockControls(true);
				menu_state = StatesMenu::PAUSE_MENU;
			}
		}
		if ((App->input->GetKey(App->input->keyboard_buttons.buttons_code.INVENTORY) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.INVENTORY) == KEY_DOWN) && player->state == State::IDLE && App->dialog->end_dial && !App->cutscene_manager->is_executing && !player->turn_done && App->entity_manager->entity_turn == player) {
			if (App->ChangeInventory()) {
				App->audio->PlayFx(App->gui->fx_inventory);
				App->menu_manager->CreateBigInventory();
				player->BlockControls(true);
				App->menu_manager->inventory.spline_move_inventory = App->easing_splines->CreateSpline(&App->menu_manager->inventory.inventory_background->position.x, 320, 1200, TypeSpline::EASE_OUT_BACK, std::bind(&UI_inventory::SetClipInInventory, App->menu_manager->inventory));
				menu_state = StatesMenu::INVENTORY_MENU;
			}
		}
		break;
	case StatesMenu::INVENTORY_MENU:
		if (App->input->GetKey(App->input->keyboard_buttons.buttons_code.INVENTORY) == KEY_DOWN || App->input->GetControllerButton(App->input->controller_Buttons.buttons_code.INVENTORY) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->ChangeInventory();
			App->easing_splines->CleanUp();
			App->menu_manager->DestroyBigInventory();
			player->BlockControls(false);
			menu_state = StatesMenu::NO_MENU;
		}
		if (App->menu_manager->inventory.spline_move_inventory == nullptr) {
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_AXIS_TRIGGERRIGHT) == KEY_DOWN) {
				App->menu_manager->inventory.ChangeInventory(true);
			}
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_AXIS_TRIGGERLEFT) == KEY_DOWN) {
				App->menu_manager->inventory.ChangeInventory(false);
			}
		}
		break;
	case StatesMenu::FIRSTABILITY_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->menu_manager->DestroyHelpAbilityMenu();
			menu_state = StatesMenu::NO_MENU;
			//App->menu_manager->ShowHUD(true);
			player->BlockControls(false);
		}
	
		break;
	case StatesMenu::GO_TO_QUEST_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->menu_manager->DestroyGoToQuestMenu();
			menu_state = StatesMenu::NO_MENU;
		}
		break;
	case StatesMenu::POTION_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->menu_manager->DeletePotionMenu();
			menu_state = StatesMenu::INVENTORY_MENU;
		}
		break;
	case StatesMenu::PAUSE_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->audio->PlayFx(App->main_menu->fx_push_button_return);
			App->ChangePause();
			//App->menu_manager->ShowHUD(true);
			//std::function<void(void)> funct = App->menu_manager->DestroyPauseMenu();
			App->easing_splines->CreateSpline(&App->menu_manager->pause.pause_panel->position.y, -830, 500, TypeSpline::EASE, std::bind(&m1MenuManager::DestroyPauseMenu,App->menu_manager));
			//info->funct = &m1MenuManager::DestroyPauseMenu;

			//App->menu_manager->DestroyPauseMenu();
			menu_state = StatesMenu::NO_MENU;
			player->BlockControls(false);
		}
		break;
	case StatesMenu::OPTIONS_MENU:
		if (App->menu_manager->options.options_panel != nullptr) {
			App->menu_manager->UpdateOptionsMenu();
		}
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->menu_manager->CreatePauseMenu();
			App->menu_manager->DestroyOptions();
			//App->menu_manager->ShowHUD(true);
			player->BlockControls(true);
			App->menu_manager->EnableHUD(true);
			App->menu_manager->hud.diagonal_compass->drawable = true;
			App->menu_manager->hud.vertical_compass->drawable = false;
			menu_state = StatesMenu::PAUSE_MENU;
		}
		break;
	case StatesMenu::SHOP_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			close_shop = false;
			App->menu_manager->DestroyShopMenu();
			menu_state = StatesMenu::NO_MENU;
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN || App->input->GetAxisDown(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == 1) {
			if (App->gui->GetFocus() == App->menu_manager->shop.shop_button_sword && App->menu_manager->shop.shop_item_zone->GetGlobalPosition().y > 240) {
				App->menu_manager->shop.shop_vertical_slider->SetValue(45);
			}
			else if (App->gui->GetFocus() == App->menu_manager->shop.shop_button_helmet && App->menu_manager->shop.shop_vertical_slider->value != 90) {
				App->menu_manager->shop.shop_vertical_slider->SetValue(90);
			}
			else if (App->gui->GetFocus() == App->menu_manager->shop.shop_button_ring) {
				if (close_shop) {
					App->audio->PlayFx(App->gui->fx_focus);
					App->gui->FocusButton(App->menu_manager->shop.button_close_shop);
				}
				else
					close_shop = true;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN || App->input->GetAxisDown(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY) == -1) {
			if (App->gui->GetFocus() == App->menu_manager->shop.shop_button_sword) {
				App->menu_manager->shop.shop_vertical_slider->SetValue(45);
			}
			else if (App->gui->GetFocus() == App->menu_manager->shop.shop_button_mana_potion) {
				App->menu_manager->shop.shop_vertical_slider->SetValue(0);
			}
			else if (App->gui->GetFocus() == App->menu_manager->shop.button_close_shop) {
				App->audio->PlayFx(App->gui->fx_focus);
				App->gui->FocusButton(App->menu_manager->shop.shop_button_ring);
			}
			else
				close_shop = false;
		}
		break;
	case StatesMenu::HELP_DIAGONAL_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->menu_manager->DestroyHelpDiagonalMenu();
			player->BlockControls(false);
			//App->menu_manager->ShowHUD(true);
			menu_state = StatesMenu::NO_MENU;
		}
		break;
	case StatesMenu::HELP_ATTACK_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->menu_manager->DestroyHelpAttackMenu();
			player->BlockControls(false);
			//App->menu_manager->ShowHUD(true);
			menu_state = StatesMenu::NO_MENU;
		}
		break;
	case StatesMenu::HELP_ABILITY_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->menu_manager->DestroyHelpAbilityMenu();
			player->BlockControls(false);
			//App->menu_manager->ShowHUD(true);
			menu_state = StatesMenu::NO_MENU;
		}
		break;
	case StatesMenu::CONTROLS_MENU:
		if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_START) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_B) == KEY_DOWN) {
			App->menu_manager->CreateOptions();
			App->menu_manager->DestroyControls();
			menu_state = StatesMenu::OPTIONS_MENU;
		}
		if (App->menu_manager->control_to_change != nullptr && !App->menu_manager->control_to_change->Update()) {
			delete App->menu_manager->control_to_change;
			App->menu_manager->control_to_change = nullptr;
		}
		break;
	}

	if (App->menu_manager->debug_screen.debug_screen != nullptr) {
		App->menu_manager->UpdateDebugScreen();
	}
	ShitFunctionJAJA();

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
void m1Scene::CreateEntitiesFromXML(pugi::xml_node& node)
{
	e1Entity* ent = nullptr;
	ent = App->entity_manager->CreateEntity((e1Entity::EntityType)node.child("stats").attribute("entity_type").as_int(), -38, 375, "player");
	player = (e1Player*)ent;
}
bool m1Scene::Load(pugi::xml_node& node)
{
	pugi::xml_node options = node.child("options");
	App->win->fullscreen = options.attribute("cb_fullscreen").as_bool();
	App->audio->mute = options.attribute("mute_general").as_bool();
	App->audio->mute_volume = options.attribute("mute_music").as_bool();
	App->audio->mute_fx = options.attribute("mute_fx").as_bool();
	App->audio->volume_general = options.attribute("general_volume").as_uint();
	App->audio->volume = options.attribute("music_volume").as_uint();
	App->audio->volume_fx = options.attribute("fx_volume").as_uint();

	return true;
}
bool m1Scene::Save(pugi::xml_node& node) const
{
	pugi::xml_node options = node.append_child("options");
	options.append_attribute("cb_fullscreen") = (bool)App->win->fullscreen;
	options.append_attribute("mute_general") = (bool)App->audio->mute;
	options.append_attribute("mute_music") = (bool)App->audio->mute_volume;
	options.append_attribute("mute_fx") = (bool)App->audio->mute_fx;
	options.append_attribute("general_volume") = (uint)App->audio->volume_general;
	options.append_attribute("music_volume") = (uint)App->audio->volume;
	options.append_attribute("fx_volume") = (uint)App->audio->volume_fx;

	return true;
}

void m1Scene::CreateEntities()
{
	//iterate all objects of map made with Tiled to find entities

	for (std::list<ObjectLayer*>::iterator position = App->map->data.objects.begin(); position != App->map->data.objects.end(); position++) {
		if ((*position)->name == "player") {
			if (player == nullptr) {
				if ((*position)->ent_type == "default") { // start position
					switch (player_type) {
					case PlayerType::WARRIOR:
						player = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::WARRIOR, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
						break;
					case PlayerType::ARCHER:
						player = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::ARCHER, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
						break;
					case PlayerType::MAGE:
						player = (e1Player*)App->entity_manager->CreateEntity(e1Entity::EntityType::MAGE, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
						break;
					}
					App->render->CenterCameraOnPlayer(player->position);
					//CreateHUD(); POSSIBLE BUG
				}
			}
			else {
				if ((*position)->ent_type == "shop" && App->map->last_map == Maps::SHOP) { // position after leaving shop
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->Init();
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "home" && App->map->last_map == Maps::HOME){ // position after leaving home
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->Init();
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "in_shop") { // position in the shop
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->Init();
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "in_home" && player->state != State::MENU) { // position in the home
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->Init();
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "after_death" && player->state == State::MENU) { // position in the home
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->Init();
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "default" && App->map->last_map == Maps::TUTORIAL) {
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->Init();
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "default2" && App->map->last_map == Maps::QUEST2) {
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->Init();
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
				else if ((*position)->ent_type == "default3" && App->map->last_map == Maps::FINAL_QUEST) {
					player->position.create(App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y);
					player->Init();
					player->CenterPlayerInTile();
					App->render->CenterCameraOnPlayer(player->position);
				}
			}
		}
		else if ((*position)->ent_type == "static") {
			if ((*position)->name == "rock") {
				App->entity_manager->CreateEntity(e1Entity::EntityType::ROCK, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
			}
			else if ((*position)->name == "NPC_DAUGHTER") {
				if (App->map->actual_map == Maps::HOME) {
					if (!App->globals.CutSceneHomeToSleepQuest2) {
						App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
					}
				}
				else if (App->map->actual_map == Maps::LOBBY) {
					App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
				}
			}
			else
				App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
		}
		else if ((*position)->name == "npc") {
			if ((*position)->ent_type == "Daughter") {
				App->entity_manager->CreateEntity(e1Entity::EntityType::DAUGHTER, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x, App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y, (*position)->name);
			}			
		}
		else if ((*position)->name == "collider") { // COLLIDERS
			if ((*position)->properties.FindNameValue("shop")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_SHOP, nullptr);
			}
			else if ((*position)->properties.FindNameValue("home")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_HOME, nullptr);
			}
			else if ((*position)->properties.FindNameValue("menu_quest")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_MENU_QUEST, nullptr);
			}
			else if ((*position)->properties.FindNameValue("cutscene_bridge")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_CUTSCENE_BRIDGE, nullptr);
			}
			else if ((*position)->properties.FindNameValue("quest2")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_QUEST_ICE, nullptr);
			}
			else if ((*position)->properties.FindNameValue("bed") && App->globals.CutSceneLobbyQuest2Finish) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_BED, nullptr);
			}
			else if ((*position)->properties.FindNameValue("quest3")) {
				App->collision->AddCollider({ App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).x,App->map->TiledToWorld((*position)->coll_x, (*position)->coll_y).y,(*position)->coll_width, (*position)->coll_height }, COLLIDER_QUEST_FIRE, nullptr);
			}
		}
		else {
			LOG("There isn't any entity with name %s and type %s", (*position)->name.data(), (*position)->ent_type.data());
		}
	}
}



void m1Scene::ShitFunctionJAJA()
{
	if (App->fade_to_black->current_step == App->fade_to_black->fade_from_black && !App->cutscene_manager->is_executing && !App->globals.CutSceneLobbyExplain && App->map->actual_map == Maps::LOBBY) {
		App->cutscene_manager->PlayCutscene("assets/xml/CutsceneLobbyTutorial.xml");
		App->globals.CutSceneLobbyExplain = true;
		App->globals.Tutorial_first_time = false;
	}
	if (App->fade_to_black->current_step == App->fade_to_black->fade_from_black && !App->cutscene_manager->is_executing && !App->globals.CutSceneLobbyQuest2Finish && App->map->actual_map == Maps::LOBBY && !App->globals.Tutorial_first_time && App->globals.ice_queen_killed) {
		App->cutscene_manager->PlayCutscene("assets/xml/CutsceneLobbyQuest2.xml");
		App->globals.CutSceneLobbyQuest2Finish = true;
	}
	if (App->fade_to_black->current_step == App->fade_to_black->fade_from_black && !App->cutscene_manager->is_executing && !App->globals.CutSceneHomeToSleeQuest3 && App->map->actual_map == Maps::LOBBY && App->globals.CutSceneHomeToSleepQuest2 == true && App->globals.CutSceneLobbyQuest2Finish && App->map->last_map == Maps::HOME && App->globals.sleep2) {
		App->cutscene_manager->PlayCutscene("assets/xml/CutsceneLobbyQuest3.xml");
		App->globals.CutSceneHomeToSleeQuest3 = true;
	}
	if (App->fade_to_black->current_step == App->fade_to_black->fade_from_black && !App->cutscene_manager->is_executing && App->globals.CutsceneFinalGame && !App->globals.CutsceneFinalFinalGame) {
		App->map->lobby_state = LobbyState::NORMAL_LOBBY;
		App->map->ChangeMap(Maps::LOBBY);
		App->cutscene_manager->PlayCutscene("assets/xml/CutsceneLobbyCredits.xml");
		App->globals.CutsceneFinalFinalGame = true;	
	}
	if (!App->cutscene_manager->is_executing && App->globals.CutsceneFinalFinalGame && !App->globals.CutSceneLobbyCredits) {		
		App->map->Disable();
		App->menu_manager->DestroyHUD();
		App->menu_manager->CreateCongratualtions();
		App->globals.CutSceneLobbyCredits = true;
	}
}

bool m1Scene::Interact(u1GUI* interact)
{
	bool ret = true;
	switch (menu_state) {
	case StatesMenu::GO_TO_QUEST_MENU:
		if (interact == App->menu_manager->quest.tutorial_button) {
			App->audio->PlayFx(fx_ability_warrior);
		
			App->menu_manager->DestroyGoToQuestMenu();
			App->fade_to_black->FadeToBlack(Maps::TUTORIAL);
			menu_state = StatesMenu::NO_MENU;
			App->menu_manager->EnableHUD(true);
			ret = false;
		}
		if (interact == App->menu_manager->quest.cancel_quest_button) {
			App->audio->PlayFx(App->main_menu->fx_push_button_return);
			App->menu_manager->DestroyGoToQuestMenu();
			menu_state = StatesMenu::NO_MENU;
			ret = false;
		}
		if (interact == App->menu_manager->quest.quest2_button) {
			App->audio->PlayFx(fx_ability_warrior);

			App->menu_manager->DestroyGoToQuestMenu();
			App->fade_to_black->FadeToBlack(Maps::QUEST2);
			menu_state = StatesMenu::NO_MENU;
			App->menu_manager->EnableHUD(true);
			ret = false;
		}
		if (interact != nullptr && interact != App->menu_manager->quest.cancel_quest_button) {
			App->audio->PlayFx(fx_potion_menu);
		}
		break;
	case StatesMenu::INVENTORY_MENU:
		if (interact == App->menu_manager->inventory.hp_potion_button) {
			if (App->map->actual_map != Maps::LOBBY && App->map->actual_map != Maps::HOME && App->map->actual_map != Maps::SHOP) {
				App->menu_manager->DeletePotionMenu();
				App->menu_manager->CreatePotionMenu(App->menu_manager->inventory.hp_potion_button);
				menu_state = StatesMenu::POTION_MENU;
			}		
			ret = false;
		}
		if (interact == App->menu_manager->inventory.mana_potion_button) {
			if (App->map->actual_map != Maps::LOBBY && App->map->actual_map != Maps::HOME && App->map->actual_map != Maps::SHOP) {
				App->menu_manager->DeletePotionMenu();
				App->menu_manager->CreatePotionMenu(App->menu_manager->inventory.mana_potion_button);
				menu_state = StatesMenu::POTION_MENU;
			}
			ret = false;
		}
		if (interact != nullptr) {
			App->audio->PlayFx(fx_potion_menu);
		}
		break;
	case StatesMenu::POTION_MENU:
		if (interact == App->menu_manager->potion.use_hp_button) {
			if (player->stats.num_hp_potions >= 1) {
				App->audio->PlayFx(fx_potion);
				--player->stats.num_hp_potions;
				player->AugmentLives(120);
				App->menu_manager->inventory.hp_potion_label->SetText(std::string("x " + std::to_string(player->stats.num_hp_potions)).data());
				App->menu_manager->DeletePotionMenu();
				menu_state = StatesMenu::INVENTORY_MENU;
				ret = false;
			}
			else
				App->audio->PlayFx(fx_denegated_potion);
		}
		if (interact == App->menu_manager->potion.use_mana_button) {
			if (player->stats.num_mana_potions >= 1) {
				App->audio->PlayFx(fx_potion);
				--player->stats.num_mana_potions;
				player->AugmentMana(75);
				App->menu_manager->inventory.mana_potion_label->SetText(std::string("x " + std::to_string(player->stats.num_mana_potions)).data());
				App->menu_manager->DeletePotionMenu();
				menu_state = StatesMenu::INVENTORY_MENU;
				ret = false;
			}
			else
				App->audio->PlayFx(fx_denegated_potion);
		}
		if (interact == App->menu_manager->potion.cancel_button) {
			App->audio->PlayFx(fx_potion_menu);
			App->menu_manager->DeletePotionMenu();
			menu_state = StatesMenu::INVENTORY_MENU;
			ret = false;
		}
		/*if (interact != nullptr) {
			
		}*/
		break;
	case StatesMenu::DIE_MENU:
		if (interact == App->menu_manager->game_over.button_continue_lobby) {
			App->menu_manager->DestroyGameOver();

			if (App->map->actual_map == Maps::TUTORIAL && !App->globals.CutSceneAfterBossTutorialPlayed) {
				App->fade_to_black->FadeToBlack(Maps::TUTORIAL);
				App->menu_manager->EnableHUD(true);
			}
			else 
				App->fade_to_black->FadeToBlack(Maps::HOME);
			
			menu_state = StatesMenu::NO_MENU;

			ret = false;
			
		}
		if (interact == App->menu_manager->game_over.button_return_main) {
			active = false;
			App->audio->PlayFx(App->main_menu->fx_push_button_return);
			App->menu_manager->DestroyGameOver();
			App->entity_manager->Disable();
			App->map->Disable();
			App->ChangePause();		
			App->main_menu->Enable();
			App->menu_manager->DestroyHUD();
			App->map->lobby_state = LobbyState::NORMAL_LOBBY;
			App->scene->SetMenuState(StatesMenu::NO_MENU);
			ret = false;
		}
		break;
	case StatesMenu::SHOP_MENU:
		if (interact == App->menu_manager->shop.button_close_shop) {
			App->menu_manager->DestroyShopMenu();
			App->audio->PlayFx(App->main_menu->fx_push_button_return);
			menu_state = StatesMenu::NO_MENU;
			close_shop = false;
			ret = false;
		}

		if (interact == App->menu_manager->shop.shop_button_hp_potion) {
			if (player->stats.gold >= price_hp_potion || player->god_mode) {
				// audio comprar
				App->audio->PlayFx(App->scene->fx_buy);
				player->ReduceGold(price_hp_potion);
				++player->stats.num_hp_potions;
				App->menu_manager->inventory.hp_potion_label->SetText(std::string("x " + std::to_string(player->stats.num_hp_potions)).data());
				App->menu_manager->inventory.money_label->SetText(std::string("x " + std::to_string(player->stats.gold)).data());
			}
			else {
				// audio no money
				App->audio->PlayFx(App->scene->fx_no_money);
			}
		}
		if (interact == App->menu_manager->shop.shop_button_mana_potion) {
			if (player->stats.gold >= price_mana_potion || player->god_mode) {
				// audio comprar
				App->audio->PlayFx(App->scene->fx_buy);
				player->ReduceGold(price_mana_potion);
				++player->stats.num_mana_potions;
				App->menu_manager->inventory.mana_potion_label->SetText(std::string("x " + std::to_string(player->stats.num_mana_potions)).data());
				App->menu_manager->inventory.money_label->SetText(std::string("x " + std::to_string(player->stats.gold)).data());
			}
			else {
				// audio no money
				App->audio->PlayFx(App->scene->fx_no_money);
			}
		}
		if (interact == App->menu_manager->shop.shop_button_sword) {
			if ((player->stats.gold >= price_ability3 || player->god_mode) && !App->globals.ability3_gained) {
				// audio comprar
				App->audio->PlayFx(App->scene->fx_buy_special);
				player->ReduceGold(price_ability3);
				App->globals.ability3_gained = true;
				App->menu_manager->inventory.money_label->SetText(std::string("x " + std::to_string(player->stats.gold)).data());

				
				if (player_type == PlayerType::WARRIOR)
					App->menu_manager->shop.shop_background_item3->SetImage({ 2751,1614,161,61 });
				else if (player_type == PlayerType::ARCHER)
					App->menu_manager->shop.shop_background_item3->SetImage({ 2751,1752,161,61 });
				else if (player_type == PlayerType::MAGE)
					App->menu_manager->shop.shop_background_item3->SetImage({ 2751,1683,161,61 });

				App->menu_manager->shop.shop_coin3->drawable = false;
				App->menu_manager->shop.shop_sword_image->drawable = false;
			}
			else {
				// audio no money
				App->audio->PlayFx(App->scene->fx_no_money);
			}
		}
		if (interact == App->menu_manager->shop.shop_button_helmet) {
			if ((player->stats.gold >= price_helmet || player->god_mode) && !App->globals.helmet_bought) {
				// audio comprar
				App->audio->PlayFx(App->scene->fx_buy_special);
				player->ReduceGold(price_helmet);
				App->globals.helmet_bought = true;
				App->menu_manager->inventory.money_label->SetText(std::string("x " + std::to_string(player->stats.gold)).data());

				player->stats.max_lives += helmet_hp;
				player->AugmentLives(helmet_hp);
				App->menu_manager->hud.player_hp_bar->max_capacity = player->stats.max_lives;
				App->menu_manager->hud.player_hp_bar->UpdateBar(helmet_hp, UIType::HPBAR);

				App->menu_manager->hud.player_hp_bar->PrintBarNumbers();

				App->menu_manager->shop.shop_background_item4->SetImage({ 2751,1821,161,61 });
				App->menu_manager->shop.shop_helmet_image->drawable = false;
				App->menu_manager->shop.shop_coin4->drawable = false;
				


			}
			else {
				// audio no money
				App->audio->PlayFx(App->scene->fx_no_money);
			}
		}
		if (interact == App->menu_manager->shop.shop_button_ring) {
			if ((player->stats.gold >= price_ring || player->god_mode) && !App->globals.ring_bought) {
				// audio comprar
				App->audio->PlayFx(App->scene->fx_buy_special);
				player->ReduceGold(price_ring);
				App->globals.ring_bought = true;
				App->menu_manager->inventory.money_label->SetText(std::string("x " + std::to_string(player->stats.gold)).data());

				player->stats.max_mana += ring_mana;
				player->AugmentMana(ring_mana);
				App->menu_manager->hud.player_mana_bar->max_capacity = player->stats.max_mana;
				App->menu_manager->hud.player_mana_bar->UpdateBar(ring_mana, UIType::MANABAR);

				App->menu_manager->hud.player_mana_bar->PrintBarNumbers();

				App->menu_manager->shop.shop_background_item5->SetImage({ 2751,1890,161,61 });
				App->menu_manager->shop.shop_ring_image->drawable = false;
				App->menu_manager->shop.shop_coin5->drawable = false;

			}
			else {
				// audio no money
				App->audio->PlayFx(App->scene->fx_no_money);
			}
		}
		break;
	}

	return ret;
}

StatesMenu m1Scene::GetMenuState()
{
	return menu_state;
}

void m1Scene::SetMenuState(const StatesMenu & menu)
{
	menu_state = menu;
}