#include "stdafx.h"
#include "Common/MiniMath.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "Camera/Viewport.h"

using std::vector;

//====================================================================================================
// Statics
//====================================================================================================

CClipper* CClipper::s_pInstance = NULL;

//====================================================================================================
// Class Implementations
//====================================================================================================
CClipper* CClipper::GetInstance( void )
{
    if ( NULL == s_pInstance )
    {
        s_pInstance = new CClipper();
    }
    return s_pInstance;
}

//----------------------------------------------------------------------------------------------------
// BEGIN CLIPPING FUNCTIONS
//----------------------------------------------------------------------------------------------------
bool CClipper::ClipPoint( int x, int y )
{
    // skip clipping of clipping is set to "off"
    if ( false == m_bIsClip ) return true;

    // get the viewport from the viewport class
    CRect vp;
    Viewport()->GetViewport( vp );

    return ( x > vp.left && x < vp.right && y > vp.top && y < vp.bottom );
}

//----------------------------------------------------------------------------------------------------

bool CClipper::ClipLine( SVertex3& vtx1, SVertex3& vtx2 )
{
    // skip clipping of clipping is set to "off"
    if ( false == m_bIsClip ) return true;

    // using Cohen-Sutherland line clipping
    // http://www.cs.helsinki.fi/group/goa/viewing/leikkaus/lineClip.html
    /* ***OUT CODES***
                1001  |  1000  |  1010      LEFT   = 1st bit
            ----------------------------    RIGHT  = 2nd bit
                0001  |  0000  |  0010      BOTTOM = 3rd bit
            ----------------------------    TOP    = 4th bit
                0101  |  0100  |  0110
    */

    // get the viewport from the viewport class
    CRect vp;
    Viewport()->GetViewport( vp );

    // assign outcodes to each vertex
    const unsigned char OC_LEFT   = 1 << 0;
    const unsigned char OC_RIGHT  = 1 << 1;
    const unsigned char OC_BOTTOM = 1 << 2;
    const unsigned char OC_TOP    = 1 << 3;
    
    unsigned char code1 = 0, code2 = 0;
    {
        // left and right
        if      ( vtx1.point.x < vp.left )  code1 |= OC_LEFT;
        else if ( vtx1.point.x > vp.right ) code1 |= OC_RIGHT;
        if      ( vtx2.point.x < vp.left )  code2 |= OC_LEFT;
        else if ( vtx2.point.x > vp.right ) code2 |= OC_RIGHT;
        // bottom and top
        if      ( vtx1.point.y > vp.bottom ) code1 |= OC_BOTTOM;
        else if ( vtx1.point.y < vp.top )    code1 |= OC_TOP;
        if      ( vtx2.point.y > vp.bottom ) code2 |= OC_BOTTOM;
        else if ( vtx2.point.y < vp.top )    code2 |= OC_TOP;
    }
    
    // if bitwise OR yields 0000, trivially accept
    if ( ( code1 | code2 ) == 0 ) return true;

    // if bitwise AND DOES NOT yield 0000, trivially reject
    if ( ( code1 & code2 ) != 0 ) return false;

    // handle each bit of the outcode to clip endpoints to viewport
    // vars for LERP
    int dx, dy;
    float t;

    // handle vertex 1
    if      ( code1 & OC_LEFT )
    {
        dx = roundftoi( vtx2.point.x - vtx1.point.x );
        t = ( vp.left - vtx1.point.x ) / ( float )dx;
        vtx1 = Vertex3Lerp( vtx1, vtx2, t );
    }
    else if ( code1 & OC_RIGHT )
    {
        dx = roundftoi( vtx2.point.x - vtx1.point.x );
        t = ( vp.right - vtx1.point.x ) / ( float )dx;
        vtx1 = Vertex3Lerp( vtx1, vtx2, t );
    }
    else if ( code1 & OC_BOTTOM )
    {
        dy = roundftoi( vtx2.point.y - vtx1.point.y );
        t = ( vp.bottom - vtx1.point.y ) / ( float )dy;
        vtx1 = Vertex3Lerp( vtx1, vtx2, t );
    }
    else if ( code1 & OC_TOP )
    {
        dy = roundftoi( vtx2.point.y - vtx1.point.y );
        t = ( vp.top - vtx1.point.y ) / ( float )dy;
        vtx1 = Vertex3Lerp( vtx1, vtx2, t );
    }

    // handle vertex 2
    if      ( code2 & OC_LEFT )
    {
        dx = roundftoi( vtx1.point.x - vtx2.point.x );
        t = ( vp.left - vtx2.point.x ) / ( float )dx;
        vtx2 = Vertex3Lerp( vtx2, vtx1, t );
    }
    else if ( code2 & OC_RIGHT )
    {
        dx = roundftoi( vtx1.point.x - vtx2.point.x );
        t = ( vp.right - vtx2.point.x ) / ( float )dx;
        vtx2 = Vertex3Lerp( vtx2, vtx1, t );
    }
    else if ( code2 & OC_BOTTOM )
    {
        dy = roundftoi( vtx1.point.y - vtx2.point.y );
        t = ( vp.bottom - vtx2.point.y ) / ( float )dy;
        vtx2 = Vertex3Lerp( vtx2, vtx1, t );
    }
    else if ( code2 & OC_TOP )
    {
        dy = roundftoi( vtx1.point.y - vtx2.point.y );
        t = ( vp.top - vtx2.point.y ) / ( float )dy;
        vtx2 = Vertex3Lerp( vtx2, vtx1, t );
    }

    // recursive call
    return ClipLine( vtx1, vtx2 );
}

//----------------------------------------------------------------------------------------------------

bool CClipper::ClipTriangle( vector< SVertex3 >& vBuffer, vector< SVertex3 >& newVertices )
{
    // skip clipping of clipping is set to "off"
    if ( false == m_bIsClip ) return true;

    // using Sutherland-Hodgman clipping
    // http://en.wikipedia.org/wiki/Sutherland-Hodgeman

    // static enum for tracking which plane is currently being clipped
    static EClipPlane clipPlane = CP_LEFT;

    unsigned int uiBufSize = vBuffer.size();

    // vertex 2 begins at the end of the vertex buffer
    SVertex3 v2 = vBuffer[ uiBufSize - 1 ];

    // iterate through vertices to clip along chosen clip plane
    for ( unsigned int i = 0; i < uiBufSize; ++i )
    {
        SVertex3 v1 = vBuffer[ i ];
        if ( true == IsInClipBounds( clipPlane, v1 ) )
        {
            if ( false == IsInClipBounds( clipPlane, v2 ) )
            {
                newVertices.push_back( IntersectWithPlane( v2, v1, clipPlane ) );
            }
            newVertices.push_back( v1 );
        }
        else if ( true == IsInClipBounds( clipPlane, v2 ) )
        {
            newVertices.push_back( IntersectWithPlane( v1, v2, clipPlane ) );
        }

        v2 = v1;
    }

    // recursive call with new clip plane or return false for failure ( poly out of clip area )
    // case 1 -  clipped all planes and the output vector DOES contain vertices
    if ( CP_TOP == clipPlane && 0 != newVertices.size() )
    {
        clipPlane = CP_LEFT;
        return true;
    }
    // case 2 - no vertices output, means the poly is completely outside the clip plane
    else if ( 0 == newVertices.size() )
    {
        clipPlane = CP_LEFT;
        return false;
    }
    // case 3 - recursively call clip triangle for the next plane to be processed
    else
    {
        clipPlane = ( EClipPlane )( clipPlane + 1 );
        vBuffer.clear();
        return ClipTriangle( newVertices, vBuffer );
    }
}

//----------------------------------------------------------------------------------------------------

bool CClipper::IsInClipBounds( EClipPlane clipPlane, const SVertex3& v )
{
    // get the viewport from the viewport class
    CRect vp;
    Viewport()->GetViewport( vp );

    switch ( clipPlane )
    {
    case CP_LEFT:   return ( v.point.x > vp.left );
    case CP_BOTTOM: return ( v.point.y < vp.bottom );
    case CP_RIGHT:  return ( v.point.x < vp.right );
    case CP_TOP:    return ( v.point.y > vp.top );
    default:        return false;
    }
}

//----------------------------------------------------------------------------------------------------

SVertex3 CClipper::IntersectWithPlane( const SVertex3& vtx1, const SVertex3& vtx2, EClipPlane planeFlag )
{
    float t = 0.0f;

    // get the viewport from the viewport class
    CRect vp;
    Viewport()->GetViewport( vp );

    // clip according to desired plane
    switch ( planeFlag )
    {
    case CP_LEFT:
        {
            float dx = vtx2.point.x - vtx1.point.x;
            if ( 0 != dx ) t = ( vp.left - vtx1.point.x ) / dx;
        }
        break;
    case CP_RIGHT:
        {
            float dx = vtx2.point.x - vtx1.point.x;
            if ( 0 != dx ) t = ( vp.right - vtx1.point.x ) / dx;
        }
        break;
    case CP_BOTTOM:
        {
            float dy = vtx2.point.y - vtx1.point.y;
            if ( 0 != dy ) t = ( vp.bottom - vtx1.point.y ) / dy;
        }
        break;
    case CP_TOP:
        {
            float dy = vtx2.point.y - vtx1.point.y;
            if ( 0 != dy ) t = ( vp.top - vtx1.point.y ) / dy;
        }
        break;
    default:
        break;
    }
    return Vertex3Lerp( vtx1, vtx2, t );
}

//----------------------------------------------------------------------------------------------------
// END CLIPPING FUNCTIONS
//----------------------------------------------------------------------------------------------------

CClipper::~CClipper( void )
{
    // empty destructor
}