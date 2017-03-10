#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include "Common/Vertex2.h"
#include "Common/Vertex3.h"

class CRasterizer
{
public:
	static CRasterizer* Instance();
protected:
	CRasterizer() {}
	CRasterizer(const CRasterizer&);
	CRasterizer& operator= (const CRasterizer&);
private:
	static CRasterizer* pinstance;

public:
	void Initialize() {}

    // Sets
	void SetColor( float r, float g, float b );
    void SetColor( const CColor& color );

    // Draw
	void DrawPoint( int x, int y );
	void DrawPoint( float x, float y );
	void DrawPoint( float x, float y, float r, float g, float b );
    void DrawPoint( float x, float y, float z, float r, float g, float b );

    void DrawLine( SVertex3& vtx1, SVertex3& vtx2 );
    void DrawTriangle( SVertex3& vtx1, SVertex3& vtx2, SVertex3& vtx3 );

private:
    // helper function to get the left and right y vertices for a triangle to be filled
    void GetTriYVertices( SVertex3 vBuffer[], int iBufferSize );
};

//====================================================================================================
// Static Accessor Function
//====================================================================================================
static CRasterizer* Rasterizer( void )
{
    return CRasterizer::Instance();
}

#endif // __RASTERIZER_H__
