#pragma once

#include "Behaviours\Interface\IDecorator.h"

class Successor : public Behaviour::IDecorator
{
public:

	// Successor requires tag
	// Decorator requires child
	Successor(const std::string& a_Tag, const Behaviour::behaviour_ptr& a_Child);

	// Public destructor
	virtual ~Successor() = default;

	// Executes child and always return success
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

	// Inherited via IDecorator
	virtual Behaviour::behaviour_ptr Clone(const std::string& a_Tag, const Behaviour::behaviour_ptr& a_Child) const override;
};