#pragma once

#ifndef Michaels_Behaviour_ReturnIf
#define Michaels_Behaviour_ReturnIf

#include "Behaviours\Interface\IDecorator.h"

namespace Behaviour
{
	class ReturnIf final : public IDecorator
	{
	public:

		// Public constructor requires child behaviour, result for if condition and return result
		ReturnIf(const behaviour_ptr& a_Child, eBehaviourResult a_If, eBehaviourResult a_Return);
		// Public constructor with optional tag
		ReturnIf(const behaviour_ptr& a_Child, const std::string& a_Tag, eBehaviourResult a_If, eBehaviourResult a_Return);

		// Default destructor
		virtual ~ReturnIf() = default;

		// Executes child behaviour and captures result
		// If childs result matches if condition, the return result is returned
		// If childs result doesn't match if condition, the childs result is returned
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

	public:

		// Set the if condition to check for
		void IfCondition(eBehaviourResult a_If);

		// Set the result to return
		void ReturnCondition(eBehaviourResult a_Return);

		// Get the if condition being checked for
		eBehaviourResult IfCondition() const;

		// Get the result to return
		eBehaviourResult ReturnCondition() const;

	private:

		// Private clone function must be derived from
		// Creates new inverter using clone as child
		virtual behaviour_ptr Clone(const std::string& a_Tag, const behaviour_ptr& a_Child) const override;

		// Result being check for
		eBehaviourResult m_IfResult;

		// Result to return
		eBehaviourResult m_ReturnResult;
	};
}


#endif // Michaels_Behaviour_ReturnIf