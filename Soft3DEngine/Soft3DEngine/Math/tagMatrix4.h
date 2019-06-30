
#pragma once

struct tagVector4;
struct tagVector3;

struct tagMatrix4x3
{
public:
	union
	{
		struct 
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
			float _41, _42, _43;
		};
		float m[4][3];
	};
};

struct tagMatrix4x4
{
public:
	inline tagMatrix4x4()
	{
		_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
		_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
		_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
		_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
	}
	inline tagMatrix4x4(float _f11, float _f12, float _f13, float _f14,
		float _f21, float _f22, float _f23, float _f24,
		float _f31, float _f32, float _f33, float _f34,
		float _f41, float _f42, float _f43, float _f44)
	{
		_11 = _f11; _12 = _f12; _13 = _f13; _14 = _f14;
		_21 = _f21; _22 = _f22; _23 = _f23; _24 = _f24;
		_31 = _f31; _32 = _f32; _33 = _f33; _34 = _f34;
		_41 = _f41; _42 = _f42; _43 = _f43; _44 = _f44;
	}
	inline tagMatrix4x4 operator + ( const tagMatrix4x4& mat ) const
	{
		return tagMatrix4x4(_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
			_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
			_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
			_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
	}
	inline tagMatrix4x4 operator - ( const tagMatrix4x4& mat ) const
	{
		return tagMatrix4x4(_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
			_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
			_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
			_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
	}
	inline tagMatrix4x4 operator * ( float f ) const
	{
		return tagMatrix4x4(_11 * f, _12 * f, _13 * f, _14 * f,
			_21 * f, _22 * f, _23 * f, _24 * f,
			_31 * f, _32 * f, _33 * f, _34 * f,
			_41 * f, _42 * f, _43 * f, _44 * f);
	}
	inline tagMatrix4x4 operator / ( float f ) const
	{
		return tagMatrix4x4(_11 / f, _12 / f, _13 / f, _14 / f,
			_21 / f, _22 / f, _23 / f, _24 / f,
			_31 / f, _32 / f, _33 / f, _34 / f,
			_41 / f, _42 / f, _43 / f, _44 / f);
	}
	void Translate(float fX, float fY, float fZ);
	void TranslateX(float fX);
	void TranslateY(float fY);
	void TranslateZ(float fZ);
	void Scale(float fX, float fY, float fZ);
	void Scale(float fScaling);
	void RotateX(float fX);
	void RotateY(float fY);
	void RotateZ(float fZ);
	void MoveTo(float fX, float fY, float fZ);
	void LookTo(float fX, float fY, float fZ);
	void LookTo(float fX, float fY, float fZ, float fUpX, float fUpY, float fUpZ);
	tagVector3 GetPosition();
	float GetScalingX();
	float GetScalingY();
	float GetScalingZ();
public:
	union
	{
		struct 
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
		float m1[16];
	};
};

inline void Matrix4x3Lerp(tagMatrix4x3 *pMatrix, tagMatrix4x3 *pMatrix1, tagMatrix4x3 *pMatrix2, float fLerp)
{
	float fLerp1 = 1.0f - fLerp;

	pMatrix->_11 = pMatrix1->_11 * fLerp1 + pMatrix2->_11 * fLerp;
	pMatrix->_12 = pMatrix1->_12 * fLerp1 + pMatrix2->_12 * fLerp;
	pMatrix->_13 = pMatrix1->_13 * fLerp1 + pMatrix2->_13 * fLerp;

	pMatrix->_21 = pMatrix1->_21 * fLerp1 + pMatrix2->_21 * fLerp;
	pMatrix->_22 = pMatrix1->_22 * fLerp1 + pMatrix2->_22 * fLerp;
	pMatrix->_23 = pMatrix1->_23 * fLerp1 + pMatrix2->_23 * fLerp;

	pMatrix->_31 = pMatrix1->_31 * fLerp1 + pMatrix2->_31 * fLerp;
	pMatrix->_32 = pMatrix1->_32 * fLerp1 + pMatrix2->_32 * fLerp;
	pMatrix->_33 = pMatrix1->_33 * fLerp1 + pMatrix2->_33 * fLerp;

	pMatrix->_41 = pMatrix1->_41 * fLerp1 + pMatrix2->_41 * fLerp;
	pMatrix->_42 = pMatrix1->_42 * fLerp1 + pMatrix2->_42 * fLerp;
	pMatrix->_43 = pMatrix1->_43 * fLerp1 + pMatrix2->_43 * fLerp;
}

inline void Matrix4x4Lerp(tagMatrix4x4 *pMatrix, tagMatrix4x4 *pMatrix1, tagMatrix4x4 *pMatrix2, float fLerp)
{
	float fLerp1 = 1.0f - fLerp;

	pMatrix->_11 = pMatrix1->_11 * fLerp1 + pMatrix2->_11 * fLerp;
	pMatrix->_12 = pMatrix1->_12 * fLerp1 + pMatrix2->_12 * fLerp;
	pMatrix->_13 = pMatrix1->_13 * fLerp1 + pMatrix2->_13 * fLerp;
	pMatrix->_14 = pMatrix1->_14 * fLerp1 + pMatrix2->_14 * fLerp;

	pMatrix->_21 = pMatrix1->_21 * fLerp1 + pMatrix2->_21 * fLerp;
	pMatrix->_22 = pMatrix1->_22 * fLerp1 + pMatrix2->_22 * fLerp;
	pMatrix->_23 = pMatrix1->_23 * fLerp1 + pMatrix2->_23 * fLerp;
	pMatrix->_24 = pMatrix1->_24 * fLerp1 + pMatrix2->_24 * fLerp;

	pMatrix->_31 = pMatrix1->_31 * fLerp1 + pMatrix2->_31 * fLerp;
	pMatrix->_32 = pMatrix1->_32 * fLerp1 + pMatrix2->_32 * fLerp;
	pMatrix->_33 = pMatrix1->_33 * fLerp1 + pMatrix2->_33 * fLerp;
	pMatrix->_34 = pMatrix1->_34 * fLerp1 + pMatrix2->_34 * fLerp;

	pMatrix->_41 = pMatrix1->_41 * fLerp1 + pMatrix2->_41 * fLerp;
	pMatrix->_42 = pMatrix1->_42 * fLerp1 + pMatrix2->_42 * fLerp;
	pMatrix->_43 = pMatrix1->_43 * fLerp1 + pMatrix2->_43 * fLerp;
	pMatrix->_44 = pMatrix1->_44 * fLerp1 + pMatrix2->_44 * fLerp;
}

inline void Matrix4x4Identity(tagMatrix4x4 *pMatrix)
{
	pMatrix->_11 = 1.0f;
	pMatrix->_12 = 0.0f;
	pMatrix->_13 = 0.0f;
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = 0.0f;
	pMatrix->_22 = 1.0f;
	pMatrix->_23 = 0.0f;
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = 0.0f;
	pMatrix->_32 = 0.0f;
	pMatrix->_33 = 1.0f;
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = 0.0f;
	pMatrix->_42 = 0.0f;
	pMatrix->_43 = 0.0f;
	pMatrix->_44 = 1.0f;
}

inline bool Matrix4x4IsIdentity(tagMatrix4x4 *pMatrix)
{
	return	pMatrix->_11 == 1.0f &&
			pMatrix->_12 == 0.0f &&
			pMatrix->_13 == 0.0f &&
			pMatrix->_14 == 0.0f &&
			pMatrix->_21 == 0.0f &&
			pMatrix->_22 == 1.0f &&
			pMatrix->_23 == 0.0f &&
			pMatrix->_24 == 0.0f &&
			pMatrix->_31 == 0.0f &&
			pMatrix->_32 == 0.0f &&
			pMatrix->_33 == 1.0f &&
			pMatrix->_34 == 0.0f &&
			pMatrix->_41 == 0.0f &&
			pMatrix->_42 == 0.0f &&
			pMatrix->_43 == 0.0f &&
			pMatrix->_44 == 1.0f;
}

inline void Matrix4x4Translation(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ)
{
	pMatrix->_11 = 1.0f;
	pMatrix->_12 = 0.0f;
	pMatrix->_13 = 0.0f;
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = 0.0f;
	pMatrix->_22 = 1.0f;
	pMatrix->_23 = 0.0f;
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = 0.0f;
	pMatrix->_32 = 0.0f;
	pMatrix->_33 = 1.0f;
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = fX;
	pMatrix->_42 = fY;
	pMatrix->_43 = fZ;
	pMatrix->_44 = 1.0f;
}

inline void Matrix4x4Scaling(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ)
{
	pMatrix->_11 = fX;
	pMatrix->_12 = 0.0f;
	pMatrix->_13 = 0.0f;
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = 0.0f;
	pMatrix->_22 = fY;
	pMatrix->_23 = 0.0f;
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = 0.0f;
	pMatrix->_32 = 0.0f;
	pMatrix->_33 = fZ;
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = 0.0f;
	pMatrix->_42 = 0.0f;
	pMatrix->_43 = 0.0f;
	pMatrix->_44 = 1.0f;
}

inline void Matrix4x4Scaling_Additive(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ)
{
	pMatrix->_11 *= fX;
	pMatrix->_12 *= fX;
	pMatrix->_13 *= fX;
	pMatrix->_14 *= fX;

	pMatrix->_21 *= fY;
	pMatrix->_22 *= fY;
	pMatrix->_23 *= fY;
	pMatrix->_24 *= fY;

	pMatrix->_31 *= fZ;
	pMatrix->_32 *= fZ;
	pMatrix->_33 *= fZ;
	pMatrix->_34 *= fZ;
}

inline void Matrix4x4Translation_Additive(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ)
{
	pMatrix->_41 += pMatrix->_11 * fX + pMatrix->_21 * fY + pMatrix->_31 * fZ;
	pMatrix->_42 += pMatrix->_12 * fX + pMatrix->_22 * fY + pMatrix->_32 * fZ;
	pMatrix->_43 += pMatrix->_13 * fX + pMatrix->_23 * fY + pMatrix->_33 * fZ;
	pMatrix->_44 += pMatrix->_14 * fX + pMatrix->_24 * fY + pMatrix->_34 * fZ;
}

inline void Matrix4x4Translation_AdditiveX(tagMatrix4x4 *pMatrix, float fX)
{
	pMatrix->_41 += pMatrix->_11 * fX;
	pMatrix->_42 += pMatrix->_12 * fX;
	pMatrix->_43 += pMatrix->_13 * fX;
	pMatrix->_44 += pMatrix->_14 * fX;
}

inline void Matrix4x4Translation_AdditiveY(tagMatrix4x4 *pMatrix, float fY)
{
	pMatrix->_41 += pMatrix->_21 * fY;
	pMatrix->_42 += pMatrix->_22 * fY;
	pMatrix->_43 += pMatrix->_23 * fY;
	pMatrix->_44 += pMatrix->_24 * fY;
}

inline void Matrix4x4Translation_AdditiveZ(tagMatrix4x4 *pMatrix, float fZ)
{
	pMatrix->_41 += pMatrix->_31 * fZ;
	pMatrix->_42 += pMatrix->_32 * fZ;
	pMatrix->_43 += pMatrix->_33 * fZ;
	pMatrix->_44 += pMatrix->_34 * fZ;
}

inline float AdjustAngle(float fAngle)
{
	return fAngle;
	
	//while (fAngle > MATH_PI * 2.0f)
	//{
	//	fAngle -= MATH_PI * 2.0f;
	//}
	//if (ABS(fAngle - MATH_PI / 2.0f) <= 0.00001f)
	//{
	//	fAngle -= 0.00001f;			//这里不知道什么原因，如果不减的话，在fY = MATH_PI的时候，会出现物体消失的情况
	//}
	//return fAngle;
}

inline void Matrix4x4RotationX(tagMatrix4x4 *pMatrix, float fX)
{
	fX = AdjustAngle(fX);

	float fCosX = Cos(fX);
	float fSinX = Sin(fX);

	pMatrix->_11 = 1.0f;
	pMatrix->_12 = 0.0f;
	pMatrix->_13 = 0.0f;
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = 0.0f;
	pMatrix->_22 = fCosX;
	pMatrix->_23 = fSinX;
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = 0.0f;
	pMatrix->_32 = -fSinX;
	pMatrix->_33 = fCosX;
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = 0.0f;
	pMatrix->_42 = 0.0f;
	pMatrix->_43 = 0.0f;
	pMatrix->_44 = 1.0f;
}

inline void Matrix4x4RotationY(tagMatrix4x4 *pMatrix, float fY)
{
	fY = AdjustAngle(fY);

	float fCosY = Cos(fY);
	float fSinY = Sin(fY);

	pMatrix->_11 = fCosY;
	pMatrix->_12 = 0.0f;
	pMatrix->_13 = -fSinY;
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = 0.0f;
	pMatrix->_22 = 1.0f;
	pMatrix->_23 = 0.0f;
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = fSinY;
	pMatrix->_32 = 0.0f;
	pMatrix->_33 = fCosY;
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = 0.0f;
	pMatrix->_42 = 0.0f;
	pMatrix->_43 = 0.0f;
	pMatrix->_44 = 1.0f;
}

inline void Matrix4x4RotationZ(tagMatrix4x4 *pMatrix, float fZ)
{
	fZ = AdjustAngle(fZ);

	float fCosZ = Cos(fZ);
	float fSinZ = Sin(fZ);

	pMatrix->_11 = fCosZ;
	pMatrix->_12 = fSinZ;
	pMatrix->_13 = 0.0f;
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = -fSinZ;
	pMatrix->_22 = fCosZ;
	pMatrix->_23 = 0.0f;
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = 0.0f;
	pMatrix->_32 = 0.0f;
	pMatrix->_33 = 1.0f;
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = 0.0f;
	pMatrix->_42 = 0.0f;
	pMatrix->_43 = 0.0f;
	pMatrix->_44 = 1.0f;
}

inline void Matrix4x4RotationX_Additive(tagMatrix4x4 *pMatrix, float fX)
{
	fX = AdjustAngle(fX);

	float fCos = Cos(fX);
	float fSin = Sin(fX);

	float fTemp21 = pMatrix->_21 * fCos + pMatrix->_31 * fSin;
	float fTemp22 = pMatrix->_22 * fCos + pMatrix->_32 * fSin;
	float fTemp23 = pMatrix->_23 * fCos + pMatrix->_33 * fSin;
	float fTemp24 = pMatrix->_24 * fCos + pMatrix->_34 * fSin;

	float fTemp31 = pMatrix->_21 *-fSin + pMatrix->_31 * fCos;
	float fTemp32 = pMatrix->_22 *-fSin + pMatrix->_32 * fCos;
	float fTemp33 = pMatrix->_23 *-fSin + pMatrix->_33 * fCos;
	float fTemp34 = pMatrix->_24 *-fSin + pMatrix->_34 * fCos;

	pMatrix->_21 = fTemp21;
	pMatrix->_22 = fTemp22;
	pMatrix->_23 = fTemp23;
	pMatrix->_24 = fTemp24;
	pMatrix->_31 = fTemp31;
	pMatrix->_32 = fTemp32;
	pMatrix->_33 = fTemp33;
	pMatrix->_34 = fTemp34;
}

inline void Matrix4x4RotationY_Additive(tagMatrix4x4 *pMatrix, float fY)
{
	fY = AdjustAngle(fY);

	float fCos = Cos(fY);
	float fSin = Sin(fY);

	float fTemp11 = pMatrix->_11 * fCos - pMatrix->_31 * fSin;
	float fTemp12 = pMatrix->_12 * fCos - pMatrix->_32 * fSin;
	float fTemp13 = pMatrix->_13 * fCos - pMatrix->_33 * fSin;
	float fTemp14 = pMatrix->_14 * fCos - pMatrix->_34 * fSin;

	float fTemp31 = pMatrix->_11 * fSin + pMatrix->_31 * fCos;
	float fTemp32 = pMatrix->_12 * fSin + pMatrix->_32 * fCos;
	float fTemp33 = pMatrix->_13 * fSin + pMatrix->_33 * fCos;
	float fTemp34 = pMatrix->_14 * fSin + pMatrix->_34 * fCos;

	pMatrix->_11 = fTemp11;
	pMatrix->_12 = fTemp12;
	pMatrix->_13 = fTemp13;
	pMatrix->_14 = fTemp14;
	pMatrix->_31 = fTemp31;
	pMatrix->_32 = fTemp32;
	pMatrix->_33 = fTemp33;
	pMatrix->_34 = fTemp34;
}

inline void Matrix4x4RotationZ_Additive(tagMatrix4x4 *pMatrix, float fZ)
{
	fZ = AdjustAngle(fZ);

	float fCos = Cos(fZ);
	float fSin = Sin(fZ);

	float fTemp11 = pMatrix->_11 * fCos + pMatrix->_21 * fSin;
	float fTemp12 = pMatrix->_12 * fCos + pMatrix->_22 * fSin;
	float fTemp13 = pMatrix->_13 * fCos + pMatrix->_23 * fSin;
	float fTemp14 = pMatrix->_14 * fCos + pMatrix->_24 * fSin;

	float fTemp21 = pMatrix->_11 *-fSin + pMatrix->_21 * fCos;
	float fTemp22 = pMatrix->_12 *-fSin + pMatrix->_22 * fCos;
	float fTemp23 = pMatrix->_13 *-fSin + pMatrix->_23 * fCos;
	float fTemp24 = pMatrix->_14 *-fSin + pMatrix->_24 * fCos;

	pMatrix->_11 = fTemp11;
	pMatrix->_12 = fTemp12;
	pMatrix->_13 = fTemp13;
	pMatrix->_14 = fTemp14;
	pMatrix->_21 = fTemp21;
	pMatrix->_22 = fTemp22;
	pMatrix->_23 = fTemp23;
	pMatrix->_24 = fTemp24;
}

void Matrix4x4Multiply(tagMatrix4x4 *pMatrix, tagMatrix4x4 *pMatrix1, tagMatrix4x4 *pMatrix2);

void Matrix4x4RotationZYX(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ);

void Matrix4x4RotationXYZ(tagMatrix4x4 *pMatrix, float fX, float fY, float fZ);

void Matrix4x4FromTRS(tagMatrix4x4 *pMatrix, tagVector3 *pTranslation, tagVector3 *pRotation, tagVector3 *pScaling, tagMatrix4x4 *pOrientMatrix);

inline void Matrix4x4FromMatrix4x3(tagMatrix4x4 *pMatrix, tagMatrix4x3 *pMatrix4x3)
{
	pMatrix->_11 = pMatrix4x3->_11;
	pMatrix->_12 = pMatrix4x3->_12;
	pMatrix->_13 = pMatrix4x3->_13;
	pMatrix->_14 = 0.0f;

	pMatrix->_21 = pMatrix4x3->_21;
	pMatrix->_22 = pMatrix4x3->_22;
	pMatrix->_23 = pMatrix4x3->_23;
	pMatrix->_24 = 0.0f;

	pMatrix->_31 = pMatrix4x3->_31;
	pMatrix->_32 = pMatrix4x3->_32;
	pMatrix->_33 = pMatrix4x3->_33;
	pMatrix->_34 = 0.0f;

	pMatrix->_41 = pMatrix4x3->_41;
	pMatrix->_42 = pMatrix4x3->_42;
	pMatrix->_43 = pMatrix4x3->_43;
	pMatrix->_44 = 1.0f;
}

void Matrix4x4LookAtLH(tagMatrix4x4 *pMatrix,
	float fEyeX, float fEyeY, float fEyeZ,
	float fCenterX, float fCenterY, float fCenterZ,
	float fUpX, float fUpY, float fUpZ);

void Matrix4x4LookAtRH(tagMatrix4x4 *pMatrix,
	float fEyeX, float fEyeY, float fEyeZ,
	float fCenterX, float fCenterY, float fCenterZ,
	float fUpX, float fUpY, float fUpZ);

void Matrix4x4LookAtRH_Inverse(tagMatrix4x4 *pMatrix,
	float fEyeX, float fEyeY, float fEyeZ,
	float fCenterX, float fCenterY, float fCenterZ,
	float fUpX, float fUpY, float fUpZ);

void Matrix4x4PerspectiveLH_DX(tagMatrix4x4 *pMatrix, float fFovy, float fAspect, float fZNear, float fZFar);

void Matrix4x4PerspectiveLH_OGL(tagMatrix4x4 *pMatrix, float fFovy, float fAspect, float fZNear, float fZFar);

void Matrix4x4PerspectiveRH_DX(tagMatrix4x4 *pMatrix, float fFovy, float fAspect, float fZNear, float fZFar);

void Matrix4x4PerspectiveRH_OGL(tagMatrix4x4 *pMatrix, float fFovy, float fAspect, float fZNear, float fZFar);

void Matrix4x4OrthoRH_OGL(tagMatrix4x4 *pMatrix, float fWidth, float fHeight, float fZNear, float fZFar);

void Matrix4x4Inverse(tagMatrix4x4 *pmatOut, tagMatrix4x4 *pmatIn);

inline void Matrix4x4ColorMatrix_Scale(tagMatrix4x4 *pmatOut, float fRScale, float fGScale, float fBScale)
{
	Matrix4x4Identity(pmatOut);
	pmatOut->_11 = fRScale;
	pmatOut->_22 = fGScale;
	pmatOut->_33 = fBScale;
}

inline void Matrix4x4ColorMatrix_Gray(tagMatrix4x4 *pmatOut)
{
	Matrix4x4Identity(pmatOut);
	pmatOut->_11 = 0.3f;
	pmatOut->_12 = 0.3f;
	pmatOut->_13 = 0.3f;
	pmatOut->_21 = 0.59f;
	pmatOut->_22 = 0.59f;
	pmatOut->_23 = 0.59f;
	pmatOut->_31 = 0.11f;
	pmatOut->_32 = 0.11f;
	pmatOut->_33 = 0.11f;
}

inline void Matrix4x4ColorMatrix_Sepia(tagMatrix4x4 *pmatOut)
{
	Matrix4x4Identity(pmatOut);
	pmatOut->_11 = 0.299f;
	pmatOut->_12 = 0.299f;
	pmatOut->_13 = 0.299f;
	pmatOut->_21 = 0.587f;
	pmatOut->_22 = 0.587f;
	pmatOut->_23 = 0.587f;
	pmatOut->_31 = 0.184f;
	pmatOut->_32 = 0.184f;
	pmatOut->_33 = 0.184f;
	pmatOut->_41 = 80.0f / 255.0f;
	pmatOut->_42 = 43.0f / 255.0f;
	pmatOut->_43 = -23.0f / 255.0f;
}

inline void Matrix4x4ColorMatrix_Saturate(tagMatrix4x4 *pmatOut, float fSaturation)
{
	Matrix4x4Identity(pmatOut);
	float fRWeight = 0.3086f;
	float fGWeight = 0.6094f;
	float fBWeight = 0.0820f;
	float fInvertSaturation = 1.0f - fSaturation;
	pmatOut->_11 = fInvertSaturation * fRWeight + fSaturation;
	pmatOut->_12 = fInvertSaturation * fRWeight;
	pmatOut->_13 = fInvertSaturation * fRWeight;
	pmatOut->_21 = fInvertSaturation * fGWeight;
	pmatOut->_22 = fInvertSaturation * fGWeight + fSaturation;
	pmatOut->_23 = fInvertSaturation * fGWeight;
	pmatOut->_31 = fInvertSaturation * fBWeight;
	pmatOut->_32 = fInvertSaturation * fBWeight;
	pmatOut->_33 = fInvertSaturation * fBWeight + fSaturation;
}

void Matrix4x4TransformCoord3(tagVector3 *pVector, const tagVector3 *pVector1, const tagMatrix4x4 *pmatMatrix);

void Matrix4x4TransformNormal(tagVector3 *pVector, const tagVector3 *pVector1, const tagMatrix4x4 *pmatMatrix);

void Matrix4x4TransformCoord4(tagVector4 *pVector, const tagVector4 *pVector1, const tagMatrix4x4 *pmatMatrix);

void Matrix4x4ProjectVector4(tagVector4 *pOut, tagVector4 *pIn, int nViewportX, int nViewportY, int nViewportWidth, int nViewportHeight, int nScreenHeight, tagMatrix4x4 *pViewProjection);

void Matrix4x4UnprojectVector4(tagVector4 *pOut, tagVector4 *pIn, int nViewportX, int nViewportY, int nViewportWidth, int nViewportHeight, int nScreenHeight, tagMatrix4x4 *pViewProjectionInverse);
