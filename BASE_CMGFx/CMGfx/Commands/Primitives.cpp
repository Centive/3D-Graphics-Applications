#include "StdAfx.h"
#include "Primitives.h"
#include "ScriptParser.h"
#include "States/PrimManager.h"
#include "States/StateManager.h"

BOOL CCmdDrawbegin::execute( CString &params )
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
    EPrimitiveType eCurrentPrimitive = EPrimitiveType_NONE;
    CString validParams[ EPrimitiveType_MAX ];
    validParams[ EPrimitiveType_POINT ] =     "point";
    validParams[ EPrimitiveType_LINE ] =      "line";
    validParams[ EPrimitiveType_TRIANGLE ] =  "triangle";

    // compare parameter against valid primitive types
    for ( int i = 0; i < EPrimitiveType_MAX; ++i )
    {
        if ( 0 == paramStr.CompareNoCase( validParams[ i ] ) )
        {
            eCurrentPrimitive = ( EPrimitiveType )i;
            break;
        }
    }

    // verify correct param and pass to state manager
    if ( EPrimitiveType_NONE != eCurrentPrimitive )
    {
        PrimManager()->BeginDraw( eCurrentPrimitive );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdDrawend::execute( CString &params )
{
    PrimManager()->EndDraw();
    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdVertex2::execute( CString &params )
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

    float coords[ numParams ];
    POSITION pos = paramStrList.GetHeadPosition();
    for ( int i = 0; i < numParams; ++i )
    {
        CString paramStr = paramStrList.GetNext( pos );
        coords[ i ] = ( float )( wcstod( paramStr, NULL ) );
    }

    SVertex3 currentVertex;
    currentVertex.point.x = coords[ 0 ];
    currentVertex.point.y = coords[ 1 ];
    currentVertex.point.z = 0.0f;
    currentVertex.color = StateManager()->GetCurrentColor();

    // add the vertex to the current primitive set in the primitive manager
    PrimManager()->AddVertex2D( currentVertex );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdVertex3::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // Need at least 3 params for x, y, z
    const int NUMPARAMS = 3;
    if ( paramStrList.GetCount() < NUMPARAMS )
    {
        return FALSE;
    }

    float coords[ NUMPARAMS ];
    POSITION pos = paramStrList.GetHeadPosition();
    for ( int i = 0; i < NUMPARAMS; ++i )
    {
        CString paramStr = paramStrList.GetNext( pos );
        coords[ i ] = ( float )( wcstod( paramStr, NULL ) );
    }

    SVertex3 v;     // constructor sets w value to 1
    v.point.x = ( float )( int )( coords[ 0 ] >= 0 ? coords[ 0 ] + 0.5f : coords[ 0 ] - 0.5f );
    v.point.y = ( float )( int )( coords[ 1 ] >= 0 ? coords[ 1 ] + 0.5f : coords[ 1 ] - 0.5f );
    v.point.z = ( float )( int )( coords[ 2 ] >= 0 ? coords[ 2 ] + 0.5f : coords[ 2 ] - 0.5f );
    v.color = StateManager()->GetCurrentColor();

    // add the vertex to the current primitive set in the primitive manager
    PrimManager()->AddVertex3D( v );

    return TRUE;
}