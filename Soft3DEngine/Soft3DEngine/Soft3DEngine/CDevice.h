
#pragma once

class CPrimitiveList
{
public:
	CPrimitiveList();
	~CPrimitiveList();
public:
	tagVertex *m_pVertexList;
	int m_nVertexCount;
	unsigned short *m_pIndexList;
	int m_nIndexCount;
};

class CDevice
{
public:
	CDevice();
	void Initilize(HWND hWnd);
	void SetupWorldMatrix(tagMatrix4x4 *pmatWorld);
	void SetupViewMatrix(tagMatrix4x4 *pmatView);
	void SetupProjectionMatrix(tagMatrix4x4 *pmatProjection);
protected:
	void CreateFrameBuffer();
	void UpdateWorldViewProjectionMatrix();
	void Clear(const tagVector4 &vColor, float fDepth);
	void DrawLine(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2);
	void DrawTriangle(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, tagInnerVertex *pInnerVertex3);
	void DrawScanLine(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, float fY);
	void FillTriangle1(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, tagInnerVertex *pInnerVertex3);
	void FillTriangle2(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, tagInnerVertex *pInnerVertex3);
	void FillTriangle(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, tagInnerVertex *pInnerVertex3);
	void DrawPrimitiveList(CPrimitiveList *pPrimitiveList);
	void PostProcess();
	void BeginScene(HDC hDC);
	void EndScene();
protected:
	virtual void VertexShader(tagInnerVertex *pInnerVertex) = 0;
	virtual void PixelShader(int nX, int nY, tagInnerVertex *pInnerVertex) = 0;
protected:
	virtual void PostProcessShader(int nX, int nY, tagVector4 *pResultColor) = 0;
	virtual float HDR_CalculateAverageLight() = 0;
protected:
	HWND m_hWnd;
	BYTE *m_pPixels;
	Gdiplus::Bitmap *m_pBitmap;
	Gdiplus::Graphics *m_pGraphics;
	int m_nWidth;
	int m_nHeight;
	float m_fHalfWidth;
	float m_fHalfHeight;
	float m_fMaxX;
	float m_fMaxY;
	tagMatrix4x4 m_matWorldViewProjection;
	tagMatrix4x4 m_matWorld;
	tagMatrix4x4 m_matView;
	tagMatrix4x4 m_matProjection;
	CTexture *m_pFrameBuffer1;
	CTexture *m_pFrameBuffer2;
	CTexture *m_pDepthBuffer;
	bool m_bCorrectPerspective;
	bool m_bWireframeMode;
	bool m_bAlphaBlend;
	bool m_bEnablePostProcess;
	bool m_bEnableHDR;
};