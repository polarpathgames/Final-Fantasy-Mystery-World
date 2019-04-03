#ifndef __P2LINE_H__
#define __P2LINE_H__

#include "p2Defs.h"
#include <math.h>

template<class TYPE>
class p2Line
{
public:

	TYPE x1, y1, x2, y2;

	p2Line()
	{}

	p2Line(const p2Line<TYPE>& v)
	{
		this->x1 = v.x1;
		this->y1 = v.y1;
		this->x2 = v.x2;
		this->y2 = v.y2;
	}

	p2Line(const TYPE& x1, const TYPE& y1, const TYPE& x2, const TYPE& y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	p2Line& create(const TYPE& x1, const TYPE& y1, const TYPE& x2, const TYPE& y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;

		return(*this);
	}

	p2Line operator -(const p2Line &v) const
	{
		p2Line r;

		r.x1 = x1 - v.x1;
		r.y1 = y1 - v.y1;
		r.x2 = x2 - v.x2;
		r.y2 = y2 - v.y2;

		return(r);
	}

	p2Line operator + (const p2Line &v) const
	{
		p2Line r;

		r.x1 = x1 + v.x1;
		r.y1 = y1 + v.y1;
		r.x2 = x2 + v.x2;
		r.y2 = y2 + v.y2;

		return(r);
	}

	const p2Line& operator -=(const p2Line &v)
	{
		x1 -= v.x1;
		y1 -= v.y1;
		x2 -= v.x2;
		y2 -= v.y2;

		return(*this);
	}

	const p2Line& operator +=(const p2Line &v)
	{
		x1 += v.x1;
		y1 += v.y1;
		x2 += v.x2;
		y2 += v.y2;

		return(*this);
	}

	bool operator ==(const p2Line& v) const
	{
		return (x1 == v.x1 && y1 == v.y1 && x2 == v.x2 && y2 == v.y2);
	}

	bool operator !=(const p2Line& v) const
	{
		return (x1 != v.x1 || y1 != v.y1 || x2 != v.x2 || y2 != v.y2);
	}

	p2Line& SetToZero()
	{
		x1 = y1 = x2 = y2 = 0;
		return(*this);
	}

	p2Line& Negate()
	{
		x1 = -x1;
		y1 = -y1;
		x2 = -x2;
		y2 = -y2;

		return(*this);
	}

};

typedef p2Line<int> iLine;
typedef p2Line<float> fLine;

#endif
