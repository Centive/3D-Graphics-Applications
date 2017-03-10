//====================================================================================================
// Includes
//====================================================================================================
#include "stdafx.h"
#include "Viewport.h"
#include "gl/gl.h"
#include "Common/Common.h"
#include "Display/Rasterizer.h"

//====================================================================================================
// Statics
//====================================================================================================
CViewport* CViewport::s_pInstance = NULL;

//====================================================================================================
// Class Implementations
//====================================================================================================

CViewport::CViewport() :
    m_fWidth( 0.0f ),
    m_fHeight( 0.0f ),
    m_fAspectRatio( 0.0f ),
    m_ppZBuffer( NULL ),
    m_bShowViewport( false ),
    m_bIsBackfaceCull( false ),
    m_bIsZBuffering( false )
{
    ResetViewport( WINDOW_WIDTH, WINDOW_HEIGHT );
}

//----------------------------------------------------------------------------------------------------

CViewport::~CViewport()
{
    DestroyZBuffer();
}

//----------------------------------------------------------------------------------------------------

CViewport* CViewport::GetInstance( void )
{
    if ( NULL == s_pInstance )
    {
        s_pInstance = new CViewport;
    }
    return s_pInstance;
}

//----------------------------------------------------------------------------------------------------

void CViewport::DrawViewport( void )
{
    if ( true == m_bShowViewport )
    {
        Rasterizer()->SetColor( 1.0f, 1.0f, 1.0f );
        glBegin( GL_LINE_STRIP );
        glVertex2i( ( int )m_Origin.x,                    ( int )m_Origin.y - 1 );
        glVertex2i( ( int )m_Origin.x,                    ( int )( m_Origin.y + m_fHeight ) );
        glVertex2i( ( int )( m_Origin.x + m_fWidth + 1 ), ( int )( m_Origin.y + m_fHeight ) );
        glVertex2i( ( int )( m_Origin.x + m_fWidth + 1 ), ( int )m_Origin.y - 1 );
        glVertex2i( ( int )m_Origin.x,                    ( int )m_Origin.y - 1 );
        glEnd();
    }
}

//----------------------------------------------------------------------------------------------------

void CViewport::ResetViewport( int windowWidth, int windowHeight, bool bIsNewWindow )
{
    // destroy the Z Buffer if it exists
    DestroyZBuffer();

    // set new attributes
    m_Origin.Zero();
    m_uiWindowWidth  = windowWidth;
    m_uiWindowHeight = windowHeight;

    // check for viewport not set
    if ( true == bIsNewWindow )
    {
        m_fWidth  = ( float )windowWidth;
        m_fHeight = ( float )windowHeight;
    }

    // Create new Z Buffer
    CreateZBuffer();

    // compute aspect ratio
    m_fAspectRatio = ( float )WINDOW_WIDTH / WINDOW_HEIGHT;

    // compute NDC to Screen matrix
    ComputeNDCtoScreen();

    // TODO: reset flags??
}

//----------------------------------------------------------------------------------------------------

void CViewport::GetViewport( CRect& rect ) const
{
    rect.left   = ( LONG )m_Origin.x;
    rect.top    = ( LONG )m_Origin.y;
    rect.right  = ( LONG )( rect.left + m_fWidth );
    rect.bottom = ( LONG )( rect.top  + m_fHeight );
}

//----------------------------------------------------------------------------------------------------

void CViewport::SetViewport( float xMin, float yMin, float width, float height )
{
    // set attributes
    m_Origin.x = xMin;
    m_Origin.y = yMin;
    m_fWidth   = width;
    m_fHeight  = height;

    // compute aspect ratio
    ASSERT( 0 < height );
    ASSERT( 0 < width );
    m_fAspectRatio = width / height;

    // compute NDC to Screen matrix
    ComputeNDCtoScreen();
}

//----------------------------------------------------------------------------------------------------

bool CViewport::CheckZBufferValue( int x, int y, float z )
{
    // z buffering is turned off
    if ( false == m_bIsZBuffering || NULL == m_ppZBuffer ) return true;

    // if outside of screen bounds
    if ( x < 0 || x >= ( int )m_uiWindowWidth || y < 0 || y >= ( int )m_uiWindowHeight ) return false;

    // calculate integer z buffer value
    int zVal = ( int )( (1 << 16) * sizeof( int ) * z );

    // store new value if less than previous ( closer )
    if ( zVal <= m_ppZBuffer[ y ][ x ] )
    {
        int val = m_ppZBuffer[ y ][ x ];
        m_ppZBuffer[ y ][ x ] = zVal;
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------

void CViewport::ResetZBuffer( void )
{
    for ( UINT y = 0; y < m_uiWindowHeight; ++y )
    {
        for ( UINT x = 0; x < m_uiWindowWidth; ++x )
        {
            m_ppZBuffer[ y ][ x ] = 512000;
        }
    }
}

//----------------------------------------------------------------------------------------------------

void CViewport::ComputeNDCtoScreen( void )
{
    float halfWidth = m_fWidth * 0.5f;
    float halfHeight = m_fHeight * 0.5f;
    // construct NDC to screen space matrix
    m_NDCtoScreen.SetRows( CVector4( halfWidth,   0.0f, 0.0f, halfWidth  + m_Origin.x ),
                           CVector4( 0.0f, -halfHeight, 0.0f, halfHeight + m_Origin.y ),
                           CVector4( 0.0f, 0.0f, 0.5f, 0.5f ),
                           CVector4( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

//----------------------------------------------------------------------------------------------------

void CViewport::CreateZBuffer( void )
{
    // create new Z Buffer
    m_ppZBuffer = new int*[ m_uiWindowHeight ];
    ASSERT( NULL != m_ppZBuffer );
    for ( UINT i = 0; i < m_uiWindowHeight; ++i )
    {
        m_ppZBuffer[ i ] = new int[ m_uiWindowWidth ];
        ASSERT( NULL != m_ppZBuffer[ i ] );
    }

    ResetZBuffer();
}

//----------------------------------------------------------------------------------------------------

void CViewport::DestroyZBuffer( void )
{
    // clean up Z Buffer
    if ( NULL != m_ppZBuffer )
    {
        ASSERT( 0 < m_uiWindowHeight );
        for ( UINT i = 0; i < m_uiWindowHeight; ++i )
        {
            if ( NULL != m_ppZBuffer[ i ] )
            {
                delete [] m_ppZBuffer[ i ];
                m_ppZBuffer[ i ] = NULL;
            }
        }
        delete [] m_ppZBuffer;
        m_ppZBuffer = NULL;
    }
}