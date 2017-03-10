#pragma once

//====================================================================================================
// Includes
//====================================================================================================
#include <vector>
#include "Common/Vertex3.h"

//====================================================================================================
// Enums
//====================================================================================================
enum EPrimitiveType
{
    EPrimitiveType_NONE = -1,

    EPrimitiveType_POINT,
    EPrimitiveType_LINE,
    EPrimitiveType_TRIANGLE,

    EPrimitiveType_MAX
};

//====================================================================================================
// Class
//====================================================================================================
class CPrimManager
{
public:
    ~CPrimManager( void );

    // Instance Retrieval
    static CPrimManager* GetInstance( void );

    // Gets and Sets
    EPrimitiveType GetCurrentPrimitiveMode( void ) const { return m_CurrentPrimitive; }

    // Vertex Functions
    void BeginDraw( EPrimitiveType ePrimType );

    void AddVertex2D( const SVertex3& vertex );
    void AddVertex3D( const SVertex3& vertex );

    void EndDraw( void );

    // function to check if currently in primitive draw mode
    bool InDrawMode( void ) { return m_bDrawBegin; }

protected:
    // Protected Operations
    CPrimManager() : m_CurrentPrimitive( EPrimitiveType_NONE ), m_bDrawBegin( false ) {}
    CPrimManager( const CPrimManager& );
    CPrimManager& operator=( const CPrimManager& );

private:
    // static singleton instance
    static CPrimManager*    s_pInstance;

    // members
    bool                    m_bDrawBegin;
    EPrimitiveType          m_CurrentPrimitive;
    std::vector< SVertex3 > m_Vertex2DBuffer;        // for 2D geometry
    std::vector< SVertex3 > m_Vertex3DBuffer;        // for 3D geometry
};

//====================================================================================================
// Static Function Accessor
//====================================================================================================
static CPrimManager* PrimManager( void )
{
    return CPrimManager::GetInstance();
}