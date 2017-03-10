//====================================================================================================
// Includes
//====================================================================================================
#include "StdAfx.h"
#include "Matrix33.h"
#include "MiniMath.h"
#include "Vector3.h"

//====================================================================================================
// Enum for matrix components
//====================================================================================================
enum EIndex { _11, _21, _31, _12, _22, _32, _13, _23, _33, mVmax };

//====================================================================================================
// typedefs
//====================================================================================================
typedef unsigned int UINT;

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ CMatrix33::CMatrix33()
//-------------------------------------------------------------------------------
// Copy constructor
//-------------------------------------------------------------------------------
CMatrix33::CMatrix33(const CMatrix33& other)
{
    mV[0] = other.mV[0];
    mV[1] = other.mV[1];
    mV[2] = other.mV[2];
    mV[3] = other.mV[3];
    mV[4] = other.mV[4];
    mV[5] = other.mV[5];
    mV[6] = other.mV[6];
    mV[7] = other.mV[7];
    mV[8] = other.mV[8];

}   // End of CMatrix33::CMatrix33()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator=()
//-------------------------------------------------------------------------------
// Assignment operator
//-------------------------------------------------------------------------------
CMatrix33&
CMatrix33::operator=(const CMatrix33& other)
{
    // if same object
    if ( this == &other )
        return *this;
        
    mV[0] = other.mV[0];
    mV[1] = other.mV[1];
    mV[2] = other.mV[2];
    mV[3] = other.mV[3];
    mV[4] = other.mV[4];
    mV[5] = other.mV[5];
    mV[6] = other.mV[6];
    mV[7] = other.mV[7];
    mV[8] = other.mV[8];
    
    return *this;

}   // End of CMatrix33::operator=()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator==()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CMatrix33::operator==( const CMatrix33& other ) const
{
    for ( UINT i = 0; i < mVmax; ++i )
    {
        if ( !( mV[ i ] == other.mV[ i ] ) )
            return false;
    }
    return true;

}   // End of CMatrix33::operator==()


//-------------------------------------------------------------------------------
// @ CMatrix33::operator!=()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
CMatrix33::operator!=( const CMatrix33& other ) const
{
    for ( UINT i = 0; i < mVmax; ++i )
    {
        if ( !( mV[ i ] == other.mV[ i ] ) )
            return true;
    }
    return false;

}   // End of CMatrix33::operator!=()


//-------------------------------------------------------------------------------
// @ CMatrix33::SetRows()
//-------------------------------------------------------------------------------
// Set matrix, row by row
//-------------------------------------------------------------------------------
void 
CMatrix33::SetRows( const CVector3& row1, const CVector3& row2, const CVector3& row3 )
{
    mV[0] = row1.x;
    mV[3] = row1.y;
    mV[6] = row1.z;

    mV[1] = row2.x;
    mV[4] = row2.y;
    mV[7] = row2.z;

    mV[2] = row3.x;
    mV[5] = row3.y;
    mV[8] = row3.z;

}   // End of CMatrix33::SetRows()


//-------------------------------------------------------------------------------
// @ CMatrix33::GetRows()
//-------------------------------------------------------------------------------
// Get matrix, row by row
//-------------------------------------------------------------------------------
void 
CMatrix33::GetRows( CVector3& row1, CVector3& row2, CVector3& row3 ) const
{
    row1.x = mV[0];
    row1.y = mV[3];
    row1.z = mV[6];

    row2.x = mV[1];
    row2.y = mV[4];
    row2.z = mV[7];

    row3.x = mV[2];
    row3.y = mV[5];
    row3.z = mV[8];
}   // End of CMatrix33::GetRows()


//-------------------------------------------------------------------------------
// @ CMatrix33::GetRow()
//-------------------------------------------------------------------------------
// Get matrix, row by row
//-------------------------------------------------------------------------------
CVector3 
CMatrix33::GetRow( unsigned int i ) const
{
    ASSERT( i < 3 );
    return CVector3( mV[i], mV[i+3], mV[i+6] );

}   // End of CMatrix33::GetRow()


//-------------------------------------------------------------------------------
// @ CMatrix33::SetColumns()
//-------------------------------------------------------------------------------
// Set matrix, row by row
//-------------------------------------------------------------------------------
void 
CMatrix33::SetColumns( const CVector3& col1, const CVector3& col2, const CVector3& col3 )
{
    mV[0] = col1.x;
    mV[1] = col1.y;
    mV[2] = col1.z;

    mV[3] = col2.x;
    mV[4] = col2.y;
    mV[5] = col2.z;

    mV[6] = col3.x;
    mV[7] = col3.y;
    mV[8] = col3.z;

}   // End of CMatrix33::SetColumns()


//-------------------------------------------------------------------------------
// @ CMatrix33::GetColumns()
//-------------------------------------------------------------------------------
// Get matrix, row by row
//-------------------------------------------------------------------------------
void 
CMatrix33::GetColumns( CVector3& col1, CVector3& col2, CVector3& col3 ) const
{
    col1.x = mV[0];
    col1.y = mV[1];
    col1.z = mV[2];

    col2.x = mV[3];
    col2.y = mV[4];
    col2.z = mV[5];

    col3.x = mV[6];
    col3.y = mV[7];
    col3.z = mV[8];

}   // End of CMatrix33::GetColumns()


//-------------------------------------------------------------------------------
// @ CMatrix33::GetColumns()
//-------------------------------------------------------------------------------
// Get matrix, row by row
//-------------------------------------------------------------------------------
CVector3 
CMatrix33::GetColumn( unsigned int i ) const 
{
    ASSERT( i < 3 );
    return CVector3( mV[3*i], mV[3*i+1], mV[3*i+2] );

}   // End of CMatrix33::GetColumns()


//-------------------------------------------------------------------------------
// @ CMatrix33::Clean()
//-------------------------------------------------------------------------------
// Set elements close to zero equal to zero
//-------------------------------------------------------------------------------
void
CMatrix33::Clean()
{
    for (unsigned int i = 0; i < 9; ++i)
    {
        if ( ::IsZero( mV[i] ) )
            mV[i] = 0.0f;
    }

}   // End of CMatrix33::Clean()

bool CMatrix33::IsZero() const
{
    for ( UINT i = 0; i < mVmax; ++i )
    {
        if ( fabsf( mV[ i ] ) > kEpsilon ) return false;
    }
    return true;
}

//----------------------------------------------------------------------------------------------------

bool CMatrix33::IsIdentity() const
{
    return ( mV[ _11 ] == 1 && mV[ _12 ] == 0 && mV[ _13 ] == 0 &&
             mV[ _21 ] == 0 && mV[ _22 ] == 1 && mV[ _23 ] == 0 &&
             mV[ _31 ] == 0 && mV[ _32 ] == 0 && mV[ _33 ] == 1 );
}

//----------------------------------------------------------------------------------------------------

void CMatrix33::Identity()
{
    mV[ _11 ] = 1; mV[ _12 ] = 0; mV[ _13 ] = 0;
    mV[ _21 ] = 0; mV[ _22 ] = 1; mV[ _23 ] = 0;
    mV[ _31 ] = 0; mV[ _32 ] = 0; mV[ _33 ] = 1;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::Transpose()
{
    float temp;
    temp = mV[ _12 ]; mV[ _12 ] = mV[ _21 ]; mV[ _21 ] = temp;
    temp = mV[ _13 ]; mV[ _13 ] = mV[ _31 ]; mV[ _31 ] = temp;
    temp = mV[ _23 ]; mV[ _23 ] = mV[ _32 ]; mV[ _32 ] = temp;
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33 Transpose( const CMatrix33& mat )
{
    CMatrix33 retMat;
    for ( UINT i = 0; i < 3; ++i )
    {
        for ( UINT j = 0; j < 3; ++j )
        {
            retMat( i, j ) = mat( j, i );
        }
    }
    return retMat;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::Rotation( float zRotation, float yRotation, float xRotation )
{
    // pre-calc the cos's and sin's
    float A = cosf( xRotation );
    float B = sinf( xRotation );
    float C = cosf( yRotation );
    float D = sinf( yRotation );
    float E = cosf( zRotation );
    float F = sinf( zRotation );

    mV[ _11 ] =  ( C * E );                   mV[ _12 ] = -( C * F );                   mV[ _13 ] = -( D );
    mV[ _21 ] = -( B * D * E ) + ( A * F );   mV[ _22 ] =  ( B * D * F ) + ( A * E );   mV[ _23 ] = -( B * C );
    mV[ _31 ] =  ( A * D * E ) + ( B * F );   mV[ _32 ] = -( A * D * F ) + ( B * E );   mV[ _33 ] =  ( A * C );

    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::Scaling( const CVector3& scale )
{
    mV[ _11 ] = scale.x; mV[ _12 ] = 0;       mV[ _13 ] = 0;
    mV[ _21 ] = 0;       mV[ _22 ] = scale.y; mV[ _23 ] = 0;
    mV[ _31 ] = 0;       mV[ _32 ] = 0;       mV[ _33 ] = scale.z;
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::Translation( float tx, float ty )
{
    mV[ _11 ] = 1;      mV[ _12 ] = 0;      mV[ _13 ] = tx;
    mV[ _21 ] = 0;      mV[ _22 ] = 1;      mV[ _23 ] = ty;
    mV[ _31 ] = 0;      mV[ _32 ] = 0;      mV[ _33 ] = 1;
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::Shear( float shx, float shy )
{
    mV[ _11 ] = 1;      mV[ _12 ] = shx;    mV[ _13 ] = 0;
    mV[ _21 ] = shy;    mV[ _22 ] = 1;      mV[ _23 ] = 0;
    mV[ _31 ] = 0;      mV[ _32 ] = 0;      mV[ _33 ] = 1;
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::RotationX( float angle )
{
    mV[ _11 ] = 1; mV[ _12 ] = 0;             mV[ _13 ] = 0;
    mV[ _21 ] = 0; mV[ _22 ] = cosf( angle ); mV[ _23 ] = -sinf( angle );
    mV[ _31 ] = 0; mV[ _32 ] = sinf( angle ); mV[ _33 ] = cosf( angle );
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::RotationY( float angle )
{
    mV[ _11 ] = cosf( angle );  mV[ _12 ] = 0; mV[ _13 ] = sinf( angle );
    mV[ _21 ] = 0;              mV[ _22 ] = 1; mV[ _23 ] = 0;
    mV[ _31 ] = -sinf( angle ); mV[ _32 ] = 0; mV[ _33 ] = cosf( angle );
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::RotationZ( float angle )
{
    mV[ _11 ] = cosf( angle );  mV[ _12 ] = -sinf( angle ); mV[ _13 ] = 0;
    mV[ _21 ] = sinf( angle );  mV[ _22 ] = cosf( angle );  mV[ _23 ] = 0;
    mV[ _31 ] = 0;              mV[ _32 ] = 0;              mV[ _33 ] = 1;
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33 CMatrix33::operator+( const CMatrix33& other ) const
{
    CMatrix33 retMat;
    for ( UINT i = 0; i < mVmax; ++i )
    {
        retMat.mV[ i ] = mV[ i ] + other.mV[ i ];
    }
    return retMat;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::operator+=( const CMatrix33& other )
{
    for ( UINT i = 0; i < mVmax; ++i )
    {
        mV[ i ] += other.mV[ i ];
    }
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33 CMatrix33::operator-( const CMatrix33& other ) const
{
    CMatrix33 retMat;
    
    for ( UINT i = 0; i < mVmax; ++i )
    {
        retMat.mV[ i ] = mV[ i ] - other.mV[ i ];
    }

    return retMat;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::operator-=( const CMatrix33& other )
{
    for ( UINT i = 0; i < mVmax; ++i )
    {
        mV[ i ] -= other.mV[ i ];
    }
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33 CMatrix33::operator-() const
{
    CMatrix33 retMat;
    
    for ( UINT i = 0; i < mVmax; ++i )
    {
        retMat.mV[ i ] = -mV[ i ];
    }

    return retMat;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::operator*=( const CMatrix33& matrix )
{
    CMatrix33 m = *this;
    mV[ _11 ] = m.mV[ _11 ] * matrix.mV[ _11 ] + m.mV[ _12 ] * matrix.mV[ _21 ] + m.mV[ _13 ] * matrix.mV[ _31 ];
    mV[ _12 ] = m.mV[ _11 ] * matrix.mV[ _12 ] + m.mV[ _12 ] * matrix.mV[ _22 ] + m.mV[ _13 ] * matrix.mV[ _32 ];
    mV[ _13 ] = m.mV[ _11 ] * matrix.mV[ _13 ] + m.mV[ _12 ] * matrix.mV[ _23 ] + m.mV[ _13 ] * matrix.mV[ _33 ];
    mV[ _21 ] = m.mV[ _21 ] * matrix.mV[ _11 ] + m.mV[ _22 ] * matrix.mV[ _21 ] + m.mV[ _23 ] * matrix.mV[ _31 ];
    mV[ _22 ] = m.mV[ _21 ] * matrix.mV[ _12 ] + m.mV[ _22 ] * matrix.mV[ _22 ] + m.mV[ _23 ] * matrix.mV[ _32 ];
    mV[ _23 ] = m.mV[ _21 ] * matrix.mV[ _13 ] + m.mV[ _22 ] * matrix.mV[ _23 ] + m.mV[ _23 ] * matrix.mV[ _33 ];
    mV[ _31 ] = m.mV[ _31 ] * matrix.mV[ _11 ] + m.mV[ _32 ] * matrix.mV[ _21 ] + m.mV[ _33 ] * matrix.mV[ _31 ];
    mV[ _32 ] = m.mV[ _31 ] * matrix.mV[ _12 ] + m.mV[ _32 ] * matrix.mV[ _22 ] + m.mV[ _33 ] * matrix.mV[ _32 ];
    mV[ _33 ] = m.mV[ _31 ] * matrix.mV[ _13 ] + m.mV[ _32 ] * matrix.mV[ _23 ] + m.mV[ _33 ] * matrix.mV[ _33 ];
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33 CMatrix33::operator*( const CMatrix33& matrix ) const
{
    CMatrix33 retMat;
    retMat.mV[ _11 ] = mV[ _11 ] * matrix.mV[ _11 ] + mV[ _12 ] * matrix.mV[ _21 ] + mV[ _13 ] * matrix.mV[ _31 ];
    retMat.mV[ _12 ] = mV[ _11 ] * matrix.mV[ _12 ] + mV[ _12 ] * matrix.mV[ _22 ] + mV[ _13 ] * matrix.mV[ _32 ];
    retMat.mV[ _13 ] = mV[ _11 ] * matrix.mV[ _13 ] + mV[ _12 ] * matrix.mV[ _23 ] + mV[ _13 ] * matrix.mV[ _33 ];
    retMat.mV[ _21 ] = mV[ _21 ] * matrix.mV[ _11 ] + mV[ _22 ] * matrix.mV[ _21 ] + mV[ _23 ] * matrix.mV[ _31 ];
    retMat.mV[ _22 ] = mV[ _21 ] * matrix.mV[ _12 ] + mV[ _22 ] * matrix.mV[ _22 ] + mV[ _23 ] * matrix.mV[ _32 ];
    retMat.mV[ _23 ] = mV[ _21 ] * matrix.mV[ _13 ] + mV[ _22 ] * matrix.mV[ _23 ] + mV[ _23 ] * matrix.mV[ _33 ];
    retMat.mV[ _31 ] = mV[ _31 ] * matrix.mV[ _11 ] + mV[ _32 ] * matrix.mV[ _21 ] + mV[ _33 ] * matrix.mV[ _31 ];
    retMat.mV[ _32 ] = mV[ _31 ] * matrix.mV[ _12 ] + mV[ _32 ] * matrix.mV[ _22 ] + mV[ _33 ] * matrix.mV[ _32 ];
    retMat.mV[ _33 ] = mV[ _31 ] * matrix.mV[ _13 ] + mV[ _32 ] * matrix.mV[ _23 ] + mV[ _33 ] * matrix.mV[ _33 ];
    return retMat;
}

//----------------------------------------------------------------------------------------------------

CVector3 CMatrix33::operator*( const CVector3& vector ) const
{
    CVector3 retVec;
    retVec.x = mV[ _11 ] * vector.x + mV[ _12 ] * vector.y + mV[ _13 ] * vector.z;
    retVec.y = mV[ _21 ] * vector.x + mV[ _22 ] * vector.y + mV[ _23 ] * vector.z;
    retVec.z = mV[ _31 ] * vector.x + mV[ _32 ] * vector.y + mV[ _33 ] * vector.z;
    return retVec;
}

//----------------------------------------------------------------------------------------------------

CVector3 operator*( const CVector3& vector, const CMatrix33& matrix )
{
    // TODO: row vector??
    CVector3 retVec;
    retVec.x = matrix.mV[ _11 ] * vector.x + matrix.mV[ _12 ] * vector.y + matrix.mV[ _13 ] * vector.z;
    retVec.y = matrix.mV[ _21 ] * vector.x + matrix.mV[ _22 ] * vector.y + matrix.mV[ _23 ] * vector.z;
    retVec.z = matrix.mV[ _31 ] * vector.x + matrix.mV[ _32 ] * vector.y + matrix.mV[ _33 ] * vector.z;
    return retVec;
}

//----------------------------------------------------------------------------------------------------

CMatrix33& CMatrix33::operator*=( float scalar )
{
    for ( UINT i = 0; i < mVmax; ++i )
    {
        mV[ i ] *= scalar;
    }
    return *this;
}

//----------------------------------------------------------------------------------------------------

CMatrix33 operator*( float scalar, const CMatrix33& matrix )
{
    CMatrix33 retMat;

    for ( UINT i = 0; i < mVmax; ++i )
    {
        retMat.mV[ i ] = matrix.mV[ i ] * scalar;
    }

    return retMat;
}

//----------------------------------------------------------------------------------------------------

CMatrix33 CMatrix33::operator*( float scalar ) const
{
    CMatrix33 retMat;

    for ( UINT i = 0; i < mVmax; ++i )
    {
        retMat.mV[ i ] = mV[ i ] * scalar;
    }

    return retMat;
}