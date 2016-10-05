#include "mvp.h"

FFMvp::FFMvp()
{
	v3Scale			= FFVector3f(1.0f, 1.0f, 1.0f);
	v3WorldPos		= FFVector3f(0.0f, 0.0f, 0.0f);
	v3RotateInfo	= FFVector3f(0.0f, 0.0f, 0.0f);
}

FFMvp::~FFMvp()
{

}

const FFMatrix4f& FFMvp::GetWPTrans()
{
	FFMatrix4f PersProjTrans;

	GetWorldTrans();
	PersProjTrans.InitPersProjTransform(persProjInfo);

	m4WPtransformation = PersProjTrans * m4Wtransformation;
	return m4WPtransformation;
}

const FFMatrix4f& FFMvp::GetWVTrans()
{
	GetWorldTrans();
	GetViewTrans();

	m4WVtransformation = m4Vtransformation * m4Wtransformation;
	return m4WVtransformation;
}

const FFMatrix4f& FFMvp::GetVPTrans()
{
	GetViewTrans();
	GetProjTrans();

	m4VPtransformation = m4ProjTransformation * m4Vtransformation;
	return m4VPtransformation;
}

const FFMatrix4f& FFMvp::GetWVPTrans()
{
	GetWorldTrans();
	GetVPTrans();

	m4WVPtransformation = m4VPtransformation * m4Wtransformation;
	return m4WVPtransformation;
}

const FFMatrix4f& FFMvp::GetWVOrthoPTrans()
{
	GetWorldTrans();
	GetViewTrans();

	FFMatrix4f P;
	P.InitOrthoProjTransform(orthoProjInfo);

	m4WVPtransformation = P * m4Vtransformation * m4Wtransformation;
	return m4WVPtransformation;
}

const FFMatrix4f& FFMvp::GetWorldTrans()
{
	FFMatrix4f ScaleTrans, RotateTrans, TranslationTrans;

	ScaleTrans.InitScaleTransform(v3Scale.x, v3Scale.y, v3Scale.z);
	RotateTrans.InitRotateTransform(v3RotateInfo.x, v3RotateInfo.y, v3RotateInfo.z);
	TranslationTrans.InitTranslationTransform(v3WorldPos.x, v3WorldPos.y, v3WorldPos.z);

	m4Wtransformation = TranslationTrans * RotateTrans * ScaleTrans;
	return m4Wtransformation;
}

const FFMatrix4f& FFMvp::GetViewTrans()
{
	FFMatrix4f CameraTranslationTrans, CameraRotateTrans;

	CameraTranslationTrans.InitTranslationTransform(-camMain.v3Pos.x, -camMain.v3Pos.y, -camMain.v3Pos.z);
	CameraRotateTrans.InitCameraTransform(camMain.v3Target, camMain.v3Up);

	m4Vtransformation = CameraRotateTrans * CameraTranslationTrans;

	return m4Vtransformation;
}

const FFMatrix4f& FFMvp::GetProjTrans()
{
	m4ProjTransformation.InitPersProjTransform(persProjInfo);
	return m4ProjTransformation;
}
