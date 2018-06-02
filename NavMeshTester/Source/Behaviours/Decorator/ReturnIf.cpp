#include "Behaviours\Decorator\ReturnIf.h"

namespace Behaviour
{
	ReturnIf::ReturnIf(const behaviour_ptr& a_Child, eBehaviourResult a_If, eBehaviourResult a_Return)
		: IDecorator("ReturnIf", a_Child), m_IfResult(a_If), m_ReturnResult(a_Return)
	{

	}

	ReturnIf::ReturnIf(const behaviour_ptr& a_Child, const std::string& a_Tag, eBehaviourResult a_If, eBehaviourResult a_Return)
		: IDecorator(a_Tag, a_Child), m_IfResult(a_If), m_ReturnResult(a_Return)
	{

	}

	eBehaviourResult ReturnIf::Execute(Agent* a_Agent, float deltaTime)
	{
		// Execute the child behaviour, capture the result
		eBehaviourResult Result = m_Child->Execute(a_Agent, deltaTime);

		// Does the result match the condition to check for?
		if (Result == m_IfResult)
		{
			// Return the set result
			return m_ReturnResult;
		}
		else
		{
			// Validate result
			VALIDATERESULT(Result);

			// Return the result
			return Result;
		}
	}

	void ReturnIf::IfCondition(eBehaviourResult a_If)
	{
		// Set the result to check for
		m_IfResult = a_If;
	}

	void ReturnIf::ReturnCondition(eBehaviourResult a_Return)
	{
		// Set the result to return
		m_ReturnResult = a_Return;
	}

	eBehaviourResult ReturnIf::IfCondition() const
	{
		// Return the result being checked for
		return m_IfResult;
	}

	eBehaviourResult ReturnIf::ReturnCondition() const
	{
		// Return the result being returned
		return m_ReturnResult;
	}

	behaviour_ptr ReturnIf::Clone(const std::string& a_Tag, const behaviour_ptr& a_Child) const
	{
		// Create the new returnif behaviour with same conditions and the given tag and child
		auto Ret = std::make_shared<ReturnIf>(a_Child, a_Tag, m_IfResult, m_ReturnResult);

		// Return the clone
		return Ret;
	}
}