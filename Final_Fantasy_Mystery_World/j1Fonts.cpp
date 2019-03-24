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

	std::list<Font>::iterator item = fonts.begin();

	for (; item != fonts.end(); item = ++item)
	{
		TTF_CloseFont((*item).font);
	}

	fonts.clear();
	TTF_Quit();
	return true;
}

// Load new texture from file path
Font const j1Fonts::Load(const char* path, int size)
{
	Font font(TTF_OpenFont(path, size),(FontType)fonts.size());

	if (font.font == NULL)
	{
		LOG("Could not load TTF font with path: %s. TTF_OpenFont: %s", path, TTF_GetError());
	}
	else if (FindFont(font.type)) {
		LOG("Already loaded font with ID %i", font.type);
		TTF_CloseFont(font.font);
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
	_TTF_Font* font_font = nullptr;
	if (FindFont(font, font_font)) {
		fonts.remove(Font(font_font,font));
		TTF_CloseFont(font_font);
	}

	return true;
}

bool j1Fonts::FindFont(FontType font_type, _TTF_Font * font)
{
	for (std::list<Font>::iterator item = fonts.begin(); item != fonts.end(); ++item) {
		if ((*item).type == font_type) {
			font = (*item).font;
			return true;
		}
	}
	return false;
}

// Print text using font
SDL_Texture* j1Fonts::Print(const char* text, SDL_Color color, FontType font)
{
	SDL_Texture* ret = NULL;
	SDL_Surface* surface = nullptr;

	std::list<Font>::iterator item = fonts.begin();
	for (; item != fonts.end(); ++item) {
		if ((*item).type == font) {
			 surface = TTF_RenderText_Blended((*item).font, text, color);
		}
	}
	if (item == fonts.end()) {
		surface = TTF_RenderText_Blended(default.font, text, color);
	}

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

SDL_Texture* j1Fonts::PrintWrapped(const char* text, SDL_Color color, _TTF_Font* font, Uint32 wrap_length)
{
	SDL_Texture* ret = NULL;

	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped((font) ? font : default.font, text, color, wrap_length);
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
bool j1Fonts::CalcSize(const char* text, int& width, int& height, _TTF_Font* font) const
{
	bool ret = false;

	if (TTF_SizeText((font) ? font : default.font, text, &width, &height) != 0)
		LOG("Unable to calc size of text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else
		ret = true;

	return ret;
}