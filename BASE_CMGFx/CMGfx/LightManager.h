#pragma once

#include "Common\Color.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include <vector>

class CLightManager
{
public:
	//SINGLETON
	static CLightManager *getInstance();

	//ADD LIGHTS
	void AddDirectionalLight(float x, float y, float z);
	void AddPointLight(float x, float y, float z);
	void AddSpotLight(float x1, float y1, float z1, float x2, float y2, float z2, float angle, float decay);
	
	//SET LIGHTS
	void SetWorldAmbient(CColor worldAmbient);
	void SetAmbient(CColor ambient);
	void SetDiffuse(CColor diffuse);
	void SetSpecular(CColor specular);

	//SET ATTENUATIONS
	void SetAttenConstant(float constant);
	void SetAttenLinear(float linear);
	void SetAttenQuadratic(float quadratic);

	CColor CombinedLightEquation(CVector3 surfacePoint, CVector3 viewerPosition, CVector3 normal);
	void ClearLights();

private:
	//SINGLETON
	CLightManager() {}
	static CLightManager *instance;

	//MEMBERS
	std::vector<CLight*> mLights;
	CColor mCurWorldAmbient;
	CColor mCurAmbient;
	CColor mCurDiffuse;
	CColor mCurSpecular;
	float mCurAttenConstant;
	float mCurAttenLinear;
	float mCurAttenQuadratic;
};