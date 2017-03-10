#pragma once
#include "CmdCommand.h"

// for setting the current openGl color state
class CCmdColor : public CCmdCommand
{
public:
	CCmdColor( void ) {}
	~CCmdColor( void ) {}

public:
	BOOL execute( CString &params );
};

// for setting the current fillmode for primitives
class CCmdFillmode : public CCmdCommand
{
public:
    CCmdFillmode( void ) {}
    ~CCmdFillmode( void ) {}

public:
    BOOL execute( CString &params );
};
