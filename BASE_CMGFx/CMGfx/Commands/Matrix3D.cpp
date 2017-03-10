#include "StdAfx.h"
#include "Matrix3D.h"
#include "ScriptParser.h"
#include "States/MatrixManager.h"

//====================================================================================================
// Class Function Implementations
//====================================================================================================

BOOL CCmdMat3DIdentity::execute( CString &params )
{
    MatrixManager()->Set3DIdentity();
    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdMat3DTranslate::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 3 parameters -- tx, ty, and tz
    const int NUMPARAMS = 3;
    if ( paramStrList.GetCount() < NUMPARAMS )
    {
        return FALSE;
    }

    // get parameters and convert to float values
    float paramVals[ NUMPARAMS ];
    POSITION pos = paramStrList.GetHeadPosition();
    for ( int i = 0; i < NUMPARAMS; ++i )
    {
        CString paramStr = paramStrList.GetNext( pos );
        paramVals[ i ] = ( float )( wcstod( paramStr, NULL ) );
    }

    // pass the parameters to the MatrixManager
    MatrixManager()->Add3DTranslation( CVector3( paramVals[ 0 ], paramVals[ 1 ], paramVals[ 2 ] ) );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdMat3DScale::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 3 parameters -- sx, sy, and sz
    const int NUMPARAMS = 3;
    if ( paramStrList.GetCount() < NUMPARAMS )
    {
        return FALSE;
    }

    // get parameters and convert to float values
    float paramVals[ NUMPARAMS ];
    POSITION pos = paramStrList.GetHeadPosition();
    for ( int i = 0; i < NUMPARAMS; ++i )
    {
        CString paramStr = paramStrList.GetNext( pos );
        paramVals[ i ] = ( float )( wcstod( paramStr, NULL ) );
    }

    // pass the parameters to the MatrixManager
    MatrixManager()->Add3DScaling( CVector3( paramVals[ 0 ], paramVals[ 1 ], paramVals[ 2 ] ) );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdMat3DRotate::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 3 parameters -- rx, ry, and rz -- will reverse order for function call
    const int NUMPARAMS = 3;
    if ( paramStrList.GetCount() < NUMPARAMS )
    {
        return FALSE;
    }
    // get parameters and convert to float values
    float paramVals[ NUMPARAMS ];
    POSITION pos = paramStrList.GetHeadPosition();
    for ( int i = 0; i < NUMPARAMS; ++i )
    {
        CString paramStr = paramStrList.GetNext( pos );
        paramVals[ i ] = ( float )( wcstod( paramStr, NULL ) );
    }

    // pass the parameters to the MatrixManager -- param order is reversed as per function call requirement
    MatrixManager()->Add3DRotation( paramVals[ 2 ], paramVals[ 1 ], paramVals[ 0 ] );

    return TRUE;
}