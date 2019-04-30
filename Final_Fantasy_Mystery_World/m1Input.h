#ifndef __m1INPUT_H__
#define __m1INPUT_H__

#include "m1Module.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_gamecontroller.h"
#include "SDL\include\SDL_haptic.h"

//#define NUM_KEYS 352
#define NUM_CONTROLLER_BUTTONS SDL_CONTROLLER_BUTTON_MAX //16
#define NUM_MOUSE_BUTTONS 5
#define DEAD_ZONE 3000
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;

enum j1KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum class Axis {

	AXIS_UP,
	AXIS_DOWN,
	AXIS_RIGHT,
	AXIS_LEFT,
	AXIS_UP_LEFT,
	AXIS_UP_RIGHT,
	AXIS_DOWN_LEFT,
	AXIS_DOWN_RIGHT,
	R_AXIS_UP,
	R_AXIS_DOWN,
	R_AXIS_RIGHT,
	R_AXIS_LEFT,
	R_AXIS_UP_LEFT,
	R_AXIS_UP_RIGHT,
	R_AXIS_DOWN_LEFT,
	R_AXIS_DOWN_RIGHT,
	NONE

};

struct axis {
	int value = 0;
	j1KeyState state = j1KeyState::KEY_IDLE;

	void Update();
};

struct Joystick {
	axis x;
	axis y;

	void UpdateState();
};


struct ButtonsUsed {

	int UP;
	int DOWN;
	int LEFT;
	int RIGHT;
	int DIRECTION_UP;
	int DIRECCTION_DOWN;
	int DIRECTION_LEFT;
	int DIRECCTION_RIGHT;
	int DIAGONALS;
	int BASIC_ATTACK;
	int SHOW_SKILLS;
	int HABILTY1;
	int HABILITY2;
	int INVENTORY;

};


struct ButtonChar {
	char* UP = nullptr;
	char* DOWN = nullptr;
	char* LEFT = nullptr;
	char* RIGHT = nullptr;
	char* DIRECTION_UP = nullptr;
	char* DIRECCTION_DOWN = nullptr;
	char* DIRECTION_LEFT = nullptr;
	char* DIRECCTION_RIGHT = nullptr;
	char* DIAGONALS = nullptr;
	char* SHOW_SKILLS = nullptr;
	char* BASIC_ATTACK = nullptr;
	char* ABILITY1 = nullptr;
	char* ABILITY2 = nullptr;
	char* INVENTORY = nullptr;
};


struct KeyboardButtons {
	ButtonsUsed buttons_code;
	ButtonChar buttons_char;
};

struct ControllerButtons {
	ButtonsUsed buttons_code;
	ButtonChar buttons_char;
};
enum j1EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

class m1Input : public m1Module
{

public:

	m1Input();

	// Destructor
	virtual ~m1Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	void UpdateEvents(SDL_Event &event);

	void UpdateController();

	void UpdateMouse();

	void UpdateKeyboard();

	// Called before quitting
	bool CleanUp();

	// Gather relevant win events
	bool GetWindowEvent(j1EventWindow ev);

	// Check key states (includes mouse and joy buttons)
	j1KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	j1KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	j1KeyState GetControllerButtonDown(int id) const
	{
		return controller_buttons[id];
	}

	const int GetAxisX() {
		return left_joy.x.value;
	}

	const int GetAxisY() {
		return left_joy.y.value;
	}
	const int GetRightAxisX() {
		return right_joy.x.value;
	}
	const int GetRightAxisY() {
		return right_joy.y.value;
	}

	void DefaultControls();

	bool CheckAxisStates(const Axis &axis);

	bool ControllerVibration(float strength, uint32 duration);
	

	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);
	bool MovedMouse();

	KeyboardButtons keyboard_buttons;
	ControllerButtons controller_Buttons;
	SDL_GameController* Controller = nullptr;

	//Controler Haptic

	SDL_Joystick *joystick;
	SDL_GameController *Pad;
	SDL_HapticEffect effect;
	std::string text_input;

	SDL_Haptic *haptic = nullptr;


private:
	bool		windowEvents[WE_COUNT];
	j1KeyState*	keyboard;
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	SDL_Event ev;

	j1KeyState controller_buttons[NUM_CONTROLLER_BUTTONS];

	int			mouse_motion_x = 0;
	int			mouse_motion_y = 0;
	int			mouse_x = 0;
	int			mouse_y = 0;
	int			last_mouse_x = 0;
	int			last_mouse_y = 0;
	Joystick	left_joy;
	Joystick	right_joy;
};

#endif // __j1INPUT_H__