#include "Math.h"
#include <numbers>

const float DegreesInRad = std::numbers::pi / 180.0f;
const float RadsInDegrees = 180.0f / std::numbers::pi;

float KOA ToRads(float degrees)
{
    return degrees * DegreesInRad;
}

float ToDegrees(float rads)
{
    return rads * RadsInDegrees;
}