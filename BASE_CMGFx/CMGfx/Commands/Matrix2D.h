#pragma once
#include "CmdCommand.h"

//====================================================================================================
// Classes for 2D Matrix commands
//====================================================================================================
//====================================================================================================
// Set Identity Matrix
//====================================================================================================
class CCmdMat2DIdentity : public CCmdCommand
{
public:
	CCmdMat2DIdentity( void ) {}
	~CCmdMat2DIdentity( void ) {}

public:
	BOOL execute( CString &params );
};

//====================================================================================================
// Set Translation Matrix
//====================================================================================================
class CCmdMat2DTranslate : public CCmdCommand
{
public:
    CCmdMat2DTranslate( void ) {}
    ~CCmdMat2DTranslate( void ) {}

public:
    BOOL execute( CString &params );
};

//====================================================================================================
// Set Scale Matrix
//====================================================================================================
class CCmdMat2DScale : public CCmdCommand
{
public:
    CCmdMat2DScale( void ) {}
    ~CCmdMat2DScale( void ) {}

public:
    BOOL execute( CString &params );
};

//====================================================================================================
// Set Rotation Matrix
//====================================================================================================
class CCmdMat2DRotate : public CCmdCommand
{
public:
    CCmdMat2DRotate( void ) {}
    ~CCmdMat2DRotate( void ) {}

public:
    BOOL execute( CString &params );
};

//====================================================================================================
// Set Shear Matrix
//====================================================================================================
class CCmdMat2DShear : public CCmdCommand
{
public:
    CCmdMat2DShear( void ) {}
    ~CCmdMat2DShear( void ) {}

public:
    BOOL execute( CString &params );
};