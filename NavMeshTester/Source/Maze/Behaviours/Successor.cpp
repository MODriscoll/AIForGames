#include "Maze\Behaviours\Successor.h"

Successor::Successor(const std::string& a_Tag, const Behaviour::behaviour_ptr& a_Child)
	: IDecorator(a_Tag, a_Child)
{
}

Behaviour::eBehaviourResult Successor::Execute(Agent* a_Agent, float deltaTime)
{
	// Execute the child behaviour, capture the result
	Behaviour::eBehaviourResult Result = m_Child->Execute(a_Agent, deltaTime);

	// Return success if result is not pending
	return Result == Behaviour::eBehaviourResult::Pending ? Result : Behaviour::eBehaviourResult::Success;
}

Behaviour::behaviour_ptr Successor::Clone(const std::string & a_Tag, const Behaviour::behaviour_ptr & a_Child) const
{
	return nullptr;
}