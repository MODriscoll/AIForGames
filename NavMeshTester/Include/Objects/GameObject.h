#pragma once

#include "Components\RigidBody2D.h"
#include "Components\Transform2D.h"

#include <string>

namespace aie
{
	class Renderer2D;
}

// Improve later
class GameObject
{
public:

	GameObject()
		: Tag("Object"), bResetVelocity(false) { }
	GameObject(const std::string& a_Tag)
		: Tag(a_Tag), bResetVelocity(false) { }
	virtual ~GameObject() = default;

	virtual void Update(float deltaTime)
	{
		RigidBody.Simulate(deltaTime);

		Transform.Position += RigidBody.Velocity * deltaTime;

		if (bResetVelocity)
			RigidBody.Velocity.Set(0.f, 0.f);
	}

	virtual void Render(aie::Renderer2D* renderer)
	{

	}

	std::string& GetTag() { return Tag; }

	Transform2D& GetTransform() { return Transform; }
	RigidBody2D& GetRigidBody() { return RigidBody; }

public:

	bool bResetVelocity;

protected:

	std::string Tag;

	Transform2D Transform;	// Keep here always
	RigidBody2D RigidBody;	// Move to components when implemented

	// Add components here later
	// Add parent heirarchy here later

private:
};