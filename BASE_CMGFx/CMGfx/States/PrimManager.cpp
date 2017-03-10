#include "stdafx.h"
#include "PrimManager.h"
#include "Display/GeoRouter.h"

//====================================================================================================
// Statics
//====================================================================================================
CPrimManager* CPrimManager::s_pInstance = NULL;

//====================================================================================================
// Class Implementation
//====================================================================================================

CPrimManager* CPrimManager::GetInstance( void )
{
    if ( NULL == s_pInstance )
    {
        s_pInstance = new CPrimManager();
    }
    return s_pInstance;
}

//----------------------------------------------------------------------------------------------------

void CPrimManager::BeginDraw( EPrimitiveType ePrimType )
{
    if ( false == m_bDrawBegin )
    {
        m_CurrentPrimitive = ePrimType;
        m_Vertex2DBuffer.clear();
        m_Vertex3DBuffer.clear();
        m_bDrawBegin = true;
    }
}

//----------------------------------------------------------------------------------------------------

void CPrimManager::AddVertex2D( const SVertex3& vertex )
{
    if ( true == m_bDrawBegin )
    {
        m_Vertex2DBuffer.push_back( vertex );
    }
}

//----------------------------------------------------------------------------------------------------

void CPrimManager::AddVertex3D( const SVertex3& vertex )
{
    if ( true == m_bDrawBegin )
    {
        m_Vertex3DBuffer.push_back( vertex );
    }
}

//----------------------------------------------------------------------------------------------------

void CPrimManager::EndDraw( void )
{
    // drawbegin command has not been invoked
    if ( false == m_bDrawBegin ) return;

    // send the current primitive through the pipeline via the GeoRouter
    GeoRouter()->RouteCurrentGeometry( m_Vertex2DBuffer, false );
    GeoRouter()->RouteCurrentGeometry( m_Vertex3DBuffer, true );        // true indicates 3D Geo

    // reset flag
    m_bDrawBegin = false;

    // clear vertex buffer
    m_Vertex2DBuffer.clear();
    m_Vertex3DBuffer.clear();
}

//----------------------------------------------------------------------------------------------------

CPrimManager::~CPrimManager( void )
{
    // empty destructor
}