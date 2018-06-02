#pragma once

#include "Behaviours\Interface\IBehaviour.h"

class AtExit : public Behaviour::IBehaviour
{
public:

	// Exit condition requires tag
	AtExit(const std::string& a_Tag);

	// Default destructor
	virtual ~AtExit() = default;

	// Checks if the given agent is at the exit of the maze
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime);
};