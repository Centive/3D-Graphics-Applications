#include "StdAfx.h"
#include "Vector4.h"
#include "MiniMath.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

CVector4 CVector4::xAxis( 1.0f, 0.0f, 0.0f, 0.0f );
CVector4 CVector4::yAxis( 0.0f, 1.0f, 0.0f, 0.0f );
CVector4 CVector4::zAxis( 0.0f, 0.0f, 1.0f, 0.0f );
CVector4 CVector4::wAxis( 0.0f, 0.0f, 0.0f, 1.0f );
CVector4 CVector4::origin( 0.0f, 0.0f, 0.0f, 0.0f );

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CVector4::CVector4()
//-------------------------------------------------------------------------------
// Copy constructor
//-------------------------------------------------------------------------------
CVector4::CVector4(const CVector4& other) : 
    x( other.x ),
    y( other.y ),
    z( other.z ),
    w( other.w )
{

}   // End of CVector4::CVector4()


//-------------------------------------------------------------------------------
// @ CVector4::operator=()
//-------------------------------------------------------------------------------
// Assignment operator
//-------------------------------------------------------------------------------
CVector4&
CVector4::operator=(const CVector4& other)
{
    // if same object
    if ( this == &other )
        return *this;
        
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    
    return *this;

}   // End of CVector4::operator=()

//-------------------------------------------------------------------------------
// @ CVector4::Length()
//-------------------------------------------------------------------------------
// Vector length
//-------------------------------------------------------------------------------
float 
CVector4::Length() const
{
    return sqrtf( x*x + y*y + z*z + w*w );

}   // End of CVector4::Length()


//-------------------------------------------------------------------------------
// @ CVector4::LengthSquared()
//-------------------------------------------------------------------------------
// Vector length squared (avoids square root)
//-------------------------------------------------------------------------------
float 
CVector4::LengthSquared() const
{
    return ( x*x + y*y + z*z + w*w );

}   // End of CVector4::LengthSquared()


//-------------------------------------------------------------------------------
// @ CVector4::operator==()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CVector4::operator==( const CVector4& other ) const
{
    if ( ::IvAreEqual( other.x, x )
        && ::IvAreEqual( other.y, y )
        && ::IvAreEqual( other.z, z )
        && ::IvAreEqual( other.w, w ) )
        return true;

    return false;   
}   // End of CVector4::operator==()


//-------------------------------------------------------------------------------
// @ CVector4::operator!=()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CVector4::operator!=( const CVector4& other ) const
{
    if ( ::IvAreEqual( other.x, x )
        && ::IvAreEqual( other.y, y )
        && ::IvAreEqual( other.z, z )
        && ::IvAreEqual( other.w, w ) )
        return false;

    return true;
}   // End of CVector4::operator!=()


//-------------------------------------------------------------------------------
// @ CVector4::IsZero()
//-------------------------------------------------------------------------------
// Check for zero vector
//-------------------------------------------------------------------------------
bool 
CVector4::IsZero() const
{
    return ::IsZero(x*x + y*y + z*z + w*w);

}   // End of CVector4::IsZero()


//-------------------------------------------------------------------------------
// @ CVector4::IsUnit()
//-------------------------------------------------------------------------------
// Check for unit vector
//-------------------------------------------------------------------------------
bool 
CVector4::IsUnit() const
{
    return ::IsZero(1.0f - x*x - y*y - z*z - w*w);

}   // End of CVector4::IsUnit()


//-------------------------------------------------------------------------------
// @ CVector4::Clean()
//-------------------------------------------------------------------------------
// Set elements close to zero equal to zero
//-------------------------------------------------------------------------------
void
CVector4::Clean()
{
    if ( ::IsZero( x ) )
        x = 0.0f;
    if ( ::IsZero( y ) )
        y = 0.0f;
    if ( ::IsZero( z ) )
        z = 0.0f;
    if ( ::IsZero( w ) )
        w = 0.0f;

}   // End of CVector4::Clean()


//-------------------------------------------------------------------------------
// @ CVector4::Normalize()
//-------------------------------------------------------------------------------
// Set to unit vector
//-------------------------------------------------------------------------------
void
CVector4::Normalize()
{
    float lengthsq = x*x + y*y + z*z + w*w;

    if ( ::IsZero( lengthsq ) )
    {
        Zero();
    }
    else
    {
        float factor = 1.0f/sqrtf( lengthsq );
        x *= factor;
        y *= factor;
        z *= factor;
        w *= factor;
    }

}   // End of CVector4::Normalize()


//-------------------------------------------------------------------------------
// @ CVector4::operator+()
//-------------------------------------------------------------------------------
// Add vector to self and return
//-------------------------------------------------------------------------------
CVector4 
CVector4::operator+( const CVector4& other ) const
{
    return CVector4( x + other.x, y + other.y, z + other.z, w + other.w );

}   // End of CVector4::operator+()


//-------------------------------------------------------------------------------
// @ CVector4::operator+=()
//-------------------------------------------------------------------------------
// Add vector to self, store in self
//-------------------------------------------------------------------------------
CVector4& 
CVector4::operator+=( const CVector4& other )
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;

}   // End of CVector4::operator+=()


//-------------------------------------------------------------------------------
// @ CVector4::operator-()
//-------------------------------------------------------------------------------
// Subtract vector from self and return
//-------------------------------------------------------------------------------
CVector4 
CVector4::operator-( const CVector4& other ) const
{
    return CVector4( x - other.x, y - other.y, z - other.z, w - other.w );

}   // End of CVector4::operator-()


//-------------------------------------------------------------------------------
// @ CVector4::operator-=()
//-------------------------------------------------------------------------------
// Subtract vector from self, store in self
//-------------------------------------------------------------------------------
CVector4& 
CVector4::operator-=( const CVector4& other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;

}   // End of CVector4::operator-=()


//-------------------------------------------------------------------------------
// @ operator*()
//-------------------------------------------------------------------------------
// Scalar multiplication
//-------------------------------------------------------------------------------
CVector4   
CVector4::operator*( float scalar )
{
    return CVector4( scalar*x, scalar*y, scalar*z,
                      scalar*w );

}   // End of operator*()


//-------------------------------------------------------------------------------
// @ operator*()
//-------------------------------------------------------------------------------
// Scalar multiplication
//-------------------------------------------------------------------------------
CVector4   
operator*( float scalar, const CVector4& vector )
{
    return CVector4( scalar*vector.x, scalar*vector.y, scalar*vector.z,
                      scalar*vector.w );

}   // End of operator*()


//-------------------------------------------------------------------------------
// @ CVector4::operator*()
//-------------------------------------------------------------------------------
// Scalar multiplication by self
//-------------------------------------------------------------------------------
CVector4&
CVector4::operator*=( float scalar )
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;

}   // End of CVector4::operator*()


//-------------------------------------------------------------------------------
// @ operator/()
//-------------------------------------------------------------------------------
// Scalar division
//-------------------------------------------------------------------------------
CVector4   
CVector4::operator/( float scalar )
{
    return CVector4( x/scalar, y/scalar, z/scalar, w/scalar );

}   // End of operator*()


//-------------------------------------------------------------------------------
// @ CVector4::operator/=()
//-------------------------------------------------------------------------------
// Scalar division by self
//-------------------------------------------------------------------------------
CVector4&
CVector4::operator/=( float scalar )
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;

}   // End of CVector4::operator/=()


//-------------------------------------------------------------------------------
// @ CVector4::Dot()
//-------------------------------------------------------------------------------
// Dot product by self
//-------------------------------------------------------------------------------
float               
CVector4::Dot( const CVector4& vector ) const
{
    return (x*vector.x + y*vector.y + z*vector.z + w*vector.w);

}   // End of CVector4::Dot()


//-------------------------------------------------------------------------------
// @ Dot()
//-------------------------------------------------------------------------------
// Dot product friend operator
//-------------------------------------------------------------------------------
float               
Dot( const CVector4& vector1, const CVector4& vector2 )
{
    return (vector1.x*vector2.x + vector1.y*vector2.y + vector1.z*vector2.z
            + vector1.w*vector2.w);

}   // End of Dot()
