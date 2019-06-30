#pragma once

struct tagVector3
{
public:
	inline tagVector3()
		: fX(0.0f)
		, fY(0.0f)
		, fZ(0.0f)
	{
	}
	inline tagVector3( float fX, float fY, float fZ )
	{
		this->fX = fX;
		this->fY = fY;
		this->fZ = fZ;
	}
	inline void operator += ( const tagVector3& v )
	{
		fX += v.fX;
		fY += v.fY;
		fZ += v.fZ;
	}
	inline void operator -= ( const tagVector3& v )
	{
		fX -= v.fX;
		fY -= v.fY;
		fZ -= v.fZ;
	}
	inline tagVector3 operator + ( const tagVector3& v ) const
	{
		return tagVector3(fX + v.fX, fY + v.fY, fZ + v.fZ);
	}
	inline tagVector3 operator - ( const tagVector3& v ) const
	{
		return tagVector3(fX - v.fX, fY - v.fY, fZ - v.fZ);
	}
	inline tagVector3 operator * ( float f ) const
	{
		return tagVector3(fX * f, fY * f, fZ * f);
	}
	inline tagVector3 operator / ( float f ) const
	{
		float fInv = 1.0f / f;
		return tagVector3(fX * fInv, fY * fInv, fZ * fInv);
	}
	inline tagVector3 operator - () const
	{	
		return tagVector3(-fX, -fY, -fZ);
	}
public:
	float fX;
	float fY;
	float fZ;
};

inline void Vector3Clear(tagVector3 *pVector)
{
	pVector->fX = 0.0f;
	pVector->fY = 0.0f;
	pVector->fZ = 0.0f;
}

inline void Vector3Lerp(tagVector3 *pVector, const tagVector3 *pVector1, const tagVector3 *pVector2, float fLerp)
{
	float fLerp1 = 1.0f - fLerp;

	pVector->fX = pVector1->fX * fLerp1 + pVector2->fX * fLerp;
	pVector->fY = pVector1->fY * fLerp1 + pVector2->fY * fLerp;
	pVector->fZ = pVector1->fZ * fLerp1 + pVector2->fZ * fLerp;
}

inline float Vector3LengthSq(const tagVector3 *pVector)
{
	return (pVector->fX * pVector->fX + pVector->fY * pVector->fY + pVector->fZ * pVector->fZ);
}

inline float Vector3Length(const tagVector3 *pVector)
{
	return Sqrt(pVector->fX * pVector->fX + pVector->fY * pVector->fY + pVector->fZ * pVector->fZ);
}

inline float invSqrt(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int*)&x; // get bits for floating value
	i = 0x5f3759df - (i >> 1); // gives initial guess
	x = *(float*)&i; // convert bits back to float
	x = x * (1.5f - xhalf * x * x); // Newton step
	return x;
}

inline void Vector3Normalize(tagVector3 *pVector)
{
	float fLengthSq = Vector3LengthSq(pVector);
	if (fLengthSq == 0.0f)
	{
		return;
	}
	float fLengthInv = invSqrt(fLengthSq);
	pVector->fX *= fLengthInv;
	pVector->fY *= fLengthInv;
	pVector->fZ *= fLengthInv;
}

inline void Vector3Normalize_Standard(tagVector3 *pVector)
{
	float fLength = Vector3Length(pVector);
	if (fLength == 0.0f)
	{
		return;
	}
	float fLengthInv = 1.0f / fLength;
	pVector->fX *= fLengthInv;
	pVector->fY *= fLengthInv;
	pVector->fZ *= fLengthInv;
}

inline float Vector3Dot(const tagVector3 *pVector1, const tagVector3 *pVector2)
{
	return pVector1->fX * pVector2->fX + pVector1->fY * pVector2->fY + pVector1->fZ * pVector2->fZ;
}

inline void Vector3CrossProduct(tagVector3 *pVector, const tagVector3 *pVector1, const tagVector3 *pVector2)
{
	pVector->fX = pVector1->fY * pVector2->fZ - pVector1->fZ * pVector2->fY;
	pVector->fY = pVector1->fZ * pVector2->fX - pVector1->fX * pVector2->fZ;
	pVector->fZ = pVector1->fX * pVector2->fY - pVector1->fY * pVector2->fX;
}

inline bool Vector3IsBetweenVectors(const tagVector3 *pVector, const tagVector3 *pVector1, const tagVector3 *pVector2)
{
	tagVector3 vTemp1 = *pVector2 - *pVector1;
	float fTemp1 = Vector3LengthSq(&vTemp1);

	tagVector3 vTemp2 = *pVector1 - *pVector;
	float fTemp2 = Vector3LengthSq(&vTemp2);

	tagVector3 vTemp3 = *pVector2 - *pVector;
	float fTemp3 = Vector3LengthSq(&vTemp3);

	return fTemp2 <= fTemp1 && fTemp3 <= fTemp1;
}

