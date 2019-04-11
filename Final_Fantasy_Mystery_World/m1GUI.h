#ifndef __m1UIMANAGER_H__
#define __m1UIMANAGER_H__

#include "m1Module.h"
#include "p2Animation.h"
#include <list>

#include "p2Defs.h"
#include "p2Point.h"

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
enum class FontType;

class u1UI_ELEMENT;
class u1Image;
class u1Label;
class u1Button;
class u1Slider;
class u1CheckBox;

class m1GUI: public m1Module
{
public:
	m1GUI();
	virtual ~m1GUI();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool UpdateFocusMouse();
	void FocusInput();
	bool FocusFirstUIFocusable();
	bool FocusButton(u1Button* button);
	bool PostUpdate();
	bool CleanUp();



	u1Slider* AddSlider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, bool horizontal, u1GUI* parent, m1Module* callback = nullptr);
	u1CheckBox* AddCheckBox(const int &pos_x, const int &pos_y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, m1Module* callback = nullptr);

	u1Image* AddImage(const int &x, const int &y, const SDL_Rect & rect, m1Module * callback, u1GUI * parent, bool draw, bool drag, bool interact, bool focus);
	u1Button* AddButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &mouse_in, const SDL_Rect &clicked, m1Module* callback, u1GUI* parent, bool draw, bool drag, bool inter, bool focus);
	u1Label* AddLabel(const int &x, const int &y, const char* text, u1GUI* parent, Color color, const FontType &font, m1Module* callback, bool focus, const uint32 & wrap = 0u);


	void CreateScreen();

	bool DeleteUIElement(u1GUI * element);
	void BFS(std::list<u1GUI *> &visited, u1GUI * elem);
	bool DeleteAllUIElements();
	bool GetElemOnMouse(int x, int y, u1GUI* & element);
	bool CheckCollision(int x, int y, u1GUI* item);

	bool ShowCursor(bool enable);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture*		atlas = nullptr;
	u1GUI*				focus = nullptr;
	SDL_Rect			focus_tx = { 0,0,0,0 };
	bool				using_mouse = true;
	std::list<u1GUI*>	ui_list;

	SDL_Rect			cursor_rect;
	iPoint				cursor_position;
	iPoint				cursor_offset = {-12, -3};
	bool				show_cursor = true;

public:

	u1GUI * screen = nullptr;
	bool debug_ui = false;

};
#endif // !__j1UIMANAGER_H__
