//====================================================================================================
// Classes for 3D Matrix commands
//====================================================================================================
#pragma once
#include "CmdCommand.h"

//====================================================================================================
// Set Identity Matrix
//====================================================================================================
class CCmdMat3DIdentity : public CCmdCommand
{
public:
	CCmdMat3DIdentity( void ) {}
	~CCmdMat3DIdentity( void ) {}

public:
	BOOL execute( CString &params );
};

//====================================================================================================
// Set Translation Matrix
//====================================================================================================
class CCmdMat3DTranslate : public CCmdCommand
{
public:
    CCmdMat3DTranslate( void ) {}
    ~CCmdMat3DTranslate( void ) {}

public:
    BOOL execute( CString &params );
};

//====================================================================================================
// Set Scale Matrix
//====================================================================================================
class CCmdMat3DScale : public CCmdCommand
{
public:
    CCmdMat3DScale( void ) {}
    ~CCmdMat3DScale( void ) {}

public:
    BOOL execute( CString &params );
};

//====================================================================================================
// Set Rotation Matrix
//====================================================================================================
class CCmdMat3DRotate : public CCmdCommand
{
public:
    CCmdMat3DRotate( void ) {}
    ~CCmdMat3DRotate( void ) {}

public:
    BOOL execute( CString &params );
};