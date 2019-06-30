
CGame *CGame_GetInstance()
{
	static CGame s_Game;

	return &s_Game;
}

CGame::CGame()
{
	m_pCamera = NULL;

	m_clrEnvironment = tagVector4(0.4f, 0.4f, 0.4f, 1.0f);
}

void CGame::Initilize(HWND hWnd)
{
	CDevice::Initilize(hWnd);

	CreateGroundTexture();

	CreateGroundModel();

	LoadKnightTexture();

	LoadKnightModel();

	SetupLights();
}

void CGame::CreateGroundTexture()
{
	m_pTexture1 = new CTexture();

	m_pTexture1->CreateColorBuffer(8, 8);

	tagVector4 clrColor_White(1.0f, 1.0f, 1.0f, 1.0f);
	tagVector4 clrColor_Black(0.0f, 0.0f, 0.0f, 1.0f);

	int x;
	int y;
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			bool bBlack = (x + y) % 2 == 0;
			m_pTexture1->SetPixel(x, y, bBlack ? &clrColor_Black : &clrColor_White);
		}
	}
}

void CGame::CreateGroundModel()
{
	float fSize = 7.0f;
	float fY = -10.0f;
	
	tagVertex stVertex1;
	stVertex1.vNormal = tagVector3(0.0f, 1.0f, 0.0f);
	stVertex1.vPosition = tagVector3(-fSize, fY, -fSize);
	stVertex1.fU = 0.0f;
	stVertex1.fV = 0.0f;
	m_Mesh1.m_vecVertexList.push_back(stVertex1);

	tagVertex stVertex2;
	stVertex2.vNormal = tagVector3(0.0f, 1.0f, 0.0f);
	stVertex2.vPosition = tagVector3(fSize, fY, -fSize);
	stVertex2.fU = 1.0f;
	stVertex2.fV = 0.0f;
	m_Mesh1.m_vecVertexList.push_back(stVertex2);

	tagVertex stVertex3;
	stVertex3.vNormal = tagVector3(0.0f, 1.0f, 0.0f);
	stVertex3.vPosition = tagVector3(-fSize, fY, fSize);
	stVertex3.fU = 0.0f;
	stVertex3.fV = 1.0f;
	m_Mesh1.m_vecVertexList.push_back(stVertex3);

	tagVertex stVertex4;
	stVertex4.vNormal = tagVector3(0.0f, 1.0f, 0.0f);
	stVertex4.vPosition = tagVector3(fSize, fY, fSize);
	stVertex4.fU = 1.0f;
	stVertex4.fV = 1.0f;
	m_Mesh1.m_vecVertexList.push_back(stVertex4);

	m_Mesh1.m_vecIndexList.push_back(0);
	m_Mesh1.m_vecIndexList.push_back(2);
	m_Mesh1.m_vecIndexList.push_back(1);

	m_Mesh1.m_vecIndexList.push_back(1);
	m_Mesh1.m_vecIndexList.push_back(2);
	m_Mesh1.m_vecIndexList.push_back(3);
}

void CGame::LoadKnightTexture()
{
	m_pTexture2 = new CTexture();

	m_pTexture2->LoadTexture("Knight.simpleimage");
}

void CGame::LoadKnightModel()
{
	FILE *pFile = NULL;
	fopen_s(&pFile, "Knight.simplemodel", "rb");

	int nVertexCount = 0;
	fread(&nVertexCount, sizeof(int), 1, pFile);

	tagVertex stVertex;
	int i;
	for (i = 0; i < nVertexCount; i++)
	{
		fread(&stVertex, sizeof(tagVertex), 1, pFile);

		m_Mesh2.m_vecVertexList.push_back(stVertex);
	}

	int nIndexCount = 0;
	fread(&nIndexCount, sizeof(int), 1, pFile);
	unsigned short usIndex = 0;

	for (i = 0; i < nIndexCount; i++)
	{
		fread(&usIndex, sizeof(unsigned short), 1, pFile);

		m_Mesh2.m_vecIndexList.push_back(usIndex);
	}

	fclose(pFile);
}

void CGame::SetupCamera()
{
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	m_pCamera = new CCamera();

	m_pCamera->m_vEyePoint = tagVector3(10.0f, 10.0f, 10.0f);

	m_pCamera->m_fAspect = m_nWidth / (float)m_nHeight;

	m_pCamera->SetupCamera();
}

void CGame::SetupLights()
{
	CDirectionalLight *directionalLight1 = new CDirectionalLight(tagVector4(0.6f, 0.6f, 0.6f, 1.0f), tagVector3(1.75f, -2.0f, -1.5f));

	m_vecLightList.push_back(directionalLight1);

	CPointLight *pointLight1 = new CPointLight(tagVector4(1.0f, 1.0f, 1.0f, 1.0f), tagVector3(40, 40.0f, -40));

	//m_vecLightList.push_back(pointLight1);

	CSpotLight *spotLight1 = new CSpotLight(tagVector4(1.0f, 1.0f, 1.0f, 1.0f), tagVector3(0, 15.0f, 0), tagVector3(0.0f, -1.0f, 0.0f),
		20.0f, 30.0f, 0.5f);

	//m_vecLightList.push_back(spotLight1);

	int i;
	int nCount = m_vecLightList.size();
	for (i = 0; i < nCount; i++)
	{
		m_vecLightList[i]->Initialize();
	}
}

void CGame::RenderScene()
{
	unsigned int dwTime1 = GetTickCount();

	float fRotationY = dwTime1 / 500.0f;// *0.2f;

	tagVector4 vClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Clear(vClearColor, 1.0f);

	SetupCamera();

	tagMatrix4x4 matWorld1;
	tagMatrix4x4 matWorld2;
	tagMatrix4x4 matWorld3;
	tagMatrix4x4 matWorld;
	Matrix4x4RotationY(&matWorld1, fRotationY);
	Matrix4x4Identity(&matWorld2);
	Matrix4x4Scaling(&matWorld3, 0.8f, 0.8f, 0.8f);
	Matrix4x4Multiply(&matWorld, &matWorld2, &matWorld1);
	Matrix4x4Multiply(&matWorld, &matWorld3, &matWorld);
	SetupWorldMatrix(&matWorld);

	CPrimitiveList PrimitiveList1;
	PrimitiveList1.m_pVertexList = &(m_Mesh1.m_vecVertexList[0]);
	PrimitiveList1.m_nVertexCount = m_Mesh1.m_vecVertexList.size();
	PrimitiveList1.m_pIndexList = &(m_Mesh1.m_vecIndexList[0]);
	PrimitiveList1.m_nIndexCount = m_Mesh1.m_vecIndexList.size();

	m_pTexture = m_pTexture1;

	DrawPrimitiveList(&PrimitiveList1);

	Matrix4x4RotationY(&matWorld1, fRotationY);
	Matrix4x4RotationX(&matWorld2, -MATH_PI / 2);
	Matrix4x4Scaling(&matWorld3, 0.8f, 0.8f, 0.8f);
	Matrix4x4Multiply(&matWorld, &matWorld2, &matWorld1);
	Matrix4x4Multiply(&matWorld, &matWorld3, &matWorld);
	SetupWorldMatrix(&matWorld);

	CPrimitiveList PrimitiveList2;
	PrimitiveList2.m_pVertexList = &(m_Mesh2.m_vecVertexList[0]);
	PrimitiveList2.m_nVertexCount = m_Mesh2.m_vecVertexList.size();
	PrimitiveList2.m_pIndexList = &(m_Mesh2.m_vecIndexList[0]);
	PrimitiveList2.m_nIndexCount = m_Mesh2.m_vecIndexList.size();

	m_pTexture = m_pTexture2;

	DrawPrimitiveList(&PrimitiveList2);

	PostProcess();

	unsigned int dwTime2 = GetTickCount();

	char szBuffer[1000];
	sprintf(szBuffer, "%d\n", dwTime2 - dwTime1);
	OutputDebugStringA(szBuffer);
}

void CGame::Draw(HDC hDC)
{
	BeginScene(hDC);

	RenderScene();

	EndScene();
}

void CGame::VertexShader(tagInnerVertex *pInnerVertex)
{
	tagVector3 *pPosition = &(pInnerVertex->vPosition_Input);
	tagVector4 vPosition1(pPosition->fX, pPosition->fY, pPosition->fZ, 1.0f);
	tagVector4 vPositionScreen;

	Matrix4x4TransformCoord4(&vPositionScreen, &vPosition1, &m_matWorldViewProjection);

	float f1_div_W = 1.0f / vPositionScreen.fW;

	float fX = m_fHalfWidth + vPositionScreen.fX * f1_div_W * m_fHalfWidth;
	float fY = m_fHalfHeight - vPositionScreen.fY * f1_div_W * m_fHalfHeight;
	float fZ = vPositionScreen.fZ * f1_div_W;

	pInnerVertex->vPosition_Output = tagVector3(fX, fY, fZ);

	Matrix4x4TransformCoord3(&(pInnerVertex->vWorldPosition_Output), &(pInnerVertex->vPosition_Input), &m_matWorld);
	Matrix4x4TransformNormal(&(pInnerVertex->vWorldNormal_Output), &(pInnerVertex->vNormal_Input), &m_matWorld);

	pInnerVertex->fU_Output = pInnerVertex->fU_Input;
	pInnerVertex->fV_Output = pInnerVertex->fV_Input;

	if (m_bCorrectPerspective)
	{
		float fInvZ = 1.0f / vPositionScreen.fZ;
		pInnerVertex->fInvZ = fInvZ;
		pInnerVertex->fU_Times_InvZ = pInnerVertex->fU_Output * fInvZ;
		pInnerVertex->fV_Times_InvZ = pInnerVertex->fV_Output * fInvZ;
	}
}

void CGame::PixelShader(int nX, int nY, tagInnerVertex *pInnerVertex)
{
	float fDepthOld = m_pDepthBuffer->GetDepth(nX, nY);
	float fDepthNew = pInnerVertex->vPosition_Output.fZ;
	if (fDepthNew < fDepthOld)
	{
		if (m_bWireframeMode)
		{
			tagVector4 clrWhite(1.0f, 1.0f, 1.0f, 1.0f);

			m_pFrameBuffer1->SetPixel(nX, nY, &clrWhite);
		}
		else
		{
			tagVector4 stTextureColor;

			if (m_pTexture)
			{
				m_pTexture->GetPixelByUV(pInnerVertex->fU_Output, pInnerVertex->fV_Output, &stTextureColor);
			}

			float fGrayScale = stTextureColor.fX * 0.334f + stTextureColor.fY * 0.333f + stTextureColor.fZ * 0.333f;

			fGrayScale *= 2.5f;

			CLightSample lightSample;
			tagVector4 light = m_clrEnvironment;
			tagVector4 specular;

			int i;
			int nCount = m_vecLightList.size();
			for (i = 0; i < nCount; i++)
			{
				m_vecLightList[i]->Sample(&lightSample, pInnerVertex->vWorldPosition_Output);
				if (lightSample.m_EL.fX > 0.0f ||
					lightSample.m_EL.fY > 0.0f ||
					lightSample.m_EL.fZ > 0.0f)
				{
					tagVector3 vNormal = pInnerVertex->vWorldNormal_Output;
					Vector3Normalize(&vNormal);

					float NdotL = Vector3Dot(&vNormal, &(lightSample.m_L));
					if (NdotL > 0.0f)
					{
						light = light + lightSample.m_EL * NdotL;
					}

					tagVector3 v = m_pCamera->m_vEyePoint - pInnerVertex->vWorldPosition_Output;
					Vector3Normalize(&v);

					if (0)
					{
						tagVector3 h = v + lightSample.m_L;
						Vector3Normalize(&h);

						float NdotH = Vector3Dot(&vNormal, &h);

						if (NdotH > 0.0f)
						{
							float fShiness = 20.0f;
							specular = specular + lightSample.m_EL * powf(NdotH, fShiness);
						}
					}

					if (0)
					{
						tagVector3 r = vNormal * (2 * NdotL) - lightSample.m_L;

						float RDotV = Vector3Dot(&r, &v);

						if (RDotV > 0.0f)
						{
							float fShiness = 20.0f;
							specular = specular + lightSample.m_EL * powf(RDotV, fShiness * 0.25f);
						}
					}

					if (1)
					{
						tagVector3 r = vNormal * (2 * NdotL) - lightSample.m_L;

						float RDotV = Vector3Dot(&r, &v);

						if (RDotV > 0.0f)
						{
							float fShiness = 20.0f;

							fShiness *= 0.25f;

							float spec = RDotV / (fShiness - RDotV * fShiness + RDotV);

							specular = specular + lightSample.m_EL * spec;
						}
					}
				}
			}

			DO_CLAMP_MAX(light.fX, 1.0f);
			DO_CLAMP_MAX(light.fY, 1.0f);
			DO_CLAMP_MAX(light.fZ, 1.0f);

			stTextureColor.fX *= light.fX;
			stTextureColor.fY *= light.fY;
			stTextureColor.fZ *= light.fZ;

			stTextureColor.fX += specular.fX * fGrayScale;
			stTextureColor.fY += specular.fY * fGrayScale;
			stTextureColor.fZ += specular.fZ * fGrayScale;

			DO_CLAMP_MAX(stTextureColor.fX, 1.0f);
			DO_CLAMP_MAX(stTextureColor.fY, 1.0f);
			DO_CLAMP_MAX(stTextureColor.fZ, 1.0f);

			if (m_bAlphaBlend)
			{
				tagVector4 stDestinationColor;

				m_pFrameBuffer1->GetPixel(nX, nY, &stDestinationColor);

				float fAlpha = 0.5f;

				tagVector4 stResultColor = stTextureColor * fAlpha + stDestinationColor * (1.0f - fAlpha);

				m_pFrameBuffer1->SetPixel(nX, nY, &stResultColor);
			}
			else
			{
				m_pFrameBuffer1->SetPixel(nX, nY, &stTextureColor);
			}
		}

		m_pDepthBuffer->SetDepth(nX, nY, fDepthNew);
	}
}

void CGame::PostProcessShader(int nX, int nY, tagVector4 *pResultColor)
{
	tagVector4 stSourceColor;
	m_pFrameBuffer1->GetPixel(nX, nY, &stSourceColor);

	float fGray = stSourceColor.fX * 0.299f + 
				  stSourceColor.fY * 0.587f +
				  stSourceColor.fZ * 0.114f;

	pResultColor->fX = fGray;
	pResultColor->fY = fGray;
	pResultColor->fZ = fGray;
	pResultColor->fW = stSourceColor.fW;
}

float CGame::HDR_CalculateAverageLight()
{
	int nX;
	int nY;

	float fTotalLight = 0.0f;

	for (nY = 0; nY < m_nHeight; nY++)
	{
		for (nX = 0; nX < m_nWidth; nX++)
		{
			tagVector4 stSourceColor;
			m_pFrameBuffer1->GetPixel(nX, nY, &stSourceColor);

			float fGray = stSourceColor.fX * 0.299f +
				stSourceColor.fY * 0.587f +
				stSourceColor.fZ * 0.114f;

			fTotalLight += fGray;
		}
	}

	return fTotalLight / (m_nWidth * m_nHeight);
}