#ifndef __j1UIMANAGER_H__
#define __j1UIMANAGER_H__

#include "j1Module.h"
#include "p2Animation.h"


enum UI
{
	IMAGE,
	LABEL,
	NONE,
};

struct SDL_Texture;
struct SDL_Rect;

class GUI;

class j1UIManager: public j1Module
{
public:
	j1UIManager();
	virtual ~j1UIManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	//GUI* AddImage(int x, int y, SDL_Rect* rect);

	const SDL_Texture* GetAtlas() const;

private:
	SDL_Texture* atlas;

public:



};
#endif // !__j1UIMANAGER_H__
