#pragma once

//====================================================================================================
// Includes
//====================================================================================================
#include "Color.h"
#include "Vector4.h"

struct SVertex3
{
    CColor   color;
    CVector4 point;

    bool operator==( const SVertex3& rhs )
    {
        return ( this->point.x == rhs.point.x && this->point.y == rhs.point.y && this->point.z == rhs.point.z );
    }
};

inline SVertex3 Vertex3Lerp( const SVertex3 &v1, const SVertex3 &v2, const float t )
{
    SVertex3 result;
    result.point.x = v1.point.x + t * (v2.point.x - v1.point.x);
    result.point.y = v1.point.y + t * (v2.point.y - v1.point.y);
    result.point.z = v1.point.z + t * (v2.point.z - v1.point.z);
    result.color.r = v1.color.r + t * (v2.color.r - v1.color.r);
    result.color.g = v1.color.g + t * (v2.color.g - v1.color.g);
    result.color.b = v1.color.b + t * (v2.color.b - v1.color.b);
    return result;
}