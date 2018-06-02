#include "Behaviours\Steering\Arrival.h"

#include "Objects\Agent.h"

namespace Behaviour
{
	Arrival::Arrival()
		: ISteer("Arrival"), m_Radius(100.f)
	{

	}

	Arrival::Arrival(const std::string& a_Tag)
		: ISteer(a_Tag), m_Radius(100.f)
	{

	}

	eBehaviourResult Arrival::Execute(Agent* a_Agent, float deltaTime)
	{
		// Is there a target?
		if (m_Target != nullptr)
		{
			// Calculate the arrival force, apply it to the agent
			a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));

			// Return successfull result
			return eBehaviourResult::Success;
		}

		// Return failed result
		return eBehaviourResult::Failure;
	}

	Vector2 Arrival::Calculate(Agent* a_Agent)
	{
		// Is there no target?
		if (m_Target == nullptr)
		{
			// Return no force
			return Vector2();
		}

		// Get reference to targets and agents position
		const Vector2& APos = a_Agent->GetTransform().Position;
		const Vector2& TPos = m_Target->GetTransform().Position;

		// Get reference to agents velocity
		const Vector2& AVel = a_Agent->GetRigidBody().Velocity;

		// Get the desired velocity subtracting the positions
		Vector2 Des = TPos - APos;

		// Get the distance from the target
		float Dis = Des.Magnitude();

		// Normalise the velocity
		Des.Normalise();

		// Is the agent within the slowing circle?
		if (Dis < m_Radius)
		{
			// Scale the normalised velocity by the maximum velocity and radius
			Des *= m_MaxVelocity * (Dis / m_Radius);
		}
		else
		{
			// Scale the normalised velocity by the maximum velocity
			Des *= m_MaxVelocity;
		}

		// Subtract the current velocity from the desired velocity
		Des -= AVel;

		// Return the velocity
		return Des;
	}

	behaviour_ptr Arrival::Clone(const std::string& a_Tag) const
	{
		// Create the new arrival behaviour
		auto CL = std::make_shared<Arrival>(a_Tag);

		// Clone base variables into the behaviour
		CloneInto(CL.get());

		// Set the clones variables to mimic 
		CL->Radius(m_Radius);

		// Return the clone
		return CL;
	}

	void Arrival::Radius(float a_Radius)
	{
		// Set the radius of the slowing circle
		m_Radius = a_Radius;
	}

	float Arrival::Radius() const
	{
		// Return the radius of the slowing circle
		return m_Radius;
	}
}