
CCamera::CCamera()
{
	m_vEyePoint = tagVector3(10.0f, 10.0f, 10.0f);
	m_vLookAt = tagVector3(0.0f, 0.0f, 0.0f);
	m_vUpVector = tagVector3(0.0f, 1.0f, 0.0f);

	m_fFov = MATH_PI / 4;
	m_fAspect = 1.0f;
	m_fZNear = 0.2f;
	m_fZFar = 300.0f;
}

CCamera::~CCamera()
{

}

void CCamera::SetupCamera()
{
	tagMatrix4x4 matView;
	tagMatrix4x4 matProjection;

	Matrix4x4LookAtRH((tagMatrix4x4 *)&matView,
		m_vEyePoint.fX, m_vEyePoint.fY, m_vEyePoint.fZ,
		m_vLookAt.fX, m_vLookAt.fY, m_vLookAt.fZ,
		m_vUpVector.fX, m_vUpVector.fY, m_vUpVector.fZ);

	Matrix4x4PerspectiveRH_OGL((tagMatrix4x4 *)&matProjection, m_fFov, m_fAspect, m_fZNear, m_fZFar);

	CGame_GetInstance()->SetupViewMatrix(&matView);
	CGame_GetInstance()->SetupProjectionMatrix(&matProjection);
}