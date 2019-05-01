#ifndef __m1TEXTURES_H__
#define __m1TEXTURES_H__

#include "m1Module.h"
#include <map>
#include <list>

struct SDL_Texture;
struct SDL_Surface;

struct TextureData {
	std::string path;
	int dependence = 0;
};
class m1Textures : public m1Module
{
public:

	m1Textures();

	// Destructor
	virtual ~m1Textures();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before quitting
	bool CleanUp();
	
	// Load Texture
	SDL_Texture* const	Load(const char* path);
	bool				UnLoad(SDL_Texture* texture);
	SDL_Texture* const	LoadSurface(SDL_Surface* surface, const char* path);
	void				GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:
	
	typedef std::map<SDL_Texture*, TextureData> TextureMap;
	TextureMap textures;
};


#endif // __j1TEXTURES_H__