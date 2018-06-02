#pragma once

#ifndef Michaels_Behaviour_Alignment
#define Michaels_Behaviour_Alignment

#include "IFlock.h"

namespace Behaviour
{
	class Alignment final : public IFlock
	{
	public:

		// Public constructor with default tag
		Alignment();
		// Public constructor with optional tag
		Alignment(const std::string& a_Tag);

		// Default destructor
		virtual ~Alignment() = default;

		// Aligns given agent together with flock
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed align the given agent with the flock
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this alignment behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;
	};
}

#endif // Michaels_Behaviour_Alignment
