#ifndef __j1FONTS_H__
#define __j1FONTS_H__

#include "j1Module.h"
#include <list>
#include "SDL\include\SDL_pixels.h"

#define DEFAULT_PATH "fonts/"
#define DEFAULT_FONT "Final_Fantasy_font.ttf"
#define DEFAULT_FONT_SIZE 36

struct SDL_Texture;
struct _TTF_Font;

enum class FontType {
	FINAL_FANTASY = 0,
	PIXELMIX = 1,

	NONE
};

struct Font {
	Font() {}
	Font(_TTF_Font* font, FontType type) :font(font), type(type) {}
	_TTF_Font* font = nullptr;
	FontType type = FontType::NONE;
};

class j1Fonts : public j1Module
{
public:

	j1Fonts();

	// Destructor
	virtual ~j1Fonts();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Load Font
	Font const Load(const char* path, int size = 12);
	bool UnLoad(FontType font);

	bool FindFont(FontType font_type, _TTF_Font* font = nullptr);

	// Create a surface from text
	SDL_Texture* Print(const char* text, SDL_Color color = { 255, 255, 255, 255 }, FontType type);
	SDL_Texture* PrintWrapped(const char* text, SDL_Color color, _TTF_Font* font, Uint32 wrap_length);
	bool CalcSize(const char* text, int& width, int& height, _TTF_Font* font = NULL) const;

public:

	std::list<Font>	fonts;
	Font			default;
};


#endif // __j1FONTS_H__