/************************************************************************
* @author yffei
*
************************************************************************/
#pragma once
#include "vertor.h"

struct FFQuaternion
{
	float x, y, z, w;

	FFQuaternion(float _x, float _y, float _z, float _w);

	void Normalize();

	FFQuaternion Conjugate();

	FFVector3f ToDegrees();
};

FFQuaternion operator*(const FFQuaternion& l, const FFQuaternion& r);

FFQuaternion operator*(const FFQuaternion& q, const FFVector3f& v);
