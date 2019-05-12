#ifndef P2Math
#define P2Math

#include "p2Point.h"

float lerp(const float& origin, const float& end, float by);
p2Point<float> lerp(const p2Point<int>& origin, const p2Point<int>& end, const float& by);

#endif // !P2Math