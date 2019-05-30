#include "App.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "m1Window.h"
#include "m1Input.h"
#include "m1Cutscene.h"
#include "m1Render.h"
#include "m1Textures.h"
#include "m1Audio.h"
#include "m1Scene.h"
#include "m1VideoPlayer.h"
#include "m1GUI.h"
#include "m1Map.h"
#include "m1Collisions.h"
#include "m1Fonts.h"
#include "m1MainMenu.h"
#include "m1EasingSplines.h"
#include "m1EntityManager.h"
#include "m1FadeToBlack.h"
#include "m1Pathfinding.h"
#include "m1DialogSystem.h"
#include "m1ParticleManager.h"
#include "m1MenuManager.h"
#include "Brofiler/Brofiler.h"

// Constructor
Application::Application(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(ptimer);

	input = DBG_NEW m1Input();
	win = DBG_NEW m1Window();
	render = DBG_NEW m1Render();
	tex = DBG_NEW m1Textures();
	audio = DBG_NEW m1Audio();
	map = DBG_NEW m1Map();
	scene = DBG_NEW m1Scene();
	gui = DBG_NEW m1GUI();
	main_menu = DBG_NEW m1MainMenu();
	fonts = DBG_NEW m1Fonts();
	dialog = DBG_NEW m1DialogSystem();
	entity_manager = DBG_NEW m1EntityManager();
	pathfinding = DBG_NEW m1PathFinding();
	fade_to_black = DBG_NEW m1FadeToBlack();
	collision = DBG_NEW m1Collision();
	easing_splines = DBG_NEW m1EasingSplines();
	cutscene_manager = DBG_NEW m1CutScene();
	particles = DBG_NEW m1ParticleManager();
	menu_manager = DBG_NEW m1MenuManager();
	video_player = DBG_NEW m1VideoPlayer();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map);
	AddModule(pathfinding);
	AddModule(scene);
	AddModule(main_menu);
	AddModule(fonts);
	AddModule(collision);
	AddModule(particles);
	
	AddModule(entity_manager);
	AddModule(gui);
	AddModule(dialog);
	AddModule(fade_to_black);
	AddModule(easing_splines);
	AddModule(cutscene_manager);
	AddModule(menu_manager);
	AddModule(video_player);

	// render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
Application::~Application()
{
	// release modules

	for (std::list<m1Module*>::reverse_iterator item = modules.rbegin(); item != modules.rend(); ++item) {
		RELEASE(*item);

	}
	modules.clear();
}

void Application::AddModule(m1Module* module)
{
	module->Init();
	modules.push_back(module);
}

// Called before render is available
bool Application::Awake()
{
	PERF_START(ptimer);


	pugi::xml_node		app_config;

	bool ret = false;
	config_name.assign("assets/xml/config.xml");
	config = LoadConfig(config_file, config_name.data());

	if (config.empty() == false)
	{
		// self-config
		ret = true;
		app_config = config.child("app");
		title.assign(app_config.child("title").child_value());
		organization.assign(app_config.child("organization").child_value());
		version.assign(app_config.child("version").child_value());

		int cap = app_config.attribute("framerate_cap").as_int();
		if (cap > 0)
		{
			framerate_cap = 1000 / cap;
		}

		fast_start = app_config.child("fast_start").attribute("value").as_bool();
		if (fast_start == true) {
			main_menu->active = false;
			map->active = false;
		}
		else {
			scene->active = false;
			map->active = false;
			entity_manager->active = false;
			main_menu->active = false;
		}
	}

	if (ret == true)
	{
		std::list<m1Module*>::iterator item = modules.begin();

		while (item != modules.end() && ret)
		{
			ret = (*item)->Awake(config.child((*item)->name.data()));

			item++;
		}
	}

	config_file.reset();

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool Application::Start()
{
	PERF_START(ptimer);
	bool ret = true;

	std::list<m1Module*>::iterator item = modules.begin();

	while (item != modules.end() && ret == true)
	{
		if ((*item)->active)
			ret = (*item)->Start();
		++item;
	}
	startup_time.Start();

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool Application::Update()
{
	BROFILER_CATEGORY("Update", Profiler::Color::Aqua);

	bool ret = true;
	PrepareUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true || quit_game)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node Application::LoadConfig(pugi::xml_document& config_file, std::string name) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = config_file.load_file(name.data());

	if (result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");
	
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	BROFILER_CATEGORY("PrepareUpdate", Profiler::Color::Blue);

	frame_count++;
	last_sec_frame_count++;
	if (!is_paused)
		dt = frame_time.ReadSec();

	else
		dt = 0.0f;

	frame_time.Start();
	ptimer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	BROFILER_CATEGORY("FinishUpdate", Profiler::Color::Lime);

	if (want_to_save == true)
		SavegameNow();

	if (want_to_load == true)
		LoadGameNow();

	// Framerate calculations --

	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	avg_fps = float(frame_count) / startup_time.ReadSec();
	uint32 last_frame_ms = frame_time.Read();
	frames_on_last_update = prev_last_sec_frame_count;

	BROFILER_CATEGORY("Waiting", Profiler::Color::Red);

	if (framerate_cap > 0 && last_frame_ms < framerate_cap && capactivated)
	{
		SDL_Delay(framerate_cap - last_frame_ms);
	}
}

// Call modules before each loop iteration
bool Application::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate", Profiler::Color::Orange);

	bool ret = true;

	m1Module* pModule = NULL;

	for (std::list<m1Module*>::iterator item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pModule = *item;

		if (pModule->active == false) {
			continue;
		}

		ret = (*item)->PreUpdate();

		if (ret == false) {
			LOG("Module %s failed PreUpdate", (*item)->name.data());
		}
	}


	return ret;
}

// Call modules on each loop iteration
bool Application::DoUpdate()
{
	BROFILER_CATEGORY("DoUpdate", Profiler::Color::Yellow);

	bool ret = true;

	m1Module* pModule = NULL;

	for (std::list<m1Module*>::iterator item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pModule = (*item);

		if (pModule->active == false) {
			continue;
		}
		
		ret = (*item)->Update(dt);

		if (ret == false) {
			LOG("Module %s failed Update", (*item)->name.data());
		}
	}

	return ret;
}

// Call modules after each loop iteration
bool Application::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate", Profiler::Color::Purple);

	bool ret = true;

	m1Module* pModule = NULL;

	for (std::list<m1Module*>::iterator item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pModule = (*item);

		if (pModule->active == false) {
			continue;
		}

		ret = (*item)->PostUpdate();

		if (ret == false) {
			LOG("Module %s failed PostUpdate", (*item)->name.data());
		}
	}

	return ret;
}

// Called before quitting
bool Application::CleanUp()
{
	BROFILER_CATEGORY("CleanUp", Profiler::Color::Salmon);

	PERF_START(ptimer);
	bool ret = true;


	std::list<m1Module*>::reverse_iterator item = modules.rbegin();

	while (item != modules.rend() && ret == true)
	{
		if (*item != NULL) {
			ret = (*item)->CleanUp();

			if (ret == false) {
				LOG("Module %s failed ClenUp", (*item)->name.data());
			}
		}
		++item;
	}

	config_file.reset();

	PERF_PEEK(ptimer);
	return ret;

}

// ---------------------------------------
int Application::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* Application::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* Application::GetTitle() const
{
	return title.data();
}

// ---------------------------------------
const char* Application::GetOrganization() const
{

	return organization.data();
}

const char * Application::GetVersion() const
{
	return version.data();
}

// Load / Save
void Application::LoadGame(const char* file)
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list
	want_to_load = true;
	load_game.assign(file);
}

// ---------------------------------------
void Application::SaveGame(const char* file) const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	want_to_save = true;
	save_game.assign(file);
}

// ---------------------------------------


bool Application::LoadGameNow()
{
	bool ret = false;
	pugi::xml_document data;
	pugi::xml_node root;

	pugi::xml_parse_result result = data.load_file(load_game.data());
	if (result != NULL)
	{
		ret = true;

		LOG("Loading DBG_NEW Game State from %s...", load_game.data());

		root = data.child("game_state");

		std::list<m1Module*>::iterator item = modules.begin();


		while (item != modules.end() && ret == true)
		{
			ret = (*item)->Load(root.child((*item)->name.data()));
			++item;
		}

		data.reset();
		if (ret == true)
			LOG("...finished loading");
		else
			LOG("...loading process interrupted with error on module %s", (*item != NULL) ? (*item)->name.data() : "unknown");


	}
	else
		LOG("Could not parse game state xml file %s. pugi error: %s", load_game.data(), result.description());



	want_to_load = false;
	return ret;
}

bool Application::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", save_game.data());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;

	root = data.append_child("game_state");

	std::list<m1Module*>::const_iterator item = modules.begin();

	while (item != modules.end() && ret)
	{
		ret = (*item)->Save(root.append_child((*item)->name.data()));
		item++;
	}

	if (ret == true)
	{
		data.save_file(save_game.data());
		LOG("... finished saving", );
	}
	else
		LOG("Save process halted from an error in module %s", (*item != NULL) ? (*item)->name.data() : "unknown");

	data.reset();
	want_to_save = false;
	return ret;
}

void Application::QuitGame()
{
	quit_game = true;
}

bool Application::GetPause()
{
	return is_paused;
}

bool Application::ChangePause()
{
	return is_paused = !is_paused;
}

uint32 Application::GetFps()
{
	return frames_on_last_update;
}

float Application::GetDeltaTime()
{
	return dt;
}

bool Application::GetInventory()
{
	return is_inventory;
}

bool Application::ChangeInventory()
{
	return is_inventory = !is_inventory;
}