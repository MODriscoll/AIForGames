#include "Behaviours\Steering\Flocking\Alignment.h"

#include "Objects\Agent.h"

namespace Behaviour
{
	Alignment::Alignment()
		: IFlock("Alignment")
	{

	}

	Alignment::Alignment(const std::string& a_Tag)
		: IFlock(a_Tag)
	{

	}

	eBehaviourResult Alignment::Execute(Agent* a_Agent, float deltaTime)
	{
		// Is the flock not empty?
		if (!Empty())
		{
			// Calculate the alignment force, apply it to the agent
			a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));

			// Return successfull result
			return eBehaviourResult::Success;
		}

		// Return failed result
		return eBehaviourResult::Failure;
	}

	Vector2 Alignment::Calculate(Agent* a_Agent)
	{
		// Set the initial velocity to zero
		Vector2 Vel(0.f, 0.f);

		// Is there no flock?
		if (Empty())
		{
			// Return the initial velocity
			return Vel;
		}

		// Set the initial in-range count to zero
		size_t InR = 0;

		// Get reference to agents position
		const Vector2& APos = a_Agent->GetTransform().Position;

		// Cycle through the flock
		for (auto& mem : *m_Flock)
		{
			// Is the given agent apart of this flock?
			if (mem == a_Agent)
			{
				// Restart the loop
				continue;
			}

			// Get reference to flock members position and velocity
			const Vector2& MPos = mem->GetTransform().Position;
			const Vector2& MVel = mem->GetRigidBody().Velocity;

			// Get this distance between the member and the agent
			Vector2 Dis = MPos - APos;

			// Is this member within range?
			if (Dis.Magnitude() < m_Distance)
			{
				// Add this members velocity
				Vel += MVel;

				// Increase the in-range count
				++InR;
			}
		}

		// Was at least one member in range?
		if (InR > 0)
		{
			// Scale the velocity down by the in-range count to get the average velocity
			Vel /= static_cast<float>(InR);

			// Normalise the velocity
			Vel.Normalise();

			// Scale the velocity by the maximum velocity
			Vel *= m_MaxVelocity;
		}

		Vel -= a_Agent->GetRigidBody().Velocity;

		// Return the velocity
		return Vel;
	}

	behaviour_ptr Alignment::Clone(const std::string& a_Tag) const
	{
		// Create the new alignment behaviour
		auto CL = std::make_shared<Alignment>(a_Tag);

		// Clone base variables into the behaviour
		CloneInto(CL.get());

		// Set the clones variables to mimic 
		CL->Distance(m_Distance);
		CL->Set(m_Flock);

		// Return the clone
		return CL;
	}
}