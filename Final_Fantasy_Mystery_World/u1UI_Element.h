#ifndef __u1UI_Element_H__
#define __u1UI_Element_H__

#include "m1GUI.h"
#include "p2Point.h"

struct SDL_Texture;
struct SDL_Rect;

enum class Element_Event {
	HOVER_ENTER,
	HOVER,
	HOVER_EXIT,
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

class u1GUI
{
public:
	u1GUI() :type(UIType::NON) {}
	u1GUI(UIType type,const int &x,const int &y, u1GUI* parent, const SDL_Rect& section, bool draw = true, bool inter = false, bool drag = false, bool allow_focus = true);
	virtual ~u1GUI();

	bool Update();
	virtual bool PostUpdate() { return true; }
	void Draw();
	virtual void InnerDraw();
	virtual void UpdateElement() {};
	void PreUpdate();
	virtual void PreUpdateElement() {};
	virtual bool CleanUp();

	void SetPos(const int &x, const int &y);

	UIType GetType()const;
	int GetPriority() const;
	iPoint GetGlobalPosition() const;
	iPoint GetLocalPosition() const;
	void SetPosRespectParent(Position_Type, const int& margin = 0);

	SDL_Rect GetRect() const;

	void DebugDraw();

	void AddListener(m1Module* module);
	void DeleteListener(m1Module* module);

public:
	iPoint position = { 0,0 };

	SDL_Rect section = { 0,0 };

	bool interactable = true;
	bool draggable = true;
	bool drawable = true;
	bool allow_focus = true;

	bool to_delete = false;
	iPoint draw_offset = { 0,0 };
	iPoint focus_offset = { 0,0 };

	bool clipable = false;

	u1GUI* parent = nullptr;

	std::list<u1GUI*> childs;

	Element_Event current_state = Element_Event::NONE;
	iPoint last_mouse;

private:
	UIType type = NON;

	int priority = 0;

	std::list<m1Module*> listeners;
};


#endif // !__GUI_H__
