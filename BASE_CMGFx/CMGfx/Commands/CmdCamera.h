#pragma once

//====================================================================================================
// Includes
//====================================================================================================
#include "Commands/CmdCommand.h"

//====================================================================================================
// Camera command classes
//====================================================================================================

// sets up a perspective projection camera
class CCmdCameraPersp : public CCmdCommand
{
public:
    CCmdCameraPersp( void ) {}
    ~CCmdCameraPersp( void ) {}

public:
    BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

// sets the camera field of view
class CCmdCameraFOV : public CCmdCommand
{
public:
    CCmdCameraFOV( void ) {}
    ~CCmdCameraFOV( void ) {}

public:
    BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

// sets the camera near plane
class CCmdNearPlane : public CCmdCommand
{
public:
    CCmdNearPlane( void ) {}
    ~CCmdNearPlane( void ) {}

public:
    BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

// sets the camera far plane
class CCmdFarPlane : public CCmdCommand
{
public:
    CCmdFarPlane( void ) {}
    ~CCmdFarPlane( void ) {}

public:
    BOOL execute( CString &params );
};