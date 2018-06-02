#include "Behaviours\Steering\Evade.h"

#include "Objects\Agent.h"

namespace Behaviour
{
	Evade::Evade()
		: ISteer("Evade")
	{

	}

	Evade::Evade(const std::string& a_Tag)
		: ISteer(a_Tag)
	{

	}

	eBehaviourResult Evade::Execute(Agent* a_Agent, float deltaTime)
	{
		// Is there a target?
		if (m_Target != nullptr)
		{
			// Calculate the evade force, apply it to the agent
			a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));

			// Return successfull result
			return eBehaviourResult::Success;
		}

		// Return failed result
		return eBehaviourResult::Failure;
	}

	Vector2 Evade::Calculate(Agent* a_Agent)
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

		// Get the desired velocity subtracting the target from the agent's position 
		Vector2 Des = APos - Tar;

		// Normalise the velocity
		Des.Normalise();

		// Scale the normalised velocity by the maximum velocity
		Des *= m_MaxVelocity;

		// Subtract the current velocity from the desired velocity
		Des -= AVel;

		// Return the velocity
		return Des;
	}

	behaviour_ptr Evade::Clone(const std::string& a_Tag) const
	{
		// Create the new evade behaviour
		auto CL = std::make_shared<Evade>(a_Tag);

		// Clone base variables into the behaviour
		CloneInto(CL.get());

		// Return the clone
		return CL;
	}
}