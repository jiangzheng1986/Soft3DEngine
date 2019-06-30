//---------------------------------------------------------------------------------------------------------
// Author: 蒋政(AndersJiang@boyaa.com)
//---------------------------------------------------------------------------------------------------------

#pragma once

#define MIN_(x, y) ((x) < (y) ? (x) : (y))

#define MAX_(x, y) ((x) > (y) ? (x) : (y))

#define ABS(x) ((x) > 0 ? (x) : -(x))

#define LERP(a, b, f) ( (a) * (1.0f - (f)) + (b) *(f) )

const float MATH_PI = 3.141592654f;

const float MATH_EPSILON = 0.00001f;

float DegreeToRadian(float fDegree);

float RadianToDegree(float fRadian);

float DirToAngle(float fX, float fY);

bool IsNumberPowerOfTwo(int nNumber);

void Randomize();

void Randomize(int nSeed);

int RandomInt(int nMin, int nMax);

float RandomFloat(float fMin, float fMax);

int SmartRandomInt(int n1, int n2);

float SmartRandomFloat(float f1, float f2);

struct tagVector3;

void SmartRandomVector(tagVector3 *pVector, tagVector3 *pVector1, tagVector3 *pVector2);

void SmartRandomUnitVector(tagVector3 *pVector);

float Sin(float fX);

float Cos(float fX);

float Sqrt(float fX);

float ACos(float fX);

float Pow(float fX, float fY);

float EaseIn(float fTime, float fRate);

float EaseOut(float fTime, float fRate);

float EaseInOut(float fTime, float fRate);

bool HasScaling(float fScalingX, float fScalingY, float fScalingZ);