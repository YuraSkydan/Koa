#include "VectorOperations.h"

Vector3f RandomInUnitSphere()
{
	Vector3f v;
	do
	{
		v = 2.0f * Vector3f(drand48(), drand48(), drand48()) - Vector3f(1.0f, 1.0f, 1.0f);
	} while (v.SquaredMagnitude() >= 1.0f);

	return v;
}