#ifndef __m1INPUT_H__
#define __m1INPUT_H__

#include "m1Module.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_gamecontroller.h"
//#define NUM_KEYS 352
#define NUM_CONTROLLER_BUTTONS SDL_CONTROLLER_BUTTON_MAX //16
#define NUM_MOUSE_BUTTONS 5
#define DEAD_ZONE 7000
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;

enum class Axis {

	AXIS_UP,
	AXIS_DOWN,
	AXIS_RIGHT,
	AXIS_LEFT,
	AXIS_UP_LEFT,
	AXIS_UP_RIGHT,
	AXIS_DOWN_LEFT,
	AXIS_DOWN_RIGHT,

	NONE

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
	int INVENTORY;

};


struct ButtonChar {
	char* UP;
	char* DOWN;
	char* LEFT;
	char* RIGHT;
	char* DIRECTION_UP;
	char* DIRECCTION_DOWN;
	char* DIRECTION_LEFT;
	char* DIRECCTION_RIGHT;
	char* DIAGONALS;
	char* SHOW_SKILLS;
	char* BASIC_ATTACK;
	char* HABILITY1;
	char* INVENTORY;
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

enum j1KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
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
		return axis_x;
	}

	const int GetAxisY() {
		return axis_y;
	}
	void DefaultControls();

	bool CheckAxisStates(const Axis &axis);

	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

	KeyboardButtons keyboard_buttons;
	ControllerButtons controller_Buttons;
	SDL_GameController* Controller = nullptr;

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
	int			axis_x = 0;
	int			axis_y = 0;

};

#endif // __j1INPUT_H__