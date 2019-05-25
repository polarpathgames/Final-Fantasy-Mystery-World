#pragma once
#ifndef __P2MATH_H__
#define __P2MATH_H__
#include "p2Point.h"
#define _USE_MATH_DEFINES


float lerp(const float& origin, const float& end, float by);
p2Point<float> lerp(const p2Point<int>& origin, const p2Point<int>& end, const float& by);

double DegToRad(const double& value);
double RadToDeg(const double& value);

#endif // !P2Math