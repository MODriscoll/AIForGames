#pragma once

#ifndef Michaels_Behaviour_Pursue
#define Michaels_Behaviour_Pursue

#include "ISteer.h"

namespace Behaviour
{
	class Pursue final : public ISteer
	{
	public:

		// Public constructor with default tag
		Pursue();
		// Public constructor with optional tag
		Pursue(const std::string& a_Tag);

		// Default destructor
		virtual ~Pursue() = default;

		// Pursues given agent towards the set target
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed to move the given agent towards the set target
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this pursue behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;
	};
}

#endif // Michaels_Behaviour_Pursue