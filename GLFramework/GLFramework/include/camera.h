/************************************************************************
* @author yffei
*
************************************************************************/
#pragma once
#include "common.h"
#include "vertor.h"

class FFCamera
{
public:
	FFCamera(int  WndWidth, int WndHeight);
	FFCamera(int  WndWidth, int WndHeight, FFVector3f pos, FFVector3f target, FFVector3f up);
	~FFCamera();

	void OnRender();

	const FFVector3f& GetPos() const
	{
		return v3Pos;
	}

	const FFVector3f& GetTarget() const
	{
		return v3Target;
	}

	const FFVector3f& GetUp() const
	{
		return v3Up;
	}

private:
	int			iWindowWidth;
	int			iWindowHeight;

	float		fAngleH;
	float		fAngleW;

	FFVector3f	v3Pos;
	FFVector3f	v3Target;
	FFVector3f	v3Up;
};