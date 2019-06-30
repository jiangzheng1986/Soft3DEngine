
#pragma once

int GetShiftOfInteger(int nValue);

class CTexture
{
public:
	CTexture();
	~CTexture();
	void CreateColorBuffer(int nWidth, int nHeight);
	void CreateDepthBuffer(int nWidth, int nHeight);
	void LoadTexture(const char *pszFilename);
	void ClearColor(const tagVector4 &vColor);
	void ClearDepth(float fDepth);
	void ReleaseTexture();
	inline void GetPixel(int nX, int nY, tagVector4 *pColor);
	inline void SetPixel(int nX, int nY, const tagVector4 *pColor);
	inline void GetPixelByUV(float fU, float fV, tagVector4 *pColor);
	void CopyToColorBuffer(unsigned int *pColorBuffer);
	inline void SetDepth(int nX, int nY, float fDepth);
	inline float GetDepth(int nX, int nY);
public:
	int m_nWidth;
	int m_nHeight;
	int m_nShiftY;
	tagVector4 *m_pColorData;
	float *m_pDepthData;
};