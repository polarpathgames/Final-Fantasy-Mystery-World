#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "p2Rooms.h"
#include "m1Render.h"
#include "m1Textures.h"
#include "m1Map.h"
#include <map>

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

m1Textures::m1Textures() : m1Module()
{
	name.assign("textures");
}

// Destructor
m1Textures::~m1Textures()
{}

// Called before render is available
bool m1Textures::Awake(pugi::xml_node& config)
{
	LOG("Init Image library");
	bool ret = true;
	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool m1Textures::Start()
{
	//LOG("start textures");
	bool ret = true;
	return ret;
}

// Called before quitting
bool m1Textures::CleanUp()
{
	LOG("Freeing textures and Image library");


	for (TextureMap::iterator item = textures.begin(); item != textures.end(); ++item) {
		SDL_DestroyTexture((*item).first);
		(*item).second.path.clear();
	}

	textures.clear();
	IMG_Quit();

	if (App->map->quest_rooms != nullptr) {
		std::vector<Room*>::iterator item = App->map->quest_rooms->rooms.begin();
		for (; item != App->map->quest_rooms->rooms.end(); ++item) {
			if ((*item) != nullptr) {
				delete (*item);
				(*item) = nullptr;
			}
		}
		delete App->map->quest_rooms;
		App->map->quest_rooms = nullptr;
	}
	return true;
}


// Load DBG_NEW texture from file path
SDL_Texture* const m1Textures::Load(const char* path)
{

	TextureMap::iterator item = textures.begin();
	for (; item != textures.end(); ++item) {
		if ((*item).first != nullptr && (*item).second.path.compare(path) == 0) {
			(*item).second.dependence++;
			return (*item).first;
		}
	}

	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = LoadSurface(surface, path);
		SDL_FreeSurface(surface);
	}

	return texture;
}

// Unload texture
bool m1Textures::UnLoad(SDL_Texture* texture)
{

	TextureMap::iterator item = textures.begin();
	while (item != textures.end()) {
		if ((*item).first != nullptr && (*item).first == texture) // if texture finded
		{
			if ((*item).second.dependence > 0) {	//if other object is using that texture
				(*item).second.dependence--;
				++item;
			}
			else {
				SDL_DestroyTexture((*item).first);
				(*item).second.path.clear();
				textures.erase(item);
				return true;
			}
		}
		else ++item;
	}

	return true;
}

// Translate a surface into a texture
SDL_Texture* const m1Textures::LoadSurface(SDL_Surface* surface, const char* path)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

	if (texture == NULL)
	{
		LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		textures.insert(std::make_pair(texture, TextureData{ path,0 }));
	}

	return texture;
}

// Retrieve size of a texture
void m1Textures::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*)&width, (int*)&height);
}