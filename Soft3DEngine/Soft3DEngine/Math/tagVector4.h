
#pragma once

struct tagVector4
{
public:
	tagVector4()
		: fX(0.0f)
		, fY(0.0f)
		, fZ(0.0f)
		, fW(0.0f)
	{
	}
	tagVector4(float fX, float fY,float fZ, float fW)
	{
		this->fX = fX;
		this->fY = fY;
		this->fZ = fZ;
		this->fW = fW;
	}
	tagVector4(const tagVector3 &v)
	{
		this->fX = v.fX;
		this->fY = v.fY;
		this->fZ = v.fZ;
		this->fW = 1.0f;
	}
	void operator += ( const tagVector4& v )
	{
		fX += v.fX;
		fY += v.fY;
		fZ += v.fZ;
		fW += v.fW;
	}
	void operator -= ( const tagVector4& v )
	{
		fX -= v.fX;
		fY -= v.fY;
		fZ -= v.fZ;
		fW -= v.fW;
	}
	tagVector4 operator + ( const tagVector4& v ) const
	{
		return tagVector4(fX + v.fX, fY + v.fY, fZ + v.fZ, fW + v.fW);
	}
    tagVector4 operator - ( const tagVector4& v ) const
	{
		return tagVector4(fX - v.fX, fY - v.fY, fZ - v.fZ, fW - v.fW);
	}
	tagVector4 operator * ( float f ) const
	{
		return tagVector4(fX * f, fY * f, fZ * f, fW * f);
	}
	tagVector4 operator / ( float f ) const
	{
		return tagVector4(fX / f, fY / f, fZ / f, fW / f);
	}
	void Modulate(tagVector4 *v)
	{
		fX *= v->fX;
		fY *= v->fY;
		fZ *= v->fZ;
		fW *= v->fW;
	}
public:
	float fX;
	float fY;
	float fZ;
	float fW;
};

