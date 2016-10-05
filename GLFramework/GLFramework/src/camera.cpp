#include "camera.h"

FFCamera::FFCamera(int WndWidth, int WndHeight): iWindowWidth(WndWidth), iWindowHeight(WndHeight)
{
	
}

FFCamera::FFCamera(int WndWidth, int WndHeight, FFVector3f pos, FFVector3f target, FFVector3f up)
{
	iWindowWidth	= WndWidth;
	iWindowHeight	= WndHeight;

	v3Pos = pos;
	v3Target = target;
	v3Target.Normalize();
	v3Up = up;
	v3Up.Normalize();
}

FFCamera::~FFCamera()
{

}

void FFCamera::OnRender()
{
}
