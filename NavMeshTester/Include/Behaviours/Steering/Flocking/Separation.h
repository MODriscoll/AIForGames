#pragma once

#ifndef Michaels_Behaviour_Separation
#define Michaels_Behaviour_Separation

#include "IFlock.h"

namespace Behaviour
{
	class Separation final : public IFlock
	{
	public:

		// Public constructor with default tag
		Separation();
		// Public constructor with optional tag
		Separation(const std::string& a_Tag);

		// Default destructor
		virtual ~Separation() = default;

		// Seperates given agent from the flock
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed seperate the given agent from the flock
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this cohesion behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag)const;
	};
}

#endif // Michaels_Behaviour_Separation