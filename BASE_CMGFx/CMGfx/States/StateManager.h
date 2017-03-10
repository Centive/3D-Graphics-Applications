#ifndef INCLUDED_STATEMANAGER
#define INCLUDED_STATEMANAGER
#include "Common/color.h"

//====================================================================================================
// Enums
//====================================================================================================
enum EFillmode 
{
    EFillmode_NONE = -1,

    EFillmode_POINT,
    EFillmode_LINE,
    EFillmode_FILL,

    EFillmode_MAX
};

//====================================================================================================
// Class
//====================================================================================================
class CStateManager
{
public:
    ~CStateManager( void );

    // Instance Retrieval
    static CStateManager* GetInstance( void );

    // function to initialize the state manager
    void Initialize( void );

    // Gets and Sets
    void SetCurrentColor( const CColor& color );
    void SetCurrentFillmode( EFillmode eFillmode );

    const CColor& GetCurrentColor( void ) const;
    EFillmode  GetCurrentFillmode( void ) const;

    // resets the color and fillmode back to their defaults -- White and FILL
    void DefaultStates( void );

protected:
    // Protected Operations
    CStateManager() : m_CurrentFillmode( EFillmode_FILL ) {}
    CStateManager( const CStateManager& );
    CStateManager& operator=( const CStateManager& );

private:
    // static singleton instance
    static CStateManager* s_pInstance;

    // members
    CColor      m_CurrentColor;
    EFillmode   m_CurrentFillmode;
};

//====================================================================================================
// Static Function Accessor
//====================================================================================================
static CStateManager* StateManager( void )
{
    return CStateManager::GetInstance();
}

#endif