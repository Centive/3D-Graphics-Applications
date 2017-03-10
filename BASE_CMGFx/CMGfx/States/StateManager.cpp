#include "stdafx.h"
#include "StateManager.h"
#include "PrimManager.h"
#include "Display/Rasterizer.h"

//====================================================================================================
// Statics
//====================================================================================================

CStateManager* CStateManager::s_pInstance = NULL;

//====================================================================================================
// Class
//====================================================================================================

//====================================================================================================
// Function Definitions
//====================================================================================================
CStateManager* CStateManager::GetInstance( void )
{
    if ( NULL == s_pInstance )
    {
        s_pInstance = new CStateManager();
    }
    return s_pInstance;
}

//----------------------------------------------------------------------------------------------------

void CStateManager::Initialize( void )
{
    DefaultStates();
}

//----------------------------------------------------------------------------------------------------

void CStateManager::SetCurrentColor( const CColor& color )
{
    m_CurrentColor = color;
    if ( false == PrimManager()->InDrawMode() ) Rasterizer()->SetColor( color );
}

//----------------------------------------------------------------------------------------------------

void CStateManager::SetCurrentFillmode( EFillmode eFillmode )
{
    m_CurrentFillmode = eFillmode;
}

//----------------------------------------------------------------------------------------------------

const CColor& CStateManager::GetCurrentColor() const
{
    return m_CurrentColor;
}

//----------------------------------------------------------------------------------------------------

EFillmode CStateManager::GetCurrentFillmode( void ) const
{
    return m_CurrentFillmode;
}

//----------------------------------------------------------------------------------------------------

void CStateManager::DefaultStates( void )
{
    m_CurrentColor.r = 1.0f; m_CurrentColor.g = 1.0f; m_CurrentColor.b = 1.0f;
    m_CurrentFillmode = EFillmode_FILL;
}

//----------------------------------------------------------------------------------------------------

CStateManager::~CStateManager( void )
{
    // empty destructor
}