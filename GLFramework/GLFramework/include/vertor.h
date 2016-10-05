/************************************************************************
* @author yffei
*
************************************************************************/
#pragma once
#include <stdio.h>
#include <stdlib.h>

struct FFVector2f
{
	float x;
	float y;

	FFVector2f()
	{
	}

	FFVector2f(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};


struct FFVector3f
{
	float x;
	float y;
	float z;

	FFVector3f() {}

	FFVector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	FFVector3f(const float* pFloat)
	{
		x = pFloat[0];
		y = pFloat[0];
		z = pFloat[0];
	}

	FFVector3f(float f)
	{
		x = y = z = f;
	}

	FFVector3f& operator+=(const FFVector3f& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	FFVector3f& operator-=(const FFVector3f& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	FFVector3f& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	operator const float*() const
	{
		return &(x);
	}


	FFVector3f Cross(const FFVector3f& v) const;

	FFVector3f& Normalize();

	void Rotate(float Angle, const FFVector3f& Axis);

	void Print() const
	{
		printf("(%.02f, %.02f, %.02f)", x, y, z);
	}
};


struct FFVector4f
{
	float x;
	float y;
	float z;
	float w;

	FFVector4f()
	{
	}

	FFVector4f(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Print(bool endl = true) const
	{
		printf("(%.02f, %.02f, %.02f, %.02f)", x, y, z, w);

		if (endl) {
			printf("\n");
		}
	}

	FFVector3f to3f() const
	{
		FFVector3f v(x, y, z);
		return v;
	}
};



inline FFVector3f operator+(const FFVector3f& l, const FFVector3f& r)
{
	FFVector3f Ret(l.x + r.x,
		l.y + r.y,
		l.z + r.z);

	return Ret;
}

inline FFVector3f operator-(const FFVector3f& l, const FFVector3f& r)
{
	FFVector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);

	return Ret;
}

inline FFVector3f operator*(const FFVector3f& l, float f)
{
	FFVector3f Ret(l.x * f,
		l.y * f,
		l.z * f);

	return Ret;
}


inline FFVector4f operator/(const FFVector4f& l, float f)
{
	FFVector4f Ret(l.x / f,
		l.y / f,
		l.z / f,
		l.w / f);

	return Ret;
}