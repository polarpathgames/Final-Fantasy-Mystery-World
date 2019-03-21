#ifndef __j1INPUT_H__
#define __j1INPUT_H__

#include "j1Module.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_gamecontroller.h"
//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
#define MAX_GAMEPADS 1
#define MAX_BUTTONS 10
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;
struct ControllerDir
{
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	int axisX = 0;
	int axisY = 0;
	int deadzone = 8000;
};

enum CONTROLLER_BUTTONS {

	BUTTON_RT,
	BUTTON_D_PAD_UP,
	BUTTON_D_PAD_DOWN,
	BUTTON_D_PAD_LEFT,
	BUTTON_D_PAD_RIGHT,
	NONE

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

class j1Input : public j1Module
{

public:

	j1Input();

	// Destructor
	virtual ~j1Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

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

	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

private:
	bool		windowEvents[WE_COUNT];
	j1KeyState*	keyboard;
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	SDL_Event ev;
	bool controller_state[MAX_BUTTONS];
	j1KeyState controller[MAX_BUTTONS];
	SDL_GameController* gamepads[MAX_GAMEPADS] = { nullptr };
	ControllerDir GamepadDir[MAX_GAMEPADS];
	int			mouse_motion_x;
	int			mouse_motion_y;
	int			mouse_x;
	int			mouse_y;
};

#endif // __j1INPUT_H__