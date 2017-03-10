#pragma once

#include "Light.h"
#include "Common\Color.h"
#include "Common\Vector3.h"

class CPointLight : public CLight
{
public:
	CPointLight();
	virtual ~CPointLight();

	virtual CColor CalculateColor(CVector3 surfacePoint, CVector3 viewerPosition, CVector3 normal);
	void SetAttenConst(float attenConst) { mAttenConst = attenConst; }
	void SetAttenLinear(float attenLinear) { mAttenLinear = attenLinear; }
	void SetAttenQuadratic(float attenQuadratic) { mAttenQuadratic = attenQuadratic; }
private:
	float mAttenConst;
	float mAttenLinear;
	float mAttenQuadratic;
};