#include "p2Defs.h"
#include "p2Log.h"
#include "App.h"
#include "m1Input.h"
#include "m1Textures.h"
#include "m1Render.h"
#include "m1Window.h"
#include "m1Map.h"
#include "m1EasingSplines.h"
#include <string>
#include "p2Log.h"

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
	std::list<EaseSplineInfo*>::iterator item = easing_splines.begin();

	for (; item != easing_splines.end(); ++item) {
		if (*item != nullptr) {
			if (!(*item)->Update(dt)) {
				//easing_splines.erase(item); // look this, not sure :(
				delete(*item);
				(*item) = nullptr;
			}
		}
	}

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
			easing_splines.erase(item);
		}
	}

	easing_splines.clear();

	return true;
}

void m1EasingSplines::CreateSpline(int * position, const int target_position, const float time_to_travel, TypeSpline type)
{
	EaseSplineInfo* info = new EaseSplineInfo(position, target_position, time_to_travel, type);

	if (info != nullptr)
		easing_splines.push_back(info);
	else
		LOG("Could not create the Spline...");
}




bool EaseSplineInfo::Update(float dt)
{
	bool ret = true;

	float time_passed = SDL_GetTicks() - time_started;

	if (time_passed < time_to_travel) {
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
		default:
			break;
		}
	}
	else 
		ret = false;
	
	return ret;
}

int EaseFunctions::EaseOutQuint(float time_passed, int initial_position, int distance_to_travel, float time_to_travel)
{
	return distance_to_travel * ((time_passed = time_passed / time_to_travel - 1)*time_passed*time_passed*time_passed*time_passed + 1) + initial_position;;
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
