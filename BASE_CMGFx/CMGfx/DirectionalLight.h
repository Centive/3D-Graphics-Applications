#pragma once

#include "Light.h"
#include "Common\Color.h"
#include "Common\Vector3.h"

class CDirectionalLight : public CLight
{
public:
	CDirectionalLight();
	virtual ~CDirectionalLight();

	CColor CalculateColor(CVector3 surfacePoint, CVector3 viewerPosition, CVector3 normal);
private:
	//
};