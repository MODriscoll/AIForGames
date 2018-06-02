#pragma once

#include "Math\Maths.h"
#include "Math\Vectors\Vector2.h"

#include <glm\glm.hpp>

// Temporary Rigidbody
// Will be improved
class RigidBody2D final
{
public:

	RigidBody2D() 
		: Mass(1.f), FakeFriction(1.f), MaxVelocity(float_limits::max()) { }
	~RigidBody2D() { }

	void AddForce(const Vector2& a_Force)
	{
		Acceleration += a_Force / Mass;
	}

	void AddImpulse(const Vector2& a_Impulse)
	{
		Velocity += a_Impulse;
	}

	Vector2 GetHeading() const 
	{ 
		return Velocity.GetNormalise(); 
	}

	void Simulate(float deltaTime)
	{
		// Apply fake friction
		AddForce(-Velocity * FakeFriction);

		// Calculate velocity
		Velocity += Acceleration * deltaTime;

		// Truncate the velocity
		Velocity.Truncate(MaxVelocity);

		// Reset acceleration
		Acceleration.Set(0.f, 0.f);
	}

	Vector2 Velocity;
	Vector2 Acceleration;

	float Mass;

	float FakeFriction;
	float MaxVelocity;
};