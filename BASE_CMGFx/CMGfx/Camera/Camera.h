#pragma once

//====================================================================================================
// Includes
//====================================================================================================
#include "Common/Vector3.h"
#include "Common/Matrix44.h"

//====================================================================================================
// Class
//====================================================================================================
class CCamera
{
public:
	~CCamera();

	// Function to gain access to singleton instance
	static CCamera* GetInstance(void);

	// Function to initialize the camera
	void Initialize(const CVector3& lookFrom, const CVector3& lookAt);
	void Reset(void);

	// Functions to retrieve matrices
	const CMatrix44& GetProjection(void) { return m_Projection; }
	const CMatrix44& GetViewToWorld(void) { return m_ViewToWorld; }
	const CMatrix44& GetWorldToView(void) { return m_WorldToView; }

	// gets
	float GetFOV(void) const { return m_fFOV; }
	float GetNearPlane(void) const { return m_fNearPlane; }
	float GetFarPlane(void) const { return m_fFarPlane; }
	const CVector3& GetInterest(void) const { ASSERT(m_bInitialized); return m_LookAt; }
	CVector3 GetLookFrom() { return m_LookFrom; }
	// sets
	void SetFOV(float fov);
	void SetNearPlane(float nearPlane) { m_fNearPlane = nearPlane; ComputeProjection(); }
	void SetFarPlane(float farPlane) { m_fFarPlane = farPlane;   ComputeProjection(); }

protected:
	// protected operations for singleton
	CCamera();
	CCamera(const CCamera&);
	CCamera& operator=(const CCamera&);

private:
	// camera attributes
	CVector3 m_LookFrom;                // camera origin
	CVector3 m_LookAt;                  // camera's interest
	CVector3 m_LookUp;                  // up vector
	CVector3 m_LookSide;                // final orthonormal basis vector

	// projection attributes
	float m_fFOV;                       // camera field of view -- default is 90 degrees
	float m_fProjectionPlane;           // the distance from origin to projection plane - computed from FOV
	float m_fNearPlane;                 // the camera's near plane from which drawing should begin
	float m_fFarPlane;                  // the max distance from camera for objects to be rendered

	// stored matrices
	CMatrix44 m_WorldToView;            // stored matrix transform from world coordinates to view coordinates
	CMatrix44 m_ViewToWorld;            // stored matrix transform from view coords back to world coords
	CMatrix44 m_Projection;             // stored projection matrix

	static CCamera* s_pInstance;        // singleton instance
	bool m_bInitialized;

	/* private member functions */

	// Function to calculate the projection matrix
	void ComputeProjection(void);
};

//====================================================================================================
// Singleton Accessor
//====================================================================================================
static CCamera* Camera(void)
{
	return CCamera::GetInstance();
}