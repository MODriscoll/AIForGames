#pragma once

#include "Behaviours\Interface\IBehaviour.h"

class FreshPath : public Behaviour::IBehaviour
{
public:

	// Constructor requires tag
	FreshPath(const std::string& a_Tag);

	// Public destructor
	virtual ~FreshPath() = default;

	// Calculates new path from agents position to closest position
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;
};