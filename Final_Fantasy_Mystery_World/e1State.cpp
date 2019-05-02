#include "e1State.h"
#include "App.h"
#include "m1Textures.h"
#include "m1Render.h"
#include "m1EntityManager.h"

e1State::e1State(int x, int y, const char * name) :e1Entity(x, y) {
	if (strcmp(name,"snowstorm") == 0) {
		state = EventStates::SNOWSTORM;
		turn_effect = 3U;
		animation = new Animation();
		animation->PushBack({ 0,0,1024,768 });
		dynamic = false;
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
			switch (state)
			{
			case EventStates::SNOWSTORM: {
				doing_effect = true;
				timer.Start();
				std::vector<e1Entity*> list = App->entity_manager->GetEntities();
				for (std::vector<e1Entity*>::iterator item = list.begin(); item != list.end(); ++item) {
					if ((*item)->type == e1Entity::EntityType::PLAYER || (*item)->type == e1Entity::EntityType::ENEMY)
						static_cast<e1DynamicEntity*>(*item)->GetHitted(5);
				}
			}
				break;
			case EventStates::POISON:
				break;
			case EventStates::NONE:
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

		if (timer.ReadSec() >= 2) {
			turn_done = true;
			turn_count = 0U;
			doing_effect = false;
			drawable = false;
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