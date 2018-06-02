#pragma once

#include "Behaviours\Interface\IBehaviour.h"

class FollowPath : public Behaviour::IBehaviour
{
public:

	// Follow path requires tag
	FollowPath(const std::string& a_Tag);

	// Public destructor
	virtual ~FollowPath() = default;

	// Moves agent along the set path
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime);

public:

	// In-Range radius for nodes
	void Radius(float a_Radius);

	// Get the in-range radius
	float Radius() const;

private:

	// Radius around nodes
	float m_Radius;
};