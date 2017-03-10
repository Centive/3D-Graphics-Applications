#include "StdAfx.h"
#include "Matrix2D.h"
#include "ScriptParser.h"
#include "States/MatrixManager.h"

//====================================================================================================
// Class Function Implementations
//====================================================================================================

BOOL CCmdMat2DIdentity::execute( CString &params )
{
    MatrixManager()->Set2DIdentity();
    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdMat2DTranslate::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 2 parameters -- tx and ty
    const int numParams = 2;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    // get parameters and convert to float values
    float paramVals[ numParams ];
    POSITION pos = paramStrList.GetHeadPosition();
    for ( int i = 0; i < numParams; ++i )
    {
        CString paramStr = paramStrList.GetNext( pos );
        paramVals[ i ] = ( float )( wcstod( paramStr, NULL ) );
    }

    // pass the parameters to the MatrixManager
    MatrixManager()->Add2DTranslation( paramVals[ 0 ], paramVals[ 1 ] );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdMat2DScale::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 2 parameters -- sx and sy
    const int numParams = 2;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    // get parameters and convert to float values
    float paramVals[ numParams ];
    POSITION pos = paramStrList.GetHeadPosition();
    for ( int i = 0; i < numParams; ++i )
    {
        CString paramStr = paramStrList.GetNext( pos );
        paramVals[ i ] = ( float )( wcstod( paramStr, NULL ) );
    }

    // pass the parameters to the MatrixManager
    MatrixManager()->Add2DScaling( paramVals[ 0 ], paramVals[ 1 ] );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdMat2DRotate::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 1 parameter -- rz
    const int numParams = 1;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    // get parameter and convert to float value
    float paramVal;
    POSITION pos = paramStrList.GetHeadPosition();
    paramVal = ( float )( wcstod( paramStrList.GetNext( pos ), NULL ) );

    // pass the parameter to the MatrixManager
    MatrixManager()->Add2DRotation( paramVal );

    return TRUE;
}

//----------------------------------------------------------------------------------------------------

BOOL CCmdMat2DShear::execute( CString &params )
{
    // Decode parameters
    CStringList paramStrList;
    CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

    // should be 2 parameters -- shx and shy
    const int numParams = 2;
    if ( paramStrList.GetCount() < numParams )
    {
        return FALSE;
    }

    // get parameters and convert to float values
    float paramVals[ numParams ];
    POSITION pos = paramStrList.GetHeadPosition();
    for ( int i = 0; i < numParams; ++i )
    {
        CString paramStr = paramStrList.GetNext( pos );
        paramVals[ i ] = ( float )( wcstod( paramStr, NULL ) );
    }

    // pass the parameters to the MatrixManager
    MatrixManager()->Add2DShearing( paramVals[ 0 ], paramVals[ 1 ] );

    return TRUE;
}