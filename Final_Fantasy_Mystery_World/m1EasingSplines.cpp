#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "m1Input.h"
#include "m1Textures.h"
#include "m1Render.h"
#include "m1MenuManager.h"
#include "m1Window.h"
#include "m1Map.h"
#include "m1EasingSplines.h"
#include <string>
#include "p2Log.h"

#include "Brofiler/Brofiler.h"

m1EasingSplines::m1EasingSplines() : m1Module()
{
	name.assign("easingsplines");
	
}

// Destructor
m1EasingSplines::~m1EasingSplines()
{

}

// Called each loop iteration
bool m1EasingSplines::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEasingSplines", Profiler::Color::Purple);

	std::list<EaseSplineInfo*>::iterator item = easing_splines.begin();

	for (; item != easing_splines.end(); ++item) {
		if (*item != nullptr) {
			if (!(*item)->Update(dt)) {
				delete(*item);
				(*item) = nullptr;
			}
		}
	}

	easing_splines.remove(nullptr);

	return true;
}

// Called before quitting
bool m1EasingSplines::CleanUp()
{
	LOG("Freeing scene");

	std::list<EaseSplineInfo*>::iterator item = easing_splines.begin();

	for (; item != easing_splines.end(); ++item) {
		if (*item != nullptr) {
			delete(*item);
			(*item) = nullptr;
		}
	}

	easing_splines.clear();

	return true;
}

EaseSplineInfo * m1EasingSplines::CreateSpline(int * position, const int target_position, const float time_to_travel, TypeSpline type, std::function<void()> fn)
{
	std::list <EaseSplineInfo*>::iterator item = easing_splines.begin();
	for (; item != easing_splines.end(); ++item) {
		if ((*item) != nullptr && (*item)->position == position) {
			(*item)->to_delete = true;
			break;
		}
	}

	EaseSplineInfo* info = DBG_NEW EaseSplineInfo(position, target_position, time_to_travel, type, fn);

	if (info != nullptr)
		easing_splines.push_back(info);
	else
		LOG("Could not create the Spline...");

	return info;
}




bool EaseSplineInfo::Update(float dt)
{
	bool ret = true;

	float time_passed = SDL_GetTicks() - time_started;

	if (time_passed < time_to_travel && !to_delete) {
		switch (type) {
		case EASE: {
			*position = ease_function.Ease(time_passed, initial_position, distance_to_travel, time_to_travel);
		} break;
		case EASE_OUT_QUINT: {
			*position = ease_function.EaseOutQuint(time_passed, initial_position, distance_to_travel, time_to_travel);
		} break;
		case EASE_IN_OUT_BACK: {
			*position = ease_function.EaseInOutBack(time_passed, initial_position, distance_to_travel, time_to_travel);
		} break;
		case EASE_IN_BACK: {
			*position = ease_function.EaseInBack(time_passed, initial_position, distance_to_travel, time_to_travel);
		} break;
		case EASE_OUT_BACK: {
			*position = ease_function.EaseOutBack(time_passed, initial_position, distance_to_travel, time_to_travel);
		} break;
		case EASE_IN_CUBIC: {
			*position = ease_function.EaseInCubic(time_passed, initial_position, distance_to_travel, time_to_travel);
		} break;
		case EASE_OUT_CUBIC: {
			*position = ease_function.EaseOutCubic(time_passed, initial_position, distance_to_travel, time_to_travel);
		} break;
		default:
			break;
		}
	}
	else {
		if (fn != nullptr)
			this->fn();
		ret = false;
	}
		
	
	return ret;
}


int EaseFunctions::EaseOutQuint(float time_passed, int initial_position, int distance_to_travel, float time_to_travel)
{
	return distance_to_travel * ((time_passed = time_passed / time_to_travel - 1)*time_passed*time_passed*time_passed*time_passed + 1) + initial_position;
}

int EaseFunctions::Ease(float time_passed, int initial_position, int distance_to_travel, float time_to_travel)
{
	return distance_to_travel * (time_passed / time_to_travel) + initial_position;
}

int EaseFunctions::EaseInOutBack(float time_passed, int initial_position, int distance_to_travel, float time_to_travel)
{
	float s = 1.70158f;
	if ((time_passed /= time_to_travel / 2) < 1) {
		return distance_to_travel / 2 * (time_passed*time_passed*(((s *= (1.525f)) + 1)*time_passed - s)) + initial_position;
	}
	else {
		float postFix = time_passed -= 2;
		return distance_to_travel / 2 * ((postFix)*time_passed*(((s *= (1.525f)) + 1)*time_passed + s) + 2) + initial_position;
	}
}

int EaseFunctions::EaseInBack(float time_passed, int initial_position, int distance_to_travel, float time_to_travel)
{
	float s = 1.70158f;
	float postFix = time_passed /= time_to_travel;
	return distance_to_travel * (postFix)*time_passed*((s + 1)*time_passed - s) + initial_position;
}

int EaseFunctions::EaseOutBack(float time_passed, int initial_position, int distance_to_travel, float time_to_travel)
{
	float s = 1.10158f;
	return distance_to_travel * ((time_passed = time_passed / time_to_travel - 1)*time_passed*((s + 1)*time_passed + s) + 1) + initial_position;
}

int EaseFunctions::EaseInCubic(float time_passed, int initial_position, int distance_to_travel, float time_to_travel)
{
	return distance_to_travel * (time_passed /= time_to_travel)*time_passed*time_passed + initial_position;
}

int EaseFunctions::EaseOutCubic(float time_passed, int initial_position, int distance_to_travel, float time_to_travel)
{
	return distance_to_travel * ((time_passed = time_passed / time_to_travel - 1)*time_passed*time_passed + 1) + initial_position;
}
