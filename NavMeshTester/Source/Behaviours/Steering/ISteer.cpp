#include "Behaviours\Steering\ISteer.h"

namespace Behaviour
{ 
	ISteer::ISteer(const std::string& a_Tag, GameObject* a_Target, float a_MaxVelocity, float a_Weight)
		: IBehaviour(a_Tag), m_Target(a_Target), m_MaxVelocity(a_MaxVelocity), m_Weight(a_Weight)
	{

	}

	eBehaviourResult Behaviour::ISteer::Execute(Agent* a_Agent, float deltaTime)
	{
		// Return success by default
		return eBehaviourResult::Success;
	}

	void ISteer::Target(GameObject* a_Target)
	{
		// Set this forces target
		m_Target = a_Target;
	}

	void ISteer::MaxVelocity(float a_MaxVelocity)
	{
		// Set this forces maximum velocity
		m_MaxVelocity = a_MaxVelocity;
	}

	void ISteer::Weight(float a_Weight)
	{
		// Set this forces weight
		m_Weight = a_Weight;
	}

	GameObject const* ISteer::Target() const
	{
		// Return this forces target
		return m_Target;
	}

	float ISteer::MaxVelocity() const
	{
		// Return this forces maximum velocity
		return m_MaxVelocity;
	}

	float ISteer::Weight() const
	{
		// Return this forces weight
		return m_Weight;
	}

	void ISteer::CloneInto(ISteer* a_Behaviour) const
	{
		// Set the clones variables to mimic 
		a_Behaviour->Target(m_Target);
		a_Behaviour->MaxVelocity(m_MaxVelocity);
		a_Behaviour->Weight(m_Weight);
	}

}
