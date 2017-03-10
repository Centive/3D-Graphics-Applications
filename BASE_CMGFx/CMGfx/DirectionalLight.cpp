#include "stdafx.h"
#include "DirectionalLight.h"


CDirectionalLight::CDirectionalLight()
{
}


CDirectionalLight::~CDirectionalLight()
{
}

CColor CDirectionalLight::CalculateColor(CVector3 surfacePoint, CVector3 viewerPosition, CVector3 normal)
{
	CVector3 dirToLight = (mPosition - surfacePoint);
	dirToLight.Normalize();

	float lightIntensity = 1.0f;

	CVector3 dirToViewer = viewerPosition - surfacePoint;
	dirToViewer.Normalize();

	CVector3 reflectedLight = 2 * (dirToLight.Dot(normal) * (normal - dirToLight));
	reflectedLight.Normalize();

	float maxCd = (dirToLight.Dot(normal) > 0) ? dirToLight.Dot(normal) : 0;
	float maxCs = (pow(reflectedLight.Dot(dirToViewer), 1) > 0) ? pow(reflectedLight.Dot(dirToViewer), 1) : 0;

	CColor Ca = lightIntensity * mAmbient;
	CColor Cd = lightIntensity * maxCd * mDiffuse;
	CColor Cs = lightIntensity * maxCs * mSpecular ;

	return CColor(Ca + Cd + Cs);
}