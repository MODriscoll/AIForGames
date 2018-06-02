#include "Behaviours\Decorator\Successor.h"

namespace Behaviour
{
	Successor::Successor(const behaviour_ptr& a_Child)
		: IDecorator("Successor", a_Child)
	{

	}

	Successor::Successor(const behaviour_ptr& a_Child, const std::string& a_Tag)
		: IDecorator(a_Tag, a_Child)
	{

	}

	eBehaviourResult Successor::Execute(Agent* a_Agent, float deltaTime)
	{
		// Execute the child behaviour
		VALIDATERESULT(m_Child->Execute(a_Agent, deltaTime));

		// Return successfull result
		return eBehaviourResult::Success;
	}


	behaviour_ptr Successor::Clone(const std::string& a_Tag, const behaviour_ptr& a_Child) const
	{
		// Create the new successor behaviour with given tag and child
		auto Suc = std::make_shared<Successor>(a_Child, a_Tag);

		// Return the clone
		return Suc;
	}
}