#ifndef __m1UIMANAGER_H__
#define __m1UIMANAGER_H__

#include "m1Module.h"
#include "p2Animation.h"
#include <list>
#include "SDL_mixer/include/SDL_mixer.h"

#include "p2Defs.h"
#include "p2Point.h"

enum UIType
{
	IMAGE,
	LABEL,
	BUTTON,
	SLIDER,
	CHECKBOX,
	BAR,
	HPBAR,
	MANABAR,
	EXPBAR,
	ENEMYBAR,
	INPUT_BOX,
	HIT_POINT_LABEL,
	SKIPBAR,
	VERTICAL_SLIDER,

	NON,
};

struct SDL_Texture;
struct SDL_Rect;

enum Color;
enum class FontType;
enum class PlayerType;

class u1UI_ELEMENT;
class u1Image;
class u1Label;
class u1Button;
class u1ChButton;
class u1Slider;
class u1CheckBox;
class u1Bar;
class u1InputText;
class u1VerticalSlider;
class u1HitPointLabel;

class m1GUI: public m1Module
{
public:
	m1GUI();
	virtual ~m1GUI();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

	bool IsInUIList(u1GUI * element);

	bool UpdateFocusMouse();
	void FocusInput();
	bool FocusFirstUIFocusable();
	bool FocusButton(u1Button* button);

	u1Slider* AddSlider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, bool horizontal, u1GUI* parent, m1Module* callback = nullptr);
	u1CheckBox* AddCheckBox(const int &pos_x, const int &pos_y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, m1Module* callback = nullptr);

	u1Image* AddImage(const int &x, const int &y, const SDL_Rect & rect, m1Module * callback, u1GUI * parent, bool draw, bool drag, bool interact, bool focus, Animation * anim = nullptr, SDL_Rect* clip_zone = NULL);
	u1Button* AddButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &mouse_in, const SDL_Rect &clicked, m1Module* callback, u1GUI* parent, bool draw, bool drag, bool inter, bool focus, const iPoint &focus_offset = { 0,0 }, SDL_Rect*clip_zone = nullptr, const SDL_Rect & extra_image = { 0,0,0,0 }, const iPoint & offset_extra_image = { 0,0 });
	u1ChButton* AddChButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &mouse_in, const SDL_Rect &clicked, m1Module* callback, u1GUI* parent, PlayerType player_type, bool draw, bool drag, bool inter, bool focus);
	u1Label* AddLabel(const int &x, const int &y, const char* text, u1GUI* parent, Color color, const FontType &font, m1Module* callback, bool focus, const uint32 & wrap = 0u, bool has_bg = false, const SDL_Color& bg_color = { 255,255,255,255 }, SDL_Rect*clip_zone = nullptr);
	u1InputText * AddInputText(const int &x, const int &y, const char* text, u1GUI* parent, Color color, const FontType &font, const SDL_Rect &rect,m1Module* callback);
	u1Bar* AddBar(const int &x, const int &y, int max_capacity, UIType type, u1GUI* parent, m1Module* callback);
	u1HitPointLabel* AddHitPointLabel(const int &x, const int &y, const char* text, u1GUI* parent,const Color &color, const FontType & type);
	u1VerticalSlider* AddVerticalSlider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent, int * position, const int &moving_distance, m1Module* callback = nullptr);

	void CreateScreen();

	bool DeleteUIElement(u1GUI * element);
	void BFS(std::list<u1GUI *> &visited, u1GUI * elem);
	bool DeleteAllUIElements();
	bool GetElemOnMouse(int x, int y, u1GUI* & element);
	bool CheckCollision(int x, int y, u1GUI* item);

	bool ShowCursor(bool enable);
	const u1GUI* GetFocus();

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

	// SFX

	Mix_Chunk* fx_pause;
	Mix_Chunk* fx_focus;
	Mix_Chunk* fx_inventory;



};
#endif // !__j1UIMANAGER_H__
