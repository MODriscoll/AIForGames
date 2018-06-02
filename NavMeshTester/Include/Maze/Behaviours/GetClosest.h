#pragma once

#include "Behaviours\Interface\IBehaviour.h"

class GetClosest : public Behaviour::IBehaviour
{
public:

	// Get closest requires a tag
	GetClosest(const std::string& a_Tag);

	// Public destructor
	virtual ~GetClosest() = default;

	// Finds the closest survivour to this agent
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;
};