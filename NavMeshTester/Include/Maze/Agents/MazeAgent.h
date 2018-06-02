#pragma once

#include "Objects\Agent.h"

// Base class for maze based agents
// Needs to inherit from agent because
// behaviour trees take in agent pointers
class MazeAgent : public Agent
{
public:

	// Default constructor
	MazeAgent();

	// Default destructor
	virtual ~MazeAgent() = default;

	// Render draws a simple circle
	// The green arrows represents rotation
	// The red arrow represents velocity
	virtual void Render(aie::Renderer2D* renderer) override;

public:

	// To be called after updating
	// Clamps this agent between the boundaries
	void Clamp(const Vector2& a_LowerLeft, const Vector2& a_UpperRight);

	// Set the radius of the agent
	void SetRadius(float a_Radius);

	// Get the radius of the agent
	float GetRadius() const;

private:

	// The radius of this agent
	float m_Radius;
};