#pragma once

class CMesh
{
public:
	std::vector<tagVertex> m_vecVertexList;
	std::vector<unsigned short> m_vecIndexList;
};

class CGame : public CDevice
{
public:
	CGame();
	void Initilize(HWND hWnd);
	void Draw(HDC hDC);
private:
	void CreateGroundTexture();
	void CreateGroundModel();
	void LoadKnightTexture();
	void LoadKnightModel();
	void SetupCamera();
	void SetupLights();
	void RenderScene();
private:
	void VertexShader(tagInnerVertex *pInnerVertex);
	void PixelShader(int nX, int nY, tagInnerVertex *pInnerVertex);
private:
	void PostProcessShader(int nX, int nY, tagVector4 *pResultColor);
	float HDR_CalculateAverageLight();
private:
	CCamera *m_pCamera;
	CTexture *m_pTexture1;
	CMesh m_Mesh1;
	CTexture *m_pTexture2;
	CMesh m_Mesh2;
	CTexture *m_pTexture;
	tagVector4 m_clrEnvironment;
	std::vector<CLight *> m_vecLightList;
};

CGame *CGame_GetInstance();