#pragma once

#include "Light.h"
#include "Common\Color.h"
#include "Common\Vector3.h"

class CSpotLight : public CLight
{
public:
	CSpotLight();
	virtual ~CSpotLight();

	virtual CColor CalculateColor(CVector3 surfacePoint, CVector3 viewerPosition, CVector3 normal);

	//SET UNIQUE ATTRIBUTES OF SPOTLIGHT
	void SetAttenConst(float attenConst) { mAttenConst = attenConst; }
	void SetAttenLinear(float attenLinear) { mAttenLinear = attenLinear; }
	void SetAttenQuadratic(float attenQuadratic) { mAttenQuadratic = attenQuadratic; }
	void SetDirection(CVector3& direction) { mLightDirection = direction; mLightDirection.Normalize(); }
	void SetAngle(float Angle) { mAngle = Angle; }
	void SetDecay(float Decay) { mDecay = Decay; }

private:
	float mAttenConst;
	float mAttenLinear;
	float mAttenQuadratic;

	CVector3 mLightDirection;
	float mAngle;
	float mDecay;
};