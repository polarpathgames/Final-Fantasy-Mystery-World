#include "e1State.h"
#include "App.h"
#include "m1Textures.h"
#include "m1Render.h"

e1State::e1State(int x, int y, const char * name) :e1Entity(x, y) {
	if (strcmp(name,"snowstorm") == 0) {
		state = EventStates::SNOWSTORM;
		turn_effect = 3u;
		animation = new Animation();
		animation->PushBack({ 0,0,1024,768 });
		position.create(App->render->camera.x, App->render->camera.y);
	}

	allow_turn = true;
	drawable = false;

	data.tileset.imagePath.assign("assets/sprites/event_states.png");
	data.tileset.texture = App->tex->Load(data.tileset.imagePath.data());
}

e1State::~e1State()
{
	if (animation == nullptr) {
		delete animation;
		animation = nullptr;
	}
}

bool e1State::PreUpdate()
{
	turn_count++;
	if (turn_count >= turn_effect) {
		// Do effect
		switch (state)
		{
		case EventStates::SNOWSTORM:
			doing_animation = true;
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
		turn_count = 0u;
	}

	return true;
}

bool e1State::Update(float dt)
{
	if (doing_animation) {
		drawable = true;
	}

	return true;
}
