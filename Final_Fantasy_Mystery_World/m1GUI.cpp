#include "App.h"
#include "m1GUI.h"
#include "m1Input.h"
#include "m1Window.h"
#include "m1Render.h"
#include "p2Log.h"
#include "m1Textures.h"
#include "m1Fonts.h"
#include "u1Image.h"
#include "m1Audio.h"
#include "u1Button.h"
#include "u1InputText.h"
#include "u1Label.h"
#include "u1ChButton.h"
#include "u1Slider.h"
#include "u1CheckBox.h"
#include "u1Bar.h"
#include "m1GUI.h"
#include "m1Audio.h"
#include "Brofiler/Brofiler.h"
#include "m1Audio.h"

#include <queue>

m1GUI::m1GUI(): m1Module()
{
	name.assign("gui");
}

m1GUI::~m1GUI() {}

bool m1GUI::Awake(pugi::xml_node &node)
{
	CreateScreen();

	//Load all ui elements info with xml...
	focus_tx = { 1024,1986,16,27 };
	cursor_rect = { 1024, 2013, 35, 40 };

	//----------------------

	return true;
}

bool m1GUI::Start()
{
	atlas = App->tex->Load("assets/gui/atlas.png");

	fx_pause = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Input_Text.wav");
	fx_focus = App->audio->LoadFx("assets/audio/sfx/InBattle_Menu_Cursor_Move.wav");
	fx_inventory = App->audio->LoadFx("assets/audio/sfx/FFMW_SFX_Potion_Glup.wav");

	SDL_ShowCursor(SDL_DISABLE);

	return true;
}

bool m1GUI::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateUIM", Profiler::Color::Orange);

	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		debug_ui = !debug_ui;
	}

	ret = UpdateFocusMouse();

	return ret;
}

bool m1GUI::UpdateFocusMouse()
{
	BROFILER_CATEGORY("UpdateFocusMouse", Profiler::Color::Orange);

	bool ret = true;

	if (focus == nullptr && ui_list.size() > 1) {
		FocusFirstUIFocusable();
	}

	if (focus != nullptr) {
		if (using_mouse) {
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN
				|| App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN
				|| App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN)==KEY_DOWN
				|| App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN
				|| App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN
				|| App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN
				|| App->input->CheckAxisStates(Axis::AXIS_UP)
				|| App->input->CheckAxisStates(Axis::AXIS_DOWN)) {
				using_mouse = false;
				show_cursor = false;
			}

			else if (!show_cursor) {
				show_cursor = true;
			}


			iPoint mouse;
			App->input->GetMousePosition(mouse.x, mouse.y);
			u1GUI* element = nullptr;
			if (GetElemOnMouse(mouse.x*App->win->GetScale(), mouse.y*App->win->GetScale(), element)) {//Check if there is an element on Mouse
				if (focus != element) {
					focus = element;
					App->audio->PlayFx(fx_focus);
				}
			}
			ret = focus->Update();
		}
		if (!using_mouse) {
			if (App->input->MovedMouse()) {
				using_mouse = true;
				show_cursor = true;
			}

			if (show_cursor) {
				show_cursor = false;
			}

			FocusInput();
			ret = focus->Update();
		}
	}

	return ret;
}

void m1GUI::FocusInput()
{

	BROFILER_CATEGORY("FocusInput", Profiler::Color::Orange);

	u1GUI* new_focus = focus;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP) == KEY_DOWN|| App->input->CheckAxisStates(Axis::AXIS_UP)) {

		u1GUI* new_focus = focus;
		if (focus != nullptr && focus->parent != nullptr) {
			for (std::list<u1GUI*>::iterator item = focus->parent->childs.begin(); item != focus->parent->childs.end(); ++item) {
				if ((*item)->allow_focus && (*item)->position.y < focus->position.y) {
					if (focus == new_focus) {
						new_focus = (*item);
					}
					else if ((*item)->position.y >= new_focus->position.y && abs(focus->position.x - new_focus->position.x) >= abs(focus->position.x - (*item)->position.x)) {
						new_focus = *item;
					}
				}
			}
			if (new_focus != focus) {
				focus->current_state = Element_Event::NONE;
				focus = new_focus;
				focus->current_state = Element_Event::HOVER;
				App->audio->PlayFx(fx_focus);
			}
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == KEY_DOWN || App->input->CheckAxisStates(Axis::AXIS_DOWN)) {
		u1GUI* new_focus = focus;
		if (focus != nullptr && focus->parent != nullptr) {
			for (std::list<u1GUI*>::iterator item = focus->parent->childs.begin(); item != focus->parent->childs.end(); ++item) {
				if ((*item)->allow_focus && (*item)->position.y > focus->position.y) {
					if (focus == new_focus) {
						new_focus = (*item);
					}
					else if ((*item)->position.y <= new_focus->position.y && abs(focus->position.x - new_focus->position.x) >= abs(focus->position.x - (*item)->position.x)) {
						new_focus = *item;
					}
				}
			}
			if (new_focus != focus) {
				focus->current_state = Element_Event::NONE;
				focus = new_focus;
				focus->current_state = Element_Event::HOVER;
				App->audio->PlayFx(fx_focus);
			}
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == KEY_DOWN) {
		u1GUI* new_focus = focus;
		if (focus != nullptr && focus->parent != nullptr) {
			for (std::list<u1GUI*>::iterator item = focus->parent->childs.begin(); item != focus->parent->childs.end(); ++item) {
				if ((*item)->allow_focus && (*item)->position.x < focus->position.x) {
					if (focus == new_focus) {
						new_focus = (*item);
					}
					else if ((*item)->position.x >= new_focus->position.x && abs(focus->position.y - new_focus->position.y) >= abs(focus->position.y - (*item)->position.y)) {
						new_focus = *item;
					}
				}
			}
			if (new_focus != focus) {
				focus->current_state = Element_Event::NONE;
				focus = new_focus;
				focus->current_state = Element_Event::HOVER;
				App->audio->PlayFx(fx_focus);
			}
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == KEY_DOWN) {
		u1GUI* new_focus = focus;
		if (focus != nullptr && focus->parent != nullptr) {
			for (std::list<u1GUI*>::iterator item = focus->parent->childs.begin(); item != focus->parent->childs.end(); ++item) {
				if ((*item)->allow_focus && (*item)->position.x > focus->position.x) {
					if (focus == new_focus) {
						new_focus = (*item);
					}
					else if ((*item)->position.x <= new_focus->position.x && abs(focus->position.y - new_focus->position.y) >= abs(focus->position.y - (*item)->position.y)) {
						new_focus = *item;
					}
				}
			}
			if (new_focus != focus) {
				focus->current_state = Element_Event::NONE;
				focus = new_focus;
				focus->current_state = Element_Event::HOVER;
				App->audio->PlayFx(fx_focus);
			}
		}
	}

}

bool m1GUI::FocusFirstUIFocusable()
{
	BROFILER_CATEGORY("FindElementToFocus", Profiler::Color::Aqua);

	for (std::list<u1GUI*>::iterator item = ui_list.begin(); item != ui_list.end(); ++item) {
		if ((*item)->allow_focus && *item != nullptr) {
			focus = *item;
			return true;
		}
	}
	//LOG("There is any button focusable");
	return false;
}

bool m1GUI::FocusButton(u1Button * button)
{
	if (button != nullptr) {
		focus = button;
		return true;
	}
	return false;
}

bool m1GUI::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateUIManager", Profiler::Color::Purple);

	bool ret = true;

	if (ui_list.size() > 0) {
		std::list<u1GUI*> tree;
		BFS(tree, screen);

		for (std::list<u1GUI*>::iterator item = tree.begin(); item != tree.end(); item++) {
			(*item)->Draw();
			if (focus == *item) {
				App->render->Blit((SDL_Texture*)GetAtlas(), focus->GetGlobalPosition().x - focus_tx.w, (focus->section.h - focus_tx.h) * 0.5F + focus->GetGlobalPosition().y + 5, &focus_tx);
			}
			if (debug_ui) {
				(*item)->DebugDraw();
			}
		}
		tree.clear();

		App->input->GetMousePosition(cursor_position.x, cursor_position.y);
		if (show_cursor)
			App->render->Blit((SDL_Texture*)GetAtlas(), cursor_position.x * App->win->GetScale() + cursor_offset.x, cursor_position.y * App->win->GetScale() + cursor_offset.y, &cursor_rect);

	}
	return ret;
}

bool m1GUI::CleanUp()
{
	std::list<u1GUI*>::iterator item = ui_list.begin();
	for (; item != ui_list.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			delete *item;
			*item = nullptr;
		}
	}

	ui_list.clear();
	App->tex->UnLoad(atlas);
	atlas = nullptr;
	return true;
}

const SDL_Texture* m1GUI::GetAtlas() const
{
	return atlas;
}

u1Image* m1GUI::AddImage(const int &x,const int &y, const SDL_Rect & rect = {0,0,0,0}, m1Module * listener = nullptr, u1GUI * parent = nullptr, bool draw = true, bool drag = false, bool interact = false, bool focus = true)
{

	u1Image* image = DBG_NEW u1Image(x, y, rect, parent, draw, interact, drag, focus);

	if (listener != nullptr) {
		image->AddListener(listener);
	}

	ui_list.push_back(image);

	return image;
}

u1Button* m1GUI::AddButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &mouse_in, const SDL_Rect &clicked, m1Module* listener, u1GUI* parent, bool draw, bool drag, bool inter, bool focus = true)
{
	u1Button* button = DBG_NEW u1Button(x, y, idle, mouse_in, clicked, parent, draw, inter, drag, focus);

	if (listener != nullptr) {
		button->AddListener(listener);
	}

	ui_list.push_back(button);
	
	return button;
}

u1ChButton* m1GUI::AddChButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &mouse_in, const SDL_Rect &clicked, m1Module* listener, u1GUI* parent, PlayerType player_type, bool draw, bool drag, bool inter, bool focus)
{
	u1ChButton* character_button = DBG_NEW u1ChButton(x, y, idle, mouse_in, clicked, parent, player_type, draw, inter, drag, focus);

	if (listener != nullptr) {
		character_button->AddListener(listener);
	}

	ui_list.push_back(character_button);

	return character_button;
}

u1Label* m1GUI::AddLabel(const int &x, const int &y, const char* text, u1GUI* parent, Color color, const FontType &font, m1Module* listener = nullptr, bool focus = false, const uint32 & wrap, bool has_bg, const SDL_Color& bg_color)
{
	u1Label* label = DBG_NEW u1Label(x, y, text, color, font, parent, false, false, wrap, false, has_bg, bg_color);

	if (listener != nullptr) {
		label->AddListener(listener);
	}

	ui_list.push_back(label);
	
	return label;
}

u1InputText* m1GUI::AddInputText(const int &x, const int &y, const char* text, u1GUI* parent, Color color, const FontType &font, m1Module* listener = nullptr, bool focus = false, bool has_bg, const SDL_Color& bg_color)
{
	u1InputText* input_text = DBG_NEW u1InputText(x, y, text, color, font, parent, false, false, false, has_bg, bg_color);

	if (listener != nullptr) {
		input_text->AddListener(listener);
	}

	ui_list.push_back(input_text);

	return input_text;
}

u1Slider* m1GUI::AddSlider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, bool horizontal, u1GUI* parent, m1Module* callback)
{
	u1Slider* slider = DBG_NEW u1Slider(x, y, rect, idle, hover, push, horizontal, parent);
	
	if (callback != nullptr) {
		slider->AddListener(callback);
	}

	ui_list.push_back(slider);

	return slider;
}

u1CheckBox* m1GUI::AddCheckBox(const int &pos_x, const int &pos_y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, u1GUI* parent = nullptr, m1Module* callback)
{
	u1CheckBox* checkbox= DBG_NEW u1CheckBox(pos_x, pos_y, idle, hover, push, parent);
	
	if (callback != nullptr) {
		checkbox->AddListener(callback);
	}

	ui_list.push_back(checkbox);
	
	return checkbox;
}

u1Bar* m1GUI::AddBar(const int &x, const int &y, int max_capacity, UIType type, u1GUI* parent, m1Module* callback)
{
	u1Bar* bar = DBG_NEW u1Bar(x, y, max_capacity, type, parent, callback);

	if (callback != nullptr) {
		bar->AddListener(callback);
	}

	ui_list.push_back(bar);

	return bar;
}


void m1GUI::CreateScreen()
{
	if (std::find(ui_list.begin(), ui_list.end(), screen) == ui_list.end()) {
		screen = AddImage(0, 0, { 0,0,(int)App->win->width,(int)App->win->height }, nullptr, nullptr, false, false, false, false);
	}
}

bool m1GUI::DeleteUIElement(u1GUI * element)
{
	focus = nullptr;
	if (element != nullptr) {
		std::list<u1GUI*>::iterator item_ui = std::find(ui_list.begin(), ui_list.end(), element);
		if (item_ui != ui_list.end()) {															//if element doesn't find in ui list it cannot be deleted

			std::list<u1GUI*> tree;
			BFS(tree, element);		//fills a list from element to delete to its childs using BFS algorithm

			for (std::list<u1GUI*>::reverse_iterator item_tree = tree.rbegin(); item_tree != tree.rend(); ++item_tree) {	//iterate list from bottom to top
				if ((*item_tree)->parent != nullptr) {				/*In the case the item has a parent we have first to delete the item of parent's child list*/
					std::list<u1GUI*>::iterator this_on_child = std::find((*item_tree)->parent->childs.begin(), (*item_tree)->parent->childs.end(), *item_tree);
					if (this_on_child != (*item_tree)->parent->childs.end()) {
						(*item_tree)->parent->childs.remove(*this_on_child);
					}
				}
				std::list<u1GUI*>::iterator elem = std::find(ui_list.begin(), ui_list.end(), *item_tree);	//find item on ui objects list
				if (elem != ui_list.end() && *elem != nullptr) {						//if it is valid
					delete *elem;
					*elem = nullptr;						//delete from list
															//delete item and deallocate memory
				}
			}
			tree.clear();
			ui_list.remove(nullptr);
			return true;
		}
	}

	LOG("Element not found to delete");

	return false;
}

void m1GUI::BFS(std::list<u1GUI*>& visited, u1GUI * elem)
{
	BROFILER_CATEGORY("BFS", Profiler::Color::Orange);

	if (elem != nullptr) {
		std::queue<u1GUI*> frontier;
		u1GUI* item = nullptr;
		visited.push_back(elem);					//Add from we want to start to visited and frontier list
		frontier.push(elem);
		while (frontier.empty() == false) {
			if ((item = frontier.front()) != nullptr) {			//Pop las item of array
				frontier.pop();
				if(item->childs.empty() == false)
					for (std::list<u1GUI*>::iterator it = item->childs.begin(); it != item->childs.end(); ++it) { //iterate for all childs of node
						if (std::find(visited.begin(),visited.end(),*it) == visited.end()) {	//if child is not on visited list we added on it and on prontier to search its childs
							frontier.push(*it);
							visited.push_back(*it);
						}
					}
			}

		}
	}
}

bool m1GUI::DeleteAllUIElements()
{
	bool ret = true;

	ret = DeleteUIElement(screen);
	SDL_assert(ui_list.size() == 0);
	CreateScreen();
	focus = nullptr;

	return ret;
}

bool m1GUI::GetElemOnMouse(int x, int y, u1GUI *& element)
{
	std::list<u1GUI*> tree;
	BFS(tree, screen);

	for (std::list<u1GUI*>::reverse_iterator item = tree.rbegin(); item != tree.rend(); ++item) {
		if ((*item)->interactable)
		{
			if (CheckCollision(x, y, *item))
			{
				if ((*item)->current_state != Element_Event::CLICKED_DOWN && (*item)->current_state != Element_Event::CLICKED_REPEAT)
					App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN ? (*item)->current_state = Element_Event::CLICKED_DOWN : (*item)->current_state = Element_Event::HOVER;
				else {
					App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) ? (*item)->current_state = Element_Event::CLICKED_REPEAT : (*item)->current_state = Element_Event::CLICKED_UP;
				}
				element = *item;
				return true;
			}
			else {
				(*item)->current_state = Element_Event::NONE;
			}
		}
	}
	tree.clear();

	return false;
}

bool m1GUI::CheckCollision(int x, int y, u1GUI *item)
{
	if (item != nullptr) {
		iPoint pos = item->GetGlobalPosition();
		return (x > pos.x && x < pos.x + item->section.w) &&
			(y > pos.y && y < pos.y + item->section.h);
	}
	return false;
}

bool m1GUI::ShowCursor(bool enable)
{
	return show_cursor = enable;
}

const u1GUI * m1GUI::GetFocus()
{
	return focus;
}
