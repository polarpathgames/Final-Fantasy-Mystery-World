#ifndef __j1UIMANAGER_H__
#define __j1UIMANAGER_H__

#include "j1Module.h"
#include "p2Animation.h"
#include <list>
#include "p2Defs.h"

enum UIType
{
	IMAGE,
	LABEL,
	BUTTON,
	SLIDER,
	CHECKBOX,
	NON,
};

struct SDL_Texture;
struct SDL_Rect;

enum Color;

class GUI;
class GUI_Image;
class GUI_Label;
class GUI_Button;
class GUI_Slider;
class GUI_CheckBox;

class j1UIManager: public j1Module
{
public:
	j1UIManager();
	virtual ~j1UIManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

	GUI_Image* AddImage(const int &x, const int &y, const SDL_Rect & rect, j1Module * callback, GUI * parent, bool draw, bool drag, bool interact);
	GUI_Button* AddButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &mouse_in, const SDL_Rect &clicked, j1Module* callback, GUI* parent, bool draw, bool drag, bool inter);
	GUI_Label* AddLabel(const int &x, const int &y, const char* text, uint size, GUI* parent, Color color, const char* font, j1Module* callback);
	//GUI_Slider* AddSlider(iPoint pos, SDL_Rect rect, SDL_Rect normal, SDL_Rect hovered, SDL_Rect pressed, bool horizontal, GUI* parent = nullptr);
	GUI_CheckBox* AddCheckBox(const int &pos_x, const int &pos_y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, j1Module* callback, GUI* parent);

	void CreateScreen();

	bool DeleteUIElement(GUI * element);
	void BFS(std::list<GUI *> &visited, GUI * elem);
	bool DeleteAllUIElements();
	bool GetElemOnMouse(int x, int y, GUI* & element);
	bool CheckCollision(int x, int y, GUI* item);
	void UI_Events(GUI* element);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas = nullptr;
	std::list<GUI*> ui_list;	

public:

	GUI * screen = nullptr;
	bool debug_ui = true;

};
#endif // !__j1UIMANAGER_H__
