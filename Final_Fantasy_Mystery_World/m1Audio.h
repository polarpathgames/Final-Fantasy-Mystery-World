#ifndef __m1AUDIO_H__
#define __m1AUDIO_H__

#include "m1Module.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include <map>

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class m1Audio : public m1Module
{
public:

	m1Audio();

	// Destructor
	virtual ~m1Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(Mix_Music* mus, float fade_time); //float fade_time = DEFAULT_MUSIC_FADE_TIME

	// Load a WAV in memory
	Mix_Music* LoadMusic(const char* path);
	Mix_Chunk* LoadFx(const char* path);



	// Play a previously loaded WAV
	bool PlayFx(Mix_Chunk* chunk, int repeat = 0);

	//Control Volume
	void StopMusic(int mut);
	void VolumeUp(int vol);
	void VolumeDown(int vol);


	//Save & Load volume
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:
	uint volume = 0u;
	uint volume_fx = 0u;
	uint max_volume = 0u; 
	uint volume_general = 0u;
	float default_music_fade_time;
	uint volume_change_ratio = 0u;
	bool mute = false;
	bool mute_volume = false;
	bool mute_fx = false;

private:
	
	std::map<Mix_Music*, std::string> music;
	std::map<Mix_Chunk*, std::string>	fx;
};

#endif // __j1AUDIO_H__