
#pragma comment(lib, "gdiplus.lib")  

CPrimitiveList::CPrimitiveList()
{
	m_pVertexList = NULL;
	m_nVertexCount = 0;
	m_pIndexList = NULL;
	m_nIndexCount = 0;
}

CPrimitiveList::~CPrimitiveList()
{

}

CDevice::CDevice()
{
	m_hWnd = NULL;
	m_nWidth = 0;
	m_nHeight = 0;
	m_fMaxX = 0.0f;
	m_fMaxY = 0.0f;
	m_pPixels = NULL;
	m_pBitmap = NULL;
	m_bCorrectPerspective = true;
	m_bWireframeMode = false;
	m_bAlphaBlend = false;
	m_bEnablePostProcess = false;
	m_bEnableHDR = false;
}

void CDevice::Initilize(HWND hWnd)
{
	m_hWnd = hWnd;

	Gdiplus::GdiplusStartupInput GdiplusStartupInput1;
	ULONG_PTR GdiToken1;
	Gdiplus::GdiplusStartup(&GdiToken1,&GdiplusStartupInput1,NULL);

	CreateFrameBuffer();
}

void CDevice::CreateFrameBuffer()
{
	m_nWidth = BACKBUFFER_WIDTH;
	m_nHeight = BACKBUFFER_HEIGHT;
	m_fHalfWidth = m_nWidth / 2.0f;
	m_fHalfHeight = m_nHeight / 2.0f;
	m_fMaxX = (float)(m_nWidth - 1);
	m_fMaxY = (float)(m_nHeight - 1);

	m_pFrameBuffer1 = new CTexture();
	m_pFrameBuffer1->CreateColorBuffer(m_nWidth, m_nHeight);

	m_pFrameBuffer2 = new CTexture();
	m_pFrameBuffer2->CreateColorBuffer(m_nWidth, m_nHeight);

	m_pDepthBuffer = new CTexture();
	m_pDepthBuffer->CreateDepthBuffer(m_nWidth, m_nHeight);

	if(m_pPixels)
	{
		delete [] m_pPixels;
		m_pPixels = NULL;
	}
	m_pPixels = new BYTE[m_nWidth * m_nHeight * 4];

	m_pBitmap = new Gdiplus::Bitmap(m_nWidth, m_nHeight, m_nWidth * 4, PixelFormat32bppARGB, m_pPixels);
}

void CDevice::UpdateWorldViewProjectionMatrix()
{
	Matrix4x4Multiply(&m_matWorldViewProjection, &m_matView, &m_matProjection);
	Matrix4x4Multiply(&m_matWorldViewProjection, &m_matWorld, &m_matWorldViewProjection);
}

void CDevice::SetupWorldMatrix(tagMatrix4x4 *pmatWorld)
{
	m_matWorld = *pmatWorld;
	UpdateWorldViewProjectionMatrix();
}

void CDevice::SetupViewMatrix(tagMatrix4x4 *pmatView)
{
	m_matView = *pmatView;
	UpdateWorldViewProjectionMatrix();
}

void CDevice::SetupProjectionMatrix(tagMatrix4x4 *pmatProjection)
{
	m_matProjection = *pmatProjection;
	UpdateWorldViewProjectionMatrix();
}

void CDevice::Clear(const tagVector4 &vColor, float fDepth)
{
	m_pFrameBuffer1->ClearColor(vColor);

	m_pDepthBuffer->ClearDepth(fDepth);
}

void CDevice::DrawLine(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2)
{
	tagInnerVertex stInnerVertex;

	float fX1 = pInnerVertex1->vPosition_Output.fX;
	float fY1 = pInnerVertex1->vPosition_Output.fY;
	float fX2 = pInnerVertex2->vPosition_Output.fX;
	float fY2 = pInnerVertex2->vPosition_Output.fY;

	float fX1_1 = ceil(fX1 - 0.5f);
	float fY1_1 = ceil(fY1 - 0.5f);
	float fX2_1 = ceil(fX2 - 0.5f);
	float fY2_1 = ceil(fY2 - 0.5f);

	int nMinX = (int)MIN_(fX1_1, fX2_1);
	int nMaxX = (int)MAX_(fX1_1, fX2_1);
	int nMinY = (int)MIN_(fY1_1, fY2_1);
	int nMaxY = (int)MAX_(fY1_1, fY2_1);

	if (nMaxX - nMinX > nMaxY - nMinY)
	{
		int nX;
		for (nX = nMinX; nX < nMaxX; nX++)
		{
			float fLerp = (nX - fX1) / (fX2 - fX1);
			DO_CLAMP(fLerp, 0.0f, 1.0f);

			InnerVertexLerpOutput(&stInnerVertex, pInnerVertex1, pInnerVertex2, fLerp, m_bCorrectPerspective);

			int nY = (int)(stInnerVertex.vPosition_Output.fY);

			if (nX >= 0 && nX < m_nWidth &&
				nY >= 0 && nY < m_nHeight)
			{
				PixelShader(nX, nY, &stInnerVertex);
			}
		}
	}
	else
	{
		int nY;
		for (nY = nMinY; nY < nMaxY; nY++)
		{
			float fLerp = (nY - fY1) / (fY2 - fY1);
			DO_CLAMP(fLerp, 0.0f, 1.0f);

			InnerVertexLerpOutput(&stInnerVertex, pInnerVertex1, pInnerVertex2, fLerp, m_bCorrectPerspective);

			int nX = (int)(stInnerVertex.vPosition_Output.fX);

			if (nX >= 0 && nX < m_nWidth &&
				nY >= 0 && nY < m_nHeight)
			{
				PixelShader(nX, nY, &stInnerVertex);
			}
		}
	}
}

void CDevice::DrawTriangle(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, tagInnerVertex *pInnerVertex3)
{
	// 背面裁剪

	tagVector3 vDifference1 = pInnerVertex2->vPosition_Output - pInnerVertex1->vPosition_Output;
	tagVector3 vDifference2 = pInnerVertex3->vPosition_Output - pInnerVertex2->vPosition_Output;
	tagVector3 vNormal;
	Vector3CrossProduct(&vNormal, &vDifference1, &vDifference2);
	if (vNormal.fZ > 0.0f)
	{
		return;
	}

	DrawLine(pInnerVertex1, pInnerVertex2);

	DrawLine(pInnerVertex2, pInnerVertex3);

	DrawLine(pInnerVertex3, pInnerVertex1);
}

void CDevice::DrawScanLine(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, float fY)
{
	tagInnerVertex stInnerVertex;

	float fX1 = pInnerVertex1->vPosition_Output.fX;
	float fY1 = pInnerVertex1->vPosition_Output.fY;
	float fX2 = pInnerVertex2->vPosition_Output.fX;
	float fY2 = pInnerVertex2->vPosition_Output.fY;

	float fX1_1 = ceil(fX1 - 0.5f);
	float fX2_1 = ceil(fX2 - 0.5f);

	if (fY < 0.0f || fY > m_fMaxY)
	{
		return;
	}

	DO_CLAMP(fX1_1, 0, m_fMaxX);
	DO_CLAMP(fX2_1, 0, m_fMaxX);

	if (!m_bAlphaBlend)
	{
		fX2_1++;
	}

	int nX = (int)fX1_1;
	int nY = (int)fY;

	float fX;
	for (fX = fX1_1; fX < fX2_1; fX++, nX++)
	{
		float fLerp = (fX - fX1) / (fX2 - fX1);
		DO_CLAMP(fLerp, 0.0f, 1.0f);

		InnerVertexLerpOutput(&stInnerVertex, pInnerVertex1, pInnerVertex2, fLerp, m_bCorrectPerspective);

		PixelShader(nX, nY, &stInnerVertex);
	}
}

void CDevice::FillTriangle1(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, tagInnerVertex *pInnerVertex3)
{
	// 画实心平底三角形 
	//  1
	// 2 3

	float fY1 = pInnerVertex1->vPosition_Output.fY;
	float fY2 = pInnerVertex2->vPosition_Output.fY;
	float fY1_1 = ceil(fY1 - 0.5f);
	float fY2_1 = ceil(fY2 - 0.5f);

	DO_CLAMP(fY1_1, 0, m_fMaxY);
	DO_CLAMP(fY2_1, 0, m_fMaxY);

	tagInnerVertex stInnerVertex1;
	tagInnerVertex stInnerVertex2;

	for (float fY = fY1_1; fY < fY2_1; fY++)
	{
		float fLerp = (fY - fY1) / (fY2 - fY1);
		DO_CLAMP(fLerp, 0.0f, 1.0f);

		InnerVertexLerpOutput(&stInnerVertex1, pInnerVertex1, pInnerVertex2, fLerp, m_bCorrectPerspective);
		InnerVertexLerpOutput(&stInnerVertex2, pInnerVertex1, pInnerVertex3, fLerp, m_bCorrectPerspective);
		
		DrawScanLine(&stInnerVertex1, &stInnerVertex2, fY);
	}
}

void CDevice::FillTriangle2(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, tagInnerVertex *pInnerVertex3)
{
	// 画实心平顶三角形  
	// 1 2
	//  3

	float fY1 = pInnerVertex1->vPosition_Output.fY;
	float fY3 = pInnerVertex3->vPosition_Output.fY;
	
	float fY1_1 = ceil(fY1 - 0.5f);
	float fY3_1 = ceil(fY3 - 0.5f);

	DO_CLAMP(fY1_1, 0, m_fMaxY);
	DO_CLAMP(fY3_1, 0, m_fMaxY);

	tagInnerVertex stInnerVertex1;
	tagInnerVertex stInnerVertex2;

	for (float fY = fY1_1; fY < fY3_1; fY++)
	{
		float fLerp = (fY - fY1) / (fY3 - fY1);
		DO_CLAMP(fLerp, 0.0f, 1.0f);

		InnerVertexLerpOutput(&stInnerVertex1, pInnerVertex1, pInnerVertex3, fLerp, m_bCorrectPerspective);
		InnerVertexLerpOutput(&stInnerVertex2, pInnerVertex2, pInnerVertex3, fLerp, m_bCorrectPerspective);

		DrawScanLine(&stInnerVertex1, &stInnerVertex2, fY);
	}
}

void CDevice::FillTriangle(tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, tagInnerVertex *pInnerVertex3)
{
	// 背面裁剪

	tagVector3 vDifference1 = pInnerVertex2->vPosition_Output - pInnerVertex1->vPosition_Output;
	tagVector3 vDifference2 = pInnerVertex3->vPosition_Output - pInnerVertex2->vPosition_Output;
	tagVector3 vNormal;
	Vector3CrossProduct(&vNormal, &vDifference1, &vDifference2);
	if (vNormal.fZ > 0.0f)
	{
		return;
	}

	// 按y排序
	tagInnerVertex *pInnerVertex_Top = NULL;
	tagInnerVertex *pInnerVertex_Middle = NULL;
	tagInnerVertex *pInnerVertex_Bottom = NULL;

	float y1 = pInnerVertex1->vPosition_Output.fY;
	float y2 = pInnerVertex2->vPosition_Output.fY;
	float y3 = pInnerVertex3->vPosition_Output.fY;

	if (y1 <= y2 && y2 <= y3) // y1 y2 y3  
	{
		pInnerVertex_Top = pInnerVertex1;
		pInnerVertex_Middle = pInnerVertex2;
		pInnerVertex_Bottom = pInnerVertex3;
	}
	else if (y1 <= y3 && y3 <= y2) // y1 y3 y2  
	{
		pInnerVertex_Top = pInnerVertex1;
		pInnerVertex_Middle = pInnerVertex3;
		pInnerVertex_Bottom = pInnerVertex2;
	}
	else if (y2 <= y1 && y1 <= y3) // y2 y1 y3  
	{
		pInnerVertex_Top = pInnerVertex2;
		pInnerVertex_Middle = pInnerVertex1;
		pInnerVertex_Bottom = pInnerVertex3;
	}
	else if (y2 <= y3 && y3 <= y1) // y2 y3 y1  
	{
		pInnerVertex_Top = pInnerVertex2;
		pInnerVertex_Middle = pInnerVertex3;
		pInnerVertex_Bottom = pInnerVertex1;
	}
	else if (y3 <= y1 && y1 <= y2) // y3 y1 y2  
	{
		pInnerVertex_Top = pInnerVertex3;
		pInnerVertex_Middle = pInnerVertex1;
		pInnerVertex_Bottom = pInnerVertex2;
	}
	else if (y3 <= y2 && y2 <= y1) // y3 y2 y1  
	{
		pInnerVertex_Top = pInnerVertex3;
		pInnerVertex_Middle = pInnerVertex2;
		pInnerVertex_Bottom = pInnerVertex1;
	}
	else
	{
		ASSERT_(false);
	}

	float xtop = pInnerVertex_Top->vPosition_Output.fX;
	float xmiddle = pInnerVertex_Middle->vPosition_Output.fX;
	float xbottom = pInnerVertex_Bottom->vPosition_Output.fX;
	
	float ytop = pInnerVertex_Top->vPosition_Output.fY;
	float ymiddle = pInnerVertex_Middle->vPosition_Output.fY;
	float ybottom = pInnerVertex_Bottom->vPosition_Output.fY;

	float fLerp = (ymiddle - ytop) / (ybottom - ytop);
	float fX1 = (xbottom - xtop) * fLerp + xtop;
	
	tagInnerVertex stInnerVertex1;
	InnerVertexLerpOutput(&stInnerVertex1, pInnerVertex_Top, pInnerVertex_Bottom, fLerp, m_bCorrectPerspective);

	if (fX1 <= xmiddle) // 左三角形 
	{
		// 画平底
		FillTriangle1(pInnerVertex_Top, &stInnerVertex1, pInnerVertex_Middle);

		// 画平顶  
		FillTriangle2(&stInnerVertex1, pInnerVertex_Middle, pInnerVertex_Bottom);
	}
	else // 右三角形  
	{
		// 画平底  
		FillTriangle1(pInnerVertex_Top, pInnerVertex_Middle, &stInnerVertex1);

		// 画平顶  
		FillTriangle2(pInnerVertex_Middle, &stInnerVertex1, pInnerVertex_Bottom);
	}
}

void CDevice::DrawPrimitiveList(CPrimitiveList *pPrimitiveList)
{
	std::vector<tagInnerVertex> vecInnerVertexList;

	int i;
	int nCount = pPrimitiveList->m_nVertexCount;

	vecInnerVertexList.resize(nCount);

	for (i = 0; i < nCount; i++)
	{
		tagVertex *pVertex = &(pPrimitiveList->m_pVertexList[i]);
		tagInnerVertex *pInnerVertex = &(vecInnerVertexList[i]);
		pInnerVertex->vPosition_Input = pVertex->vPosition;
		pInnerVertex->vNormal_Input = pVertex->vNormal;
		pInnerVertex->fU_Input = pVertex->fU;
		pInnerVertex->fV_Input = pVertex->fV;
	}

	int nIndexCount = pPrimitiveList->m_nIndexCount;
	for (i = 0; i < nIndexCount; i++)
	{
		int nIndex = pPrimitiveList->m_pIndexList[i];
		tagInnerVertex *pInnerVertex = &(vecInnerVertexList[nIndex]);
		if (!pInnerVertex->m_bProcessed)
		{
			VertexShader(pInnerVertex);

			pInnerVertex->m_bProcessed = true;
		}
	}

	int i1 = 0;
	int nTirangleCount = nIndexCount / 3;
	for (i = 0; i < nTirangleCount; i++)
	{
		int nIndex1 = pPrimitiveList->m_pIndexList[i1++];
		int nIndex2 = pPrimitiveList->m_pIndexList[i1++];
		int nIndex3 = pPrimitiveList->m_pIndexList[i1++];

		tagInnerVertex *pInnerVertex1 = &(vecInnerVertexList[nIndex1]);
		tagInnerVertex *pInnerVertex2 = &(vecInnerVertexList[nIndex2]);
		tagInnerVertex *pInnerVertex3 = &(vecInnerVertexList[nIndex3]);

		if(m_bWireframeMode)
		{
			DrawTriangle(pInnerVertex1, pInnerVertex2, pInnerVertex3);
		}
		else
		{
			FillTriangle(pInnerVertex1, pInnerVertex2, pInnerVertex3);
		}
	}
}

void CDevice::PostProcess()
{
	if (!m_bEnablePostProcess)
	{
		return;
	}

	float fAverageLight = 0.0f;
	
	if (m_bEnableHDR)
	{
		fAverageLight = HDR_CalculateAverageLight();
	}

	int nX;
	int nY;
	tagVector4 vResultColor;
	for (nY = 0; nY < m_nHeight; nY++)
	{
		for (nX = 0; nX < m_nWidth; nX++)
		{
			PostProcessShader(nX, nY, &vResultColor);

			m_pFrameBuffer2->SetPixel(nX, nY, &vResultColor);
		}
	}
}

void CDevice::BeginScene(HDC hDC)
{
	m_pGraphics = new Gdiplus::Graphics(hDC);
}

void CDevice::EndScene()
{
	if (m_bEnablePostProcess)
	{
		m_pFrameBuffer2->CopyToColorBuffer((unsigned int *)m_pPixels);
	}
	else
	{
		m_pFrameBuffer1->CopyToColorBuffer((unsigned int *)m_pPixels);
	}

	m_pGraphics->DrawImage(m_pBitmap, 0, 0);

	delete m_pGraphics;

	InvalidateRect(m_hWnd, NULL, FALSE);
}