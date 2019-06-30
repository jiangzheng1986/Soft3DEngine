
CLightSample::CLightSample()
{

}

CLightSample::CLightSample(const tagVector3 &L, const tagVector4 &EL)
{
	m_L = L;
	m_EL = EL;
}

CLightSample::~CLightSample()
{

}

CLight::CLight()
{
	
}

CDirectionalLight::CDirectionalLight(const tagVector4 &irradiance, const tagVector3 &direction)
{
	m_irradiance = irradiance;
	m_direction = direction;
}

CDirectionalLight::~CDirectionalLight()
{

}

void CDirectionalLight::Initialize()
{	
	m_L = m_direction;

	Vector3Normalize(&m_L);

	m_L = m_L * -1.0f;
}

void CDirectionalLight::Sample(CLightSample *lightSample, const tagVector3 &position)
{
	lightSample->m_L = m_L;
	lightSample->m_EL = m_irradiance;
}

CPointLight::CPointLight(const tagVector4 &intensity, const tagVector3 &position)
{
	m_intensity = intensity;
	m_position = position;
}

CPointLight::~CPointLight()
{

}

void CPointLight::Initialize()
{

}

void CPointLight::Sample(CLightSample *lightSample, const tagVector3 &position)
{
	tagVector3 delta = m_position - position;
	float rr = Vector3LengthSq(&delta);
	float r = sqrtf(rr);
	tagVector3 L = delta / r;

	float attenuation = 1.0f;// / rr;

	tagVector4 EL = m_intensity * attenuation;

	if (EL.fX < MATH_EPSILON &&
		EL.fY < MATH_EPSILON &&
		EL.fZ < MATH_EPSILON)
	{
		*lightSample = CLightSample();
		return;
	}

	lightSample->m_L = L;
	lightSample->m_EL = EL;
}

CSpotLight::CSpotLight(const tagVector4 &intensity, const tagVector3 &position, const tagVector3 &direction,
	float theta, float phi, float falloff)
{
	m_intensity = intensity;
	m_position = position;
	m_direction = direction;
	m_theta = theta;
	m_phi = phi;
	m_falloff = falloff;
}

CSpotLight::~CSpotLight()
{

}

void CSpotLight::Initialize()
{
	m_S = m_direction;
	Vector3Normalize(&m_S);
	m_S = m_S * -1.0f;

	m_cosTheta = cosf(m_theta * MATH_PI / 180 / 2);
	m_cosPhi = cosf(m_phi * MATH_PI / 180 / 2);
	m_baseMultiplier = 1.0f / (m_cosTheta - m_cosPhi);
}

void CSpotLight::Sample(CLightSample *lightSample, const tagVector3 &position)
{
	tagVector3 delta = m_position - position;
	float rr = Vector3LengthSq(&delta);
	float r = sqrtf(rr);
	tagVector3 L = delta / r;

	float spot = 0.0f;
	float SdotL = Vector3Dot(&m_S, &L);
	if (SdotL >= m_cosTheta)
	{
		spot = 1.0f;
	}
	else if (SdotL <= m_cosPhi)
	{
		spot = 0.0f;

		*lightSample = CLightSample();
		return;
	}
	else
	{
		spot = powf((SdotL - m_cosPhi) * m_baseMultiplier, m_falloff);
	}

	float attenuation = 1.0f;// / rr;

	tagVector4 EL = m_intensity * (attenuation * spot);

	if (EL.fX < MATH_EPSILON &&
		EL.fY < MATH_EPSILON &&
		EL.fZ < MATH_EPSILON)
	{
		*lightSample = CLightSample();
		return;
	}

	lightSample->m_L = L;
	lightSample->m_EL = EL;
}