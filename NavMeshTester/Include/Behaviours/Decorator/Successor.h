#pragma once

#ifndef Michaels_Behaviour_Successor
#define Michaels_Behaviour_Successor

#include "Behaviours\Interface\IDecorator.h"

namespace Behaviour
{
	class Successor final : public IDecorator
	{
	public:

		// Public constructor requires child behaviour
		Successor(const behaviour_ptr& a_Child);
		// Public constructor with optional tag
		Successor(const behaviour_ptr& a_Child, const std::string& a_Tag);

		// Default destructor
		virtual ~Successor() = default;

		// Executes child behaviour and returns success
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

	private:

		// Private clone function must be derived from
		// Creates new successor using clone as child
		virtual behaviour_ptr Clone(const std::string& a_Tag, const behaviour_ptr& a_Child) const override;
	};
}

#endif