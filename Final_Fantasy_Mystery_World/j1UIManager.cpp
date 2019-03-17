#include "j1App.h"
#include "j1UIManager.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "GUI_Image.h"
#include "GUI_Button.h"
#include "GUI_Label.h"
#include "GUI.h"

j1UIManager::j1UIManager(): j1Module()
{
}

j1UIManager::~j1UIManager() {}

bool j1UIManager::Awake(pugi::xml_node &node)
{

	return true;
}

bool j1UIManager::Start()
{
atlas = App->tex->Load("gui/atlas.png");
return true;
}

bool j1UIManager::PreUpdate()
{
	std::list<GUI*>::iterator item = ui_list.begin();
	for (; item != ui_list.end(); ++item)
	{
		if ((*item) != nullptr)
			(*item)->PreUpdate();
	}

	return true;
}

bool j1UIManager::Update(float dt)
{
	std::list<GUI*>::iterator item = ui_list.begin();
	for (; item != ui_list.end(); ++item)
	{
		if ((*item) != nullptr)
			(*item)->Update(dt);
	}

	std::list<GUI*>::iterator item2 = ui_list.begin();
	for (; item2 != ui_list.end(); ++item2)
	{
		if ((*item2) != nullptr)
			(*item2)->Draw(atlas);
	}

	return true;
}

bool j1UIManager::PostUpdate()
{
	std::list<GUI*>::iterator item = ui_list.begin();
	for (; item != ui_list.end(); ++item)
	{
		if ((*item) != nullptr)
			(*item)->PostUpdate();
	}

	return true;
}

bool j1UIManager::CleanUp()
{
	std::list<GUI*>::iterator item = ui_list.begin();
	for (; item != ui_list.end(); ++item) {
		if ((*item) != nullptr) {
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
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

GUI* j1UIManager::AddImage(int x, int y, SDL_Rect* rect, Animation* anim, j1Module* callback, GUI* parent)
{
	GUI* image = new GUI_Image(x, y, IMAGE, parent, anim, callback, rect);

	if (image != nullptr)
	{
		ui_list.push_back(image);
	}

	return image;
}

GUI* j1UIManager::AddButton(int x, int y, SDL_Rect normal, SDL_Rect mouse_in, SDL_Rect clicked, j1Module* callback, GUI* parent)
{
	GUI* button = new GUI_Button(x, y, normal, mouse_in, clicked, callback, BUTTON, parent);
	ui_list.push_back(button);
	return button;
}

GUI* j1UIManager::AddLabel(int x, int y, std::string text, j1Module* callback, GUI* parent)
{
	GUI* label = new Gui_Label(x, y, text, callback, LABEL, parent);
	ui_list.push_back(label);
	return label;
}

void j1UIManager::DestroyUI()
{
	std::list<GUI*>::iterator item = ui_list.begin();
	for (; item != ui_list.end(); ++item)
	{
		if ((*item) != nullptr)
		{
			(*item)->CleanUp();
			delete(*item);
			(*item) = nullptr;
		}
	}

	ui_list.clear();
}


