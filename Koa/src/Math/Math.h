#pragma once
#include "../Core/Core.h"

#define srand48(x) srand((int)(x))
#define drand48() ((double)rand()/RAND_MAX)

float KOA ToRads(float degrees);
float KOA ToDegrees(float rads);