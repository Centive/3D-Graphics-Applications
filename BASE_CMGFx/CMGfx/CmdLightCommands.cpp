#include "stdafx.h"
#include "CmdLightCommands.h"


BOOL CCmdAttenConstant::execute(CString & params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 1 parameter -- field of view in degrees
	const int NUMPARAMS = 1;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameter and convert to float value
	float paramVal;
	POSITION pos = paramStrList.GetHeadPosition();
	paramVal = (float)(wcstod(paramStrList.GetNext(pos), NULL));

	//SET ATTENCONSTANT
	CLightManager::getInstance()->SetAttenConstant(paramVal);

	return TRUE;
}

BOOL CCmdAttenLinear::execute(CString & params)
{
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 1 parameter -- field of view in degrees
	const int NUMPARAMS = 1;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameter and convert to float value
	float paramVal;
	POSITION pos = paramStrList.GetHeadPosition();
	paramVal = (float)(wcstod(paramStrList.GetNext(pos), NULL));

	//SET ATTENLINEAR
	CLightManager::getInstance()->SetAttenLinear(paramVal);

	return TRUE;
}

BOOL CCmdAttenQuadratic::execute(CString & params)
{
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 1 parameter -- field of view in degrees
	const int NUMPARAMS = 1;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameter and convert to float value
	float paramVal;
	POSITION pos = paramStrList.GetHeadPosition();
	paramVal = (float)(wcstod(paramStrList.GetNext(pos), NULL));

	//SET ATTENQUADRATIC
	CLightManager::getInstance()->SetAttenQuadratic(paramVal);

	return TRUE;
}

BOOL CCmdClearLights::execute(CString & params)
{
	CLightManager::getInstance()->ClearLights();

	return TRUE;
}

BOOL CCmdDirectionalLight::execute(CString & params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 3 parameters -- tx, ty, and tz
	const int NUMPARAMS = 3;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameters and convert to float values
	float paramVals[NUMPARAMS];
	POSITION pos = paramStrList.GetHeadPosition();
	for (int i = 0; i < NUMPARAMS; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		paramVals[i] = (float)(wcstod(paramStr, NULL));
	}

	//SET DIRECTIONAL LIGHT
	CLightManager::getInstance()->AddDirectionalLight(paramVals[0], paramVals[1], paramVals[2]);

	return TRUE;
}

BOOL CCmdLightAmbient::execute(CString & params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 3 parameters -- tx, ty, and tz
	const int NUMPARAMS = 3;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameters and convert to float values
	float paramVals[NUMPARAMS];
	POSITION pos = paramStrList.GetHeadPosition();
	for (int i = 0; i < NUMPARAMS; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		paramVals[i] = (float)(wcstod(paramStr, NULL));
	}

	//SET AMBIENT LIGHT
	CLightManager::getInstance()->SetAmbient(CColor(paramVals[0], paramVals[1], paramVals[2]));

	return TRUE;
}

BOOL CCmdLightDiffuse::execute(CString & params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 3 parameters -- tx, ty, and tz
	const int NUMPARAMS = 3;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameters and convert to float values
	float paramVals[NUMPARAMS];
	POSITION pos = paramStrList.GetHeadPosition();
	for (int i = 0; i < NUMPARAMS; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		paramVals[i] = (float)(wcstod(paramStr, NULL));
	}

	//SET DIFFUSE LIGHT
	CLightManager::getInstance()->SetDiffuse(CColor(paramVals[0], paramVals[1], paramVals[2]));

	return TRUE;
}

BOOL CCmdLightSpecular::execute(CString & params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 3 parameters -- tx, ty, and tz
	const int NUMPARAMS = 3;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameters and convert to float values
	float paramVals[NUMPARAMS];
	POSITION pos = paramStrList.GetHeadPosition();
	for (int i = 0; i < NUMPARAMS; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		paramVals[i] = (float)(wcstod(paramStr, NULL));
	}

	//SET SPECULAR LIGHT
	CLightManager::getInstance()->SetSpecular(CColor(paramVals[0], paramVals[1], paramVals[2]));

	return TRUE;
}

BOOL CCmdPointLight::execute(CString & params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 3 parameters -- tx, ty, and tz
	const int NUMPARAMS = 3;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameters and convert to float values
	float paramVals[NUMPARAMS];
	POSITION pos = paramStrList.GetHeadPosition();
	for (int i = 0; i < NUMPARAMS; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		paramVals[i] = (float)(wcstod(paramStr, NULL));
	}

	//SET DIRECTIONAL LIGHT
	CLightManager::getInstance()->AddPointLight(paramVals[0], paramVals[1], paramVals[2]);

	return TRUE;
}

BOOL CCmdSpotLight::execute(CString & params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 3 parameters -- tx, ty, and tz
	const int NUMPARAMS = 8;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameters and convert to float values
	float paramVals[NUMPARAMS];
	POSITION pos = paramStrList.GetHeadPosition();
	for (int i = 0; i < NUMPARAMS; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		paramVals[i] = (float)(wcstod(paramStr, NULL));
	}

	//SET DIRECTIONAL LIGHT
	CLightManager::getInstance()->AddSpotLight(paramVals[0], paramVals[1], paramVals[2], paramVals[3], paramVals[4], paramVals[5], paramVals[6], paramVals[7]);

	return TRUE;
}

BOOL CCmdWorldAmbient::execute(CString & params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// should be 3 parameters -- tx, ty, and tz
	const int NUMPARAMS = 3;
	if (paramStrList.GetCount() < NUMPARAMS)
	{
		return FALSE;
	}

	// get parameters and convert to float values
	float paramVals[NUMPARAMS];
	POSITION pos = paramStrList.GetHeadPosition();
	for (int i = 0; i < NUMPARAMS; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		paramVals[i] = (float)(wcstod(paramStr, NULL));
	}

	//SET WORLD AMBIENT LIGHT
	CLightManager::getInstance()->SetWorldAmbient(CColor(paramVals[0], paramVals[1], paramVals[2]));

	return TRUE;
}