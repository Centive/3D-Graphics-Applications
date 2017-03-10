//====================================================================================================
// Includes
//====================================================================================================
#include "stdafx.h"
#include "ScriptParser.h"
#include "CmdCamera.h"
#include "Camera/Camera.h"

#include "Common/Vector3.h"

//====================================================================================================
// Class Implementations
//====================================================================================================

BOOL CCmdCameraPersp::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // Need at least 6 params for "look from(origin)" vector(x, y, z) and "look at(interest)" vector(x, y, z)
    const int NUMPARAMS = 6;
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

    CVector3 lookFrom( coords[ 0 ], coords[ 1 ], coords[ 2 ] );
    CVector3 lookAt  ( coords[ 3 ], coords[ 4 ], coords[ 5 ] );

    // initialize the camera with the look from and look at attributes
    Camera()->Initialize( lookFrom, lookAt );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdCameraFOV::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 1 parameter -- field of view in degrees
    const int NUMPARAMS = 1;
    if ( paramStrList.GetCount() < NUMPARAMS )
    {
        return FALSE;
    }

    // get parameter and convert to float value
    float paramVal;
    POSITION pos = paramStrList.GetHeadPosition();
    paramVal = ( float )( wcstod( paramStrList.GetNext( pos ), NULL ) );

    // pass the FOV parameter to the Camera
    Camera()->SetFOV( paramVal );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdNearPlane::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 1 parameter -- near clipping plane in z units
    const int NUMPARAMS = 1;
    if ( paramStrList.GetCount() < NUMPARAMS )
    {
        return FALSE;
    }

    // get parameter and convert to float value
    float paramVal;
    POSITION pos = paramStrList.GetHeadPosition();
    paramVal = ( float )( wcstod( paramStrList.GetNext( pos ), NULL ) );

    // pass the near plane parameter to the Camera
    Camera()->SetNearPlane( paramVal );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdFarPlane::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 1 parameter -- far clipping plane in z units
    const int NUMPARAMS = 1;
    if ( paramStrList.GetCount() < NUMPARAMS )
    {
        return FALSE;
    }

    // get parameter and convert to float value
    float paramVal;
    POSITION pos = paramStrList.GetHeadPosition();
    paramVal = ( float )( wcstod( paramStrList.GetNext( pos ), NULL ) );

    // pass the far plane parameter to the Camera
    Camera()->SetFarPlane( paramVal );

    return TRUE;
}