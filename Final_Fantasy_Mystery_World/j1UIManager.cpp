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
#include "GUI.h"

#include <queue>

j1UIManager::j1UIManager(): j1Module()
{
	name.assign("gui");
}

j1UIManager::~j1UIManager() {}

bool j1UIManager::Awake(pugi::xml_node &node)
{
	CreateScreen();

	return true;
}

bool j1UIManager::Start()
{
	atlas = App->tex->Load("gui/atlas.png");
	return true;
}

bool j1UIManager::PreUpdate()
{
	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		debug_ui = !debug_ui;
	}

	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);
	GUI* element = nullptr;
	if (GetElemOnMouse(mouse.x*App->win->GetScale(), mouse.y*App->win->GetScale(), element)) {//Check if there is an element on Mouse
		ret = element->Update();
	}

	return ret;
}

bool j1UIManager::PostUpdate()
{
	bool ret = true;
	std::list<GUI*>::iterator item = ui_list.begin();
	for (; item != ui_list.end(); ++item)
	{
		if ((*item) != nullptr) {
			if ((*item)->to_delete) {
				ret = DeleteUIElement(*item);
			}
			else {
				ret = (*item)->PostUpdate();
			}
		}
	}

	std::list<GUI*> tree;
	BFS(tree, screen);

	for (std::list<GUI*>::iterator item = tree.begin(); item != tree.end(); item++) {
		(*item)->Draw();
		if (debug_ui) {
			(*item)->DebugDraw();
		}
	}

	return ret;
}

bool j1UIManager::CleanUp()
{
	std::list<GUI*>::iterator item = ui_list.begin();
	for (; item != ui_list.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			RELEASE(*item);
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

GUI_Image* j1UIManager::AddImage(const int &x,const int &y, const SDL_Rect & rect = {0,0,0,0}, j1Module * callback = nullptr, GUI * parent = nullptr, bool draw = true, bool drag = false, bool interact = false)
{
	GUI_Image* image = new GUI_Image(x, y, rect, parent);

	if (callback != nullptr) {
		image->AddListener(callback);
	}

	ui_list.push_back(image);

	return image;
}

GUI_Button* j1UIManager::AddButton(const int &x, const int &y, const SDL_Rect &idle, const SDL_Rect &mouse_in, const SDL_Rect &clicked, j1Module* callback, GUI* parent)
{
	GUI_Button* button = new GUI_Button(x, y, idle, mouse_in, clicked, parent);

	if (callback != nullptr) {
		button->AddListener(callback);
	}

	ui_list.push_back(button);
	
	return button;
}

GUI_Label* j1UIManager::AddLabel(const int &x, const int &y, const char* text, uint size, GUI* parent, Color color, const char* font, j1Module* callback = nullptr)
{
	GUI_Label* label = new GUI_Label(x, y, text, color, font, size, parent);

	if (callback != nullptr) {
		label->AddListener(callback);
	}

	ui_list.push_back(label);
	
	return label;
}

void j1UIManager::CreateScreen()
{
	if (std::find(ui_list.begin(), ui_list.end(), screen) == ui_list.end()) {
		screen = AddImage(0, 0, { 0,0,(int)App->win->width,(int)App->win->height }, nullptr, nullptr, false);
	}
}

bool j1UIManager::DeleteUIElement(GUI * element)
{
	std::list<GUI*>::iterator item_ui = std::find(ui_list.begin(), ui_list.end(), element);
	if (item_ui != ui_list.end()) {															//if element doesn't find in ui list it cannot be deleted

		std::list<GUI*> tree;
		BFS(tree, element);		//fills a list from element to delete to its childs using BFS algorithm

		for (std::list<GUI*>::reverse_iterator item_tree = tree.rbegin(); item_tree != tree.rend(); ++item_tree) {	//iterate list from bottom to top
			//if (item_tree.base() == tree.begin() && (*item_tree)->parent != nullptr) {				/*In case the item we will delete is the first element of the tree
			//																		we have to delete him first from its parent child list
			//																		the reason why we don't made that for other nodes is becuase
			//																		other nodes and its parents will be deleted for complete*/
			//	std::list<GUI*>::iterator this_on_child = std::find((*item_tree)->parent->childs.begin(), (*item_tree)->parent->childs.end(), *item_tree);
			//	if (this_on_child != (*item_tree)->parent->childs.end()) {
			//		(*item_tree)->parent->childs.remove(*this_on_child);
			//	}
			//}
			std::list<GUI*>::iterator elem = std::find(ui_list.begin(),ui_list.end(),*item_tree);	//find item on ui objects list
			if (elem != ui_list.end()) {						//if it is valid
				ui_list.remove(*elem);
				delete *elem;
				*elem = nullptr;						//delete from list
														//delete item->data;						//and deallocate memory
			}
		}
		tree.clear();

		return true;
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
					for (std::list<GUI*>::iterator it = item->childs.begin(); it != item->childs.end(); ++it) { //iterate for all childs of node
						//if (std::find(visited.begin(),visited.end(),it) == visited.end()) {	//if child is not on visited list we added on it and on prontier to search its childs
						//	frontier.push(*it);
						//	visited.push_back(*it);
						//}
					}
			}

		}
	}
}

bool j1UIManager::DeleteAllUIElements()
{
	bool ret = true;

	ret = DeleteUIElement(screen);

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