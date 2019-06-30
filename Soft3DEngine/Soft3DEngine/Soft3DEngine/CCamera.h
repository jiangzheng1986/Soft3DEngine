
#pragma once

class CCamera
{
public:
	CCamera();
	~CCamera();
	void SetupCamera();
public:
	tagVector3 m_vEyePoint;
	tagVector3 m_vLookAt;
	tagVector3 m_vUpVector;
	float m_fFov;
	float m_fAspect;
	float m_fZNear;
	float m_fZFar;
};