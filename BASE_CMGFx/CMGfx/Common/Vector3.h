#ifndef __CVector3__h__
#define __CVector3__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Vector4.h"

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class CVector3
{
public:
    // constructor/destructor
    inline CVector3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}
    inline CVector3( float _x, float _y, float _z ) :
        x(_x), y(_y), z(_z)
    {
    }
    inline CVector3( const CVector4& v4 ) : x( v4.x ), y( v4.y ), z( v4.z ) {}
    inline ~CVector3() {}

    // copy operations
    CVector3(const CVector3& other);
    CVector3& operator=(const CVector3& other);

    // accessors
    inline float& operator[]( unsigned int i )          { return (&x)[i]; }
    inline float operator[]( unsigned int i ) const { return (&x)[i]; }

    friend float Distance( const CVector3& p0, const CVector3& p1 );
    friend float DistanceSquared( const CVector3& p0, const CVector3& p1 );

    // comparison
    bool operator==( const CVector3& other ) const;
    bool operator!=( const CVector3& other ) const;
    bool IsZero() const;
    bool IsUnit() const;

    // manipulators
    inline void Set( float _x, float _y, float _z );
    void Clean();       // sets near-zero elements to 0
    inline void Zero(); // sets all elements to 0

    // operators

    // addition/subtraction
    CVector3 operator+( const CVector3& other ) const;
    friend CVector3& operator+=( CVector3& vector, const CVector3& other );
    CVector3 operator-( const CVector3& other ) const;
    friend CVector3& operator-=( CVector3& vector, const CVector3& other );

    CVector3 operator-() const;

    // scalar multiplication
    CVector3   operator*( float scalar );
    friend CVector3    operator*( float scalar, const CVector3& vector );
    CVector3&          operator*=( float scalar );
    CVector3   operator/( float scalar );
    CVector3&          operator/=( float scalar );

    // useful defaults
    static CVector3    xAxis;
    static CVector3    yAxis;
    static CVector3    zAxis;
    static CVector3    origin;

    // ADDED: Useful Vector Functions
    float Length() const;
    inline float LengthSquared() const;
    void Normalize();
    float Dot( const CVector3& vector ) const;
    CVector3 Cross( const CVector3& vector ) const;

    // member variables
    float x, y, z;

protected:

private:
};

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CVector3::Set()
//-------------------------------------------------------------------------------
// Set vector elements
//-------------------------------------------------------------------------------
inline void 
CVector3::Set( float _x, float _y, float _z )
{
    x = _x; y = _y; z = _z;
}   // End of CVector3::Set()

//-------------------------------------------------------------------------------
// @ CVector3::Zero()
//-------------------------------------------------------------------------------
// Zero all elements
//-------------------------------------------------------------------------------
inline void 
CVector3::Zero()
{
    x = y = z = 0.0f;
}   // End of CVector3::Zero()

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
