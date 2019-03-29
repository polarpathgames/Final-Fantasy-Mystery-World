#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Window.h"
#include "Brofiler/Brofiler.h"



#define MAX_KEYS 300

j1Input::j1Input() : j1Module()
{
	name.assign("input");

	keyboard = new j1KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(j1KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(j1KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
j1Input::~j1Input()
{
	delete[] keyboard;
}

// Called before render is available
bool j1Input::Awake(pugi::xml_node& config)
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//Controller

	LOG("Init controller");

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("GamePad controller could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	int maxJoys = SDL_NumJoysticks();

	for (int i = 0; i < maxJoys; ++i)

	{
		if (i >= MAX_GAMEPADS) break;

		if (SDL_IsGameController(i))
		{
			gamepads[i] = SDL_GameControllerOpen(i);
		}
	}

	return ret;
}

// Called before the first frame
bool j1Input::Start()
{
	SDL_StopTextInput();
	return true;
}

// Called each loop iteration
bool j1Input::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateInput", Profiler::Color::Orange);

	static SDL_Event event;
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for(int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if(mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if(mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}

	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				windowEvents[WE_QUIT] = true;
			break;

			case SDL_WINDOWEVENT:
				switch(event.window.event)
				{
					//case SDL_WINDOWEVENT_LEAVE:
					case SDL_WINDOWEVENT_HIDDEN:
					case SDL_WINDOWEVENT_MINIMIZED:
					case SDL_WINDOWEVENT_FOCUS_LOST:
					windowEvents[WE_HIDE] = true;
					break;

					//case SDL_WINDOWEVENT_ENTER:
					case SDL_WINDOWEVENT_SHOWN:
					case SDL_WINDOWEVENT_FOCUS_GAINED:
					case SDL_WINDOWEVENT_MAXIMIZED:
					case SDL_WINDOWEVENT_RESTORED:
					windowEvents[WE_SHOW] = true;
					break;
				}
			break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[event.button.button - 1] = KEY_DOWN;
				//LOG("Mouse button %d down", event.button.button-1);
			break;

			case SDL_MOUSEBUTTONUP:
				mouse_buttons[event.button.button - 1] = KEY_UP;
				//LOG("Mouse button %d up", event.button.button-1);
			break;

			case SDL_MOUSEMOTION:
				int scale = App->win->GetScale();
				mouse_motion_x = event.motion.xrel / scale;
				mouse_motion_y = event.motion.yrel / scale;
				mouse_x = event.motion.x / scale;
				mouse_y = event.motion.y / scale;
				//LOG("Mouse motion x %d y %d", mouse_motion_x, mouse_motion_y);
			break;
		}
	}

	//Controller inputs : Button

	for (int i = 0; i < MAX_GAMEPADS; ++i)
	{
		if (gamepads[i] != nullptr)
		{
			controller_state[BUTTON_RT] = SDL_GameControllerGetAxis(gamepads[i],SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
			controller_state[BUTTON_D_PAD_UP] = SDL_GameControllerGetButton(gamepads[i], SDL_CONTROLLER_BUTTON_DPAD_UP);
			controller_state[BUTTON_D_PAD_DOWN] = SDL_GameControllerGetButton(gamepads[i], SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			controller_state[BUTTON_D_PAD_LEFT] = SDL_GameControllerGetButton(gamepads[i], SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			controller_state[BUTTON_D_PAD_RIGHT] = SDL_GameControllerGetButton(gamepads[i], SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		}
	}

	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (controller_state[i] == 1) {
			if (controller[i] == KEY_IDLE)
				controller[i] = KEY_DOWN;
			else
				controller[i] = KEY_REPEAT;
		}
		else
		{
			if (controller[i] == KEY_REPEAT || controller[i] == KEY_DOWN)
				controller[i] = KEY_UP;
			else
				controller[i] = KEY_IDLE;
		}
	}

	if (ev.type == SDL_CONTROLLERDEVICEADDED)
	{
		if (ev.cdevice.which > MAX_GAMEPADS - 1)
		{
			LOG("Maximum number of gamepads reached, you cannot connect more...");

		}

		else if (SDL_IsGameController(ev.cdevice.which))
		{
			gamepads[ev.cdevice.which] = SDL_GameControllerOpen(ev.cdevice.which);
			LOG("Controller added: %d", ev.cdevice.which);
		}

	}

	// Controller inputs: Axis
	for (int i = 0; i < MAX_GAMEPADS; ++i)
	{
		if (gamepads[i] != nullptr)
		{
			GamepadDir[i].axisX = SDL_GameControllerGetAxis(gamepads[i], SDL_CONTROLLER_AXIS_LEFTX);
			GamepadDir[i].axisY = SDL_GameControllerGetAxis(gamepads[i], SDL_CONTROLLER_AXIS_LEFTY);
		}
	}


	if (GamepadDir[0].axisX > GamepadDir[0].deadzone)
	{
		keyboard[SDL_SCANCODE_D] = KEY_REPEAT;
	}

	else if (GamepadDir[0].axisX < -GamepadDir[0].deadzone)
	{
		keyboard[SDL_SCANCODE_A] = KEY_REPEAT;
	}


	if (GamepadDir[0].axisY < -GamepadDir[0].deadzone)
	{
		keyboard[SDL_SCANCODE_W] = KEY_REPEAT;
	}

	else if (GamepadDir[0].axisY > GamepadDir[0].deadzone)
	{
		keyboard[SDL_SCANCODE_S] = KEY_REPEAT;
	}
	if (controller[BUTTON_RT] == KEY_REPEAT) {
		keyboard[SDL_SCANCODE_LSHIFT] = KEY_REPEAT;
	}
	if (controller[BUTTON_D_PAD_UP] == KEY_DOWN) {
		keyboard[SDL_SCANCODE_I] = KEY_DOWN;
	}
	if (controller[BUTTON_D_PAD_DOWN] == KEY_DOWN) {
		keyboard[SDL_SCANCODE_K] = KEY_DOWN;
	}
	if (controller[BUTTON_D_PAD_LEFT] == KEY_DOWN) {
		keyboard[SDL_SCANCODE_J] = KEY_DOWN;
	}
	if (controller[BUTTON_D_PAD_RIGHT] == KEY_DOWN) {
		keyboard[SDL_SCANCODE_L] = KEY_DOWN;
	}
	return true;
}

// Called before quitting
bool j1Input::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool j1Input::GetWindowEvent(j1EventWindow ev)
{
	return windowEvents[ev];
}

void j1Input::GetMousePosition(int& x, int& y)
{
	x = mouse_x;
	y = mouse_y;
}

void j1Input::GetMouseMotion(int& x, int& y)
{
	x = mouse_motion_x;
	y = mouse_motion_y;
}