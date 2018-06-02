#include "Behaviours\Steering\Steerer.h"

#include "Objects\Agent.h"

namespace Behaviour
{
	Steerer::Steerer()
		: IBehaviour("Steerer"), m_MaxForce(float_limits::max()) 
	{

	}

	Steerer::Steerer(const std::string& a_Tag)
		: IBehaviour(a_Tag), m_MaxForce(float_limits::max())
	{

	}

	Steerer::~Steerer()
	{

	}

	eBehaviourResult Steerer::Execute(Agent* a_Agent, float deltaTime)
	{
		// Set the initial steering force to zero
		Vector2 Force(0.f, 0.f);

		// Set the initial force magnitude to zero
		float Mag = 0.f;

		// Cycle through all steering behaviours
		for (auto& steer : m_Behaviours)
		{
			// Calculate the force of this steering behaviour
			// Add the force scaled by the weight
			// to the current calculated force
			Force += (steer->Calculate(a_Agent) * steer->Weight());

			// Get the magnitude of the current force
			Mag = Force.Magnitude();

			// Has the force exceeded the max force?
			if (Mag > m_MaxForce)
			{
				// Truncate the current force
				Force.Truncate(m_MaxForce);

				// Break from the loop
				break;
			}
		}

		// Apply this force to the game object
		a_Agent->GetRigidBody().AddForce(Force);

		// Return successfull result
		return eBehaviourResult::Success;
	}

	behaviour_ptr Steerer::Clone(const std::string& a_Tag) const
	{
		// Create the new steerer behaviour with given tag
		auto Ste = std::make_shared<Steerer>(a_Tag);

		// Set the max force of the clone
		Ste->MaxForce(m_MaxForce);

		// Cycle through all steering behaviours
		for (auto& b : m_Behaviours)
		{
			// Clone this behaviour, cast it to a steering behaviour
			steer_ptr CL = std::static_pointer_cast<ISteer>(b->Clone());

			// Was the clone made?
			if (CL)
			{
				// Insert the clone into the new steerer
				Ste->Insert(CL);
			}
		}

		// Return the clone
		return Ste;
	}

	void Steerer::Insert(const steer_ptr& a_Behaviour)
	{
		// Insert this behaviour
		m_Behaviours.push_back(a_Behaviour);
	}

	size_t Steerer::Count() const
	{
		// Return the size of the container
		return m_Behaviours.size();
	}

	void Steerer::MaxForce(float a_MaxForce)
	{
		// Set the max force
		m_MaxForce = a_MaxForce;
	}

	float Steerer::MaxForce() const
	{
		// Return the max force
		return m_MaxForce;
	}

	ISteer* const Steerer::Get(const std::string& a_Tag)
	{
		// Cycle through all steering behaviours
		for (auto& b : m_Behaviours)
		{
			// Is this the requested steering behaviour
			if (b->Tag() == a_Tag)
			{
				// Return this behaviour
				return b.get();
			}
		}

		// If behaviour wasn't found, return nullptr
		return nullptr;
	}

	behaviour_ptr Steerer::Find(const std::string& a_Tag)
	{
		// Cycle through all steering behaviours
		for (auto& b : m_Behaviours)
		{
			// Is this the requested steering behaviour
			if (b->Tag() == a_Tag)
			{
				// Return this behaviour
				return b;
			}
		}

		// If behaviour wasn't found, return nullptr
		return nullptr;
	}
}
