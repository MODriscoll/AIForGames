#pragma once

#ifndef Michaels_Behaviour_Inverter
#define Michaels_Behaviour_Inverter

#include "Behaviours\Interface\IDecorator.h"

namespace Behaviour
{
	class Inverter final : public IDecorator
	{
	public:

		// Public constructor requires child behaviour
		Inverter(const behaviour_ptr& a_Child);
		// Public constructor with optional tag
		Inverter(const behaviour_ptr& a_Child, const std::string& a_Tag);

		// Default destructor
		virtual ~Inverter() = default;

		// Executes child behaviour and returns inverted result ( unless result is pending )
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

	private:

		// Private clone function must be derived from
		// Creates new inverter using clone as child
		virtual behaviour_ptr Clone(const std::string& a_Tag, const behaviour_ptr& a_Child) const override;
	};
}

#endif // Michaels_Behaviour_Inverter