#include "quaternion.h"
#include "common.h"
#include <cmath>

FFQuaternion::FFQuaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void FFQuaternion::Normalize()
{
	float Length = sqrtf(x * x + y * y + z * z + w * w);

	x /= Length;
	y /= Length;
	z /= Length;
	w /= Length;
}


FFQuaternion FFQuaternion::Conjugate()
{
	FFQuaternion ret(-x, -y, -z, w);
	return ret;
}

FFQuaternion operator*(const FFQuaternion& l, const FFQuaternion& r)
{
	const float w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
	const float x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
	const float y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
	const float z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

	FFQuaternion ret(x, y, z, w);

	return ret;
}

FFQuaternion operator*(const FFQuaternion& q, const FFVector3f& v)
{
	const float w = -(q.x * v.x) - (q.y * v.y) - (q.z * v.z);
	const float x = (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
	const float y = (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
	const float z = (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

	FFQuaternion ret(x, y, z, w);

	return ret;
}


FFVector3f FFQuaternion::ToDegrees()
{
	float f[3];

	f[0] = atan2(x * z + y * w, x * w - y * z);
	f[1] = acos(-x * x - y * y - z * z - w * w);
	f[2] = atan2(x * z - y * w, x * w + y * z);

	f[0] = ToDegree(f[0]);
	f[1] = ToDegree(f[1]);
	f[2] = ToDegree(f[2]);

	return FFVector3f(f);
}