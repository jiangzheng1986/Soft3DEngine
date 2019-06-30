
float DegreeToRadian(float fDegree)
{
	return fDegree / 180.0f * MATH_PI;
}

float RadianToDegree(float fRadian)
{
	return fRadian / MATH_PI * 180.0f;
}

float DirToAngle(float fX, float fY)
{
	return atan2(fY, fX);
}

bool IsNumberPowerOfTwo(int nNumber)
{
	int i;
	for (i = 0; i < 32; i++)
	{
		if ((0x00000001 << i) == nNumber)
		{
			return true;
		}
	}

	return false;
}

void Randomize()
{
	srand((unsigned int)time(NULL));
}

void Randomize(int nSeed)
{
	srand(nSeed);
}

int RandomInt(int nMin, int nMax)
{
	if ( nMin >= nMax )
	{
		return nMax;
	}

	return nMin + rand()%(nMax - nMin + 1);
}

float RandomFloat(float fMin, float fMax)
{
	if ( fMin >= fMax )
	{
		return fMax;
	}

	return fMin + rand() % 10001 / 10000.0f * (fMax - fMin);
}

int SmartRandomInt(int n1, int n2)
{
	if (n1 < n2)
	{
		return RandomInt(n1, n2);
	}
	else if (n1 > n2)
	{
		return RandomInt(n2, n1);
	}
	else
	{
		return n1;
	}
}

float SmartRandomFloat(float f1, float f2)
{
	if (f1 < f2)
	{
		return RandomFloat(f1, f2);
	}
	else if (f1 > f2)
	{
		return RandomFloat(f2, f1);
	}
	else
	{
		return f1;
	}
}

void SmartRandomVector(tagVector3 *pVector, tagVector3 *pVector1, tagVector3 *pVector2)
{
	pVector->fX = SmartRandomFloat(pVector1->fX, pVector2->fX);
	pVector->fY = SmartRandomFloat(pVector1->fY, pVector2->fY);
	pVector->fZ = SmartRandomFloat(pVector1->fZ, pVector2->fZ);
}

void SmartRandomUnitVector(tagVector3 *pVector)
{
	tagVector3 vVector1(-1.0f, -1.0f, -1.0f);
	tagVector3 vVector2(1.0f, 1.0f, 1.0f);
	tagVector3 vVector;

	while (true)
	{
		SmartRandomVector(&vVector, &vVector1, &vVector2);

		float fLengthSq = Vector3LengthSq(&vVector);

		if (fLengthSq <= 1.0f && fLengthSq > 0.0f)
		{
			break;
		}
	}

	Vector3Normalize(&vVector);

	*pVector = vVector;
}

float Sin(float fX)
{
	return (float)sinf(fX);
}

float Cos(float fX)
{
	return (float)cosf(fX);
}

float Sqrt(float fX)
{
	if (fX > 1.0f - MATH_EPSILON && fX < 1.0f + MATH_EPSILON)
	{
		return 1.0f;
	}
	else
	{
		return sqrtf(fX);
	}
}

float ACos(float fX)
{
	return acosf(fX);
}

float Pow(float fX, float fY)
{
	return powf(fX, fY);
}

float EaseIn(float fTime, float fRate)
{
	return powf(fTime, fRate);
}

float EaseOut(float fTime, float fRate)
{
	return powf(fTime, 1.0f / fRate);
}

float EaseInOut(float fTime, float fRate)
{
	fTime *= 2.0f;
	if (fTime < 1.0f)
	{
		return 0.5f * powf(fTime, fRate);
	}
	else
	{
		return (1.0f - 0.5f * powf(2.0f - fTime, fRate));
	}
}

bool HasScaling(float fScalingX, float fScalingY, float fScalingZ)
{
	if (ABS(fScalingX - 1.0f) > MATH_EPSILON)
	{
		return true;
	}

	if (ABS(fScalingY - 1.0f) > MATH_EPSILON)
	{
		return true;
	}

	if (ABS(fScalingZ - 1.0f) > MATH_EPSILON)
	{
		return true;
	}

	return false;
}