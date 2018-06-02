#include "Behaviours\Composite\Sequence.h"

namespace Behaviour
{
	Sequence::Sequence()
		: IComposite("Sequence")
	{

	}

	Sequence::Sequence(const std::string& a_Tag) 
		: IComposite(a_Tag) 
	{ 

	}

	eBehaviourResult Sequence::Execute(Agent * a_Agent, float deltaTime)
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

			// Was the execution a failure?
			if (Result == eBehaviourResult::Failure)
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

		// Return successfull result
		return eBehaviourResult::Success;
	}

	behaviour_ptr Sequence::Clone(const std::string& a_Tag) const
	{
		// Create the new sequence behaviour with given tag
		auto Seq = std::make_shared<Sequence>(a_Tag);

		// Cycle through all behaviours
		for (auto& b : m_Behaviours)
		{
			// Clone this behaviour
			behaviour_ptr CL = b->Clone();

			// Was the clone made?
			if (CL)
			{
				// Insert the clone into the new sequence
				Seq->Insert(CL);
			}
		}

		// Return the clone
		return Seq;
	}
}
