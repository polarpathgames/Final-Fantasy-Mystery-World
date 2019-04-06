#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include "j1Module.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include <list>

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class j1Audio : public j1Module
{
public:

	j1Audio();

	// Destructor
	virtual ~j1Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path); //float fade_time = DEFAULT_MUSIC_FADE_TIME

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	//Control Volume
	void StopMusic(int mut);
	void VolumeUp(int vol);
	void VolumeDown(int vol);
	void SliderVolumeFx(int vol);

	//Save & Load volume
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:
	uint volume = 0u;
	uint volume_fx = 0u;
	uint max_volume = 0u;
	float default_music_fade_time;
	uint volume_change_ratio = 0u;
	bool mute = false;
	bool mute_volume = false;
	bool mute_fx = false;

private:
	
	_Mix_Music*			music = nullptr;
	std::list<Mix_Chunk*>	fx;
};

#endif // __j1AUDIO_H__