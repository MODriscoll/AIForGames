#pragma once

#ifndef Michaels_Behaviour_Flee
#define Michaels_Behaviour_Flee

#include "ISteer.h"

namespace Behaviour
{
	class Flee final : public ISteer
	{
	public:

		// Public constructor with default tag
		Flee();
		// Public constructor with optional tag
		Flee(const std::string& a_Tag);

		// Default destructor
		virtual ~Flee() = default;

		// Flees given agent away from the set target
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed to move the given agent away from the set target
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this flee behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;
	};
}

#endif // Michaels_Behaviour_Flee
