#include "stdafx.h"
#include "SpotLight.h"


CSpotLight::CSpotLight()
{
}


CSpotLight::~CSpotLight()
{
}

CColor CSpotLight::CalculateColor(CVector3 surfacePoint, CVector3 viewerPosition, CVector3 normal)
{
	CVector3 dirToLight = (mPosition - surfacePoint);
	float distance = sqrtf(pow(dirToLight.x, 2) + pow(dirToLight.y, 2) + pow(dirToLight.z, 2));
	dirToLight.Normalize();

	float spot = (-dirToLight.Dot(mLightDirection) >= cos(mAngle)) ? pow(-dirToLight.Dot(mLightDirection), mDecay) : 0;

	float lightIntensity = spot / (mAttenConst + (mAttenLinear * distance) + (mAttenQuadratic * pow(distance, 2)));

	CVector3 dirToViewer = viewerPosition - surfacePoint;
	dirToViewer.Normalize();

	CVector3 reflectedLight = 2 * (dirToLight.Dot(normal) * (normal - dirToLight));
	reflectedLight.Normalize();

	float maxCd = (dirToLight.Dot(normal) > 0) ? dirToLight.Dot(normal) : 0;
	float maxCs = (pow(reflectedLight.Dot(dirToViewer), 1) > 0) ? pow(reflectedLight.Dot(dirToViewer), 1) : 0;

	CColor Ca = lightIntensity * mAmbient;
	CColor Cd = lightIntensity * maxCd * mDiffuse;
	CColor Cs = lightIntensity * maxCs * mSpecular;

	return CColor(Ca + Cd + Cs);
}
