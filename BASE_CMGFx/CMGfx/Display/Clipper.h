#pragma once

//====================================================================================================
// Includes
//====================================================================================================

#include "Common/Vertex2.h"
#include "Common/Vertex3.h"
#include <vector>

//====================================================================================================
// Enums
//====================================================================================================

enum EClipPlane { CP_LEFT, CP_BOTTOM, CP_RIGHT, CP_TOP };

//====================================================================================================
// Class
//====================================================================================================
class CClipper
{
public:
    ~CClipper( void );

    // Instance Retrieval
    static CClipper* GetInstance( void );
    
    // Clipping Functions
    bool ClipPoint( int x, int y );
    bool ClipPoint( int x, int y, int z );
    bool ClipLine( SVertex3& vtx1, SVertex3& vtx2 );
    bool ClipTriangle( std::vector< SVertex3 >& vBuffer, std::vector< SVertex3 >& newVertices );

    // gets
    bool IsClipping( void ) const { return m_bIsClip; }

    // sets
    void SetClipping( bool bClip ) { m_bIsClip = bClip; }

protected:
    // Protected Operations
    CClipper() : m_bIsClip( true ) {}
    CClipper( const CClipper& );
    CClipper& operator=( const CClipper& );

private:
    // members
    bool m_bIsClip;

    // static singleton instance
    static CClipper*    s_pInstance;

    // private helper functions
    bool IsInClipBounds( EClipPlane clipPlane, const SVertex3& v );
    SVertex3 IntersectWithPlane( const SVertex3& vtx1, const SVertex3& vtx2, EClipPlane planeFlag );
};

//====================================================================================================
// Static Function Accessor
//====================================================================================================
static CClipper* Clipper( void )
{
    return CClipper::GetInstance();
}