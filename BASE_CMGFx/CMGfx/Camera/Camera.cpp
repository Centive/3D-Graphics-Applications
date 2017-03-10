//====================================================================================================
// Includes
//====================================================================================================
#include "stdafx.h"
#include "Camera.h"

#include "Viewport.h"
#include "Common/MiniMath.h"
#include "Common/Vector4.h"

//====================================================================================================
// Statics
//====================================================================================================
CCamera* CCamera::s_pInstance = NULL;

//====================================================================================================
// Class Implementations
//====================================================================================================

CCamera::CCamera() :
    m_LookUp( 0, 1, 0 ),
    m_fFOV( 90.0f ),
    m_fProjectionPlane( 0.0f ),
    m_fNearPlane( 0.0f ),
    m_fFarPlane( 0.0f ),
    m_bInitialized( false )
{
    // empty
}

//----------------------------------------------------------------------------------------------------

CCamera::~CCamera()
{
    // empty
}

//----------------------------------------------------------------------------------------------------

CCamera* CCamera::GetInstance( void )
{
    if ( NULL == s_pInstance )
    {
        s_pInstance = new CCamera;
    }
    return s_pInstance;
}

//----------------------------------------------------------------------------------------------------

void CCamera::Initialize( const CVector3& lookFrom, const CVector3& lookAt )
{
    // set look from ( origin )
    m_LookFrom = lookFrom;

    // compute the look vector -- interest minus camera position
    m_LookAt = lookAt - lookFrom;
    m_LookAt.Normalize();

    // compute side vector -- cross product of world up and look at vector
    m_LookSide = m_LookAt.Cross( CVector3( 0, 1, 0 ) );
    m_LookSide.Normalize();

    // compute the camera up vector -- cross product of look and side( right )
    m_LookUp = m_LookSide.Cross( m_LookAt );
    m_LookUp.Normalize();

    // compute view to world and world to view matrices
    m_ViewToWorld.SetColumns( CVector4( m_LookSide.x, m_LookSide.y, m_LookSide.z, 0 ),
                              CVector4( m_LookUp.x,   m_LookUp.y,   m_LookUp.z,   0 ),
                              CVector4( m_LookAt.x,   m_LookAt.y,   m_LookAt.z,   0 ),
                              CVector4( lookFrom.x,   lookFrom.y,   lookFrom.z,   1 ) );

    m_WorldToView.SetRows( CVector4( m_LookSide.x, m_LookSide.y, m_LookSide.z, -lookFrom.x ),
                           CVector4( m_LookUp.x,   m_LookUp.y,   m_LookUp.z,   -lookFrom.y ),
                           CVector4( m_LookAt.x,   m_LookAt.y,   m_LookAt.z,   -lookFrom.z ),
                           CVector4( 0, 0, 0, 1 ) );

    // initialize the FOV to 90 and initialize near and far planes
    SetFOV( 90.0f );

    // set init flag
    m_bInitialized = true;
}

//----------------------------------------------------------------------------------------------------

void CCamera::Reset( void )
{
    if ( false == m_bInitialized ) return;

    // reset camera attributes
    m_LookUp = CVector3( 0, 1, 0 );
    m_LookAt = CVector3( 0, 1, 0 );
    m_LookFrom = CVector3( 0, 1, 0 );
    m_LookSide = CVector3( 0, 1, 0 );

    // reset projection variables
    m_fFOV = 90.0f;
    m_fProjectionPlane = 0.0f;
    m_fNearPlane = 0.0f;
    m_fFarPlane = 0.0f;

    // reset matrices
    m_WorldToView.Identity();
    m_ViewToWorld.Identity();
    m_Projection.Identity();

    m_bInitialized = false;
}

//----------------------------------------------------------------------------------------------------

void CCamera::SetFOV( float fov )
{
    m_fFOV = fov;

    // compute the projection plane from FOV
    m_fProjectionPlane = 1 / tanf( DEG2RAD( fov ) * 0.5f );

    // set the near plane as projection plane + 0.1f units
    m_fNearPlane = m_fProjectionPlane + 0.1f;

    // set the far plane as projection plane + 1000.0f units
    m_fFarPlane = m_fProjectionPlane + 1000.0f;

    ComputeProjection();
}

//----------------------------------------------------------------------------------------------------

void CCamera::ComputeProjection( void )
{
    // get aspect ratio from the Viewport
    float aspect = Viewport()->GetAspectRatio();

    // check divide by zero
    ASSERT( 0 != aspect );

    // pre-calc far plane minus near plane
    float farSubNear = m_fFarPlane - m_fNearPlane;

    // check divide by zero
    ASSERT( 0 != farSubNear );

    // construct the projection matrix
    m_Projection.SetRows( CVector4( m_fProjectionPlane / aspect, 0.0f, 0.0f, 0.0f ),
                          CVector4( 0.0f, m_fProjectionPlane,          0.0f, 0.0f ),
                          CVector4( 0.0f, 0.0f, ( m_fFarPlane + m_fNearPlane ) / farSubNear,
                                    ( -2 * m_fNearPlane * m_fFarPlane ) / farSubNear ),
                          CVector4( 0.0f, 0.0f, 1.0f, 0.0f ) );
}