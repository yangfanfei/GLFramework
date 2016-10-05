/************************************************************************
* @author yffei
*
************************************************************************/
#pragma once
#include <cmath>
#include <string.h>
#include "common.h"
#include "vertor.h"

class FFMatrix4f
{
public:
	float m[4][4];

	FFMatrix4f()
	{
	}

	FFMatrix4f(const FFMatrix4f& otherMatrix)
	{
		m[0][0] = otherMatrix.m[0][0]; m[0][1] = otherMatrix.m[0][1]; m[0][2] = otherMatrix.m[0][2]; m[0][3] = otherMatrix.m[0][3];
		m[1][0] = otherMatrix.m[1][0]; m[1][1] = otherMatrix.m[1][1]; m[1][2] = otherMatrix.m[1][2]; m[1][3] = otherMatrix.m[1][3];
		m[2][0] = otherMatrix.m[2][0]; m[2][1] = otherMatrix.m[2][1]; m[2][2] = otherMatrix.m[2][2]; m[2][3] = otherMatrix.m[2][3];
		m[3][0] = otherMatrix.m[3][0]; m[3][1] = otherMatrix.m[3][1]; m[3][2] = otherMatrix.m[3][2]; m[3][3] = otherMatrix.m[3][3];
	}

	FFMatrix4f(float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33)
	{
		m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
		m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
		m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
		m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
	}

	void SetZero()
	{
		ZERO_MEM(m);
	}

	FFMatrix4f Transpose() const
	{
		FFMatrix4f n;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				n.m[i][j] = m[j][i];
			}
		}

		return n;
	}


	inline void InitIdentity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}

	inline FFMatrix4f operator*(const FFMatrix4f& Right) const
	{
		FFMatrix4f Ret;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				Ret.m[i][j] = m[i][0] * Right.m[0][j] +
					m[i][1] * Right.m[1][j] +
					m[i][2] * Right.m[2][j] +
					m[i][3] * Right.m[3][j];
			}
		}

		return Ret;
	}

	FFVector4f operator*(const FFVector4f& v) const
	{
		FFVector4f r;

		r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
		r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
		r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
		r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

		return r;
	}

	operator const float*() const
	{
		return &(m[0][0]);
	}

	void Print() const
	{
		for (int i = 0; i < 4; i++) {
			printf("%f %f %f %f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
		}
	}

	float Determinant() const;

	FFMatrix4f& Inverse();

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);
	void InitRotateTransform(float RotateX, float RotateY, float RotateZ);
	void InitTranslationTransform(float x, float y, float z);
	void InitCameraTransform(const FFVector3f& Target, const FFVector3f& Up);
	void InitPersProjTransform(const FFPersProjInfo& p);
	void InitOrthoProjTransform(const FFOrthoProjInfo& p);
};