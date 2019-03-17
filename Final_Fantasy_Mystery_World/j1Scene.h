#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
struct SDL_Rect;

class GUI;
class GUI_Image;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void CreateEntities();

public:

	//GUI* mock_image_ui = nullptr;
	//SDL_Rect mock_image_rect = { 0, 0, 61, 76 };
	GUI* background = nullptr;
	bool first_update = true;
};

#endif // __j1SCENE_H__