#include "j1App.h"
#include "j1UIManager.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "GUI_Image.h"
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
	atlas = App->tex->Load("gui/mock_image.png");
	return true;
}

bool j1UIManager::PreUpdate()
{
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
	for (; item2 != ui_list.end(); ++item)
	{
		if ((*item2) != nullptr)
			(*item2)->Draw(atlas);
	}

	return true;
}

bool j1UIManager::PostUpdate()
{

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

GUI* j1UIManager::AddImage(int x, int y, SDL_Rect* rect)
{
	GUI* image = new GUI_Image(x, y, IMAGE, rect);
	ui_list.push_back(image);
	return image;
}

void j1UIManager::DestroyUI()
{
}


