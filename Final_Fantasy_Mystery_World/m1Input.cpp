#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "m1Input.h"
#include "m1Window.h"
#include "SDL/include/SDL.h"
#include "Brofiler/Brofiler.h"
#include "m1Textures.h"


#define MAX_KEYS 300

m1Input::m1Input() : m1Module()
{
	name.assign("input");

	keyboard = DBG_NEW j1KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(j1KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(j1KeyState) * NUM_MOUSE_BUTTONS);
	memset(controller_buttons, KEY_IDLE, sizeof(j1KeyState) * NUM_CONTROLLER_BUTTONS);
}

// Destructor
m1Input::~m1Input()
{
	delete[] keyboard;
}

// Called before render is available
bool m1Input::Awake(pugi::xml_node& config)
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
	if (SDL_InitSubSystem(SDL_INIT_HAPTIC) < 0)
	{
		LOG("SDL_GAMECONTROLLER HAPTIC could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	Controller = SDL_GameControllerOpen(0);


	return ret;
}

// Called before the first frame
bool m1Input::Start()
{
	SDL_StopTextInput();

	DefaultControls();


	mouse_motion_x = 0;
	mouse_motion_y = 0;
	mouse_x= 0;
	mouse_y = 0;
	last_mouse_x = 0;
	last_mouse_y = 0;


	return true;
}

void m1Input::DefaultControls()
{
	keyboard_buttons.buttons_code.BASIC_ATTACK = SDL_SCANCODE_SPACE;
	keyboard_buttons.buttons_code.DIAGONALS = SDL_SCANCODE_LSHIFT;
	keyboard_buttons.buttons_code.DIRECCTION_DOWN = SDL_SCANCODE_DOWN;
	keyboard_buttons.buttons_code.DIRECCTION_RIGHT = SDL_SCANCODE_RIGHT;
	keyboard_buttons.buttons_code.DIRECTION_LEFT = SDL_SCANCODE_LEFT;
	keyboard_buttons.buttons_code.DIRECTION_UP = SDL_SCANCODE_UP;
	keyboard_buttons.buttons_code.DOWN = SDL_SCANCODE_S;
	keyboard_buttons.buttons_code.LEFT = SDL_SCANCODE_A;
	keyboard_buttons.buttons_code.RIGHT = SDL_SCANCODE_D;
	keyboard_buttons.buttons_code.UP = SDL_SCANCODE_W;
	keyboard_buttons.buttons_code.HABILTY1 = SDL_SCANCODE_1;
	keyboard_buttons.buttons_code.HABILITY2 = SDL_SCANCODE_2;
	keyboard_buttons.buttons_code.SHOW_SKILLS = SDL_SCANCODE_V;
	keyboard_buttons.buttons_code.INVENTORY = SDL_SCANCODE_E;

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
	keyboard_buttons.buttons_char.ABILITY1 = "F";
	keyboard_buttons.buttons_char.SHOW_SKILLS = "V";
	keyboard_buttons.buttons_char.INVENTORY = "E";

	controller_Buttons.buttons_code.BASIC_ATTACK = SDL_CONTROLLER_BUTTON_A;
	controller_Buttons.buttons_code.DIAGONALS = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
	controller_Buttons.buttons_code.DIRECCTION_DOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
	controller_Buttons.buttons_code.DIRECTION_UP = SDL_CONTROLLER_BUTTON_DPAD_UP;
	controller_Buttons.buttons_code.DIRECTION_LEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
	controller_Buttons.buttons_code.DIRECCTION_RIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
	controller_Buttons.buttons_code.HABILTY1 = SDL_CONTROLLER_BUTTON_X;
	controller_Buttons.buttons_code.HABILITY2 = SDL_CONTROLLER_BUTTON_B;
	controller_Buttons.buttons_code.SHOW_SKILLS = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
	controller_Buttons.buttons_code.INVENTORY = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;

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
	controller_Buttons.buttons_char.ABILITY1 = "B";
	controller_Buttons.buttons_char.SHOW_SKILLS = "LB";
	controller_Buttons.buttons_char.INVENTORY = "RB";
}

// Called each loop iteration
bool m1Input::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateInput", Profiler::Color::Orange);

	static SDL_Event event;
	
	UpdateKeyboard();

	UpdateMouse();

	UpdateController();

	UpdateEvents(event);
	
	return true;
}

void m1Input::UpdateEvents(SDL_Event &event)
{
	BROFILER_CATEGORY("Events", Profiler::Color::Orange);

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			windowEvents[WE_QUIT] = true;
			break;
		case SDL_TEXTINPUT:
			text_input = (std::string)event.text.text;
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
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
		case SDL_JOYDEVICEADDED:
			if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
			{
				LOG("GamePad controller could not initialize! SDL_Error: %s\n", SDL_GetError());
			}
			if (SDL_HapticRumblePlay(haptic, 0.3f, 1000) < 0)
			{
				LOG("rumble play error");
			}
			Controller = SDL_GameControllerOpen(0);

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
		{
			int scale = App->win->GetScale();

			mouse_motion_x = event.motion.xrel / scale;
			mouse_motion_y = event.motion.yrel / scale;

			//LOG("Mouse motion x %d y %d", mouse_motion_x, mouse_motion_y);
		}
		break;

		case SDL_CONTROLLERDEVICEADDED:
		{
			//Open the first available controller
			for (int i = 0; i < SDL_NumJoysticks(); ++i) {
				if (SDL_IsGameController(i)) {
					Controller = SDL_GameControllerOpen(i);
					if (Controller) {

						if (SDL_JoystickIsHaptic(SDL_GameControllerGetJoystick(Controller)) > 0)
						{
							haptic = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(Controller));

							if (haptic != nullptr)
							{
								LOG("HAPTIC SUCCESS");
								//Get initialize rumble 
								if (SDL_HapticRumbleInit(haptic) < 0) // initialize simple rumble
								{
									LOG("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
								}

								/*if (SDL_HapticRumblePlay(haptic, 0.3f, 1000) < 0)
								{
									LOG("rumble play error");
								}*/
							}
						}
						else
						{
							LOG("haptic error! SDL_Error: %s\n", SDL_GetError());
							LOG("haptic error! SDL_Error: %i\n", SDL_JoystickIsHaptic(SDL_GameControllerGetJoystick(Controller)));
						}
					}
					else {
						LOG("gamepad awake assign failed");
					}
				}
			}
			break;
		}

		case SDL_CONTROLLERDEVICEREMOVED:
			LOG("disconnected gamepad");
			if (Controller != nullptr)
			{
				SDL_HapticClose(haptic);
				haptic = nullptr;
				SDL_GameControllerClose(Controller);
				Controller = nullptr;
				break;
			}
		}

	}

}

void m1Input::UpdateController()
{
	BROFILER_CATEGORY("UpdateControllers", Profiler::Color::Orange);

	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		if (controller_buttons[i] == KEY_DOWN)
			controller_buttons[i] = KEY_REPEAT;

		if (controller_buttons[i] == KEY_UP)
			controller_buttons[i] = KEY_IDLE;
	}

	//axis
	if (Controller != nullptr) {
		axis_x = SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_LEFTX);
		axis_y = SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_LEFTY);
		r_axis_x = SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_RIGHTX);
		r_axis_y = SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_RIGHTY);
		//LOG("X: %i Y: %i", axis_x, axis_y);
	}
}

void m1Input::UpdateMouse()
{
	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if (mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}

	int scale = App->win->GetScale();

	last_mouse_x = mouse_x;
	last_mouse_y = mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	mouse_x /= scale;
	mouse_y /= scale;
}

void m1Input::UpdateKeyboard()
{
	BROFILER_CATEGORY("UpdateKeyboard", Profiler::Color::Orange);

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}
}

// Called before quitting
bool m1Input::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	RELEASE_ARRAY(keyboard)
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_HapticStopAll(haptic);
	SDL_HapticClose(haptic);
	SDL_QuitSubSystem(SDL_INIT_HAPTIC);
	return true;
}

// ---------
bool m1Input::GetWindowEvent(j1EventWindow ev)
{
	return windowEvents[ev];
}

void m1Input::GetMousePosition(int& x, int& y)
{
	x = mouse_x;
	y = mouse_y;
}

void m1Input::GetMouseMotion(int& x, int& y)
{
	x = mouse_motion_x;
	y = mouse_motion_y;
}

bool m1Input::MovedMouse()
{
	return mouse_x != last_mouse_x || mouse_y != last_mouse_y;
}

bool m1Input::CheckAxisStates(const Axis &axis) {

	BROFILER_CATEGORY("ChackAxisStates", Profiler::Color::Orange);

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
		case Axis::R_AXIS_UP_RIGHT:
			if (r_axis_x > DEAD_ZONE && r_axis_y < -DEAD_ZONE)
				ret = true;
			break;
		case Axis::R_AXIS_DOWN_RIGHT:
			if (r_axis_x > DEAD_ZONE && r_axis_y > DEAD_ZONE)
				ret = true;
			break;
		case Axis::R_AXIS_DOWN_LEFT:
			if (r_axis_x < -DEAD_ZONE && r_axis_y > DEAD_ZONE)
				ret = true;
			break;
		case Axis::R_AXIS_UP_LEFT:
			if (r_axis_x < -DEAD_ZONE && r_axis_y < -DEAD_ZONE)
				ret = true;
			break;
		case Axis::R_AXIS_RIGHT:
			if (r_axis_x > DEAD_ZONE && r_axis_y > -DEAD_ZONE && r_axis_y < DEAD_ZONE)
				ret = true;
			break;
		case Axis::R_AXIS_LEFT:
			if (r_axis_x < -DEAD_ZONE && r_axis_y > -DEAD_ZONE && r_axis_y < DEAD_ZONE)
				ret = true;
			break;
		case Axis::R_AXIS_UP:
			if (r_axis_x > -DEAD_ZONE && r_axis_x < DEAD_ZONE && r_axis_y < -DEAD_ZONE)
				ret = true;
			break;
		case Axis::R_AXIS_DOWN:
			if (r_axis_x > -DEAD_ZONE && r_axis_x < DEAD_ZONE && r_axis_y > DEAD_ZONE)
				ret = true;
			break;
		default:
			LOG("No axis found");
			break;
		}
	}
	

	return ret;
}

bool m1Input::ControllerVibration(float strength, uint32 duration)
{
	//strength 0.0F(min) - 1.0F(max)
	//duration in milliseconds
	SDL_HapticRumblePlay(haptic, strength, duration);
	return false;
}
