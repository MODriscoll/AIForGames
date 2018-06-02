#pragma once

#include "Behaviours\Steering\ISteer.h"

#include "Math\Maths.h"

class Maze;

namespace aie
{
	class Renderer2D;
}

// Maybe move maze into a blackboard
// So each agent can create their own tree

// Simple avoiding class to help agents
// avoid walking into walls  ( grid cells
// that are set as being blockded )
class MazeAvoider final : public Behaviour::ISteer
{
private:

	// Angle difference for raycasting
	const float RayDifference = pif * 0.25f;
 
public:

	// Default constructor requires tag
	MazeAvoider(const std::string& a_Tag);

	// Default destructor
	virtual ~MazeAvoider() = default;

	// Guides the agent to steer away from blocked slots in the wall
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

	// Calculates the force needed to steer away from obstacles
	virtual Vector2 Calculate(Agent* a_Agent) override;

	void Render(aie::Renderer2D* renderer);

public:

	// Set the max range
	void SetMaxRange(float a_MaxRange);

	// Set the max avoid force
	void SetMaxAvoidForce(float a_MaxAvoidForce);

	// Get the max range
	float GetMaxRange() const;

	// Get the max avoid force
	float GetMaxAvoidForce() const;

private:

	// Determines force to add using two points
	Vector2 DetermineForce(Maze* a_Maze, const Vector2& a_CP1, const Vector2& a_CP2);

	// The max range to check for obstacles
	float m_MaxRange;

	// The max avoidance force
	float m_MaxAvoidForce;

	// testing variables
	Vector2 cps[6];

	Vector2 forces[3];

	size_t count;
};

