#ifndef __VERTEX2_H__
#define __VERTEX2_H__

#include "Color.h"
#include "Vector2.h"

struct SVertex2
{
	CColor color;
	CVector2 point;

    SVertex2() {}
    SVertex2( const CVector2& _point, const CColor& _color ) : point( _point ), color( _color ) {}

    bool operator==( const SVertex2& rhs )
    {
        return ( this->point.x == rhs.point.x && this->point.y == rhs.point.y );
    }
};

inline void Vertex2Round( SVertex2 &v )
{
	v.point.x = (float)(int)(v.point.x + 0.5f);
	v.point.y = (float)(int)(v.point.y + 0.5f);
}

inline SVertex2 Vertex2Lerp( const SVertex2 &v1, const SVertex2 &v2, const float t )
{
	SVertex2 result;
	result.point.x = v1.point.x + t * (v2.point.x - v1.point.x);
	result.point.y = v1.point.y + t * (v2.point.y - v1.point.y);
	result.color.r = v1.color.r + t * (v2.color.r - v1.color.r);
	result.color.g = v1.color.g + t * (v2.color.g - v1.color.g);
	result.color.b = v1.color.b + t * (v2.color.b - v1.color.b);
	return result;
}

#endif // __VERTEX_H__