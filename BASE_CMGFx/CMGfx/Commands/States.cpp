#include "StdAfx.h"
#include "States.h"
#include "ScriptParser.h"
#include "Display/Rasterizer.h"
#include "States/StateManager.h"

BOOL CCmdColor::execute( CString &params )
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

	// Need at least 3 params for r, g, b
	const int numParams = 3;
	if ( paramStrList.GetCount() < numParams )
	{
		return FALSE;
	}

	float rgbvalues[ numParams ];
	POSITION pos = paramStrList.GetHeadPosition();
	for ( int i = 0; i < numParams; i++ )
	{
		CString paramStr = paramStrList.GetNext( pos );
		rgbvalues[ i ] = ( float )wcstod( paramStr, NULL );
	}

    StateManager()->SetCurrentColor( CColor( rgbvalues[ 0 ], rgbvalues[ 1 ], rgbvalues[ 2 ] ) );

	return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdFillmode::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be just 1 parameter
    const int numParams = 1;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    POSITION pos = paramStrList.GetHeadPosition();
    CString paramStr = paramStrList.GetNext( pos );

    // check to see which param was specified
    EFillmode eCurrentMode = EFillmode_NONE;
    CString validParams[ EFillmode_MAX ];
    validParams[ EFillmode_POINT ] = "point";
    validParams[ EFillmode_LINE ] =  "line";
    validParams[ EFillmode_FILL ] =  "fill";

    // compare parameter against valid fill modes
    for ( int i = 0; i < EFillmode_MAX; ++i )
    {
        if ( 0 == paramStr.CompareNoCase( validParams[ i ] ) )
        {
            eCurrentMode = ( EFillmode )i;
            break;
        }
    }

    // verify correct param and pass to state manager
    if ( EFillmode_NONE != eCurrentMode )
    {
        StateManager()->SetCurrentFillmode( eCurrentMode );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
