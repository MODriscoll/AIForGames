#pragma once

#ifndef Michaels_NavMesh_Heuristics
#define Michaels_NavMesh_Heuristics

// Forward declerations
class Vector2;

namespace NavMesh
{
	float DistanceSquared(const Vector2& a_v1, const Vector2& a_v2);
	float EuclideanDistance(const Vector2& a_v1, const Vector2& a_v2, float a_Scale = 1.f);
}

#endif // Michaels_NavMesh_Heuristics