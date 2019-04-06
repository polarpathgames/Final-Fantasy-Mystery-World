#include "p2Defs.h"
#include "p2Log.h"
#include "j1Audio.h"
#include <list>
#include <string>
#include "j1Input.h"
#include "j1App.h"
#include "j1Scene.h"
#include "GUI_Slider.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

j1Audio::j1Audio() : j1Module()
{
	music = NULL;
	name.assign("audio");
}

// Destructor
j1Audio::~j1Audio()
{}

// Called before render is available
bool j1Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;

	//load config var
	volume = 100;
	volume_fx = 100;
	max_volume = 100;
	default_music_fade_time = 2.0;
	volume_change_ratio = 10;
	mute = false;


	if (mute)
	{
		Mix_VolumeMusic(0);
	}
	else
	{
		Mix_VolumeMusic(volume);

	}

	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	return ret;
}

// Called before quitting
bool j1Audio::CleanUp()
{
	if (!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	for (std::list<Mix_Chunk*>::iterator item = fx.begin(); item != fx.end(); ++item) {
		Mix_FreeChunk(*item);
	}
	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool j1Audio::PlayMusic(const char* path)
{
	bool ret = true;

	if (!active)
		return false;

	if (music != NULL)
	{
		if (default_music_fade_time  > 0.0f)
		{
			Mix_FadeOutMusic(int(default_music_fade_time  * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (default_music_fade_time  > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(default_music_fade_time  * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int j1Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if (!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.push_back(chunk);
		ret = fx.size();
	}

	return ret;
}

// Play WAV
bool j1Audio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (!active)
		return false;

	if (id > 0 && id <= fx.size())
	{
		std::list< Mix_Chunk*>::iterator item = next(fx.begin(), id - 1);
		Mix_PlayChannel(-1, (*item), repeat, 0);
	}

	return ret;
}

void j1Audio::StopMusic(int mut)
{
	switch (mut)
	{
	case -1:
		mute = !mute;
		mute_volume = mute;
		mute_fx = mute;
		if (mute == true)
		{
			for (int id = 1; id <= fx.size(); id++)
			{
				std::list< Mix_Chunk*>::iterator item = next(fx.begin(), id - 1);
				Mix_VolumeChunk((*item), 0);
			}
		}
		else
		{
			Mix_VolumeMusic(volume);
			for (int id = 1; id <= fx.size(); id++)
			{
				std::list< Mix_Chunk*>::iterator item = next(fx.begin(), id - 1);
				Mix_VolumeChunk((*item), volume_fx);
			}
		}
		break;
	case -2:
		mute_volume = !mute_volume;
		if (mute_volume == true)
		{
			Mix_VolumeMusic(0);
		}
		else
		{
			Mix_VolumeMusic(volume);
		}
		break;
	case -3:
		mute_fx = !mute_fx;
		if (mute_fx == true)
		{
			for (int id = 1; id <= fx.size(); id++)
			{
				std::list< Mix_Chunk*>::iterator item = next(fx.begin(), id - 1);
				Mix_VolumeChunk((*item), 0);
			}
		}
		else
		{
			for (int id = 1; id <= fx.size(); id++)
			{
				std::list< Mix_Chunk*>::iterator item = next(fx.begin(), id - 1);
				Mix_VolumeChunk((*item), volume_fx);
			}
		}
		break;
	}

}

void j1Audio::VolumeUp(int vol)
{
	if (!mute && ((!mute_volume && vol == -2) || (!mute_fx && vol == -3)))
	{
		switch (vol)
		{
		case -1:
			VolumeUp(-2);
			VolumeUp(-3);
			break;
		case -2:
			if (volume < max_volume) {
				volume += volume_change_ratio;
				Mix_VolumeMusic(volume);
			}
			App->scene->slider_music_volume->SetValue(volume);
			break;
		case -3:
			if (volume_fx < max_volume) {
				volume_fx += volume_change_ratio;
				for (int id = 1; id <= fx.size(); id++)
				{
					std::list< Mix_Chunk*>::iterator item = next(fx.begin(), id - 1);
					Mix_VolumeChunk((*item), volume_fx);
				}
			}
			App->scene->slider_fx_volume->SetValue(volume_fx);
			break;
		default:
			volume = vol - volume_change_ratio;
			volume_fx = vol - volume_change_ratio;
			VolumeUp(-1);
			break;
		}
	}

}

void j1Audio::VolumeDown(int vol)
{
	if (!mute && ((!mute_volume && vol == -2) || (!mute_fx && vol == -3)))
	{
		switch (vol)
		{
		case -1:
			VolumeDown(-2);
			VolumeDown(-3);
			break;
		case -2:
			if (volume > 0) {
				volume -= volume_change_ratio;
				Mix_VolumeMusic(volume);
			}
			App->scene->slider_music_volume->SetValue(volume);
			break;
		case -3:
			if (volume_fx > 0) {
				volume_fx -= volume_change_ratio;
				for (int id = 1; id <= fx.size(); id++)
				{
					std::list< Mix_Chunk*>::iterator item = next(fx.begin(), id - 1);
					Mix_VolumeChunk((*item), volume_fx);
				}
			}
			App->scene->slider_fx_volume->SetValue(volume_fx);
			break;
		default:
			volume = vol + volume_change_ratio;
			volume_fx = vol + volume_change_ratio;
			VolumeDown(-1);
			break;
		}
	}


}

void j1Audio::SliderVolumeFx(int vol)
{
	for (int id = 1; id <= fx.size(); id++)
	{
		std::list< Mix_Chunk*>::iterator item = next(fx.begin(), id - 1);
		Mix_VolumeChunk((*item), vol);
	}
	volume_fx = vol;
}

bool j1Audio::Load(pugi::xml_node & node)
{


	return true;
}

bool j1Audio::Save(pugi::xml_node & node) const
{


	return true;
}
