#pragma once
#include "CmdCommand.h"

//====================================================================================================
// Class
//====================================================================================================
class CCmdDrawbegin : public CCmdCommand
{
public:
	CCmdDrawbegin( void ) {}
	~CCmdDrawbegin( void ) {}

public:
	BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

class CCmdDrawend : public CCmdCommand
{
public:
    CCmdDrawend( void ) {}
    ~CCmdDrawend( void ) {}

public:
    BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

class CCmdVertex2 : public CCmdCommand
{
public:
    CCmdVertex2( void ) {}
    ~CCmdVertex2( void ) {}

public:
    BOOL execute( CString &params );
};

//----------------------------------------------------------------------------------------------------

class CCmdVertex3 : public CCmdCommand
{
public:
    CCmdVertex3( void ) {}
    ~CCmdVertex3( void ) {}

public:
    BOOL execute( CString &params );
};