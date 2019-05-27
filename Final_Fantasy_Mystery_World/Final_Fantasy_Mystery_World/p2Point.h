// ----------------------------------------------------
// Point class    -----------
// ----------------------------------------------------

#ifndef __P2POINT_H__
#define __P2POINT_H__

#include "p2Defs.h"
#include <math.h>

template<class TYPE>
class p2Point
{
public:

	TYPE x, y;

	p2Point()
	{}

	p2Point(const p2Point<TYPE>& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	p2Point(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;
	}

	p2Point& create(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;

		return(*this);
	}

	// Math ------------------------------------------------
	p2Point operator -(const p2Point &v) const
	{
		p2Point r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	p2Point operator + (const p2Point &v) const
	{
		p2Point r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	const p2Point& operator -=(const p2Point &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const p2Point& operator +=(const p2Point &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}

	p2Point operator *(const int &mult) {
		p2Point r;

		r.x = x * mult;
		r.y = y * mult;

		return(r);
	}

	const p2Point& operator *=(const int &mult)
	{
		x *= mult;
		y *= mult;

		return(*this);
	}

	p2Point operator *(const float &mult) {
		p2Point r;

		r.x = x * mult;
		r.y = y * mult;

		return(r);
	}

	const p2Point& operator *=(const float &mult)
	{
		x *= mult;
		y *= mult;

		return(*this);
	}

	bool operator ==(const p2Point& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const p2Point& v) const
	{
		return (x != v.x || y != v.y);
	}

	// Utils -----------------------------------------------

	int Cross(p2Point& v) {
		return x * v.y - y * v.x;
	}

	p2Point& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	void normalize() {
		float module = sqrtf(x * x + y * y);
		x /= module;
		y /= module;
	}

	p2Point& zero() {
		x = y = (TYPE)0;
		return(*this);
	}

	bool is_zero() const {
		return(x == (TYPE)0 && y == (TYPE)0);
	}


	// Distances ---------------------------------------------
	TYPE DistanceTo(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return sqrtf((fx*fx) + (fy*fy));
	}

	TYPE DistanceNoSqrt(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (fx*fx) + (fy*fy);
	}

	TYPE DistanceManhattan(const p2Point& v) const
	{
		return abs(v.x - x) + abs(v.y - y);
	}

	p2Point<int> AproximateToIntFloor() const {
		return p2Point<int>(floor(x), floor(y));
	}

	p2Point<int> AproximateToIntCast() const {
		return p2Point<int>((int)x, (int)y);
	}

	p2Point<float> AproximateToFloat() const {
		return p2Point<float>((float)x, (float)y);
	}
};

typedef p2Point<int> iPoint;
typedef p2Point<float> fPoint;

#endif // __P2POINT_H__