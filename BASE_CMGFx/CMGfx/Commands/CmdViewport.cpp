#include "StdAfx.h"
#include "CmdViewport.h"
#include "ScriptParser.h"
#include "Camera/Viewport.h"
#include "Display/Clipper.h"

BOOL CCmdViewport::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // Need at least 4 params for l, t, r, b
    const int numParams = 4;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    float coords[ numParams ];
    POSITION pos = paramStrList.GetHeadPosition();
    for ( int i = 0; i < numParams; ++i )
    {
        CString paramStr = paramStrList.GetNext( pos );
        coords[ i ] = ( float )wcstod( paramStr, NULL );
    }

    // pass values to set the viewport -- passed values are l, t, r, b -- convert to l, t, w, h
    Viewport()->SetViewport( coords[ 0 ], coords[ 1 ], coords[ 2 ] - coords[ 0 ], coords[ 3 ] - coords[ 1 ] );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdShowviewport::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // Need 1 param, either "on" or "off"
    const int numParams = 1;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    POSITION pos = paramStrList.GetHeadPosition();
    CString paramStr = paramStrList.GetNext( pos );
    CString strON( "on" ), strOFF( "off" );

    if      ( 0 == paramStr.CompareNoCase( strON ) )  Viewport()->SetViewportVisible( true );
    else if ( 0 == paramStr.CompareNoCase( strOFF ) ) Viewport()->SetViewportVisible( false );
    else return FALSE;

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdSetClipping::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // Need 1 param, either "on" or "off"
    const int numParams = 1;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    POSITION pos = paramStrList.GetHeadPosition();
    CString paramStr = paramStrList.GetNext( pos );
    CString strON( "on" ), strOFF( "off" );

    if      ( 0 == paramStr.CompareNoCase( strON ) )  Clipper()->SetClipping( true );
    else if ( 0 == paramStr.CompareNoCase( strOFF ) ) Clipper()->SetClipping( false );
    else return FALSE;

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdSetBackfaceCull::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // Need 1 param, either "on" or "off"
    const int numParams = 1;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    POSITION pos = paramStrList.GetHeadPosition();
    CString paramStr = paramStrList.GetNext( pos );
    CString strON( "on" ), strOFF( "off" );

    if      ( 0 == paramStr.CompareNoCase( strON ) )  Viewport()->SetBackfaceCull( true );
    else if ( 0 == paramStr.CompareNoCase( strOFF ) ) Viewport()->SetBackfaceCull( false );
    else return FALSE;

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdSetZBuffering::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // Need 1 param, either "on" or "off"
    const int numParams = 1;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    POSITION pos = paramStrList.GetHeadPosition();
    CString paramStr = paramStrList.GetNext( pos );
    CString strON( "on" ), strOFF( "off" );

    if      ( 0 == paramStr.CompareNoCase( strON ) )  Viewport()->SetZBuffering( true );
    else if ( 0 == paramStr.CompareNoCase( strOFF ) ) Viewport()->SetZBuffering( false );
    else return FALSE;

    return TRUE;
}