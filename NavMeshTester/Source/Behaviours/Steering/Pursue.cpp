#include "Behaviours\Steering\Pursue.h"

#include "Objects\Agent.h"

namespace Behaviour
{
	Pursue::Pursue()
		: ISteer("Pursue")
	{

	}

	Pursue::Pursue(const std::string& a_Tag)
		: ISteer(a_Tag)
	{

	}

	eBehaviourResult Pursue::Execute(Agent* a_Agent, float deltaTime)
	{
		// Is there a target?
		if (m_Target != nullptr)
		{
			// Calculate the pursue force, apply it to the agent
			a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));

			// Return successfull result
			return eBehaviourResult::Success;
		}

		// Return failed result
		return eBehaviourResult::Failure;
	}

	Vector2 Pursue::Calculate(Agent* a_Agent)
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
		const Vector2& TVel = m_Target->GetRigidBody().Velocity;

		// Get the distance by subtracting the positions
		Vector2 Dis = TPos - APos;

		// Get the prediction value 
		float Pre = Dis.Magnitude() / m_MaxVelocity;

		// Estimate the target position using targets heading scale by the prediction
		Vector2 Tar = TPos + (TVel * Pre);

		// Get the desired velocity subtracting the agent's position from the target
		Vector2 Des = Tar - APos;

		// Normalise the velocity
		Des.Normalise();

		// Scale the normalised velocity by the maximum velocity
		Des *= m_MaxVelocity;

		// Subtract the current velocity from the desired velocity
		Des -= AVel;

		// Return the velocity
		return Des;
	}

	behaviour_ptr Pursue::Clone(const std::string& a_Tag) const
	{
		// Create the new pursue behaviour
		auto CL = std::make_shared<Pursue>(a_Tag);

		// Clone base variables into the behaviour
		CloneInto(CL.get());

		// Return the clone
		return CL;
	}
}