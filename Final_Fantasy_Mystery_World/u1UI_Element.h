#ifndef __GUI_H__
#define __GUI_H__

#include "j1UIManager.h"
#include "p2Point.h"

struct SDL_Texture;
struct SDL_Rect;

enum class Mouse_Event {
	HOVER,
	CLICKED_DOWN,
	CLICKED_REPEAT,
	CLICKED_UP,

	NONE
};

enum Position_Type {
	CENTERED,
	CENTERED_UP,
	CENTERED_DOWN,
	LEFT_CENTERED,
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_CENTERED,
	RIGHT_UP,
	RIGHT_DOWN,
};

enum Color
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	GREY,
	BLACK,
	WHITE,

	COLOR_NOT_DEF
};

class GUI
{
public:
	GUI() :type(UIType::NON) {}
	GUI(UIType type,const int &x,const int &y, GUI* parent, const SDL_Rect& section, bool draw = true, bool inter = false, bool drag = false, bool allow_focus = true);
	virtual ~GUI();

	bool Update();
	virtual bool PostUpdate() { return true; }
	void Draw();
	virtual void InnerDraw();
	virtual bool CleanUp();

	void SetPos(const int &x, const int &y);

	UIType GetType()const;
	int GetPriority() const;
	iPoint GetGlobalPosition() const;
	iPoint GetLocalPosition() const;
	void SetPosRespectParent(Position_Type, const int& margin = 0);

	SDL_Rect GetRect() const;

	void DebugDraw();

	void AddListener(j1Module* module);
	void DeleteListener(j1Module* module);

public:
	iPoint position = { 0,0 };

	SDL_Rect section = { 0,0 };

	bool interactable = true;
	bool draggable = true;
	bool drawable = true;
	bool allow_focus = true;

	bool to_delete = false;
	iPoint draw_offset = { 0,0 };

	bool clipable = false;

	GUI* parent = nullptr;

	std::list<GUI*> childs;

	Mouse_Event current_state = Mouse_Event::NONE;
	iPoint last_mouse;

private:
	UIType type = NON;

	int priority = 0;

	std::list<j1Module*> listeners;
};


#endif // !__GUI_H__
