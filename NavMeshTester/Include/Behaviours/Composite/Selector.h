#pragma once

#ifndef Michaels_Behaviour_Selector
#define Michaels_Behaviour_Selector

#include "Behaviours\Interface\IComposite.h"

namespace Behaviour
{
	class Selector final : public IComposite
	{
	public:

		// Public constructor with default tag
		Selector();
		// Public constructor with optional tag
		Selector(const std::string& a_Tag);

		// Default destructor
		virtual ~Selector() = default;

		// Executes stored behaviours until a behaviour succeeds or is pending
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Creates clone of self by cloning all stored behaviours
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;
	};
}

#endif // Michaels_Behaviour_Selector