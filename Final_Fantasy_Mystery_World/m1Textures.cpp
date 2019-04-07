#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "m1Render.h"
#include "m1Textures.h"
#include <list>

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


	for (std::list<SDL_Texture*>::iterator item = textures.begin(); item != textures.end(); ++item) {
		SDL_DestroyTexture(*item);
	}

	textures.clear();
	IMG_Quit();
	return true;
}


// Load new texture from file path
SDL_Texture* const m1Textures::Load(const char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return texture;
}

// Unload texture
bool m1Textures::UnLoad(SDL_Texture* texture)
{

	for (std::list<SDL_Texture*>::iterator item = textures.begin(); item != textures.end(); ++item) {
		if (texture == *item)
		{
			SDL_DestroyTexture(*item);
			textures.erase(item);
			return true;
		}
	}

	return false;
}

// Translate a surface into a texture
SDL_Texture* const m1Textures::LoadSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(app->render->renderer, surface);

	if (texture == NULL)
	{
		LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		textures.push_back(texture);
	}

	return texture;
}

// Retrieve size of a texture
void m1Textures::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*)&width, (int*)&height);
}