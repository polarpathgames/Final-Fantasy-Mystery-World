#ifndef __j1UIMANAGER_H__
#define __j1UIMANAGER_H__

#include "j1Module.h"
#include "p2Animation.h"
#include <list>
#include "p2Point.h"
enum UIType
{
	IMAGE,
	LABEL,
	BUTTON,
	NON,
};

struct SDL_Texture;
struct SDL_Rect;

enum Color;
enum class FontType;

class GUI;
class GUI_Image;
class GUI_Label;
class GUI_Button;

class j1UIManager: public j1Module
{
public:
	j1UIManager();
	virtual ~j1UIManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	void FocusInput();
	bool FocusFirstUIFocusable();
	bool PostUpdate();
	bool CleanUp();

	GUI_Image* AddImage(const int &x, const int &y, const SDL_Rect & rect, j1Module * callback, GUI * parent, bool draw, bool drag, bool interact, bool focus);
	GUI_Button* AddButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &mouse_in, const SDL_Rect &clicked, j1Module* callback, GUI* parent, bool draw, bool drag, bool inter, bool focus);
	GUI_Label* AddLabel(const int &x, const int &y, const char* text, GUI* parent, Color color, const FontType &font, j1Module* callback, bool focus);

	void CreateScreen();

	bool DeleteUIElement(GUI * element);
	void BFS(std::list<GUI *> &visited, GUI * elem);
	bool DeleteAllUIElements();
	bool GetElemOnMouse(int x, int y, GUI* & element);
	bool CheckCollision(int x, int y, GUI* item);
	void UI_Events(GUI* element);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture*	atlas = nullptr;
	GUI*			focus = nullptr;
	SDL_Rect		focus_tx = { 0,0,0,0 };
	bool			using_mouse = true;
	std::list<GUI*> ui_list;	

public:

	GUI * screen = nullptr;
	bool debug_ui = false;

};
#endif // !__j1UIMANAGER_H__
