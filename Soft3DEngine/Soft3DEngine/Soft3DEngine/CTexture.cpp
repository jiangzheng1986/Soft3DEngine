
int GetShiftOfInteger(int nValue)
{
	if (nValue == 1)
	{
		return 0;
	}
	else if (nValue == 2)
	{
		return 1;
	}
	else if (nValue == 4)
	{
		return 2;
	}
	else if (nValue == 8)
	{
		return 3;
	}
	else if (nValue == 16)
	{
		return 4;
	}
	else if (nValue == 32)
	{
		return 5;
	}
	else if (nValue == 64)
	{
		return 6;
	}
	else if (nValue == 128)
	{
		return 7;
	}
	else if (nValue == 256)
	{
		return 8;
	}
	else if (nValue == 512)
	{
		return 9;
	}
	else if (nValue == 1024)
	{
		return 10;
	}
	else if (nValue == 2048)
	{
		return 11;
	}
	else if (nValue == 4096)
	{
		return 12;
	}
	else if (nValue == 8192)
	{
		return 13;
	}
	else
	{
		ASSERT_(false);
		return 0;
	}
}

CTexture::CTexture()
{
	m_nWidth = 0;
	m_nHeight = 0;
	m_nShiftY = 0;
	m_pColorData = NULL;
	m_pDepthData = NULL;
}

CTexture::~CTexture()
{
	ReleaseTexture();
}

void CTexture::CreateColorBuffer(int nWidth, int nHeight)
{
	ReleaseTexture();

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nShiftY = GetShiftOfInteger(nWidth);

	m_pColorData = new tagVector4[nWidth * nHeight];
}

void CTexture::CreateDepthBuffer(int nWidth, int nHeight)
{
	ReleaseTexture();

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nShiftY = GetShiftOfInteger(nWidth);

	m_pDepthData = new float[nWidth * nHeight];
}

void CTexture::LoadTexture(const char *pszFilename)
{
	ReleaseTexture();

	FILE *pFile = NULL;
	fopen_s(&pFile, pszFilename, "rb");

	int nWidth = 0;
	fread(&nWidth, sizeof(int), 1, pFile);

	int nHeight = 0;
	fread(&nHeight, sizeof(int), 1, pFile);

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nShiftY = GetShiftOfInteger(nWidth);

	int nBytesPerPixel = 0;
	fread(&nBytesPerPixel, sizeof(int), 1, pFile);

	ASSERT_(nBytesPerPixel == 3);

	unsigned char *pImageData = new unsigned char[nWidth * nHeight * nBytesPerPixel];
	m_pColorData = new tagVector4[nWidth * nHeight];

	fread(pImageData, sizeof(unsigned char), nWidth * nHeight * nBytesPerPixel, pFile);

	unsigned char *pImageData1 = pImageData;
	tagVector4 *pColorData1 = m_pColorData;

	float fInv = 1 / 255.0f;

	int i;
	int j;
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
			unsigned char byBlue = pImageData1[0];
			unsigned char byGreen = pImageData1[1];
			unsigned char byRed = pImageData1[2];

			pColorData1->fX = byRed * fInv;
			pColorData1->fY = byGreen * fInv;
			pColorData1->fZ = byBlue * fInv;
			pColorData1->fW = 1.0f;

			pImageData1 += nBytesPerPixel;
			pColorData1++;
		}
	}

	delete[] pImageData;

	fclose(pFile);
}

void CTexture::ClearColor(const tagVector4 &vColor)
{
	int nTotalPixels = m_nWidth * m_nHeight;

	int i;
	for (i = 0; i < nTotalPixels; i++)
	{
		m_pColorData[i] = vColor;
	}
}

void CTexture::ClearDepth(float fDepth)
{
	int nTotalPixels = m_nWidth * m_nHeight;

	int i;
	for (i = 0; i < nTotalPixels; i++)
	{
		m_pDepthData[i] = fDepth;
	}
}

void CTexture::ReleaseTexture()
{
	if (m_pColorData)
	{
		delete [] m_pColorData;
		m_pColorData = NULL;
	}

	if (m_pDepthData)
	{
		delete [] m_pDepthData;
		m_pDepthData = NULL;
	}
}

void CTexture::GetPixel(int nX, int nY, tagVector4 *pColor)
{
	//ASSERT_(nX >= 0 && nY >= 0 && nX < m_nWidth && nY < m_nHeight);

	*pColor = *(m_pColorData + (nY << m_nShiftY) + nX);
}

void CTexture::SetPixel(int nX, int nY, const tagVector4 *pColor)
{
	//ASSERT_(nX >= 0 && nY >= 0 && nX < m_nWidth && nY < m_nHeight);

	*(m_pColorData + (nY << m_nShiftY) + nX) = *pColor;
}

void CTexture::GetPixelByUV(float fU, float fV, tagVector4 *pColor)
{
	if (fU >= 1.0f || fU < 0.0f)
	{
		fU += 100.0f;
		fU = fU - (int)fU;
	}
	if (fV >= 1.0f || fV < 0.0f)
	{
		fV += 100.0f;
		fV = fV - (int)fV;
	}

	int nX = (int)((m_nWidth - 1) * fU);
	int nY = (int)((m_nHeight - 1) * fV);
	GetPixel(nX, nY, pColor);
}

void CTexture::CopyToColorBuffer(unsigned int *pColorBuffer)
{
	int nTotalPixels = m_nWidth * m_nHeight;

	int i;
	for (i = 0; i < nTotalPixels; i++)
	{
		pColorBuffer[i] = Vector4ColorToDwordColor(m_pColorData[i]);
	}
}

void CTexture::SetDepth(int nX, int nY, float fDepth)
{
	//ASSERT_(nX >= 0 && nY >= 0 && nX < m_nWidth && nY < m_nHeight);

	*(m_pDepthData + (nY << m_nShiftY) + nX) = fDepth;
}

float CTexture::GetDepth(int nX, int nY)
{
	//ASSERT_(nX >= 0 && nY >= 0 && nX < m_nWidth && nY < m_nHeight);

	return *(m_pDepthData + (nY << m_nShiftY) + nX);
}