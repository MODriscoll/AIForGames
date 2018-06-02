#pragma once

#ifndef Michaels_Behaviour_Sequence
#define Michaels_Behaviour_Sequence

#include "Behaviours\Interface\IComposite.h"

namespace Behaviour
{
	class Sequence final : public IComposite
	{
	public:

		// Public constructor with default tag
		Sequence();
		// Public constructor with optional tag
		Sequence(const std::string& a_Tag);

		// Default destructor
		virtual ~Sequence() = default;

		// Executes stored behaviours until a behaviour fails or is pending
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Creates clone of self by cloning all stored behaviours
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;
	};
}

#endif // Michaels_Behaviour_Sequence