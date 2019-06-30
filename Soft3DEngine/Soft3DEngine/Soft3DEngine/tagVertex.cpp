
void InnerVertexLerpOutput(tagInnerVertex *pResult, tagInnerVertex *pInnerVertex1, tagInnerVertex *pInnerVertex2, float fLerp, bool bCorrectPerspective)
{
	pResult->vPosition_Output = LERP(pInnerVertex1->vPosition_Output, pInnerVertex2->vPosition_Output, fLerp);
	pResult->vWorldPosition_Output = LERP(pInnerVertex1->vWorldPosition_Output, pInnerVertex2->vWorldPosition_Output, fLerp);
	pResult->vWorldNormal_Output = LERP(pInnerVertex1->vWorldNormal_Output, pInnerVertex2->vWorldNormal_Output, fLerp);
	
	if(bCorrectPerspective == false)
	{
		pResult->fU_Output = LERP(pInnerVertex1->fU_Output, pInnerVertex2->fU_Output, fLerp);
		pResult->fV_Output = LERP(pInnerVertex1->fV_Output, pInnerVertex2->fV_Output, fLerp);
	}
	else
	{
		pResult->fInvZ = LERP(pInnerVertex1->fInvZ, pInnerVertex2->fInvZ, fLerp);
		pResult->fU_Times_InvZ = LERP(pInnerVertex1->fU_Times_InvZ, pInnerVertex2->fU_Times_InvZ, fLerp);
		pResult->fV_Times_InvZ = LERP(pInnerVertex1->fV_Times_InvZ, pInnerVertex2->fV_Times_InvZ, fLerp);
		
		float fZ = 1.0f / pResult->fInvZ;
		pResult->fU_Output = pResult->fU_Times_InvZ * fZ;
		pResult->fV_Output = pResult->fV_Times_InvZ * fZ;
	}
}

unsigned int Vector4ColorToDwordColor(const tagVector4 &vColor)
{
	unsigned int dwR = (unsigned int)(vColor.fX * 255);
	unsigned int dwG = (unsigned int)(vColor.fY * 255);
	unsigned int dwB = (unsigned int)(vColor.fZ * 255);
	unsigned int dwA = (unsigned int)(vColor.fW * 255);
	return dwR | (dwG << 8) | (dwB << 16) | (dwA << 24);
}