#pragma once

#include "Commands/CmdCommand.h"
#include "Commands/ScriptParser.h"
#include "LightManager.h"

class CCmdAttenConstant : public CCmdCommand
{
public:
	CCmdAttenConstant() {}
	~CCmdAttenConstant() {}
	BOOL execute(CString &params);
};

class CCmdAttenLinear : public CCmdCommand
{
public:
	CCmdAttenLinear() {}
	~CCmdAttenLinear() {}

	BOOL execute(CString &params);
};

class CCmdAttenQuadratic : public CCmdCommand
{
public:
	CCmdAttenQuadratic() {}
	~CCmdAttenQuadratic() {}

	BOOL execute(CString &params);
};

class CCmdClearLights : public CCmdCommand
{
public:
	CCmdClearLights() {}
	~CCmdClearLights() {}

	BOOL execute(CString &params);
};

class CCmdDirectionalLight : public CCmdCommand
{
public:
	CCmdDirectionalLight() {}
	~CCmdDirectionalLight() {}

	BOOL execute(CString &params);
};

class CCmdLightAmbient : public CCmdCommand
{
public:
	CCmdLightAmbient() {}
	~CCmdLightAmbient() {}

	BOOL execute(CString &params);
};

class CCmdLightDiffuse : public CCmdCommand
{
public:
	CCmdLightDiffuse() {}
	~CCmdLightDiffuse() {}

	BOOL execute(CString &params);
};

class CCmdLightSpecular : public CCmdCommand
{
public:
	CCmdLightSpecular() {}
	~CCmdLightSpecular() {}

	BOOL execute(CString &params);
};

class CCmdPointLight : public CCmdCommand
{
public:
	CCmdPointLight() {}
	~CCmdPointLight() {}

	BOOL execute(CString &params);
};

class CCmdSpotLight : public CCmdCommand
{
public:
	CCmdSpotLight() {}
	~CCmdSpotLight() {}

	BOOL execute(CString &params);
};

class CCmdWorldAmbient : public CCmdCommand
{
public:
	CCmdWorldAmbient() {}
	~CCmdWorldAmbient() {}

	BOOL execute(CString &params);
};