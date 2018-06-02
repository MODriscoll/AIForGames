#pragma once

#include "Behaviours\Interface\IBehaviour.h"

class InShortRange : public Behaviour::IBehaviour
{
public:

	// In short range requires tag
	InShortRange(const std::string& a_Tag);

	// Public destructor
	virtual ~InShortRange() = default;

	// Checks if closest survivour is in the short range
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;
};