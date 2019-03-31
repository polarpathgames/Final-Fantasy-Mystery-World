#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Fonts.h"

#include "SDL\include\SDL.h"
#include "SDL_TTF\include\SDL_ttf.h"
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )

j1Fonts::j1Fonts() : j1Module()
{
	name.assign("fonts");
}

// Destructor
j1Fonts::~j1Fonts()
{}

// Called before render is available
bool j1Fonts::Awake(pugi::xml_node& conf)
{
	LOG("Init True Type Font library");
	bool ret = true;

	if (TTF_Init() == -1)
	{
		LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		ret = false;
	}
	else
	{
		const char* path = conf.child("path").attribute("folder").as_string(DEFAULT_PATH);
		const char* font = conf.child("default_font").attribute("file").as_string(DEFAULT_FONT);
		int size = conf.child("default_font").attribute("size").as_int(DEFAULT_FONT_SIZE);
		default = Load(PATH(path,font), size);

		for (conf = conf.child("font"); conf; conf = conf.next_sibling()) {
			Load(PATH(path, conf.attribute("file").as_string()));
		}
	}

	return ret;
}

// Called before quitting
bool j1Fonts::CleanUp()
{
	LOG("Freeing True Type fonts and library");

	std::list<Font*>::iterator item = fonts.begin();

	for (; item != fonts.end(); ++item)
	{
		TTF_CloseFont((*item)->font);
		delete *item;
		*item = nullptr;
	}

	fonts.clear();
	TTF_Quit();
	return true;
}

// Load new texture from file path
Font* const j1Fonts::Load(const char* path, int size)
{
	Font* ret = nullptr;
	std::list<Font*>::const_iterator item = FindPathFont(path);
	
	if (item != fonts.end()) {
		LOG("Already loaded font with ID %i", (*item)->type);
		ret = *item;
	}
	else {
		ret = new Font(TTF_OpenFont(path, size), (FontType)fonts.size(), path);
		if (ret->font == NULL) {
			LOG("Could not load TTF font with path: %s. TTF_OpenFont: %s. Closing and using default font", path, TTF_GetError());
			TTF_CloseFont(ret->font);
			delete ret;
			ret = default;
		}
		else
		{
			LOG("Successfully loaded font %s size %d", path, size);
			fonts.push_back(ret);
		}
	}
	
	return ret;
}

bool j1Fonts::UnLoad(FontType font)
{
	std::list<Font*>::const_iterator item;
	if ((item = FindIdFont(font)) != fonts.end()) {
		TTF_CloseFont((*item)->font);
		delete *item;
		fonts.remove(*item);
	}
	else {
		LOG("Could not found font to delete with id %i", (int)font);
	}

	return true;
}

std::list<Font*>::const_iterator j1Fonts::FindIdFont(FontType font_type)
{
	for (std::list<Font*>::iterator item = fonts.begin(); item != fonts.end(); ++item) {
		if ((*item)->type == font_type) {
			return item;
		}
	}
	LOG("No Font found with id %i", (int)font_type);
	return fonts.end();
}

std::list<Font*>::const_iterator j1Fonts::FindPathFont(const char* name)
{
	for (std::list<Font*>::iterator item = fonts.begin(); item != fonts.end(); ++item) {
		if (strcmp(name,(*item)->name.data()) == 0) {
			return item;
		}
	}
	LOG("No Font found with name %s", name);
	return fonts.end();
}

// Print text using font
SDL_Texture* j1Fonts::Print(const char* text, SDL_Color color, FontType font_type)
{
	SDL_Texture* ret = NULL;

	std::list<Font*>::const_iterator item;
	SDL_Surface* surface = TTF_RenderText_Blended(((item = FindIdFont(font_type))!=fonts.end()) ? (*item)->font : default->font, text, color);

	if (surface == NULL)
	{
		LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		ret = App->tex->LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return ret;
}

SDL_Texture* j1Fonts::PrintWrapped(const char* text, SDL_Color color, FontType font_type, Uint32 wrap_length)
{
	SDL_Texture* ret = NULL;
	std::list<Font*>::const_iterator item;
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(((item = FindIdFont(font_type)) != fonts.end()) ? (*item)->font : default->font, text, color, wrap_length);
	SDL_SetSurfaceAlphaMod(surface, color.a);

	if (surface == NULL)
	{
		LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		ret = App->tex->LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return ret;
}

// calculate size of a text
bool j1Fonts::CalcSize(const char* text, int& width, int& height, FontType font_type)
{
	bool ret = false;
	std::list<Font*>::const_iterator item;
	if (TTF_SizeText(((item = FindIdFont(font_type)) != fonts.end()) ? (*item)->font : default->font, text, &width, &height) != 0)
		LOG("Unable to calc size of text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else
		ret = true;

	return ret;
}