#ifndef __P2ANIMATION_H__
#define __P2ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#include <vector>

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	std::vector<SDL_Rect> frames;

public:
	float current_frame = 0.0f;
	int loops = 0;

public:

	Animation()
	{}

	Animation(const Animation& anim) : loop(anim.loop), speed(anim.speed)
	{}

	void PushBack(const SDL_Rect& rect)
	{
		frames.push_back(rect);
	}

	SDL_Rect& GetCurrentFrame(float dt)
	{
		current_frame += speed * dt;
		if (current_frame >= frames.size())
		{
			current_frame = (loop) ? 0.0f : frames.size() - 1;
			loops++;
		}
		return frames[(int)current_frame];
	}
	
	SDL_Rect GetFrame(const int & frame_num) {
		return frames[frame_num];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		loops = 0;
		current_frame = 0.0f;
	}

	int SeeCurrentFrame() {
		return (int)current_frame;
	}
};

#endif
