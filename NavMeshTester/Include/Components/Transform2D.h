#pragma once

#include "Math\Maths.h"
#include "Math\Vectors\Vector2.h"

// Temporary transform
// Will be improved
class Transform2D final
{
public:

	Transform2D()
		: Rotation(0.f), Scale(1.f, 1.f) { }
	~Transform2D() { }

	Vector2 Position;
	float Rotation;
	Vector2 Scale;
};