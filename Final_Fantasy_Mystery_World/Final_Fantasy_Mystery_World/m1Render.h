#ifndef __m1RENDER_H__
#define __m1RENDER_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "m1Module.h"
#include <random>


class m1Render : public m1Module
{
public:

	m1Render();

	// Destructor
	virtual ~m1Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	// Blit
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	bool Blit(SDL_Texture* texture, float x, float y, const SDL_Rect* section = NULL, bool apply_scale = false, SDL_RendererFlip flip = SDL_FLIP_NONE, float speed = 1.0f, const SDL_Rect* clip_zone = NULL,double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	
	iPoint ScreenToWorld(int x, int y) const;

	bool IsOnCamera(const int&x, const int&y, const int&w, const int& h) const;
	void ResetCamera();

	void SmoothCamera(iPoint playerpos);
	void CenterCameraOnPlayer(iPoint playerpos);


	//Joss Tremble Camera Logic
	float CameraTremble(float value, float traumaDecay);
	float GetShakeAmount() const;
	float GetFloatNegOneToOne();

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
	float trauma = 0;
	float traumaDecay = 2.2f;
	float maxOffset = 16.f;
	iPoint preShakePos;
	bool debug = false;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	bool vsync = false;

public:

	SDL_Renderer*	renderer;
	SDL_Rect		camera;
	SDL_Rect		viewport;
	SDL_Color		background;
	fPoint			smoth_position = { 0,0 };
	float			smooth_speed = 0.3f;
	SDL_Surface*	surface = NULL;

	

	//DEBUG ZOOM
	int				zoom = 1;
	int				max_zoom = 4;
	bool			debug_border = false;
};

#endif // __j1RENDER_H__