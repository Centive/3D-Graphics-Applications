#pragma once
#include "CmdCommand.h"

class CCmdViewport : public CCmdCommand
{
public:
	CCmdViewport( void ) {}
	~CCmdViewport( void ) {}

public:
	BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

class CCmdShowviewport : public CCmdCommand
{
public:
    CCmdShowviewport( void ) {}
    ~CCmdShowviewport( void ) {}

public:
    BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

class CCmdSetClipping : public CCmdCommand
{
public:
    CCmdSetClipping( void ) {}
    ~CCmdSetClipping( void ) {}

public:
    BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

class CCmdSetBackfaceCull : public CCmdCommand
{
public:
    CCmdSetBackfaceCull( void ) {}
    ~CCmdSetBackfaceCull( void ) {}

public:
    BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

class CCmdSetZBuffering : public CCmdCommand
{
public:
    CCmdSetZBuffering( void ) {}
    ~CCmdSetZBuffering( void ) {}

public:
    BOOL execute( CString &params );
};