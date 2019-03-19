#ifndef __GUI_H__
#define __GUI_H__

#include "j1UIManager.h"
#include "p2Point.h"

struct SDL_Texture;
struct SDL_Rect;

class GUI
{
public:
	GUI() :type(UIType::NON) {}
	GUI(UIType type,const int &x,const int &y, GUI* parent, const int &width = 0, const int &height = 0);
	virtual ~GUI();

	virtual bool PreUpdate() { return true; }
	virtual bool Update(float dt);
	virtual bool PostUpdate() { return true; }
	virtual void Draw();
	virtual bool CleanUp();
	virtual bool MouseIn(GUI* element);

	void SetPos(const int &x, const int &y);

	UIType GetType()const;
	int GetPriority() const;
	iPoint GetGlobalPosition() const;
	iPoint GetLocalPosition() const;
	//void SetPosRespectParent(Position_Type, const int& margin = 0);

	void DebugDraw();

	void AddListener(j1Module* module);
	void DeleteListener(j1Module* module);

public:
	iPoint position = { 0,0 };

	SDL_Rect section = { 0,0 };

	bool interactable = true;
	bool draggable = true;
	bool drawable = true;

	bool to_delete = false;
	iPoint draw_offset = { 0,0 };

	bool clipable = false;

	GUI* parent = nullptr;

	std::list<GUI*> childs;

	//Mouse_Event current_state = NONE;
	iPoint last_mouse;

private:
	UIType type = NON;

	int priority = 0;

	std::list<j1Module*> listeners;
};


#endif // !__GUI_H__
