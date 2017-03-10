#pragma once

//====================================================================================================
// Includes
//====================================================================================================
#include <vector>
#include "Common/Vector3.h"
#include "Common/Vertex2.h"
#include "Common/Vertex3.h"

//====================================================================================================
// Class
//====================================================================================================
class CGeoRouter
{
public:
    ~CGeoRouter( void );

    // function to retrieve singleton instance
    static CGeoRouter* GetInstance( void );

    // function to initiate the router for current 2D or 3D geometry
    void RouteCurrentGeometry( std::vector< SVertex3 >& vBuffer, bool bIs3DGeo = true );

protected:
    // Protected Operations
    CGeoRouter() {}
    CGeoRouter( const CGeoRouter& ) {}
    CGeoRouter& operator=( const CGeoRouter& ) {}

private:
    // static singleton instance
    static CGeoRouter*    s_pInstance;

    /* private member functions */
    void Transform2DGeo( std::vector< SVertex3 >& vBuffer );
    void Transform3DGeo( std::vector< SVertex3 >& vBuffer );
    bool IsBackface( const CVector3& vtx1, const CVector3& vtx2, const CVector3& vtx3 );
};

//====================================================================================================
// Static Function Accessor
//====================================================================================================
static CGeoRouter* GeoRouter( void )
{
    return CGeoRouter::GetInstance();
}