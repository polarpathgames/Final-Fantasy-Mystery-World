#include "p2Defs.h"
#include "p2Log.h"
#include "m1Audio.h"
#include <map>
#include <string>
#include "m1Input.h"
#include "App.h"
#include "m1Scene.h"
#include "u1Slider.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

m1Audio::m1Audio() : m1Module()
{
	name.assign("audio");
}

// Destructor
m1Audio::~m1Audio()
{}

// Called before render is available
bool m1Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;

	//load config var
	// THIS IN CONFIG.XML
	volume = 30;
	volume_fx = 100;
	max_volume = 100;
	default_music_fade_time = 0.5F;
	volume_change_ratio = 10;
	mute = false;
	volume_general = 100;

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


	Mix_VolumeMusic(volume);

	return ret;
}

// Called before quitting
bool m1Audio::CleanUp()
{
	
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	std::map < Mix_Music*,std::string>::iterator m = music.begin();
	for (; m != music.end(); ++m) {
		if ((*m).first != nullptr) {
			Mix_FreeMusic((*m).first);
		}
	}
	music.clear();

	std::map<Mix_Chunk*,std::string>::iterator f = fx.begin();
	for (; f != fx.end(); ++f) {
		if ((*f).first != nullptr) {
			Mix_FreeChunk((*f).first);
		}
	}
	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool m1Audio::PlayMusic(Mix_Music* mus, float fade_time)
{
	bool ret = true;

	if (mus == nullptr)
	{
		LOG("Cannot load music. Mix_GetError():\n", Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time  > 0.0f)
		{
			if (Mix_FadeInMusic(mus, -1, (int)(fade_time  * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music. Mix_GetError()", Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(mus, -1) < 0)
			{
				LOG("Cannot play in music. Mix_GetError()", Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing");
	return ret;
}
Mix_Music * m1Audio::LoadMusic(const char * path)
{

	std::map<Mix_Music*, std::string>::iterator item = music.begin();
	for (; item != music.end(); ++item) {
		if ((*item).first != nullptr && (*item).second == path) {
			return (*item).first;
		}
	}

	Mix_Music* mus = nullptr;

	mus = Mix_LoadMUS(path);

	if (mus == nullptr) {
		LOG("Cannot load music %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else {
		music.insert(std::pair<Mix_Music*, std::string>(mus, path));
	}
	return mus;
}
// Load WAV
Mix_Chunk* m1Audio::LoadFx(const char* path)
{

	std::map<Mix_Chunk*, std::string>::iterator item = fx.begin();
	for (; item != fx.end(); ++item) {
		if ((*item).first != nullptr && (*item).second == path) {
			return (*item).first;
		}
	}

	Mix_Chunk* chunk = nullptr;

	chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.insert(std::pair<Mix_Chunk*, std::string>(chunk, path));
	}
	return chunk;
}



// Play WAV
bool m1Audio::PlayFx(Mix_Chunk* chunk, int repeat)
{
	bool ret = false;
	
	std::map<Mix_Chunk*,std::string>::iterator item = fx.begin();
	for (; item != fx.end(); ++item) {
		if ((*item).first != nullptr && (*item).first == chunk) {
			Mix_PlayChannel(-1, (*item).first, repeat, 0);
			break;
		}
	}

	return ret;
}

void m1Audio::StopMusic(int mut)
{
	switch (mut)
	{
	case -1:
		mute = !mute;
		mute_volume = mute;
		mute_fx = mute;
		if (mute == true)
		{
			Mix_Volume(-1, 0);
		}
		else
		{
			Mix_VolumeMusic(volume);
			for (int id = 1; id <= fx.size(); id++)
			{
				std::map<Mix_Chunk*,std::string>::iterator item = fx.begin();
				for (; item != fx.end(); ++item) {
					if ((*item).first != nullptr) {
						Mix_VolumeChunk((*item).first, volume_fx);
					}
				}
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
			Mix_Volume(-1, 0);
		}
		else
		{
			std::map<Mix_Chunk*,std::string>::iterator item = fx.begin();
			for (; item != fx.end(); ++item) {
				if ((*item).first != nullptr) {
					Mix_VolumeChunk((*item).first, volume_fx);
				}
			}
		}
		break;
	}

}

void m1Audio::VolumeUp(int vol)
{
	if (!mute && ((!mute_volume && vol == -2) || (!mute_fx && vol == -3) || (!mute_fx && vol == -1)))
	{
		switch (vol)
		{
		case -1:
			VolumeUp(-2);
			VolumeUp(-3);
			if(volume_general < max_volume)
				volume_general += volume_change_ratio;
			break;
		case -2:
			if (volume < max_volume) {
				volume += volume_change_ratio;
				Mix_VolumeMusic(volume);
			}
			break;
		case -3:
			if (volume_fx < max_volume) {
				volume_fx += volume_change_ratio;
				std::map<Mix_Chunk*,std::string>::iterator item = fx.begin();
				for (; item != fx.end(); ++item) {
					if ((*item).first != nullptr) {
						Mix_VolumeChunk((*item).first, volume_fx);
					}
				}
			}
			break;
		default:
			volume = vol - volume_change_ratio;
			volume_fx = vol - volume_change_ratio;
			volume_general = vol - volume_change_ratio;
			VolumeUp(-1);
			break;
		}
	}

}

void m1Audio::VolumeDown(int vol)
{
	if (!mute && ((!mute_volume && vol == -2) || (!mute_fx && vol == -3) || (!mute_fx && vol == -1)))
	{
		switch (vol)
		{
		case -1:
			VolumeDown(-2);
			VolumeDown(-3);
			if(volume_general>0)
				volume_general -= volume_change_ratio;
			break;
		case -2:
			if (volume > 0) {
				volume -= volume_change_ratio;
				Mix_Volume(-1, 0);
			}
			break;
		case -3:
			if (volume_fx > 0) {
				volume_fx -= volume_change_ratio;
				Mix_Volume(-1, volume_fx);
			}
			break;
		default:
			volume = vol + volume_change_ratio;
			volume_fx = vol + volume_change_ratio;
			volume_general = vol + volume_change_ratio;
			VolumeDown(-1);
			break;
		}
	}


}

bool m1Audio::Load(pugi::xml_node & node)
{


	return true;
}

bool m1Audio::Save(pugi::xml_node & node) const
{


	return true;
}