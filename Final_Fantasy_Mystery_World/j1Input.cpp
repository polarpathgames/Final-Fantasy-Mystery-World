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
	memset(controller_buttons, KEY_IDLE, sizeof(j1KeyState) * NUM_CONTROLLER_BUTTONS);
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

	Controller = SDL_GameControllerOpen(0);


	return ret;
}

// Called before the first frame
bool j1Input::Start()
{
	SDL_StopTextInput();

DefaultControls();


	mouse_motion_x = 0;
	mouse_motion_y = 0;
	mouse_x= 0;
	mouse_y = 0;


	return true;
}

void j1Input::DefaultControls()
{
	keyboard_buttons.buttons_code.BASIC_ATTACK = SDL_SCANCODE_G;
	keyboard_buttons.buttons_code.DIAGONALS = SDL_SCANCODE_LSHIFT;
	keyboard_buttons.buttons_code.DIRECCTION_DOWN = SDL_SCANCODE_K;
	keyboard_buttons.buttons_code.DIRECCTION_RIGHT = SDL_SCANCODE_L;
	keyboard_buttons.buttons_code.DIRECTION_LEFT = SDL_SCANCODE_J;
	keyboard_buttons.buttons_code.DIRECTION_UP = SDL_SCANCODE_I;
	keyboard_buttons.buttons_code.DOWN = SDL_SCANCODE_S;
	keyboard_buttons.buttons_code.LEFT = SDL_SCANCODE_A;
	keyboard_buttons.buttons_code.RIGHT = SDL_SCANCODE_D;
	keyboard_buttons.buttons_code.UP = SDL_SCANCODE_W;

	keyboard_buttons.buttons_char.BASIC_ATTACK = "G";
	keyboard_buttons.buttons_char.DIAGONALS = "LSHIFT";
	keyboard_buttons.buttons_char.DIRECCTION_DOWN = "K";
	keyboard_buttons.buttons_char.DIRECCTION_RIGHT = "L";
	keyboard_buttons.buttons_char.DIRECTION_LEFT = "J";
	keyboard_buttons.buttons_char.DIRECTION_UP = "I";
	keyboard_buttons.buttons_char.DOWN = "S";
	keyboard_buttons.buttons_char.LEFT = "A";
	keyboard_buttons.buttons_char.RIGHT = "D";
	keyboard_buttons.buttons_char.UP = "W";

	controller_Buttons.buttons_code.BASIC_ATTACK = SDL_CONTROLLER_BUTTON_A;
	controller_Buttons.buttons_code.DIAGONALS = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
	controller_Buttons.buttons_code.DIRECCTION_DOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
	controller_Buttons.buttons_code.DIRECTION_UP = SDL_CONTROLLER_BUTTON_DPAD_UP;
	controller_Buttons.buttons_code.DIRECTION_LEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
	controller_Buttons.buttons_code.DIRECCTION_RIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;

	controller_Buttons.buttons_char.BASIC_ATTACK = "A";
	controller_Buttons.buttons_char.DIAGONALS = "LT";
	controller_Buttons.buttons_char.DIRECCTION_DOWN = "D-PAD DOWN";
	controller_Buttons.buttons_char.DIRECTION_UP = "D-PAD UP";
	controller_Buttons.buttons_char.DIRECTION_LEFT = "D-PAD LEFT";
	controller_Buttons.buttons_char.DIRECCTION_RIGHT = "D-PAD RIGHT";
	controller_Buttons.buttons_char.DOWN = "L-JOSTICK";
	controller_Buttons.buttons_char.LEFT = "L-JOSTICK";
	controller_Buttons.buttons_char.RIGHT = "L-JOSTICK";
	controller_Buttons.buttons_char.UP = "L-JOSTICK";
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

	for (int i = 0; i < NUM_CONTROLLER_BUTTONS; ++i)
	{
		if (controller_buttons[i] == KEY_DOWN)
			controller_buttons[i] = KEY_REPEAT;

		if (controller_buttons[i] == KEY_UP)
			controller_buttons[i] = KEY_IDLE;
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
			case SDL_CONTROLLERBUTTONDOWN:
				if (event.cbutton.which == 0) {
					controller_buttons[event.cbutton.button] = KEY_DOWN;
				}
				break;

			case SDL_CONTROLLERBUTTONUP:
				if (event.cbutton.which == 0)
					controller_buttons[event.cbutton.button] = KEY_UP;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[event.button.button - 1] = KEY_DOWN;
				//LOG("Mouse button %d down", event.button.button-1);
			break;
			case SDL_CONTROLLERAXISMOTION:
				if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT && event.caxis.value > DEAD_ZONE) {
					controller_buttons[event.cbutton.button] = KEY_DOWN;
				}
				if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT && event.caxis.value < DEAD_ZONE) {
					controller_buttons[event.cbutton.button] = KEY_UP;
				}
				if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT && event.caxis.value > DEAD_ZONE) {
					controller_buttons[event.cbutton.button] = KEY_DOWN;
				}
				if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT && event.caxis.value < DEAD_ZONE) {
					controller_buttons[event.cbutton.button] = KEY_UP;
				}
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

	//axis
	if (Controller != nullptr) {
		axis_x = SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_LEFTX);
		axis_y = SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_LEFTY);
		LOG("X: %i Y: %i", axis_x, axis_y);
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

bool j1Input::ChceckAxisStates(const Axis &axis) {

	bool ret = false;
	if (Controller != nullptr) {
		switch (axis) {
		case Axis::AXIS_UP_RIGHT:
			if (axis_x > DEAD_ZONE && axis_y < -DEAD_ZONE)
				ret = true;
			break;
		case Axis::AXIS_DOWN_RIGHT:
			if (axis_x > DEAD_ZONE && axis_y > DEAD_ZONE)
				ret = true;
			break;
		case Axis::AXIS_DOWN_LEFT:
			if (axis_x < -DEAD_ZONE && axis_y > DEAD_ZONE)
				ret = true;
			break;
		case Axis::AXIS_UP_LEFT:
			if (axis_x < -DEAD_ZONE && axis_y < -DEAD_ZONE)
				ret = true;
			break;
		case Axis::AXIS_RIGHT:
			if (axis_x > DEAD_ZONE && axis_y > -DEAD_ZONE && axis_y < DEAD_ZONE)
				ret = true;
			break;
		case Axis::AXIS_LEFT:
			if (axis_x < -DEAD_ZONE && axis_y > -DEAD_ZONE && axis_y < DEAD_ZONE)
				ret = true;
			break;
		case Axis::AXIS_UP:
			if (axis_x > -DEAD_ZONE && axis_x < DEAD_ZONE && axis_y < -DEAD_ZONE)
				ret = true;
			break;
		case Axis::AXIS_DOWN:
			if (axis_x > -DEAD_ZONE && axis_x < DEAD_ZONE && axis_y > DEAD_ZONE)
				ret = true;
			break;
		default:
			LOG("No axis found");
			break;
		}
	}
	

	return ret;
}