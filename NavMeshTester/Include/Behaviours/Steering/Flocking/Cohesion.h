#pragma once

#ifndef Michaels_Behaviour_Cohesion
#define Michaels_Behaviour_Cohesion

#include "IFlock.h"

namespace Behaviour
{
	class Cohesion final : public IFlock
	{
	public:

		// Public constructor with default tag
		Cohesion();
		// Public constructor with optional tag
		Cohesion(const std::string& a_Tag);

		// Default destructor
		virtual ~Cohesion() = default;

		// Guides given agent to the center of the flock
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed guide the given agent to the center of the flock
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this cohesion behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;
	};
}

#endif // Michaels_Behaviour_Cohesion