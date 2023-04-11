#pragma once
#include "../Core/Core.h"

#define srand48(x) srand((int)(x))
#define drand48() ((double)rand()/RAND_MAX)

float KOA_API ToRadians(float degrees);
float KOA_API ToDegrees(float rads);