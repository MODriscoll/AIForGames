#pragma once

#include "Behaviours\Interface\IBehaviour.h"

class SeekClosest : public Behaviour::IBehaviour
{
public:

	// Seek closest requires tag
	SeekClosest(const std::string& a_Tag);

	// Public destructor
	virtual ~SeekClosest() = default;

	// Moves this agent closer to the target
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;
};