#include "Behaviours\Steering\Trail.h"

#include "Objects\Agent.h"

namespace Behaviour
{
	Trail::Trail()
		: ISteer("Trail")
	{

	}

	Trail::Trail(const std::string& a_Tag)
		: ISteer(a_Tag)
	{

	}

	eBehaviourResult Trail::Execute(Agent* a_Agent, float deltaTime)
	{
		// Is there a target?
		if (m_Target != nullptr)
		{
			// Calculate the trail force, apply it to the agent
			a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));

			// Return successfull result
			return eBehaviourResult::Success;
		}

		// Return failed result
		return eBehaviourResult::Failure;
	}

	Vector2 Trail::Calculate(Agent* a_Agent)
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

		// Get reference to targets and agents velocity
		const Vector2& AVel = a_Agent->GetRigidBody().Velocity;
		const Vector2& TVel = a_Agent->GetRigidBody().Velocity;

		// Set the trail to the inverse of the targets velocity
		Vector2 Tra = -TVel;

		// Normalise the inverse
		Tra.Normalise();

		// Scale the trail by the trail distance
		Tra *= m_Distance;
		
		// Calculate the trail position
		Tra += TPos;
		
		// Get the desired velocity subtracting the positions
		Vector2 Des = Tra - APos;

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

	behaviour_ptr Trail ::Clone(const std::string& a_Tag) const
	{
		// Create the new trail behaviour
		auto CL = std::make_shared<Trail>(a_Tag);

		// Clone base variables into the behaviour
		CloneInto(CL.get());

		// Set the clones variables to mimic 
		CL->Distance(m_Distance);
		CL->Radius(m_Radius);

		// Return the clone
		return CL;
	}

	void Trail::Distance(float a_Distance)
	{
		// Set the trail distance
		m_Distance = a_Distance;
	}

	void Trail::Radius(float a_Radius)
	{
		// Set the radius of the slowing circle
		m_Radius = a_Radius;
	}

	float Trail::Distance() const
	{
		// Return the trail distance
		return m_Distance;
	}

	float Trail::Radius() const
	{
		// Return the radius of the slowing circle
		return m_Radius;
	}
}