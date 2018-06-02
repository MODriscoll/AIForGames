#include "Behaviours\Composite\Selector.h"

namespace Behaviour
{
	Selector::Selector()
		: IComposite("Selector")
	{

	}

	Selector::Selector(const std::string& a_Tag)
		: IComposite(a_Tag)
	{

	}

	eBehaviourResult Selector::Execute(Agent* a_Agent, float deltaTime)
	{
		// Declare staring iteration
		auto it = m_Pending != m_Behaviours.end() ? m_Pending : m_Behaviours.begin();

		// Set pending behaviour to end
		m_Pending = m_Behaviours.end();

		// Starting from iteration, cycle through behaviours
		for (; it != m_Pending; ++it)
		{
			// Update this behaviour, capture the result
			eBehaviourResult Result = (*it)->Execute(a_Agent, deltaTime);

			// Was the execution successfull?
			if (Result == eBehaviourResult::Success)
			{
				// Return the result
				return Result;
			}

			// Is the execution pending?
			if (Result == eBehaviourResult::Pending)
			{
				// Set pending to this behaviour
				m_Pending = it;

				// Return the result
				return Result;
			}

			// Validate result
			VALIDATERESULT(Result);
		}

		// Return failed result
		return eBehaviourResult::Failure;
	}

	behaviour_ptr Selector::Clone(const std::string& a_Tag) const
	{
		// Create the new selector behaviour with given tag
		auto Sel = std::make_shared<Selector>(a_Tag);

		// Cycle through all behaviours
		for (auto& b : m_Behaviours)
		{
			// Clone this behaviour
			behaviour_ptr CL = b->Clone();

			// Was the clone made?
			if (CL)
			{
				// Insert the clone into the new selector
				Sel->Insert(CL);
			}
		}

		// Return the clone
		return Sel;
	}
}