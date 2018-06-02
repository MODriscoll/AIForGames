#include "NavMesh\NavMeshHeuristics.h"

#include "Math\Vectors\Vector2.h"

namespace NavMesh
{
	float DistanceSquared(const Vector2& a_v1, const Vector2& a_v2)
	{
		// Return this distance squared of the displacement
		return (a_v2 - a_v1).Squared();
	}

	float EuclideanDistance(const Vector2& a_v1, const Vector2& a_v2, float a_Scale)
	{
		// Return this euclidean distance of the displacement
		return a_Scale * (a_v2 - a_v1).Magnitude();
	}
}