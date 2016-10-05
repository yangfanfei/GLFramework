#include "vertor.h"
#include "common.h"
#include "quaternion.h"
#include <cmath>

FFVector3f FFVector3f::Cross(const FFVector3f& v) const
{
	const float _x = y * v.z - z * v.y;
	const float _y = z * v.x - x * v.z;
	const float _z = x * v.y - y * v.x;

	return FFVector3f(_x, _y, _z);
}

FFVector3f& FFVector3f::Normalize()
{
	const float Length = sqrtf(x * x + y * y + z * z);

	x /= Length;
	y /= Length;
	z /= Length;

	return *this;
}

void FFVector3f::Rotate(float Angle, const FFVector3f& Axe)
{
	const float SinHalfAngle = sinf(ToRadian(Angle / 2));
	const float CosHalfAngle = cosf(ToRadian(Angle / 2));

	const float Rx = Axe.x * SinHalfAngle;
	const float Ry = Axe.y * SinHalfAngle;
	const float Rz = Axe.z * SinHalfAngle;
	const float Rw = CosHalfAngle;
	FFQuaternion RotationQ(Rx, Ry, Rz, Rw);

	FFQuaternion ConjugateQ = RotationQ.Conjugate();
	//  ConjugateQ.Normalize();
	FFQuaternion W = RotationQ * (*this) * ConjugateQ;

	x = W.x;
	y = W.y;
	z = W.z;
}