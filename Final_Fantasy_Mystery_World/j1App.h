#ifndef __APP_H__
#define __APP_H__


#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"
#include <list>
#include <string>

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Map;
class j1Scene;
class j1UIManager;
class j1Fonts;
class MainMenu;
class j1EntityManager;
class j1PathFinding;
class j1FadeToBlack;
class j1Collision;
class EasingSplines;
class j1DialogSystem;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGame(const char* file);
	void SaveGame(const char* file) const;

	//Exit
	void QuitGame();

	bool GetPause();
	bool ChangePause();
	pugi::xml_node LoadConfig(pugi::xml_document&, std::string name) const;

	bool capactivated = true;

private:

	// Load config file


	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;


public:

	// Modules
	j1Window * win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1Map*				map;
	j1Scene*			scene;
	j1Fonts*            fonts;
	j1UIManager*        ui_manager;
	MainMenu*           main_menu;
	j1EntityManager*		entity_manager;
	j1PathFinding*		pathfinding;
	j1FadeToBlack*		fade_to_black;
	j1Collision*		collision;
	EasingSplines*		easing_splines;
	j1DialogSystem*     dialog;
private:

	std::list<j1Module*>	modules;
	int					argc;
	char**				args = nullptr;

	std::string			title;
	std::string			organization;

	mutable bool		want_to_save = false;
	bool				want_to_load = false;
	std::string			load_game;
	mutable std::string	save_game;

	bool				quit_game = false;
	bool				is_paused = false;
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	std::string			config_name;

	j1PerfTimer			ptimer;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	uint16_t			framerate_cap;
	float				dt;
};

extern j1App* App;



#endif
