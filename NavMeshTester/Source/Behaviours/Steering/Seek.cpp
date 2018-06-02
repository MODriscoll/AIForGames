#include "Behaviours\Steering\Seek.h"

#include "Objects\Agent.h"

namespace Behaviour
{
	Seek::Seek()
		: ISteer("Seek")
	{

	}

	Seek::Seek(const std::string& a_Tag)
		: ISteer(a_Tag)
	{

	}

	eBehaviourResult Seek::Execute(Agent* a_Agent, float deltaTime)
	{
		// Is there a target?
		if (m_Target != nullptr)
		{
			// Calculate the seek force, apply it to the agent
			a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));
			
			// Return successfull result
			return eBehaviourResult::Success;
		}

		// Return failed result
		return eBehaviourResult::Failure;
	}
	
	Vector2 Seek::Calculate(Agent* a_Agent)
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

		// Normalise the velocity
		Des.Normalise();

		// Scale the normalised velocity by the maximum velocity
		Des *= m_MaxVelocity;

		// Subtract the current velocity from the desired velocity
		Des -= AVel;

		// Return the velocity
		return Des;
	}

	behaviour_ptr Seek::Clone(const std::string& a_Tag) const
	{
		// Create the new seek behaviour
		auto CL = std::make_shared<Seek>(a_Tag);

		// Clone base variables into the behaviour
		CloneInto(CL.get());

		// Return the clone
		return CL;
	}
}