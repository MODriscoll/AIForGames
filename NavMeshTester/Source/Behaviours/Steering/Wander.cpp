#include "Behaviours\Steering\Wander.h"

#include "Objects\Agent.h"

namespace Behaviour
{
	Wander::Wander()
		: ISteer("Wander"), m_Distance(1.f), m_Jitter(1.f), m_Radius(1.f), m_Previous(0.f)
	{

	}


	Wander::Wander(const std::string& a_Tag)
		: ISteer(a_Tag), m_Distance(1.f), m_Jitter(1.f), m_Radius(1.f), m_Previous(0.f)
	{

	}

	eBehaviourResult Wander::Execute(Agent* a_Agent, float deltaTime)
	{
		// Calculate the wander force, apply it to the agent
		a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));

		// Return successfull result
		return eBehaviourResult::Success;
	}

	Vector2 Wander::Calculate(Agent* a_Agent)
	{
		// Get the agents heading
		Vector2 Cen = a_Agent->GetRigidBody().GetHeading();

		// Scale the heading by the distance 
		Cen *= m_Distance;

		// Set the displacement force using a pre-set direction
		Vector2 Dis(0.f, -1.f);

		// Scale the displacement by the radius
		Dis *= m_Radius;

		// Get the displacements magnitude
		float Mag = Dis.Magnitude();

		// Use the previous angle to set a new direction for the displacement
		// Scale it by it's previous magnitude afterwards
		Dis = Vector2::Direction(m_Previous) * Mag;

		// Influence the randomness by incrementing the previous value a bit
		m_Previous += (std::rand() % 1000) / 1000.f * m_Jitter - m_Jitter * 0.5f;

		// Calculate the final force by summing the center and displacement
		Cen += Dis;

		// Normalise the final force
		Cen.Normalise();

		// Scale the force by the maximum velocity
		Cen *= m_MaxVelocity;		

		// Return the force
		return Cen;
	}

	behaviour_ptr Wander::Clone(const std::string& a_Tag) const
	{
		// Create the new wander behaviour
		auto CL = std::make_shared<Wander>(a_Tag);

		// Clone base variables into the behaviour
		CloneInto(CL.get());

		// Set the clones variables to mimic 
		CL->Distance(m_Distance);
		CL->Jitter(m_Jitter);
		CL->Radius(m_Radius);

		// Return the clone
		return CL;
	}

	void Wander::Distance(float a_Distance)
	{
		// Set the distance of the random circle
		m_Distance = a_Distance;
	}

	void Wander::Jitter(float a_Jitter)
	{
		// Set the jitter amount
		m_Jitter = a_Jitter;
	}

	void Behaviour::Wander::Radius(float a_Radius)
	{
		// Set the radius of the random circle
		m_Radius = a_Radius;
	}

	float Wander::Distance() const
	{
		// Return the distance of the random circle
		return m_Distance;
	}

	float Wander::Jitter() const
	{
		// Return the jitter amount
		return m_Jitter;
	}

	float Wander::Radius() const
	{
		// Return the radius of the random circle
		return m_Radius;
	}
}