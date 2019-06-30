
#pragma once

#pragma warning(disable: 4996)

#include <math.h>

#include <time.h>

#include <windows.h>

#include <Gdiplus.h>

#include <stdlib.h>

#include <vector>

#include "Math/_Math.h"

#include "Math/tagMatrix4.h"

#include "Math/tagVector3.h"

#include "Math/tagVector4.h"

#include "Soft3DEngine/tagVertex.h"

#include "Soft3DEngine/CCamera.h"

#include "Soft3DEngine/Lighting.h"

#include "Soft3DEngine/CTexture.h"

#include "Soft3DEngine/CDevice.h"

#include "Game/CGame.h"

#include "Soft3DEngine.h"

#define ASSERT_( x ) //if ( !(x) ) { int i = 0; i = i / i; }

#define DO_CLAMP(x, _min, _max) {if((x) < (_min)){(x) = (_min);} if((x) > (_max)){(x) = (_max);}}

#define DO_CLAMP_MAX(x, _max) {if((x) > (_max)){(x) = (_max);}}

#define ABS_(x) ((x) < 0 ? -(x) : (x))