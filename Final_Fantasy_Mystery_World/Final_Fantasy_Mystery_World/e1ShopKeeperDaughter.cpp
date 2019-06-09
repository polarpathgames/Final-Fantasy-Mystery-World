#include "e1ShopKeeperDaughter.h"
#include "e1NPC.h"
#include "App.h"
#include "m1Map.h"
#include "p2Rooms.h"
#include "m1Cutscene.h"
#include "m1EntityManager.h"
#include "m1Input.h"
#include "m1FadeToBlack.h"
#include "m1Scene.h"
#include "m1GUI.h"
#include "e1Player.h"
#include "m1Render.h"
#include "m1Window.h"
#include "u1Image.h"

e1ShopKeeperDaughter::e1ShopKeeperDaughter(const int &x, const int &y) : e1NPC(x, y)
{
	LoadEntityData("assets/entities/Little_Girl.tsx");
	name.assign("ShopKeeperDaughter");
	npc_type = NPCType::DAUGHTER;
	current_animation = &anim.IdleUpRight;
	actual_tile = App->map->WorldToMap(position.x + 16, position.y + 38);
	App->map->data.no_walkables.push_back(actual_tile + iPoint{ 0,-1 });
}

e1ShopKeeperDaughter::~e1ShopKeeperDaughter()
{
	App->map->data.no_walkables.remove(actual_tile + iPoint{ 0,-1 });
}

bool e1ShopKeeperDaughter::PreUpdate()
{
	return true;
}

bool e1ShopKeeperDaughter::Update(float dt)
{
	if (App->map->quest_rooms != nullptr && App->map->quest_rooms->actual_room != nullptr && !App->entity_manager->ThereAreEnemies() && !App->cutscene_manager->is_executing) {
		if (actual_tile.DistanceTo(App->scene->player->actual_tile) <= 1) {
			if (!App->globals.CutSceneAfterBossTutorialPlayed) {
				if (button_interact == nullptr) {

					button_interact = App->gui->AddImage(0, 0, { 1524,2052,31,31 }, nullptr, App->gui->screen, true, false, false, false);

					iPoint pos{ 0,0 };
					pos.x = (int)(App->render->camera.x) + (App->scene->player->GetPosition().x) * (int)App->win->GetScale() - button_interact->section.w*0.5F;
					pos.y = (int)(App->render->camera.y) + (App->scene->player->position.y) * (int)App->win->GetScale() - button_interact->section.h;

					button_interact->SetPos(pos.x, pos.y);
				}
				else {
					iPoint pos{ 0,0 };
					pos.x = (int)(App->render->camera.x) + (App->scene->player->GetPosition().x) * (int)App->win->GetScale() - button_interact->section.w*0.5F;
					pos.y = (int)(App->render->camera.y) + (App->scene->player->position.y) * (int)App->win->GetScale() - button_interact->section.h;
					button_interact->SetPos(pos.x, pos.y);
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) {
				App->cutscene_manager->PlayCutscene("assets/xml/CutsceneAfterBossTutorial.xml");
				App->globals.CutSceneAfterBossTutorialPlayed = true;
				App->globals.CutSceneFinalRoomTutorialPlayed = true;
				if (button_interact != nullptr) {
					App->gui->DeleteUIElement((u1GUI*)button_interact);
					button_interact = nullptr;
				}
			}
		}
		else {
			if (button_interact != nullptr) {
				App->gui->DeleteUIElement((u1GUI*)button_interact);
				button_interact = nullptr;
			}
		}
		if (App->globals.CutSceneAfterBossTutorialPlayed && !App->cutscene_manager->is_executing) {
			App->fade_to_black->FadeToBlack(Maps::LOBBY);
		}
	}
	return true;
}



void e1ShopKeeperDaughter::IdAnimToEnum() //Assign every id animation to enum animation
{
	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 1:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 0:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;
		case 3:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 4:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 6:
			data.animations[i].animType = AnimationState::WALKING_DOWN_RIGHT;
			break;
		case 7:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;
		case 9:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 10:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 12:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 13:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 15:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 16:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 18:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 19:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 21:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 22:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		}
	}
}