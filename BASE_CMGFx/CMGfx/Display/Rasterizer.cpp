#include "StdAfx.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "Common/MiniMath.h"
#include "Clipper.h"
#include "Rasterizer.h"
#include "Camera/Viewport.h"
#include "States/StateManager.h"

//====================================================================================================
// Statics
//====================================================================================================
CRasterizer* CRasterizer::pinstance = 0;// initialize pointer

//----------------------------------------------------------------------------------------------------

CRasterizer* CRasterizer::Instance () 
{
	if (pinstance == 0)  // is it the first call?
	{  
		pinstance = new CRasterizer; // create sole instance
	}
	return pinstance; // address of sole instance
}

//----------------------------------------------------------------------------------------------------

void CRasterizer::SetColor( float r, float g, float b )
{
	// Set OpenGL color
	glColor3f( r, g, b );
}

//----------------------------------------------------------------------------------------------------

void CRasterizer::SetColor( const CColor& color )
{
    glColor3f( color.r, color.g, color.b );
}

//----------------------------------------------------------------------------------------------------

void CRasterizer::DrawPoint( int x, int y )
{
	// Draw OpenGL pixel
	glBegin( GL_POINTS );
	glVertex2i( x, y );
	glEnd();
}

//----------------------------------------------------------------------------------------------------

void CRasterizer::DrawPoint( float x, float y )
{
	// Draw OpenGL pixel
	glBegin( GL_POINTS );
	glVertex2i( ( int )( x + 0.5f ), ( int )( y + 0.5f ) );
	glEnd();
}

//----------------------------------------------------------------------------------------------------

void CRasterizer::DrawPoint( float x, float y, float r, float g, float b )
{
	SetColor( r, g, b );
	DrawPoint( x, y );
}

//----------------------------------------------------------------------------------------------------

void CRasterizer::DrawPoint( float x, float y, float z, float r, float g, float b )
{
    // Check Z buffer when drawing pixel
    if ( true == Viewport()->CheckZBufferValue( ( int )( x + 0.5f ), ( int )( y + 0.5f ), z ) )
    {
        DrawPoint( x, y, r, g, b );
    }
}

//----------------------------------------------------------------------------------------------------

void CRasterizer::DrawLine( SVertex3& vtx1, SVertex3& vtx2 )
{
    /*
        line drawing code based from:
        http://www.cs.unc.edu/~mcmillan/comp136/Lecture6/Lines.html
        "Bresenham's"
    */

    // make sure int values -- will get errors otherwise
    vtx1.point.x = ( float )( int )( vtx1.point.x + 0.5f );
    vtx1.point.y = ( float )( int )( vtx1.point.y + 0.5f );
    vtx2.point.x = ( float )( int )( vtx2.point.x + 0.5f );
    vtx2.point.y = ( float )( int )( vtx2.point.y + 0.5f );

    // check if the two vertices share the same coordinate
    if ( vtx1.point.x == vtx2.point.x && vtx1.point.y == vtx2.point.y )
    {
        DrawPoint( vtx1.point.x, vtx1.point.y, vtx1.point.z, vtx1.color.r, vtx1.color.g, vtx1.color.b );
        return;
    }

    // process for different fill modes
    switch ( StateManager()->GetCurrentFillmode() )
    {
    case EFillmode_LINE:
    case EFillmode_FILL:
        {
            // to simplify equations
            CColor currColor = vtx1.color;
            float currZ = vtx1.point.z;
            int x1 = roundftoi( vtx1.point.x );
            int y1 = roundftoi( vtx1.point.y );
            int x2 = roundftoi( vtx2.point.x );
            int y2 = roundftoi( vtx2.point.y );

            int dx = ( x2 - x1 );
            int dy = ( y2 - y1 );

            // protect against division by zero later on
            if ( 0 == dx && 0 == dy ) return;

            float dz = vtx2.point.z - vtx1.point.z;
            float dr = vtx2.color.r - vtx1.color.r;
            float dg = vtx2.color.g - vtx1.color.g;
            float db = vtx2.color.b - vtx1.color.b;
            int xStep, yStep;
            float zStep;
            float rStep, gStep, bStep;

            // check for negative d values
            if ( dx < 0 ) { dx = -dx;  xStep = -1; } else { xStep = 1; }
            if ( dy < 0 ) { dy = -dy;  yStep = -1; } else { yStep = 1; }

            // calculate the step values for RGB
            if ( dx > dy )  { zStep = dz / dx; rStep = dr / dx; gStep = dg / dx; bStep = db / dx; }
            else            { zStep = dz / dy; rStep = dr / dy; gStep = dg / dy; bStep = db / dy; }

            dy <<= 1;       // dy is now 2*dy
            dx <<= 1;       // dx is now 2*dx

            DrawPoint( ( float )x1, ( float )y1, currZ, currColor.r, currColor.g, currColor.b );
            if ( dx > dy )
            {
                int fraction = dy - ( dx >> 1 );        // same as 2*dy - dx
                while ( x1 != x2 )
                {
                    if ( fraction >= 0 )
                    {
                        y1 += yStep;
                        fraction -= dx;                 // same as fraction -= 2*dx
                    }
                    x1 += xStep;
                    fraction += dy;                     // same as fraction += 2*dy

                    // increment z value
                    currZ += zStep;

                    // increment color values
                    currColor.r += rStep;
                    currColor.g += gStep;
                    currColor.b += bStep;
                    DrawPoint( ( float )x1, ( float )y1, currZ, currColor.r, currColor.g, currColor.b );
                }
            }
            else
            {
                int fraction = dx - ( dy >> 1 );
                while ( y1 != y2 )
                {
                    if ( fraction >= 0 )
                    {
                        x1 += xStep;
                        fraction -= dy;
                    }
                    y1 += yStep;
                    fraction += dx;

                    // increment z value
                    currZ += zStep;

                    // increment color values
                    currColor.r += rStep;
                    currColor.g += gStep;
                    currColor.b += bStep;
                    DrawPoint( ( float )x1, ( float )y1, currZ, currColor.r, currColor.g, currColor.b );
                }
            }
        }
        break;
    default:
        break;
    }
}

//----------------------------------------------------------------------------------------------------

void CRasterizer::DrawTriangle( SVertex3& vtx1, SVertex3& vtx2, SVertex3& vtx3 )
{
    // make sure int values -- will get errors otherwise
    vtx1.point.x = ( float )( int )( vtx1.point.x + 0.5f );
    vtx1.point.y = ( float )( int )( vtx1.point.y + 0.5f );
    vtx2.point.x = ( float )( int )( vtx2.point.x + 0.5f );
    vtx2.point.y = ( float )( int )( vtx2.point.y + 0.5f );
    vtx3.point.x = ( float )( int )( vtx3.point.x + 0.5f );
    vtx3.point.y = ( float )( int )( vtx3.point.y + 0.5f );

    switch ( StateManager()->GetCurrentFillmode() )
    {
    case EFillmode_LINE:
        {
            // don't want to destroy original vertex info when clipping
            SVertex3 v1, v2, v3;

            // in line mode, just draw lines between vertices
            v1 = vtx1; v2 = vtx2;
            if ( Clipper()->ClipLine( v1, v2 ) )
            {
                v1.point.x = ( float )( int )( v1.point.x + 0.5f );
                v1.point.y = ( float )( int )( v1.point.y + 0.5f );
                v2.point.x = ( float )( int )( v2.point.x + 0.5f );
                v2.point.y = ( float )( int )( v2.point.y + 0.5f );
                DrawLine( v1, v2 );
            }

            v2 = vtx2; v3 = vtx3;
            if ( Clipper()->ClipLine( v2, v3 ) )
            {
                v2.point.x = ( float )( int )( v2.point.x + 0.5f );
                v2.point.y = ( float )( int )( v2.point.y + 0.5f );
                v3.point.x = ( float )( int )( v3.point.x + 0.5f );
                v3.point.y = ( float )( int )( v3.point.y + 0.5f );
                DrawLine( v2, v3 );
            }

            v3 = vtx3; v1 = vtx1;
            if ( Clipper()->ClipLine( v3, v1 ) )
            {
                v3.point.x = ( float )( int )( v3.point.x + 0.5f );
                v3.point.y = ( float )( int )( v3.point.y + 0.5f );
                v1.point.x = ( float )( int )( v1.point.x + 0.5f );
                v1.point.y = ( float )( int )( v1.point.y + 0.5f );
                DrawLine( v3, v1 );
            }
        }
        break;
    case EFillmode_FILL:
        {
            // code simplification
            float v1y = vtx1.point.y, v2y = vtx2.point.y, v3y = vtx3.point.y;

            // order vertices from top to bottom
            SVertex3 yOrder[ 3 ] = { vtx1, vtx2, vtx3 };
            SVertex3 temp;
            if ( yOrder[ 1 ].point.y < yOrder[ 0 ].point.y )
            { temp = yOrder[ 0 ]; yOrder[ 0 ] = yOrder[ 1 ]; yOrder[ 1 ] = temp; }
            if ( yOrder[ 2 ].point.y < yOrder[ 1 ].point.y )
            { temp = yOrder[ 1 ]; yOrder[ 1 ] = yOrder[ 2 ]; yOrder[ 2 ] = temp; }
            if ( yOrder[ 1 ].point.y < yOrder[ 0 ].point.y )
            { temp = yOrder[ 0 ]; yOrder[ 0 ] = yOrder[ 1 ]; yOrder[ 1 ] = temp; }

            // check for a flat line along y
            if ( v1y != v2y && v1y != v3y && v2y != v3y )
            {
                // no flat line. split the triangles and process separately
                
                // find vertex to split triangles
                float t = ( yOrder[ 1 ].point.y - yOrder[ 0 ].point.y ) / ( yOrder[ 2 ].point.y - yOrder[ 0 ].point.y );
                SVertex3 splitVertex = Vertex3Lerp( yOrder[ 0 ], yOrder[ 2 ], t );

                // draw two new triangles seperately
                DrawTriangle( yOrder[ 0 ], splitVertex, yOrder[ 1 ] );
                DrawTriangle( yOrder[ 1 ], splitVertex, yOrder[ 2 ] );
            }
            else
            {
                // triangle y limits
                int yTop, yBottom;
                yTop =    ( int )yOrder[ 0 ].point.y;
                yBottom = ( int )yOrder[ 2 ].point.y;

                // vars for scan lines
                int yLines = yBottom - yTop + 1;
                SVertex3* lVerts = new SVertex3[ yLines ];
                SVertex3* rVerts = new SVertex3[ yLines ];

                // establish which two points form the horizontal line and set:
                // will be either 1st and 2nd or 2nd and 3rd (points already sorted)
                // topleft, topright, bottomleft, bottomright
                if ( yOrder[ 0 ].point.y == yOrder[ 1 ].point.y )
                {
                    if ( yOrder[ 0 ].point.x < yOrder[ 1 ].point.x )
                    {
                        lVerts[ 0 ] = yOrder[ 0 ];
                        rVerts[ 0 ] = yOrder[ 1 ];
                    }
                    else
                    {
                        lVerts[ 0 ] = yOrder[ 1 ];
                        rVerts[ 0 ] = yOrder[ 0 ];
                    }
                    lVerts[ yLines - 1 ] = rVerts[ yLines - 1 ] = yOrder[ 2 ];
                }
                else
                {
                    if ( yOrder[ 1 ].point.x < yOrder[ 2 ].point.x )
                    {
                        lVerts[ yLines - 1 ] = yOrder[ 1 ];
                        rVerts[ yLines - 1 ] = yOrder[ 2 ];
                    }
                    else
                    {
                        lVerts[ yLines - 1 ] = yOrder[ 2 ];
                        rVerts[ yLines - 1 ] = yOrder[ 1 ];
                    }
                    lVerts[ 0 ] = rVerts[ 0 ] = yOrder[ 0 ];
                }

                // Fill vertex arrays with y vertices
                GetTriYVertices( lVerts, yLines );
                GetTriYVertices( rVerts, yLines );

                // init
                int xSteps = 0;
                float zStep = 0.0f;
                float rStepX = 0.0f, gStepX = 0.0f, bStepX = 0.0f;
                CColor midColor;

                // iterate through scan lines
                for ( int i = 0; i < yLines; ++i )
                {
                    // get color increments
                    xSteps = ( int )( rVerts[ i ].point.x - lVerts[ i ].point.x + 0.5f );
                    if ( xSteps > 0 )
                    {
                        zStep  = ( rVerts[ i ].point.z - lVerts[ i ].point.z ) / xSteps;
                        rStepX = ( rVerts[ i ].color.r - lVerts[ i ].color.r ) / xSteps;
                        gStepX = ( rVerts[ i ].color.g - lVerts[ i ].color.g ) / xSteps;
                        bStepX = ( rVerts[ i ].color.b - lVerts[ i ].color.b ) / xSteps;
                    }

                    // iterate through x pixels and draw with interpolated color
                    midColor = lVerts[ i ].color;
                    float currZ = lVerts[ i ].point.z;

                    // account for proper rounding casting floats to ints
                    for ( int x  = ( int )( lVerts[ i ].point.x + 0.5f );
                              x <= ( int )( rVerts[ i ].point.x + 0.5f ); ++x )
                    {
                        if ( lVerts[ i ].point.x == rVerts[ i ].point.x ) break;
                        // draw the pixel
                        DrawPoint( ( float )x, lVerts[ i ].point.y, currZ, midColor.r, midColor.g, midColor.b );

                        // interpolate z values
                        currZ += zStep;

                        // increment the scan line's color interpolation
                        midColor.r += rStepX; midColor.g += gStepX; midColor.b += bStepX;
                    }
                } // end for

                // clean up memory
                delete [] lVerts;
                delete [] rVerts;
            } // end else
        } // end case
        break;
    default:
        break;
    }
}

//----------------------------------------------------------------------------------------------------

void CRasterizer::GetTriYVertices( SVertex3 vBuffer[], int iBufferSize )
{
    // to simplify equations
    SVertex3* vFirst = &vBuffer[ 0 ];
    SVertex3* vLast  = &vBuffer[ iBufferSize - 1 ];
    float currZ = vFirst->point.z;
    CColor currColor = vFirst->color;

    int x1 = ( int )( vFirst->point.x + 0.5f ), y1 = ( int )( vFirst->point.y + 0.5f );
    int x2 = ( int )( vLast->point.x + 0.5f ),  y2 = ( int )( vLast->point.y + 0.5f );

    int dx = x2 - x1;
    int dy = y2 - y1;

    // protect against division by zero later on
    if ( 0 == dx && 0 == dy ) return;

    float dz = vLast->point.z - vFirst->point.z;
    float dr = vLast->color.r - vFirst->color.r;
    float dg = vLast->color.g - vFirst->color.g;
    float db = vLast->color.b - vFirst->color.b;
    int xStep, yStep;
    float zStep = 0.0f;
    float rStep, gStep, bStep;

    // check for negative d values
    if ( dx < 0 ) { dx = -dx;  xStep = -1; } else { xStep = 1; }
    if ( dy < 0 ) { dy = -dy;  yStep = -1; } else { yStep = 1; }

    // calculate the step values for RGB
    if ( dx > dy )  { zStep = dz / dx; rStep = dr / dx; gStep = dg / dx; bStep = db / dx; }
    else            { zStep = dz / dy; rStep = dr / dy; gStep = dg / dy; bStep = db / dy; }

    dy <<= 1;       // dy is now 2*dy
    dx <<= 1;       // dx is now 2*dx

    int currentIndex = 0;
    int currY = y1;
    if ( dx > dy )
    {
        int fraction = dy - ( dx >> 1 );        // same as 2*dy - dx
        while ( x1 != x2 )
        {
            if ( fraction >= 0 )
            {
                y1 += yStep;
                fraction -= dx;                 // same as fraction -= 2*dx
            }
            x1 += xStep;
            fraction += dy;                     // same as fraction += 2*dy

            currZ += zStep;
            currColor.r += rStep;
            currColor.g += gStep;
            currColor.b += bStep;
            if ( y1 != currY )
            {
                currY = y1;
                if ( iBufferSize == ++currentIndex ) break;
                vBuffer[ currentIndex ].point.x = ( float )x1;
                vBuffer[ currentIndex ].point.y = ( float )y1;
                vBuffer[ currentIndex ].point.z = currZ;
                vBuffer[ currentIndex ].color = currColor;
            }
        }
    }
    else
    {
        int fraction = dx - ( dy >> 1 );
        while ( y1 != y2 )
        {
            if ( fraction >= 0 )
            {
                x1 += xStep;
                fraction -= dy;
            }
            y1 += yStep;
            fraction += dx;

            currZ += zStep;
            currColor.r += rStep;
            currColor.g += gStep;
            currColor.b += bStep;
            if ( y1 != currY )
            {
                currY = y1;
                if ( iBufferSize == ++currentIndex ) break;
                vBuffer[ currentIndex ].point.x = ( float )x1;
                vBuffer[ currentIndex ].point.y = ( float )y1;
                vBuffer[ currentIndex ].point.z = currZ;
                vBuffer[ currentIndex ].color = currColor;
            }
        }
    }
}