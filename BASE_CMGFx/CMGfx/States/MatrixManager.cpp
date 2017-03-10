#include "stdafx.h"
#include "MatrixManager.h"
#include "Common/Vector3.h"
#include "Common/MiniMath.h"

//====================================================================================================
// Statics
//====================================================================================================

CMatrixManager* CMatrixManager::s_pInstance = NULL;

//====================================================================================================
// Class
//====================================================================================================

//====================================================================================================
// Function Definitions
//====================================================================================================

CMatrixManager::CMatrixManager()
{
    m_Current2DMatrix.Identity();
}

//----------------------------------------------------------------------------------------------------

CMatrixManager* CMatrixManager::GetInstance( void )
{
    if ( NULL == s_pInstance )
    {
        s_pInstance = new CMatrixManager();
    }
    return s_pInstance;
}

//----------------------------------------------------------------------------------------------------

void CMatrixManager::Add2DTranslation( float tx, float ty )
{
    if ( false == m_Current2DMatrix.IsIdentity() )
    {
        CMatrix33 newTransform;
        newTransform.Translation( tx, ty );

        m_Current2DMatrix = newTransform * m_Current2DMatrix;
    }
    else
    {
        m_Current2DMatrix.Translation( tx, ty );
    }
}

//----------------------------------------------------------------------------------------------------

void CMatrixManager::Add2DScaling( float sx, float sy )
{
    if ( false == m_Current2DMatrix.IsIdentity() )
    {
        CMatrix33 newTransform;
        newTransform.Scaling( CVector3( sx, sy, 1 ) );

        m_Current2DMatrix = newTransform * m_Current2DMatrix;
    }
    else
    {
        m_Current2DMatrix.Scaling( CVector3( sx, sy, 1 ) );
    }
}

//----------------------------------------------------------------------------------------------------

void CMatrixManager::Add2DRotation( float rz )
{
    // rz is negated for counter-clockwise rotation
    if ( false == m_Current2DMatrix.IsIdentity() )
    {
        CMatrix33 newTransform;
        newTransform.RotationZ( DEG2RAD( -rz ) );

        m_Current2DMatrix = newTransform * m_Current2DMatrix;
    }
    else
    {
        m_Current2DMatrix.RotationZ( DEG2RAD( -rz ) );
    }
}

//----------------------------------------------------------------------------------------------------

void CMatrixManager::Add2DShearing( float shx, float shy )
{
    if ( false == m_Current2DMatrix.IsIdentity() )
    {
        CMatrix33 newTransform;
        newTransform.Shear( shx, shy );

        m_Current2DMatrix = newTransform * m_Current2DMatrix;
    }
    else
    {
        m_Current2DMatrix.Shear( shx, shy );
    }
}

//----------------------------------------------------------------------------------------------------

void CMatrixManager::Add3DTranslation( const CVector3& translation )
{
    if ( false == m_Current3DMatrix.IsIdentity() )
    {
        CMatrix44 newTransform;
        newTransform.Translation( translation );

        m_Current3DMatrix = newTransform * m_Current3DMatrix;
    }
    else
    {
        m_Current3DMatrix.Translation( translation );
    }
}

//----------------------------------------------------------------------------------------------------

void CMatrixManager::Add3DScaling( const CVector3& scaling )
{
    if ( false == m_Current3DMatrix.IsIdentity() )
    {
        CMatrix44 newTransform;
        newTransform.Scaling( scaling );

        m_Current3DMatrix = newTransform * m_Current3DMatrix;
    }
    else
    {
        m_Current3DMatrix.Scaling( scaling );
    }
}

//----------------------------------------------------------------------------------------------------

void CMatrixManager::Add3DRotation( float rz, float ry, float rx )
{
    // convert degrees to radians before calling function and negate values for counter-clockwise rotation
    if ( false == m_Current3DMatrix.IsIdentity() )
    {
        CMatrix44 newTransform;
        newTransform.Rotation( DEG2RAD( rz ), DEG2RAD( ry ), DEG2RAD( rx ) );

        m_Current3DMatrix = newTransform * m_Current3DMatrix;
    }
    else
    {
        m_Current3DMatrix.Rotation( DEG2RAD( rz ), DEG2RAD( ry ), DEG2RAD( rx ) );
    }
}

//----------------------------------------------------------------------------------------------------

CMatrixManager::~CMatrixManager( void )
{
    // empty destructor
}