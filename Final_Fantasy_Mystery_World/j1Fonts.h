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
	FF32,
	FF48,
	FF64,
	PMIX32,
	PMIX48,
	PMIX64,

	NONE
};

struct Font {
	Font() {}
	Font(_TTF_Font* font, FontType type, const char* name, uint size = DEFAULT_FONT_SIZE) :font(font), type(type), name(name), size(size) {}
	Font(_TTF_Font* font, FontType type) :font(font), type(type), name("none"), size(DEFAULT_FONT_SIZE) {}

	std::string name =	"none";
	_TTF_Font* font =	nullptr;
	FontType type =		FontType::NONE;
	uint size =			DEFAULT_FONT_SIZE;

	bool operator==(const Font& other) {
		if (this->type == other.type && size == other.size)
			return true;
		return false;
	}
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
	Font* const Load(const char* path, int size = DEFAULT_FONT_SIZE);
	bool UnLoad(FontType font);

	std::list<Font*>::const_iterator FindIdFont(FontType font_type);
	std::list<Font*>::const_iterator FindPathFont(const char* name, const int& size = 0);

	// Create a surface from text
	SDL_Texture* Print(const char* text, SDL_Color color = { 255, 255, 255, 255 }, FontType type = FontType::NONE);
	SDL_Texture* PrintWrapped(const char* text, SDL_Color color, FontType type, Uint32 wrap_length);
	bool ChangeFontSize(const int& size);
	bool CalcSize(const char* text, int& width, int& height, FontType font);

public:

	std::list<Font*>	fonts;
	Font*				default;
};


#endif // __j1FONTS_H__