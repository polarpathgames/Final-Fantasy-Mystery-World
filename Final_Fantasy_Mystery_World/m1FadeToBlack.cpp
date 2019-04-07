#include <math.h>
#include "App.h"
#include "m1FadeToBlack.h"
#include "m1Render.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "m1Window.h"
#include "p2Log.h"
#include "App.h"
#include "m1Map.h"

#include "Brofiler/Brofiler.h"

m1FadeToBlack::m1FadeToBlack()
{
}

m1FadeToBlack::~m1FadeToBlack()
{
}


// Load assets
bool m1FadeToBlack::Start()
{
	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);

	screen = { 0,0,(int)app->win->width,  (int)app->win->height };

	return true;
}

// Update: draw background
bool m1FadeToBlack::Update(float dt)
{
	BROFILER_CATEGORY("UpdateFadeToBlack", Profiler::Color::DarkOrchid);

	if (current_step == fade_step::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time)
		{
			if (to_disable != nullptr)
				to_disable->Disable();
			if (to_enable != nullptr)
				to_enable->Enable();
			if (want_to_change_map)
				app->map->ChangeMap(map_to_change);
			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = fade_step::fade_from_black;
		}
	} break;

	case fade_step::fade_from_black:
	{
		normalized = 1.0f - normalized;

		if (now >= total_time)
			current_step = fade_step::none;
	} break;
	}

	// Finally render the black square with alpha on the screen
	SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(app->render->renderer, &screen);

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool m1FadeToBlack::FadeToBlack(m1Module* module_off, m1Module* module_on, float time)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		to_enable = module_on;
		to_disable = module_off;
		want_to_change_map = false;
		ret = true;
	}

	return ret;
}
bool m1FadeToBlack::FadeToBlack(m1Module * module_off, float time)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		to_disable = module_off;
		want_to_change_map = false;
		ret = true;
	}

	return ret;
}
bool m1FadeToBlack::FadeToBlack(float time, m1Module * module_on)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		to_enable = module_on;
		want_to_change_map = false;
		ret = true;
	}

	return ret;
}
bool m1FadeToBlack::FadeToBlack(float time)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		want_to_change_map = false;
		ret = true;
	}

	return ret;
}
bool m1FadeToBlack::FadeToBlack(Maps type, float time)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		want_to_change_map = true;
		map_to_change = type;
		ret = true;
	}

	return ret;
}
bool m1FadeToBlack::FadeToBlack(m1Module * module_off, Maps type, float time)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		want_to_change_map = true;
		to_disable = module_off;
		map_to_change = type;
		ret = true;
	}

	return ret;
}
bool m1FadeToBlack::IsFading() const
{
	return current_step != fade_step::none;
}