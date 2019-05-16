#ifndef __m1EASINGSPLINES_H__
#define __m1EASINGSPLINES_H__

#include "m1Module.h"
#include <list>
#include "SDL/include/SDL_timer.h"
#include <functional>

struct SDL_Texture;
struct SDL_Rect;

enum TypeSpline {

	EASE,
	EASE_OUT_QUINT,
	EASE_IN_OUT_BACK,
	EASE_IN_BACK,
	EASE_OUT_BACK,
	EASE_IN_CUBIC,
	EASE_OUT_CUBIC,

	NONE_
};

struct EaseFunctions {
	int EaseOutQuint(float time_passed, int initial_position, int distance_to_travel, float time_to_travel);
	int Ease(float time_passed, int initial_position, int distance_to_travel, float time_to_travel);
	int EaseInOutBack(float time_passed, int initial_position, int distance_to_travel, float time_to_travel);
	int EaseInBack(float time_passed, int initial_position, int distance_to_travel, float time_to_travel);
	int EaseOutBack(float time_passed, int initial_position, int distance_to_travel, float time_to_travel);
	int EaseInCubic(float time_passed, int initial_position, int distance_to_travel, float time_to_travel);
	int EaseOutCubic(float time_passed, int initial_position, int distance_to_travel, float time_to_travel);
};

struct EaseSplineInfo {
	int * position = nullptr;
	TypeSpline type;
	int initial_position;
	int distance_to_travel;
	float time_to_travel;
	float time_started;
	EaseFunctions ease_function;
	bool to_delete = false;
	bool Update(float dt);
	//m1MenuManager void(*funct)() = nullptr;
	//m1MenuManager::void(*funct)();
	std::function<void()> fn;

	EaseSplineInfo(int * position, const int target_position, const float time_to_travel, TypeSpline type, std::function<void()> fn) {
		this->position = position;
		this->initial_position = *position;
		this->distance_to_travel = target_position - *position;
		this->type = type;
		this->time_to_travel = time_to_travel;
		this->fn = fn;
		time_started = SDL_GetTicks();
	}

};

class m1EasingSplines : public m1Module
{
public:

	m1EasingSplines();

	// Destructor
	virtual ~m1EasingSplines();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	EaseSplineInfo* CreateSpline(int * position, int target_position, const float time_to_travel, TypeSpline type, std::function<void()> fn = nullptr);

private:

	std::list<EaseSplineInfo*> easing_splines;

};

#endif 