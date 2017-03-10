#include "StdAfx.h"
#include "CmdDrawPixel.h"
#include "ScriptParser.h"
#include "Display/Rasterizer.h"
#include "States/StateManager.h"
#include "Display/Clipper.h"

BOOL CCmdDrawPixel::execute( CString &params )
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

	// Need at least 2 params for x, y
	const int numParams = 2;
	if ( paramStrList.GetCount() < numParams )
	{
		return FALSE;
	}

	int coords[numParams];
	POSITION pos = paramStrList.GetHeadPosition();
	for ( int i = 0; i < numParams; i++ )
	{
		CString paramStr = paramStrList.GetNext( pos );
		coords[ i ] = ( int )( wcstod( paramStr, NULL ) + 0.5f );
	}

    // draw the pixel
    if ( true == Clipper()->ClipPoint( coords[ 0 ], coords[ 1 ] ) )
    {
	    Rasterizer()->DrawPoint( coords[ 0 ], coords[ 1 ] );
    }

	return TRUE;
}
