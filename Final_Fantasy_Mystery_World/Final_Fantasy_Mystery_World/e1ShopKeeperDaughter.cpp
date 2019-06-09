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

e1ShopKeeperDaughter::e1ShopKeeperDaughter(const int &x, const int &y) : e1NPC(x, y, "ShopKeeperDaughter")
{
	LoadEntityData("assets/entities/Little_Girl.tsx");
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
		if (actual_tile.DistanceTo(App->scene->player->actual_tile) <= 1) {
			if (!App->globals.CutSceneAfterBossTutorialPlayed) {
				CreateInteractionButton();
			}

			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetControllerButton(SDL_CONTROLLER_BUTTON_A) == KEY_DOWN) {
				App->cutscene_manager->PlayCutscene("assets/xml/CutsceneAfterBossTutorial.xml");
				App->globals.CutSceneAfterBossTutorialPlayed = true;
				App->globals.CutSceneFinalRoomTutorialPlayed = true;
				DestroyInteractionButton();
			}
		}
		else {
			DestroyInteractionButton();
		}
		if (App->globals.CutSceneAfterBossTutorialPlayed && !App->cutscene_manager->is_executing) {
			App->fade_to_black->FadeToBlack(Maps::LOBBY);
		}
	return true;
}

void e1ShopKeeperDaughter::Draw(float dt) {
	if (drawable)
		App->render->Blit(data.tileset.texture, position.x, position.y, &(current_animation->GetCurrentFrame(dt)), true);
}