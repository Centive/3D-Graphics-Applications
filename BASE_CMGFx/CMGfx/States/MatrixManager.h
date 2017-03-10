#pragma once

//====================================================================================================
// Includes
//====================================================================================================
#include "Common/Matrix33.h"
#include "Common/Matrix44.h"

//====================================================================================================
// Class
//====================================================================================================
class CMatrixManager
{
public:
    ~CMatrixManager( void );

    // Instance Retrieval
    static CMatrixManager* GetInstance( void );
    
    // function to retrieve the currently set matrix transform
    const CMatrix33& GetCurrent2DTransform( void ) const { return m_Current2DMatrix; }
    const CMatrix44& GetCurrent3DTransform( void ) const { return m_Current3DMatrix; }
    
    // Matrix 2D state functions
    void Set2DIdentity( void ) { m_Current2DMatrix.Identity(); }
    void Add2DTranslation( float tx, float ty );
    void Add2DScaling    ( float sx, float sy );
    void Add2DRotation   ( float rz );
    void Add2DShearing   ( float shx, float shy );

    // Matrix 3D state functions
    void Set3DIdentity( void ) { m_Current3DMatrix.Identity(); }
    void Add3DTranslation( const CVector3& translation );
    void Add3DScaling    ( const CVector3& scaling );
    void Add3DRotation   ( float rz, float ry, float rx );

protected:
    // Protected Operations
    CMatrixManager();
    CMatrixManager( const CMatrixManager& );
    CMatrixManager& operator=( const CMatrixManager& );

private:
    // static singleton instance
    static CMatrixManager*    s_pInstance;

    // members
    CMatrix33   m_Current2DMatrix;
    CMatrix44   m_Current3DMatrix;
};

//====================================================================================================
// Static Function Accessor
//====================================================================================================
static CMatrixManager* MatrixManager( void )
{
    return CMatrixManager::GetInstance();
}