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
	Font* font = new Font(TTF_OpenFont(path, size),(FontType)fonts.size(), path);
	std::list<Font*>::iterator item;
	if (font->font == NULL)
	{
		LOG("Could not load TTF font with path: %s. TTF_OpenFont: %s", path, TTF_GetError());
		TTF_CloseFont(font->font);
		delete font;
		font = *fonts.begin();
	}
	else if (FindPathFont(path, item)) {
		LOG("Already loaded font with ID %i", font->type);
		TTF_CloseFont(font->font);
		delete font;
		font = *fonts.begin();
	}
	else
	{
		LOG("Successfully loaded font %s size %d", path, size);
		fonts.push_back(font);
	}

	return font;
}

bool j1Fonts::UnLoad(FontType font)
{
	std::list<Font*>::iterator font_item;
	if (FindIdFont(font, font_item)) {
		TTF_CloseFont((*font_item)->font);
		delete *font_item;
		*font_item = nullptr;
		fonts.remove(nullptr);
	}
	else {
		LOG("Could not found font to delete with id %i", (int)font);
	}

	return true;
}

bool j1Fonts::FindIdFont(FontType font_type, std::list<Font*>::iterator &font)
{
	for (std::list<Font*>::iterator item = fonts.begin(); item != fonts.end(); ++item) {
		if ((*item)->type == font_type) {
			font = item;
			return true;
		}
	}
	LOG("No Font found with id %i", (int)font_type);
	font = fonts.begin();
	return false;
}

bool j1Fonts::FindPathFont(const char* name, std::list<Font*>::iterator &font)
{
	for (std::list<Font*>::iterator item = fonts.begin(); item != fonts.end(); ++item) {
		if (strcmp(name,(*item)->name.data()) == 0) {
			font = item;
			return true;
		}
	}
	LOG("No Font found with name %s", name);
	font = fonts.begin();
	return false;
}

// Print text using font
SDL_Texture* j1Fonts::Print(const char* text, SDL_Color color, FontType font_type)
{
	SDL_Texture* ret = NULL;

	std::list<Font*>::iterator item;
	SDL_Surface* surface = TTF_RenderText_Blended((FindIdFont(font_type,item)) ? (*item)->font : default->font, text, color);

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

SDL_Texture* j1Fonts::PrintWrapped(const char* text, SDL_Color color, FontType type, Uint32 wrap_length)
{
	SDL_Texture* ret = NULL;
	std::list<Font*>::iterator item;
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped((FindIdFont(type, item)) ? (*item)->font : default->font, text, color, wrap_length);
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
bool j1Fonts::CalcSize(const char* text, int& width, int& height, FontType type)
{
	bool ret = false;
	std::list<Font*>::iterator item;
	if (TTF_SizeText((FindIdFont(type, item)) ? (*item)->font : default->font, text, &width, &height) != 0)
		LOG("Unable to calc size of text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else
		ret = true;

	return ret;
}