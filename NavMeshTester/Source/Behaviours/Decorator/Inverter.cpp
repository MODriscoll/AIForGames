#include "Behaviours\Decorator\Inverter.h"

namespace Behaviour
{
	Inverter::Inverter(const behaviour_ptr& a_Child)
		: IDecorator("Inverter", a_Child)
	{

	}

	Inverter::Inverter(const behaviour_ptr& a_Child, const std::string& a_Tag)
		: IDecorator(a_Tag, a_Child)
	{

	}

	eBehaviourResult Inverter::Execute(Agent* a_Agent, float deltaTime)
	{
		// Execute the child behaviour, capture the result
		eBehaviourResult Result = m_Child->Execute(a_Agent, deltaTime);

		// Is the result pending?
		if (Result == eBehaviourResult::Pending)
		{
			// Return the result
			return Result;
		}
		else
		{
			// Validate result
			VALIDATERESULT(Result);

			// Is the result a success?
			if (Result == eBehaviourResult::Success)
			{
				// Return failed result
				return eBehaviourResult::Failure;
			}
			else
			{
				// Return successfull result
				return eBehaviourResult::Success;
			}
		}
	}


	behaviour_ptr Inverter::Clone(const std::string& a_Tag, const behaviour_ptr& a_Child) const
	{
		// Create the new inverter behaviour with given tag and child
		auto Inv = std::make_shared<Inverter>(a_Child, a_Tag);

		// Return the clone
		return Inv;
	}
}