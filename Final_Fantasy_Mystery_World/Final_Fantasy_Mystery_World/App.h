#ifndef __APP_H__
#define __APP_H__


#include "m1Module.h"
#include "p2PerfTimer.h"
#include "p2Timer.h"
#include "PugiXml\src\pugixml.hpp"
#include <list>
#include <string>
#include "p2Random.h"

// Modules
class m1Window;
class m1Input;
class m1Render;
class m1Textures;
class m1Audio;
class m1Map;
class m1Scene;
class m1GUI;
class m1Fonts;
class m1MainMenu;
class m1EntityManager;
class m1PathFinding;
class m1FadeToBlack;
class m1Collision;
class m1EasingSplines;
class m1DialogSystem;
class m1CutScene;
class m1ParticleManager;
class m1MenuManager;

struct GlobalGameAdvances
{
	bool CutSceneTutorialGirlEscapingPlayed = false;
	bool CutSceneFinalRoomTutorialPlayed = false;
	bool CutSceneMiddleRoomTutorialPlayed = false;
	bool CutSceneAfterBossTutorialPlayed = false;
	bool CutSceneLobbyExplain = false;
	bool CutSceneLobbyQuest2Finish = false;
	bool CutSceneLobbyCredits = false;
	bool Tutorial_first_time = true;
	bool ability1_gained = false;
	bool ability2_gained = false;
	bool ability3_gained = false;
	bool helmet_bought = false;
	bool ring_bought = false;
	bool shop_gone = false;
	bool CutSceneHomeToSleepQuest2 = false;
	bool drake_killed = false;
	bool quest2_rocks_cave_destroyed = false;
	bool CutSceneQueenQuest2 = false;
	bool CutSceneFinalRoomQuest2 = false;
	bool treasure_quest2_opened = false;
	bool ice_queen_killed = false;
	bool treasure_boss_opened = false;
	bool treasure_quest3_opened = false;
	bool CutSceneHomeToSleeQuest3 = false;
	bool sleep2 = false;
	bool CutsceneFinalGame = false;
	bool CutsceneFinalFinalGame = false;
	std::string player_name;

	void Reset() {
		ice_queen_killed = false;
		sleep2 = false;
		CutSceneHomeToSleepQuest2 = false;
		CutSceneLobbyQuest2Finish = false;
		treasure_quest2_opened = false;
		treasure_boss_opened = false;
		treasure_quest3_opened = false;
		CutSceneTutorialGirlEscapingPlayed = false;
		CutSceneFinalRoomTutorialPlayed = false;
		CutSceneMiddleRoomTutorialPlayed = false;
		CutSceneAfterBossTutorialPlayed = false;
		CutSceneLobbyExplain = false;
		CutSceneHomeToSleeQuest3 = false;
		Tutorial_first_time = true;
		ability1_gained = false;
		ability2_gained = false;
		ability3_gained = false;
		helmet_bought = false;
		ring_bought = false;
		drake_killed = false;
		shop_gone = false;
		quest2_rocks_cave_destroyed = false;
		CutSceneQueenQuest2 = false;
		CutSceneFinalRoomQuest2 = false;
		CutsceneFinalGame = false;
		CutsceneFinalFinalGame = false;
		CutSceneLobbyCredits = false;
	}

};

class Application
{
public:

	// Constructor
	Application(int argc, char* args[]);

	// Destructor
	virtual ~Application();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a DBG_NEW module to handle
	void AddModule(m1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	const char* GetVersion() const;

	void LoadGame(const char* file);
	void SaveGame(const char* file) const;

	inline bool LookForFileExistence(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

	//Exit
	void QuitGame();

	bool GetPause();
	bool ChangePause();

	uint32 GetFps();
	float GetDeltaTime();

	bool GetInventory();
	bool ChangeInventory();

	pugi::xml_node LoadConfig(pugi::xml_document&, std::string name) const;

	bool capactivated = true;
	bool fast_start = false;
	bool debug = false;

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

	//GetDt
	float GetDt();



public:

	// Modules
	m1Window *			win = nullptr;
	m1Input*			input = nullptr;
	m1Render*			render = nullptr;
	m1Textures*			tex = nullptr;
	m1Audio*			audio = nullptr;
	m1Map*				map = nullptr;
	m1Scene*			scene = nullptr;
	m1Fonts*            fonts = nullptr;
	m1GUI*				gui = nullptr;
	m1MainMenu*          main_menu = nullptr;
	m1EntityManager*	entity_manager = nullptr;
	m1PathFinding*		pathfinding = nullptr;
	m1FadeToBlack*		fade_to_black = nullptr;
	m1Collision*		collision = nullptr;
	m1EasingSplines*	easing_splines = nullptr;
	m1DialogSystem*     dialog = nullptr;
	m1CutScene*			cutscene_manager = nullptr;
	m1ParticleManager*	particles = nullptr;
	m1MenuManager*		menu_manager = nullptr;
	GlobalGameAdvances  globals;
	Random random;

private:

	std::list<m1Module*>	modules;
	int						argc;
	char**					args = nullptr;

	std::string				title;
	std::string				organization;
	std::string				version;

	mutable bool			want_to_save = false;
	bool					want_to_load = false;
	std::string				load_game;
	mutable std::string		save_game;

	bool					quit_game = false;
	bool					is_paused = false;
	bool                    is_inventory = false;
	pugi::xml_document		config_file;
	pugi::xml_node			config;
	std::string				config_name;

	p2PerfTimer				ptimer;
	uint64					frame_count = 0;
	p2Timer					startup_time;
	p2Timer					frame_time;
	p2Timer					last_sec_frame_time;
	uint32					last_sec_frame_count = 0;
	uint32					prev_last_sec_frame_count = 0;
	uint16_t				framerate_cap;
	float					avg_fps = 0.0f;
	uint32					frames_on_last_update = 0u;
	float					dt;
};

extern Application* App;

#endif