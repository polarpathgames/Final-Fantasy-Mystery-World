#include "j1App.h"
#include "j1UIManager.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "GUI_Image.h"
#include "GUI_Button.h"
#include "GUI_Label.h"
#include "GUI_Slider.h"
#include "GUI_CheckBox.h"
#include "GUI.h"
#include "Brofiler/Brofiler.h"

#include <queue>

j1UIManager::j1UIManager(): j1Module()
{
	name.assign("gui");
}

j1UIManager::~j1UIManager() {}

bool j1UIManager::Awake(pugi::xml_node &node)
{
	CreateScreen();

	//Load all ui elements info with xml...

	//----------------------
	focus_tx = { 1024,1986,16,27 };

	return true;
}

bool j1UIManager::Start()
{
	atlas = App->tex->Load("gui/atlas.png");

	return true;
}

bool j1UIManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateUIM", Profiler::Color::Orange);

	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		debug_ui = !debug_ui;
	}

	int x = 0, y = 0;
	App->input->GetMouseMotion(x, y);

	if (focus == nullptr) {
		FocusFirstUIFocusable();
		using_mouse = false;
		SDL_ShowCursor(SDL_DISABLE);
	}
	
	if (focus != nullptr) {
		if (using_mouse) {
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN
				|| App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
				using_mouse = false;
				SDL_ShowCursor(SDL_DISABLE);
			}

			if (SDL_ShowCursor(-1) == 0)
				SDL_ShowCursor(SDL_ENABLE);

			iPoint mouse;
			App->input->GetMousePosition(mouse.x, mouse.y);
			GUI* element = nullptr;
			if (GetElemOnMouse(mouse.x*App->win->GetScale(), mouse.y*App->win->GetScale(), element)) {//Check if there is an element on Mouse
				focus = element;
			}
			ret = focus->Update();
		}
		if (!using_mouse) {
			if (x != 0 || y != 0) {
				using_mouse = true;
				SDL_ShowCursor(SDL_ENABLE);
			}

			if (SDL_ShowCursor(-1) == 1)
				SDL_ShowCursor(SDL_DISABLE);

			FocusInput();
			ret = focus->Update();
		}
	}

	return ret;
}

void j1UIManager::FocusInput()
{
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
		GUI* new_focus = focus;
		if (focus->parent != nullptr)
			for (std::list<GUI*>::iterator item = focus->parent->childs.begin(); item != focus->parent->childs.end(); ++item) {
				if ((*item)->allow_focus && (*item)->position.y <= focus->position.y && *item != focus) {
					if (new_focus == focus || new_focus->position.y < (*item)->position.y)
						new_focus = *item;
				}
			}
		focus->current_state = Mouse_Event::NONE;
		focus = new_focus;
		focus->current_state = Mouse_Event::HOVER;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
		GUI* new_focus = focus;
		if (focus->parent != nullptr)
			for (std::list<GUI*>::iterator item = focus->parent->childs.begin(); item != focus->parent->childs.end(); ++item) {
				if ((*item)->allow_focus && (*item)->position.y >= focus->position.y && *item != focus) {
					if (new_focus == focus || new_focus->position.y > (*item)->position.y)
						new_focus = *item;
				}
			}
		focus->current_state = Mouse_Event::NONE;
		focus = new_focus;
		focus->current_state = Mouse_Event::HOVER;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
		GUI* new_focus = focus;
		if (focus->parent != nullptr)
			for (std::list<GUI*>::iterator item = focus->parent->childs.begin(); item != focus->parent->childs.end(); ++item) {
				if ((*item)->allow_focus && (*item)->position.x <= focus->position.x && *item != focus) {
					if (new_focus == focus || new_focus->position.x < (*item)->position.x)
						new_focus = *item;
				}
			}
		focus->current_state = Mouse_Event::NONE;
		focus = new_focus;
		focus->current_state = Mouse_Event::HOVER;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
		GUI* new_focus = focus;
		if (focus->parent != nullptr)
			for (std::list<GUI*>::iterator item = focus->parent->childs.begin(); item != focus->parent->childs.end(); ++item) {
				if ((*item)->allow_focus && (*item)->position.x >= focus->position.x && *item != focus) {
					if (new_focus == focus || new_focus->position.x > (*item)->position.x)
						new_focus = *item;
				}
			}
		focus->current_state = Mouse_Event::NONE;
		focus = new_focus;
		focus->current_state = Mouse_Event::HOVER;
	}
}

bool j1UIManager::FocusFirstUIFocusable()
{
	for (std::list<GUI*>::iterator item = ui_list.begin(); item != ui_list.end(); ++item) {
		if ((*item)->allow_focus && *item != nullptr) {
			focus = *item;
			return true;
		}
	}
	//LOG("There is not any button focusable");
	return false;
}

bool j1UIManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateUIManager", Profiler::Color::Purple);

	bool ret = true;

	std::list<GUI*> tree;
	BFS(tree, screen);

	for (std::list<GUI*>::iterator item = tree.begin(); item != tree.end(); item++) {
		(*item)->Draw();
		if (focus == *item) {
			App->render->Blit((SDL_Texture*)GetAtlas(), focus->GetGlobalPosition().x - focus_tx.w, (focus->section.h - focus_tx.h) * 0.5F + focus->GetGlobalPosition().y + 5, &focus_tx);
		}
		if (debug_ui) {
			(*item)->DebugDraw();
		}
	}
	tree.clear();
	

	return ret;
}

bool j1UIManager::CleanUp()
{
	std::list<GUI*>::iterator item = ui_list.begin();
	for (; item != ui_list.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			delete *item;
			*item = nullptr;
		}
	}

	ui_list.clear();
	App->tex->UnLoad(atlas);

	return true;
}

const SDL_Texture* j1UIManager::GetAtlas() const
{
	return atlas;
}

GUI_Image* j1UIManager::AddImage(const int &x,const int &y, const SDL_Rect & rect = {0,0,0,0}, j1Module * callback = nullptr, GUI * parent = nullptr, bool draw = true, bool drag = false, bool interact = false, bool focus = true)
{
	GUI_Image* image = new GUI_Image(x, y, rect, parent, draw, interact, drag, focus);

	if (callback != nullptr) {
		image->AddListener(callback);
	}

	ui_list.push_back(image);

	return image;
}

GUI_Button* j1UIManager::AddButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &mouse_in, const SDL_Rect &clicked, j1Module* callback, GUI* parent, bool draw, bool drag, bool inter, bool focus = true)
{
	GUI_Button* button = new GUI_Button(x, y, idle, mouse_in, clicked, parent, draw, inter, drag, focus);

	if (callback != nullptr) {
		button->AddListener(callback);
	}

	ui_list.push_back(button);
	
	return button;
}

GUI_Label* j1UIManager::AddLabel(const int &x, const int &y, const char* text, GUI* parent, Color color, const FontType &font, j1Module* callback = nullptr, bool focus = false)
{
	GUI_Label* label = new GUI_Label(x, y, text, color, font, parent, focus);

	if (callback != nullptr) {
		label->AddListener(callback);
	}

	ui_list.push_back(label);
	
	return label;
}

GUI_Slider* j1UIManager::AddSlider(const int &x, const int &y, const SDL_Rect &rect, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, bool horizontal, GUI* parent, j1Module* callback)
{
	GUI_Slider* slider = new GUI_Slider(x, y, rect, idle, hover, push, horizontal, parent);
	
	if (callback != nullptr) {
		slider->AddListener(callback);
	}

	ui_list.push_back(slider);

	return slider;
}

GUI_CheckBox* j1UIManager::AddCheckBox(const int &pos_x, const int &pos_y, const SDL_Rect &idle, const SDL_Rect &hover, const SDL_Rect &push, GUI* parent = nullptr, j1Module* callback)
{
	GUI_CheckBox* checkbox= new GUI_CheckBox(pos_x, pos_y, idle, hover, push, parent);
	
	if (callback != nullptr) {
		checkbox->AddListener(callback);
	}

	ui_list.push_back(checkbox);
	
	return checkbox;
}

void j1UIManager::CreateScreen()
{
	if (std::find(ui_list.begin(), ui_list.end(), screen) == ui_list.end()) {
		screen = AddImage(0, 0, { 0,0,(int)App->win->width,(int)App->win->height }, nullptr, nullptr, false, false, false, false);
	}
}

bool j1UIManager::DeleteUIElement(GUI * element)
{
	focus = nullptr;
	if (element != nullptr) {
		std::list<GUI*>::iterator item_ui = std::find(ui_list.begin(), ui_list.end(), element);
		if (item_ui != ui_list.end()) {															//if element doesn't find in ui list it cannot be deleted

			std::list<GUI*> tree;
			BFS(tree, element);		//fills a list from element to delete to its childs using BFS algorithm

			for (std::list<GUI*>::reverse_iterator item_tree = tree.rbegin(); item_tree != tree.rend(); ++item_tree) {	//iterate list from bottom to top
				if ((*item_tree)->parent != nullptr) {				/*In the case the item has a parent we have first to delete the item of parent's child list*/
					std::list<GUI*>::iterator this_on_child = std::find((*item_tree)->parent->childs.begin(), (*item_tree)->parent->childs.end(), *item_tree);
					if (this_on_child != (*item_tree)->parent->childs.end()) {
						(*item_tree)->parent->childs.remove(*this_on_child);
					}
				}
				std::list<GUI*>::iterator elem = std::find(ui_list.begin(), ui_list.end(), *item_tree);	//find item on ui objects list
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

void j1UIManager::BFS(std::list<GUI*>& visited, GUI * elem)
{
	if (elem != nullptr) {
		std::queue<GUI*> frontier;
		GUI* item = nullptr;
		visited.push_back(elem);					//Add from we want to start to visited and frontier list
		frontier.push(elem);
		while (frontier.empty() == false) {
			if ((item = frontier.front()) != nullptr) {			//Pop las item of array
				frontier.pop();
				if(item->childs.empty() == false)
					for (std::list<GUI*>::iterator it = item->childs.begin(); it != item->childs.end(); ++it) { //iterate for all childs of node
						if (std::find(visited.begin(),visited.end(),*it) == visited.end()) {	//if child is not on visited list we added on it and on prontier to search its childs
							frontier.push(*it);
							visited.push_back(*it);
						}
					}
			}

		}
	}
}

bool j1UIManager::DeleteAllUIElements()
{
	bool ret = true;

	ret = DeleteUIElement(screen);
	CreateScreen();
	focus = nullptr;

	return ret;
}

bool j1UIManager::GetElemOnMouse(int x, int y, GUI *& element)
{
	std::list<GUI*> tree;
	BFS(tree, screen);

	for (std::list<GUI*>::reverse_iterator item = tree.rbegin(); item != tree.rend(); ++item) {
		if ((*item)->interactable)
		{
			if (CheckCollision(x, y, *item))
			{
				if ((*item)->current_state != Mouse_Event::CLICKED_DOWN && (*item)->current_state != Mouse_Event::CLICKED_REPEAT)
					App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) ? (*item)->current_state = Mouse_Event::CLICKED_DOWN : (*item)->current_state = Mouse_Event::HOVER;
				else {
					App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) ? (*item)->current_state = Mouse_Event::CLICKED_REPEAT : (*item)->current_state = Mouse_Event::CLICKED_UP;
				}
				element = *item;
				return true;
			}
			else {
				(*item)->current_state = Mouse_Event::NONE;
			}
		}
	}
	tree.clear();

	return false;
}

bool j1UIManager::CheckCollision(int x, int y, GUI *item)
{
	if (item != nullptr) {
		iPoint pos = item->GetGlobalPosition();
		return (x > pos.x && x < pos.x + item->section.w) &&
			(y > pos.y && y < pos.y + item->section.h);
	}
	return false;
}

void j1UIManager::UI_Events(GUI * element)
{
}