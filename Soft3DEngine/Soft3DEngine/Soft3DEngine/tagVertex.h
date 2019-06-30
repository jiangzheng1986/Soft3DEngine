
#pragma once

class tagVertex
{
public:
	tagVector3 vPosition;
	tagVector3 vNormal;
	float fU;
	float fV;
};

class tagInnerVertex
{
public:
	tagInnerVertex()
	{
		m_bProcessed = false;
	}
public:
	tagVector3 vPosition_Input;
	tagVector3 vNormal_Input;
	float fU_Input;
	float fV_Input;
public:
	bool m_bProcessed;
	tagVector3 vPosition_Output;
	tagVector3 vWorldPosition_Output;
	tagVector3 vWorldNormal_Output;
	float fU_Output;
	float fV_Output;
public:
	float fInvZ;
	float fU_Times_InvZ;
	float fV_Times_InvZ;
};

void InnerVertexLerpOutput(tagInnerVertex *pResult, tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, float fLerp, bool bCorrectPerspective);

unsigned int Vector4ColorToDwordColor(const tagVector4 &vColor);