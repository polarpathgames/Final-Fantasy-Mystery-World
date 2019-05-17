#include "p2Math.h"
#include "p2Point.h"
#include <math.h>
#include "p2Point.h"

float lerp(const float & origin, const float & end, float by)
{
	if (by > 1.0f) by = 1.0f;
	return origin * (1.0f - by) + end * by;
}

p2Point<float> lerp(const p2Point<int> & origin, const p2Point<int> & end, const float & by)
{
	return p2Point<float>(lerp(origin.x, end.x, by), lerp(origin.y, end.y, by));
}

double DegToRad(const double & value)
{
	return (value * M_PI) / 180;
}

double RadToDeg(const double & value)
{
	return (value * 180) / M_PI;
}
