#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "m1Module.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "e1Entity.h"
#include "p2Timer.h"

class m1MainMenu : public m1Module
{
public:
	m1MainMenu();
	~m1MainMenu();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool Update(float dt);
	bool CleanUp();

	bool Interact(u1GUI* interaction);

public:
	Mix_Chunk* fx_push_button = nullptr;
	Mix_Chunk* fx_push_button_return = nullptr;

	Mix_Music* mus_main_menu = nullptr;
	Mix_Music* mus_congrats = nullptr;
	Mix_Music* mus_credits = nullptr;
	Mix_Music* mus_selection = nullptr;

	e1Entity::EntityType entity_type;

	std::string video_path;
	bool intro_played = false;
	p2Timer video_start;
};
#endif