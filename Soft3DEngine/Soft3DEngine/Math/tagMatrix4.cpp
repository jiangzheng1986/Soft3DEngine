

void tagMatrix4x4::Translate(float fX, float fY, float fZ)
{
	Matrix4x4Translation_Additive(this, fX, fY, fZ);
}

void tagMatrix4x4::TranslateX(float fX)
{
	Matrix4x4Translation_AdditiveX(this, fX);
}

void tagMatrix4x4::TranslateY(float fY)
{
	Matrix4x4Translation_AdditiveY(this, fY);
}

void tagMatrix4x4::TranslateZ(float fZ)
{
	Matrix4x4Translation_AdditiveZ(this, fZ);
}

void tagMatrix4x4::Scale(float fX, float fY, float fZ)
{
	Matrix4x4Scaling_Additive(this, fX, fY, fZ);
}

void tagMatrix4x4::Scale(float fScaling)
{
	Matrix4x4Scaling_Additive(this, fScaling, fScaling, fScaling);
}

void tagMatrix4x4::RotateX(float fX)
{
	Matrix4x4RotationX_Additive(this, fX);
}

void tagMatrix4x4::RotateY(float fY)
{
	Matrix4x4RotationY_Additive(this, fY);
}

void tagMatrix4x4::RotateZ(float fZ)
{
	Matrix4x4RotationZ_Additive(this, fZ);
}

void tagMatrix4x4::MoveTo(float fX, float fY, float fZ)
{
	_41 = fX;
	_42 = fY;
	_43 = fZ;
}

void tagMatrix4x4::LookTo(float fX, float fY, float fZ)
{
	Matrix4x4LookAtRH_Inverse(this, this->_41, this->_42, this->_43, fX, fY, fZ, 0.0, 1.0f, 0.0f);
}

void tagMatrix4x4::LookTo(float fX, float fY, float fZ, float fUpX, float fUpY, float fUpZ)
{
	Matrix4x4LookAtRH_Inverse(this, this->_41, this->_42, this->_43, fX, fY, fZ, fUpX, fUpY, fUpZ);
}

tagVector3 tagMatrix4x4::GetPosition()
{
	return tagVector3(_41, _42, _43);
}

float tagMatrix4x4::GetScalingX()
{
	return Sqrt(_11 * _11 + _12 * _12 + _13 * _13);
}

float tagMatrix4x4::GetScalingY()
{
	return Sqrt(_21 * _21 + _22 * _22 + _23 * _23);
}

float tagMatrix4x4::GetScalingZ()
{
	return Sqrt(_31 * _31 + _32 * _32 + _33 * _33);
}

void Matrix4x4Multiply(tagMatrix4x4 *pMatrix, tagMatrix4x4 *pMatrix1, tagMatrix4x4 *pMatrix2)
{
#if !NEON_OPT_ENABLE
	char szBuf[sizeof(tagMatrix4x4)];

	tagMatrix4x4 *m = (tagMatrix4x4 *)szBuf;
	tagMatrix4x4 *m1 = pMatrix1;
	tagMatrix4x4 *m2 = pMatrix2;

	m->_11 = m1->_11 * m2->_11 + m1->_12 * m2->_21 + m1->_13 * m2->_31 + m1->_14 * m2->_41;
	m->_12 = m1->_11 * m2->_12 + m1->_12 * m2->_22 + m1->_13 * m2->_32 + m1->_14 * m2->_42;
	m->_13 = m1->_11 * m2->_13 + m1->_12 * m2->_23 + m1->_13 * m2->_33 + m1->_14 * m2->_43;
	m->_14 = m1->_11 * m2->_14 + m1->_12 * m2->_24 + m1->_13 * m2->_34 + m1->_14 * m2->_44;

	m->_21 = m1->_21 * m2->_11 + m1->_22 * m2->_21 + m1->_23 * m2->_31 + m1->_24 * m2->_41;
	m->_22 = m1->_21 * m2->_12 + m1->_22 * m2->_22 + m1->_23 * m2->_32 + m1->_24 * m2->_42;
	m->_23 = m1->_21 * m2->_13 + m1->_22 * m2->_23 + m1->_23 * m2->_33 + m1->_24 * m2->_43;
	m->_24 = m1->_21 * m2->_14 + m1->_22 * m2->_24 + m1->_23 * m2->_34 + m1->_24 * m2->_44;

	m->_31 = m1->_31 * m2->_11 + m1->_32 * m2->_21 + m1->_33 * m2->_31 + m1->_34 * m2->_41;
	m->_32 = m1->_31 * m2->_12 + m1->_32 * m2->_22 + m1->_33 * m2->_32 + m1->_34 * m2->_42;
	m->_33 = m1->_31 * m2->_13 + m1->_32 * m2->_23 + m1->_33 * m2->_33 + m1->_34 * m2->_43;
	m->_34 = m1->_31 * m2->_14 + m1->_32 * m2->_24 + m1->_33 * m2->_34 + m1->_34 * m2->_44;

	m->_41 = m1->_41 * m2->_11 + m1->_42 * m2->_21 + m1->_43 * m2->_31 + m1->_44 * m2->_41;
	m->_42 = m1->_41 * m2->_12 + m1->_42 * m2->_22 + m1->_43 * m2->_32 + m1->_44 * m2->_42;
	m->_43 = m1->_41 * m2->_13 + m1->_42 * m2->_23 + m1->_43 * m2->_33 + m1->_44 * m2->_43;
	m->_44 = m1->_41 * m2->_14 + m1->_42 * m2->_24 + m1->_43 * m2->_34 + m1->_44 * m2->_44;

	*pMatrix = *m;
#else
	matmul4_neon_((float *)pMatrix1, (float *)pMatrix2, (float *)pMatrix);
#endif
}

void Matrix4x4TransformCoord3(tagVector3 *pVector, const tagVector3 *pVector1, const tagMatrix4x4 *pmatMatrix)
{
#if !NEON_OPT_ENABLE
	tagVector3 vVector2;
	vVector2.fX = pVector1->fX * pmatMatrix->_11 + pVector1->fY * pmatMatrix->_21 + pVector1->fZ * pmatMatrix->_31 + pmatMatrix->_41;
	vVector2.fY = pVector1->fX * pmatMatrix->_12 + pVector1->fY * pmatMatrix->_22 + pVector1->fZ * pmatMatrix->_32 + pmatMatrix->_42;
	vVector2.fZ = pVector1->fX * pmatMatrix->_13 + pVector1->fY * pmatMatrix->_23 + pVector1->fZ * pmatMatrix->_33 + pmatMatrix->_43;
	*pVector = vVector2;
#else
	tagVector4 vIn;
	vIn.fX = pVector1->fX;
	vIn.fX = pVector1->fY;
	vIn.fX = pVector1->fZ;
	tagVector3 vOut;
	matvec4_neon_((float *)pmatMatrix, (float *)&vIn, (float *)&vOut);
	pVector->fX = vOut.fX;
	pVector->fY = vOut.fY;
	pVector->fZ = vOut.fZ;
#endif
}

void Matrix4x4TransformNormal(tagVector3 *pVector, const tagVector3 *pVector1, const tagMatrix4x4 *pmatMatrix)
{
	tagVector3 vVector2;
	vVector2.fX = pVector1->fX * pmatMatrix->_11 + pVector1->fY * pmatMatrix->_21 + pVector1->fZ * pmatMatrix->_31;
	vVector2.fY = pVector1->fX * pmatMatrix->_12 + pVector1->fY * pmatMatrix->_22 + pVector1->fZ * pmatMatrix->_32;
	vVector2.fZ = pVector1->fX * pmatMatrix->_13 + pVector1->fY * pmatMatrix->_23 + pVector1->fZ * pmatMatrix->_33;
	*pVector = vVector2;
}

void Matrix4x4TransformCoord4(tagVector4 *pVector, const tagVector4 *pVector1, const tagMatrix4x4 *pmatMatrix)
{
#if !NEON_OPT_ENABLE
	tagVector4 vVector2;
	vVector2.fX = pVector1->fX * pmatMatrix->_11 + pVector1->fY * pmatMatrix->_21 + pVector1->fZ * pmatMatrix->_31 + pVector1->fW * pmatMatrix->_41;
	vVector2.fY = pVector1->fX * pmatMatrix->_12 + pVector1->fY * pmatMatrix->_22 + pVector1->fZ * pmatMatrix->_32 + pVector1->fW * pmatMatrix->_42;
	vVector2.fZ = pVector1->fX * pmatMatrix->_13 + pVector1->fY * pmatMatrix->_23 + pVector1->fZ * pmatMatrix->_33 + pVector1->fW * pmatMatrix->_43;
	vVector2.fW = pVector1->fX * pmatMatrix->_14 + pVector1->fY * pmatMatrix->_24 + pVector1->fZ * pmatMatrix->_34 + pVector1->fW * pmatMatrix->_44;
	*pVector = vVector2;
#else
	matvec4_neon_((float *)pmatMatrix, (float *)pVector1, (float *)pVector);
#endif
}

void Matrix4x4RotationZYX(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ)
{
	if ( fX == 0.0f && fY == 0.0f && fZ == 0.0f )
	{
		Matrix4x4Identity(pMatrix);
		return;
	}
	tagMatrix4x4 matTemp;
	Matrix4x4RotationZ(pMatrix, fZ);
	Matrix4x4RotationY(&matTemp, fY);
	Matrix4x4Multiply(pMatrix, pMatrix, &matTemp);
	Matrix4x4RotationX(&matTemp, fX);
	Matrix4x4Multiply(pMatrix, pMatrix, &matTemp);
}

void Matrix4x4RotationXYZ(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ)
{
	if ( fX == 0.0f && fY == 0.0f && fZ == 0.0f )
	{
		Matrix4x4Identity(pMatrix);
		return;
	}
	tagMatrix4x4 matTemp;
	Matrix4x4RotationX(pMatrix, fX);
	Matrix4x4RotationY(&matTemp, fY);
	Matrix4x4Multiply(pMatrix, pMatrix, &matTemp);
	Matrix4x4RotationZ(&matTemp, fZ);
	Matrix4x4Multiply(pMatrix, pMatrix, &matTemp);
}

void Matrix4x4AddScaling(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ)
{
	pMatrix->_11 *= fX;
	pMatrix->_12 *= fX;
	pMatrix->_13 *= fX;
	pMatrix->_21 *= fY;
	pMatrix->_22 *= fY;
	pMatrix->_23 *= fY;
	pMatrix->_31 *= fZ;
	pMatrix->_32 *= fZ;
	pMatrix->_33 *= fZ;
}

void Matrix4x4AddTranslation(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ)
{
	pMatrix->_41 = fX;
	pMatrix->_42 = fY;
	pMatrix->_43 = fZ;
}

void Matrix4x4FromTRS(tagMatrix4x4 *pMatrix, tagVector3 *pTranslation, tagVector3 *pRotation, tagVector3 *pScaling, tagMatrix4x4 *pOrientMatrix)
{
	Matrix4x4RotationZYX(pMatrix, pRotation->fX, pRotation->fY, pRotation->fZ);

	Matrix4x4AddScaling(pMatrix, pScaling->fX, pScaling->fY, pScaling->fZ);

	if ( pOrientMatrix )
	{
		Matrix4x4Multiply(pMatrix, pMatrix, pOrientMatrix);
	}

	Matrix4x4AddTranslation(pMatrix, pTranslation->fX, pTranslation->fY, pTranslation->fZ);
}

void Matrix4x4LookAtLH(tagMatrix4x4 *pMatrix,
	float fEyeX, float fEyeY, float fEyeZ,
	float fCenterX, float fCenterY, float fCenterZ,
	float fUpX, float fUpY, float fUpZ)
{
	tagVector3 vUp;
	vUp.fX = fUpX;
	vUp.fY = fUpY;
	vUp.fZ = fUpZ;

	tagVector3 vForward;
	vForward.fX = fEyeX - fCenterX;
	vForward.fY = fEyeY - fCenterY;
	vForward.fZ = fEyeZ - fCenterZ;
	Vector3Normalize(&vForward);

	tagVector3 vSide;
	Vector3CrossProduct(&vSide, &vForward, &vUp);
	Vector3Normalize(&vSide);

	Vector3CrossProduct(&vUp, &vSide, &vForward);
	Vector3Normalize(&vUp);

	Matrix4x4Identity(pMatrix);

	pMatrix->_11 = vSide.fX;
	pMatrix->_21 = vSide.fY;
	pMatrix->_31 = vSide.fZ;

	pMatrix->_12 = vUp.fX;
	pMatrix->_22 = vUp.fY;
	pMatrix->_32 = vUp.fZ;

	pMatrix->_13 = -vForward.fX;
	pMatrix->_23 = -vForward.fY;
	pMatrix->_33 = -vForward.fZ;

	tagMatrix4x4 matMatrix1;
	Matrix4x4Translation(&matMatrix1, -fEyeX, -fEyeY, -fEyeZ);

	Matrix4x4Multiply(pMatrix, &matMatrix1, pMatrix);
}

void Matrix4x4LookAtRH(tagMatrix4x4 *pMatrix,
	float fEyeX, float fEyeY, float fEyeZ,
	float fCenterX, float fCenterY, float fCenterZ,
	float fUpX, float fUpY, float fUpZ)
{
	tagVector3 vUp;
	vUp.fX = fUpX;
	vUp.fY = fUpY;
	vUp.fZ = fUpZ;

	tagVector3 vForward;
	vForward.fX = fCenterX - fEyeX;
	vForward.fY = fCenterY - fEyeY;
	vForward.fZ = fCenterZ - fEyeZ;
	Vector3Normalize(&vForward);

	tagVector3 vSide;
	Vector3CrossProduct(&vSide, &vForward, &vUp);
	Vector3Normalize(&vSide);

	Vector3CrossProduct(&vUp, &vSide, &vForward);
	Vector3Normalize(&vUp);

	Matrix4x4Identity(pMatrix);

	pMatrix->_11 = vSide.fX;
	pMatrix->_21 = vSide.fY;
	pMatrix->_31 = vSide.fZ;

	pMatrix->_12 = vUp.fX;
	pMatrix->_22 = vUp.fY;
	pMatrix->_32 = vUp.fZ;

	pMatrix->_13 = -vForward.fX;
	pMatrix->_23 = -vForward.fY;
	pMatrix->_33 = -vForward.fZ;

	tagMatrix4x4 matMatrix1;
	Matrix4x4Translation(&matMatrix1, -fEyeX, -fEyeY, -fEyeZ);

	Matrix4x4Multiply(pMatrix, &matMatrix1, pMatrix);
}

void Matrix4x4LookAtRH_Inverse(tagMatrix4x4 *pMatrix,
	float fEyeX, float fEyeY, float fEyeZ,
	float fCenterX, float fCenterY, float fCenterZ,
	float fUpX, float fUpY, float fUpZ)
{
	bool bOptimize = true;

	if (bOptimize == false)
	{
		Matrix4x4LookAtRH(pMatrix,
			fEyeX, fEyeY, fEyeZ,
			fCenterX, fCenterY, fCenterZ,
			fUpX, fUpY, fUpZ);

		Matrix4x4Inverse(pMatrix, pMatrix);
	}
	else
	{
		tagVector3 vUp;			//Y
		vUp.fX = fUpX;
		vUp.fY = fUpY;
		vUp.fZ = fUpZ;
		Vector3Normalize(&vUp);

		tagVector3 vForward;	//Z
		vForward.fX = fEyeX - fCenterX;
		vForward.fY = fEyeY - fCenterY;
		vForward.fZ = fEyeZ - fCenterZ;
		Vector3Normalize(&vForward);

		tagVector3 vSide;		//X
		Vector3CrossProduct(&vSide, &vUp, &vForward);
		Vector3Normalize(&vSide);

		Vector3CrossProduct(&vUp, &vForward, &vSide);
		Vector3Normalize(&vUp);

		Matrix4x4Identity(pMatrix);

		pMatrix->_11 = vSide.fX;
		pMatrix->_12 = vSide.fY;
		pMatrix->_13 = vSide.fZ;

		pMatrix->_21 = vUp.fX;
		pMatrix->_22 = vUp.fY;
		pMatrix->_23 = vUp.fZ;

		pMatrix->_31 = vForward.fX;
		pMatrix->_32 = vForward.fY;
		pMatrix->_33 = vForward.fZ;

		pMatrix->_41 = fEyeX;
		pMatrix->_42 = fEyeY;
		pMatrix->_43 = fEyeZ;
	}
}

void Matrix4x4PerspectiveLH_DX(tagMatrix4x4 *pMatrix, float fFovy, float fAspect, float fZNear, float fZFar)
{
	Matrix4x4Identity(pMatrix);

	float fYScale = 1.0f / tan(fFovy / 2.0f);
	float fXScale = fYScale / fAspect;

	pMatrix->m[0][0] = fXScale;
	pMatrix->m[1][1] = fYScale;
	pMatrix->m[2][2] = -fZFar / (fZNear - fZFar);
	pMatrix->m[2][3] = 1.0f;
	pMatrix->m[3][2] = fZFar * fZNear / (fZNear - fZFar);
	pMatrix->m[3][3] = 0.0f;
}

void Matrix4x4PerspectiveLH_OGL(tagMatrix4x4 *pMatrix, float fFovy, float fAspect, float fZNear, float fZFar)
{
	Matrix4x4Identity(pMatrix);

	float fYScale = 1.0f / tan(fFovy / 2.0f);
	float fXScale = fYScale / fAspect;

	pMatrix->m[0][0]  =  fXScale;
	pMatrix->m[1][1]  =  fYScale;
	pMatrix->m[2][2]  =  -(fZFar + fZNear) / (fZNear - fZFar);
	pMatrix->m[2][3]  =  1.0f;
	pMatrix->m[3][2]  =  2.0f * fZFar * fZNear / (fZNear - fZFar);
	pMatrix->m[3][3]  =  0.0f;
}

void Matrix4x4PerspectiveRH_DX(tagMatrix4x4 *pMatrix, float fFovy, float fAspect, float fZNear, float fZFar)
{
	Matrix4x4Identity(pMatrix);

	float fYScale = 1.0f / tan(fFovy / 2.0f);
	float fXScale = fYScale / fAspect;

	pMatrix->m[0][0] = fXScale;
	pMatrix->m[1][1] = fYScale;
	pMatrix->m[2][2] = fZFar / (fZNear - fZFar);
	pMatrix->m[2][3] = -1.0f;
	pMatrix->m[3][2] = fZFar * fZNear / (fZNear - fZFar);
	pMatrix->m[3][3] = 0.0f;
}

void Matrix4x4PerspectiveRH_OGL(tagMatrix4x4 *pMatrix, float fFovy, float fAspect, float fZNear, float fZFar)
{
	Matrix4x4Identity(pMatrix);

	float fYScale = 1.0f / tan(fFovy / 2.0f);
	float fXScale = fYScale / fAspect;

	pMatrix->m[0][0] = fXScale;
	pMatrix->m[1][1] = fYScale;
	pMatrix->m[2][2] = (fZFar + fZNear) / (fZNear - fZFar);
	pMatrix->m[2][3] = -1.0f;
	pMatrix->m[3][2] = 2.0f * fZFar * fZNear / (fZNear - fZFar);
	pMatrix->m[3][3] = 0.0f;
}

void Matrix4x4OrthoRH_OGL(tagMatrix4x4 *pMatrix, float fWidth, float fHeight, float fZNear, float fZFar)
{
	Matrix4x4Identity(pMatrix);

	pMatrix->m[0][0] = 2.0f / fWidth;
	pMatrix->m[1][1] = 2.0f / fHeight;
	pMatrix->m[2][2] = 2.0f / (fZNear - fZFar);
	pMatrix->m[3][2] = (fZFar + fZNear) / (fZNear - fZFar);
	pMatrix->m[3][3] = 1.0f;
}

inline float MINOR(tagMatrix4x4 &mat, const int r0, const int r1, const int r2, const int c0, const int c1, const int c2)
{
	return 
		mat.m[r0][c0] * (mat.m[r1][c1] * mat.m[r2][c2] - mat.m[r2][c1] * mat.m[r1][c2]) -
		mat.m[r0][c1] * (mat.m[r1][c0] * mat.m[r2][c2] - mat.m[r2][c0] * mat.m[r1][c2]) +
		mat.m[r0][c2] * (mat.m[r1][c0] * mat.m[r2][c1] - mat.m[r2][c0] * mat.m[r1][c1]);
}

tagMatrix4x4 Matrix4x4Adjoint(tagMatrix4x4 &m)
{
	tagMatrix4x4 ma
	( 
		 MINOR(m, 1, 2, 3, 1, 2, 3),
		-MINOR(m, 0, 2, 3, 1, 2, 3),
		 MINOR(m, 0, 1, 3, 1, 2, 3),
		-MINOR(m, 0, 1, 2, 1, 2, 3),

		-MINOR(m, 1, 2, 3, 0, 2, 3),
		 MINOR(m, 0, 2, 3, 0, 2, 3),
		-MINOR(m, 0, 1, 3, 0, 2, 3),
		 MINOR(m, 0, 1, 2, 0, 2, 3),

		 MINOR(m, 1, 2, 3, 0, 1, 3),
		-MINOR(m, 0, 2, 3, 0, 1, 3),
		 MINOR(m, 0, 1, 3, 0, 1, 3),
		-MINOR(m, 0, 1, 2, 0, 1, 3),

		-MINOR(m, 1, 2, 3, 0, 1, 2),
		 MINOR(m, 0, 2, 3, 0, 1, 2),
		-MINOR(m, 0, 1, 3, 0, 1, 2),
		 MINOR(m, 0, 1, 2, 0, 1, 2)
	);

	return ma;
}

float Matrix4x4Determinant(tagMatrix4x4 &m) 
{
	return 
		m._11 * MINOR(m, 1, 2, 3, 1, 2, 3) -
		m._12 * MINOR(m, 1, 2, 3, 0, 2, 3) +
		m._13 * MINOR(m, 1, 2, 3, 0, 1, 3) -
		m._14 * MINOR(m, 1, 2, 3, 0, 1, 2);
}

void Matrix4x4Inverse(tagMatrix4x4 *pmatOut, tagMatrix4x4 *pmatIn)
{
	tagMatrix4x4 m = Matrix4x4Adjoint(*pmatIn) * (1.0f / Matrix4x4Determinant(*pmatIn));
	*pmatOut = m;
}

void Matrix4x4ProjectVector4(tagVector4 *pOut, tagVector4 *pIn, int nViewportX, int nViewportY, int nViewportWidth, int nViewportHeight, int nScreenHeight, tagMatrix4x4 *pViewProjection)
{
	tagVector4 vProjected;
	Matrix4x4TransformCoord4(&vProjected, pIn, pViewProjection);
	vProjected = vProjected / vProjected.fW;

	pOut->fX = (vProjected.fX / 2 + 0.5f) * nViewportWidth;
	pOut->fY = (vProjected.fY / 2 + 0.5f) * nViewportHeight;
	pOut->fZ = vProjected.fZ;
	pOut->fW = vProjected.fW;

	pOut->fX += nViewportX;
	pOut->fY += nViewportY;

	pOut->fY = nScreenHeight - pOut->fY;
}

void Matrix4x4UnprojectVector4(tagVector4 *pOut, tagVector4 *pIn, int nViewportX, int nViewportY, int nViewportWidth, int nViewportHeight, int nScreenHeight, tagMatrix4x4 *pViewProjectionInverse)
{
	float fX = pIn->fX;
	float fY = pIn->fY;

	fY = nScreenHeight - fY;

	fX -= nViewportX;
	fY -= nViewportY;

	tagVector4 vIn = *pIn;
	vIn.fX = (fX / nViewportWidth - 0.5f) * 2;
	vIn.fY = (fY / nViewportHeight - 0.5f) * 2;
	vIn.fZ = pIn->fZ;
	vIn.fW = pIn->fW;

	tagVector4 vUnprojected;
	Matrix4x4TransformCoord4(&vUnprojected, &vIn, pViewProjectionInverse);
	vUnprojected = vUnprojected / vUnprojected.fW;

	*pOut = vUnprojected;
}