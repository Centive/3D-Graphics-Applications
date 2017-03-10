//====================================================================================================
// Includes
//====================================================================================================
#include "stdafx.h"
#include "GeoRouter.h"
#include "Clipper.h"
#include "Rasterizer.h"
#include "Camera/Camera.h"
#include "Camera/Viewport.h"
#include "States/StateManager.h"
#include "States/PrimManager.h"
#include "States/MatrixManager.h"
#include "Common/Vector3.h"
#include "LightManager.h"

//====================================================================================================
// Statics
//====================================================================================================
CGeoRouter* CGeoRouter::s_pInstance = NULL;

//====================================================================================================
// Class Implementation
//====================================================================================================
CGeoRouter::~CGeoRouter( void )
{
    // empty
}

//----------------------------------------------------------------------------------------------------

CGeoRouter* CGeoRouter::GetInstance( void )
{
    if ( NULL == s_pInstance )
    {
        s_pInstance = new CGeoRouter;
    }
    return s_pInstance;
}

//----------------------------------------------------------------------------------------------------

void CGeoRouter::RouteCurrentGeometry( std::vector< SVertex3 >& vBuffer, bool bIs3DGeo )
{
    // number of vertices in vertex buffer
    UINT uiNumVertices = vBuffer.size();

    // current primitive and fill states
    EPrimitiveType desiredPrimitive = PrimManager()->GetCurrentPrimitiveMode();
    EFillmode      currentFillmode  = StateManager()->GetCurrentFillmode();


	for (UINT i = 0; i < uiNumVertices; ++i)
	{
		SVertex3& v = vBuffer[i];
		CVector3 normalPoints;
		normalPoints.x = v.point.x;
		normalPoints.y = v.point.y;
		normalPoints.z = v.point.z;
	
		v.color = CLightManager::getInstance()->CombinedLightEquation(v.point, normalPoints, Camera()->GetLookFrom());
	}

    // If fill mode is point mode, treat all primitives as just points
    if ( currentFillmode == EFillmode_POINT ) desiredPrimitive = EPrimitiveType_POINT;

    // apply 2D OR 3D transformations
    if ( true == bIs3DGeo ) Transform3DGeo( vBuffer );
    else                    Transform2DGeo( vBuffer );

    // Clip and Rasterize
    switch ( desiredPrimitive )
    {
    case EPrimitiveType_POINT:
        {
            // draw all points
            for ( UINT i = 0; i < uiNumVertices; ++i )
            {
                SVertex3& v = vBuffer[ i ];

                // Check if within viewport, true means should clip
                if ( Clipper()->ClipPoint( ( int )( v.point.x + 0.5f ), ( int )( v.point.y + 0.5f ) ) )
                {
                    Rasterizer()->DrawPoint( v.point.x, v.point.y, v.point.z, v.color.r, v.color.g, v.color.b );
                }
            }
        }
        break;
    case EPrimitiveType_LINE:
        {
            // not enough points to form a line
            if ( uiNumVertices < 2 ) break;

            // draw all lines
            for ( UINT i = 1; i < uiNumVertices; i += 2 )
            {
                // Clip to viewport
                if   ( Clipper()->ClipLine( vBuffer[ i - 1 ], vBuffer[ i ] ) )
                {
                    Rasterizer()->DrawLine( vBuffer[ i - 1 ], vBuffer[ i ] );
                }
            }
        }
        break;
    case EPrimitiveType_TRIANGLE:
        {
            // not enough vertices to form a triangle
            if ( uiNumVertices < 3 ) break;

            // draw all triangles
            for ( UINT i = 2; i < uiNumVertices; i += 3 )
            {
                SVertex3 &vtx1 = vBuffer[ i - 2 ],
                         &vtx2 = vBuffer[ i - 1 ],
                         &vtx3 = vBuffer[ i ];

                // check for all same y coord
                if ( vtx1.point.y == vtx2.point.y && vtx1.point.y == vtx3.point.y ) continue;

                // clip only if in fill mode, will be deferred to other drawing modes otherwise
                if ( currentFillmode != EFillmode_FILL )
                {
                    Rasterizer()->DrawTriangle( vtx1, vtx2, vtx3 );
                }
                else
                {
                    // perform clipping, may return a new poly with more than 3 vertices
                    std::vector< SVertex3 > polyBuffer;
                    std::vector< SVertex3 > newVerts;
                    polyBuffer.push_back( vtx1 ); polyBuffer.push_back( vtx2 ); polyBuffer.push_back( vtx3 );
                    if ( false == Clipper()->ClipTriangle( polyBuffer, newVerts ) ) continue;

                    // split new poly into triangles and draw
                    for ( unsigned int i = 2; i < polyBuffer.size(); ++i )
                    {
                        // rasterize the triangle given three vertices
                        Rasterizer()->DrawTriangle( polyBuffer.at( 0 ), polyBuffer.at( i - 1 ), polyBuffer.at( i ) );
                    }
                }
            }
        }
        break;
    default:
        break;
    }
}

//----------------------------------------------------------------------------------------------------

void CGeoRouter::Transform2DGeo( std::vector< SVertex3 >& vBuffer )
{
    // Apply the current matrix transform to all of the vertices
    CMatrix33 currentTransform = MatrixManager()->GetCurrent2DTransform();
    if ( false == currentTransform.IsIdentity() )
    {
        CVector3 currentVector;
        currentVector.z = 1;        // homogeneous coordinate
        for ( UINT i = 0; i < vBuffer.size(); ++i )
        {
            // transfer point values to a CVector3 for Matrix Calculations
            currentVector.x = vBuffer[ i ].point.x;
            currentVector.y = vBuffer[ i ].point.y;

            // perform transform
            currentVector = currentTransform * currentVector;

            // replace transformed points
            vBuffer[ i ].point.x = currentVector.x;
            vBuffer[ i ].point.y = currentVector.y;
        }
    }
}

//----------------------------------------------------------------------------------------------------

void CGeoRouter::Transform3DGeo( std::vector< SVertex3 >& vBuffer )
{
    // number of vertices in vertex buffer
    UINT uiNumVertices = vBuffer.size();
    if ( 0 == uiNumVertices ) return;

    // retrieve all the current matrices
    CMatrix44 matWorld = MatrixManager()->GetCurrent3DTransform();
    CMatrix44 matWorldToView = Camera()->GetWorldToView();
    CMatrix44 matProjection = Camera()->GetProjection();
    CMatrix44 matNDCtoScreen = Viewport()->GetNDCtoScreen();

    // matrix concatenation -- view and projection
    CMatrix44 matCombined = matProjection * matWorldToView;

    // current primitive and fill states
    EPrimitiveType desiredPrimitive = PrimManager()->GetCurrentPrimitiveMode();
    EFillmode      currentFillmode  = StateManager()->GetCurrentFillmode();

    // If fill mode is point mode, treat all primitives as just points
    if ( currentFillmode == EFillmode_POINT ) desiredPrimitive = EPrimitiveType_POINT;

    // apply transformations to all vertices -- and backface culling to polygons( triangles )
    switch ( desiredPrimitive )
    {
    case EPrimitiveType_POINT:
    case EPrimitiveType_LINE:
        {
            for ( UINT i = 0; i < uiNumVertices; ++i )
            {
                CVector4 &v = vBuffer[ i ].point;

                // apply the world transform
                v = matWorld * v;

                // apply view and projection matrices
                v = matCombined * v;

                // divide each element by w to get back to 3D space
                if ( 1 != v.w )
                {
                    ASSERT( 0 != v.w );
                    float w = v.w;
                    v.x /= w; v.y /= w; v.z /= w; v.w = 1.0f;
                }

                // apple the NDC to screen space matrix
                v = matNDCtoScreen * v;
            }
        }
        break;
    case EPrimitiveType_TRIANGLE:
        {
            for ( UINT i = 2; i < uiNumVertices; i += 3 )
            {
                CVector4 &v1 = vBuffer[ i - 2 ].point;
                CVector4 &v2 = vBuffer[ i - 1 ].point;
                CVector4 &v3 = vBuffer[ i ].point;

                // apply the world transform
                v1 = matWorld * v1;
                v2 = matWorld * v2;
                v3 = matWorld * v3;


                // apply view and projection matrices
                v1 = matCombined * v1;
                v2 = matCombined * v2;
                v3 = matCombined * v3;

                // perform backface culling if turned on
                if ( true == Viewport()->GetIsBackfaceCull() )
                {
                    if ( true == IsBackface( CVector3( v1 ), CVector3( v2 ), CVector3( v3 ) ) ) continue;
                }

                // divide each element by w to get back to 3D space
                if ( 1 != v1.w )
                {
                    ASSERT( 0 != v1.w );
                    float w = v1.w;
                    v1.x /= w; v1.y /= w; v1.z /= w; v1.w = 1.0f;
                }
                if ( 1 != v2.w )
                {
                    ASSERT( 0 != v2.w );
                    float w = v2.w;
                    v2.x /= w; v2.y /= w; v2.z /= w; v2.w = 1.0f;
                }
                if ( 1 != v3.w )
                {
                    ASSERT( 0 != v3.w );
                    float w = v3.w;
                    v3.x /= w; v3.y /= w; v3.z /= w; v3.w = 1.0f;
                }

                // apple the NDC to screen space matrix
                v1 = matNDCtoScreen * v1;
                v2 = matNDCtoScreen * v2;
                v3 = matNDCtoScreen * v3;
            }
        }
        break;
    default:
        break;
    }
}

//----------------------------------------------------------------------------------------------------

bool CGeoRouter::IsBackface( const CVector3& vtx1, const CVector3& vtx2, const CVector3& vtx3 )
{
    // get camera interest vector -- app will fail if camera not initialized -- (assert)
    CVector3 cameraInterest = Camera()->GetInterest();

    // compute the triangle's normal vector
    CVector3 polyNormal = ( vtx2 - vtx1 ).Cross( vtx3 - vtx2 );
    polyNormal.Normalize();

    // compute dot product between two vectors
    float dotProduct = polyNormal.Dot( vtx1 );

    // if dot product is less than 0, normal is facing away
    if ( 0 > dotProduct ) return true;
    else return false;
}