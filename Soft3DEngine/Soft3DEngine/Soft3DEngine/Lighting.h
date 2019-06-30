
#pragma once

class CLightSample
{
public:
	CLightSample();
	CLightSample(const tagVector3 &L, const tagVector4 &EL);
	~CLightSample();
public:
	tagVector3 m_L;
	tagVector4 m_EL;
};

class CLight
{
public:
	CLight();
	virtual void Initialize() = 0;
	virtual void Sample(CLightSample *lightSample, const tagVector3 &position) = 0;
};

class CDirectionalLight : public CLight
{
public:
	CDirectionalLight(const tagVector4 &irradiance, const tagVector3 &direction);
	~CDirectionalLight();
	void Initialize() override;
	void Sample(CLightSample *lightSample, const tagVector3 &position) override;
private:
	tagVector4 m_irradiance;
	tagVector3 m_direction;
	tagVector3 m_L;
};

class CPointLight : public CLight
{
public:
	CPointLight(const tagVector4 &intensity, const tagVector3 &position);
	~CPointLight();
	void Initialize() override;
	void Sample(CLightSample *lightSample, const tagVector3 &position) override;
private:
	tagVector4 m_intensity;
	tagVector3 m_position;
};

class CSpotLight : public CLight
{
public:
	CSpotLight(const tagVector4 &intensity, const tagVector3 &position, const tagVector3 &direction,
		float theta, float phi, float falloff);
	~CSpotLight();
	void Initialize() override;
	void Sample(CLightSample *lightSample, const tagVector3 &position) override;
private:
	tagVector4 m_intensity;
	tagVector3 m_position;
	tagVector3 m_direction;
	float m_theta;
	float m_phi;
	float m_falloff;
private:
	tagVector3 m_S;
	float m_cosTheta;
	float m_cosPhi;
	float m_baseMultiplier;
};