#include "stdafx.h"
#include "LightManager.h"


CLightManager* CLightManager::instance = 0;
CLightManager * CLightManager::getInstance()
{
	if (!instance)
	{
		instance = new CLightManager();
		return instance;
	}
	else
	{
		return instance;
	}
}

void CLightManager::AddDirectionalLight(float x, float y, float z)
{
	//CREATE NEW LIGHT
	CDirectionalLight * directionalLight = new CDirectionalLight();

	//SET THE LIGHTS ATTRIBUTES
	directionalLight->SetLightType(DIRECTIONAL_LIGHT);
	directionalLight->SetPosition(CVector3(x, y, z));
	directionalLight->SetAmbient(mCurAmbient);
	directionalLight->SetDiffuse(mCurDiffuse);
	directionalLight->SetSpecular(mCurSpecular);

	//ADD IT TO THE LIST OF LIGHTS
	mLights.push_back(directionalLight);
}

void CLightManager::AddPointLight(float x, float y, float z)
{
	//CREATE NEW LIGHT
	CPointLight * pointLight = new CPointLight();

	//SET THE LIGHTS ATTRIBUTES
	pointLight->SetLightType(POINT_LIGHT);
	pointLight->SetPosition(CVector3(x, y, z));
	pointLight->SetAmbient(mCurAmbient);
	pointLight->SetDiffuse(mCurDiffuse);
	pointLight->SetSpecular(mCurSpecular);
	pointLight->SetAttenConst(mCurAttenConstant);
	pointLight->SetAttenLinear(mCurAttenLinear);
	pointLight->SetAttenQuadratic(mCurAttenQuadratic);

	//ADD IT TO THE LIST OF LIGHTS
	mLights.push_back(pointLight);
}

void CLightManager::AddSpotLight(float x1, float y1, float z1, float x2, float y2, float z2, float angle, float decay)
{
	//CREATE NEW LIGHT
	CSpotLight * spotLight = new CSpotLight();

	//SET THE LIGHTS ATTRIBUTES
	spotLight->SetLightType(SPOT_LIGHT);
	spotLight->SetPosition(CVector3(x1, y1, z1));
	spotLight->SetAmbient(mCurAmbient);
	spotLight->SetDiffuse(mCurDiffuse);
	spotLight->SetSpecular(mCurSpecular);

	spotLight->SetDirection(CVector3(x2, y2, z2));
	spotLight->SetAngle(angle);
	spotLight->SetDecay(decay);
	spotLight->SetAttenConst(mCurAttenConstant);
	spotLight->SetAttenLinear(mCurAttenLinear);
	spotLight->SetAttenQuadratic(mCurAttenQuadratic);

	//ADD IT TO THE LIST OF LIGHTS
	mLights.push_back(spotLight);
}

void CLightManager::SetWorldAmbient(CColor worldAmbient)
{
	mCurWorldAmbient = worldAmbient;
}

void CLightManager::SetAmbient(CColor ambient)
{
	mCurAmbient = ambient;
}

void CLightManager::SetDiffuse(CColor diffuse)
{
	mCurDiffuse = diffuse;
}

void CLightManager::SetSpecular(CColor specular)
{
	mCurSpecular = specular;
}

void CLightManager::SetAttenConstant(float constant)
{
	mCurAttenConstant = constant;
}

void CLightManager::SetAttenLinear(float linear)
{
	mCurAttenLinear = linear;
}

void CLightManager::SetAttenQuadratic(float quadratic)
{
	mCurAttenQuadratic = quadratic;
}

CColor CLightManager::CombinedLightEquation(CVector3 surfacePoint, CVector3 viewerPosition, CVector3 normal)
{
	CColor combinedLight;
	CColor emmisive = CColor(0.1, 0.0, 0.0);
	for (std::vector<CLight*>::iterator it = mLights.begin(); it != mLights.end(); ++it)
	{
		combinedLight += (*it)->CalculateColor(surfacePoint, viewerPosition, normal);
	}

	return CColor(combinedLight + mCurWorldAmbient + emmisive);
}

void CLightManager::ClearLights()
{
	for (std::vector<CLight*>::iterator it = mLights.begin(); it != mLights.end(); ++it)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
		}
	}
	mLights.clear();
}