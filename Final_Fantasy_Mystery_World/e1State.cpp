#include "e1State.h"
#include "App.h"
#include "m1Textures.h"
#include "m1Render.h"
#include "m1Scene.h"
#include "m1EntityManager.h"

e1State::e1State(int x, int y, const char * name) :e1Entity(x, y) {
	if (strcmp(name,"snowstorm") == 0) {
		state = EventStates::SNOWSTORM;
		turn_effect = 3U;
		animation = new Animation();
		animation->PushBack({ 0,0,1024,768 });
		time_effect = 2U;
		damage = 5;
		dynamic = false;
	}

	if (strcmp(name, "poison") == 0) {
		state = EventStates::POISON;
		turn_effect = 3U;
		target = (e1Entity*)App->scene->player;
		max_number_hit = 5U;
		time_effect = 1U;
		damage = 5;
		frame = { 1032,0,18,32 };
	}

	allow_turn = true;
	drawable = false;

	data.tileset.imagePath.assign("assets/sprites/event_states.png");
	data.tileset.texture = App->tex->Load(data.tileset.imagePath.data());
}

e1State::~e1State()
{
	if (animation != nullptr) {
		delete animation;
		animation = nullptr;
	}
}

bool e1State::PreUpdate()
{
	if (!doing_effect) {
		turn_count++;
		if (turn_count >= turn_effect) {
			// Do effect
			doing_effect = true;
			timer.Start();
			switch (state)
			{
			case EventStates::SNOWSTORM: {
				std::vector<e1Entity*> list = App->entity_manager->GetEntities();
				for (std::vector<e1Entity*>::iterator item = list.begin(); item != list.end(); ++item) {
					if ((*item)->type == e1Entity::EntityType::PLAYER || (*item)->type == e1Entity::EntityType::ENEMY)
						static_cast<e1DynamicEntity*>(*item)->GetHitted(damage);
				}
				number_hit++;
			}
				break;
			case EventStates::POISON:
				if (target != nullptr) {
					static_cast<e1DynamicEntity*>(target)->GetHitted(damage);
				}
				number_hit++;
				break;
			case EventStates::NONE:
				doing_effect = false;
				turn_done = true;
				break;
			default:
				break;
			}
		}
		else {
			turn_done = true;
		}
	}

	return true;
}

bool e1State::Update(float dt)
{
	if (doing_effect) {
		drawable = true;
		if (target != nullptr) {
			position = target->position;
		}

		if (timer.ReadSec() >= time_effect) { // or animation finish
			turn_done = true;
			turn_count = 0U;
			doing_effect = false;
			drawable = false;
			if (max_number_hit != 0u) {
				if (number_hit >= max_number_hit) {
					to_delete = true;
				}
			}
		}
	}

	return true;
}

bool e1State::PostUpdate()
{
	if (drawable) {
		if (animation != nullptr) {
			App->render->Blit(data.tileset.texture, position.x, position.y, &animation->GetCurrentFrame(App->GetDeltaTime()), dynamic, SDL_FLIP_NONE);
		}
		else if (frame.h != 0 && frame.w != 0) {
			App->render->Blit(data.tileset.texture, position.x, position.y, &frame, dynamic, SDL_FLIP_NONE);
		}
		else {
			App->render->Blit(data.tileset.texture, position.x, position.y, NULL, dynamic, SDL_FLIP_NONE);
		}
	}
	return true;
}