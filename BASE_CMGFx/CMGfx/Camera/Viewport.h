#pragma once

//====================================================================================================
// Includes
//====================================================================================================
#include "Common/Matrix44.h"
#include "Common/Vector2.h"

#include <vector>

//====================================================================================================
// Class
//====================================================================================================
class CViewport
{
public:
    ~CViewport();

    // Function to gain access to singleton instance
    static CViewport* GetInstance( void );

    // Function to draw a white bounding box for viewport
    void DrawViewport( void );

    // Function to reset the viewport back to default values
    void ResetViewport( int windowWidth, int windowHeight, bool bIsNewWindow = true );

    // Function to set the visibility of the viewport's bounds
    void SetViewportVisible( bool bShowViewport ) { m_bShowViewport = bShowViewport; }

    // Function to check whether the current pixel should be drawn given the z value
    bool CheckZBufferValue( int x, int y, float z );
    void ResetZBuffer( void );

    // Gets
    const CMatrix44& GetNDCtoScreen( void ) { return m_NDCtoScreen; }

    void GetViewport( CRect& rect ) const;
    float GetAspectRatio( void ) { return m_fAspectRatio; }

    bool GetIsBackfaceCull( void ) const { return m_bIsBackfaceCull; }
    bool GetIsZBuffering( void ) const { return m_bIsZBuffering; }

    // Sets
    void SetViewport( float xMin, float yMin, float width, float height );
    void SetBackfaceCull( bool bIsCull ) { m_bIsBackfaceCull = bIsCull; }
    void SetZBuffering( bool bIsZBuffering ) { m_bIsZBuffering = bIsZBuffering; }

protected:
    // protected operations for singleton
    CViewport();
    CViewport( const CViewport& );
    CViewport& operator=( const CViewport& );

private:
    /* members */
    CVector2 m_Origin;                  // viewport top left corner
    float    m_fWidth;                  // width of viewport
    UINT     m_uiWindowWidth;           // current width of window
    float    m_fHeight;                 // height of viewport
    UINT     m_uiWindowHeight;          // current height of window

    float    m_fAspectRatio;            // aspect ratio = width / height -- **for the viewport

    CMatrix44 m_NDCtoScreen;            // stored matrix for converting from NDC to screen space
 
    int**    m_ppZBuffer;               // 2-dimensional int-array for storing z buffer values
    bool     m_bIsZBuffering;           // flag for turning z buffering on or off

    bool     m_bShowViewport;           // flag for rendering
    bool     m_bIsBackfaceCull;         // flag for turning backface culling on or off

    static CViewport* s_pInstance;      // singleton instance

    /* private member functions */
    void ComputeNDCtoScreen( void );
    void CreateZBuffer( void );
    void DestroyZBuffer( void );
};

//====================================================================================================
// Singleton Accessor
//====================================================================================================
static CViewport* Viewport( void )
{
    return CViewport::GetInstance();
}