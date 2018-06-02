#pragma once

#ifndef Michaels_Behaviour_Evade
#define Michaels_Behaviour_Evade

#include "ISteer.h"

namespace Behaviour
{
	class Evade final : public ISteer
	{
	public:

		// Public constructor with default tag
		Evade();
		// Public constructor with optional tag
		Evade(const std::string& a_Tag);

		// Default destructor
		virtual ~Evade() = default;

		// Evades given agent from the set target
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed to move the given agent away from the set target
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this evade behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;
	};
}

#endif // Michaels_Behaviour_Evade