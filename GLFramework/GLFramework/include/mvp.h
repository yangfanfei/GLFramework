/************************************************************************
* @author yffei
*  ”ÕºÕ∂”∞æÿ’Û
************************************************************************/
#pragma once

#include "camera.h"
#include "matrix.h"
#include "vertor.h"

struct FFOrientation
{
	FFVector3f v3Scale;
	FFVector3f v3Rotation;
	FFVector3f v3Pos;

	FFOrientation()
	{
		v3Scale		= FFVector3f(1.0f, 1.0f, 1.0f);
		v3Rotation	= FFVector3f(0.0f, 0.0f, 0.0f);
		v3Pos		= FFVector3f(0.0f, 0.0f, 0.0f);
	}
};

class FFMvp
{
private:
	FFVector3f		v3Scale;
	FFVector3f		v3WorldPos;
	FFVector3f		v3RotateInfo;

	FFPersProjInfo	persProjInfo;
	FFOrthoProjInfo	orthoProjInfo;

	struct Camera {
		FFVector3f v3Pos;
		FFVector3f v3Target;
		FFVector3f v3Up;
	} camMain;

	FFMatrix4f m4WVPtransformation;
	FFMatrix4f m4VPtransformation;
	FFMatrix4f m4WPtransformation;
	FFMatrix4f m4WVtransformation;
	FFMatrix4f m4Wtransformation;
	FFMatrix4f m4Vtransformation;
	FFMatrix4f m4ProjTransformation;

public:
	FFMvp();
	~FFMvp();

	void Scale(float s)
	{
		Scale(s, s, s);
	}

	void Scale(const FFVector3f& scale)
	{
		Scale(scale.x, scale.y, scale.z);
	}

	void Scale(float ScaleX, float ScaleY, float ScaleZ)
	{
		v3Scale.x = ScaleX;
		v3Scale.y = ScaleY;
		v3Scale.z = ScaleZ;
	}

	void WorldPos(float x, float y, float z)
	{
		v3WorldPos.x = x;
		v3WorldPos.y = y;
		v3WorldPos.z = z;
	}

	void WorldPos(const FFVector3f& Pos)
	{
		v3WorldPos = Pos;
	}

	void Rotate(float RotateX, float RotateY, float RotateZ)
	{
		v3RotateInfo.x = RotateX;
		v3RotateInfo.y = RotateY;
		v3RotateInfo.z = RotateZ;
	}

	void Rotate(const FFVector3f& r)
	{
		Rotate(r.x, r.y, r.z);
	}

	void SetPerspectiveProj(const FFPersProjInfo& p)
	{
		persProjInfo = p;
	}

	void SetOrthographicProj(const FFOrthoProjInfo& p)
	{
		orthoProjInfo = p;
	}

	void SetCamera(const FFVector3f& Pos, const FFVector3f& Target, const FFVector3f& Up)
	{
		camMain.v3Pos = Pos;
		camMain.v3Target = Target;
		camMain.v3Up = Up;
	}

	void SetCamera(const FFCamera& camera)
	{
		SetCamera(camera.GetPos(), camera.GetTarget(), camera.GetUp());
	}

	void Orient(const FFOrientation& o)
	{
		v3Scale = o.v3Scale;
		v3WorldPos = o.v3Pos;
		v3RotateInfo = o.v3Rotation;
	}

	const FFMatrix4f& GetWPTrans();
	const FFMatrix4f& GetWVTrans();
	const FFMatrix4f& GetVPTrans();
	const FFMatrix4f& GetWVPTrans();
	const FFMatrix4f& GetWVOrthoPTrans();
	const FFMatrix4f& GetWorldTrans();
	const FFMatrix4f& GetViewTrans();
	const FFMatrix4f& GetProjTrans();
};