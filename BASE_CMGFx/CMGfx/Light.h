#pragma once

#include "Common\Color.h"
#include "Common\Vector3.h"

enum ELIGHT_TYPE
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT
};

class CLight
{
public:
	CLight() {}
	virtual ~CLight() {}

	virtual CColor CalculateColor(CVector3 surfacePoint, CVector3 viewerPosition, CVector3 normal) = 0;

	//SET MEMBERS
	void SetLightType(ELIGHT_TYPE lightType) { mLightType = mLightType; }
	void SetPosition(CVector3 &position) { mPosition = position; }
	void SetAmbient(CColor &ambient) { mAmbient = ambient; }
	void SetDiffuse(CColor &diffuse) { mDiffuse = diffuse; }
	void SetSpecular(CColor &specular) { mSpecular = specular; }

protected:
	ELIGHT_TYPE mLightType;
	CVector3 mPosition;
	CColor mAmbient;
	CColor mDiffuse;
	CColor mSpecular;
};

