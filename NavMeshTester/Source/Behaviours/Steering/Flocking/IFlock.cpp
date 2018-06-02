#include "Behaviours\Steering\Flocking\IFlock.h"

namespace Behaviour
{
	IFlock::IFlock(const std::string& a_Tag)
		: ISteer(a_Tag), m_Flock(nullptr), m_Distance(100.f)
	{

	}

	void IFlock::Set(avector* a_Flock)
	{
		// Set the flock
		m_Flock = a_Flock;
	}

	void IFlock::Distance(float a_Distance)
	{
		// Set this distance
		m_Distance = a_Distance;
	}

	std::vector<Agent*>* IFlock::Get()
	{
		// Return the flock
		return m_Flock;
	}

	void IFlock::Remove(Agent* a_Agent)
	{
		// Find this agent in the flock
		auto Get = std::find(m_Flock->cbegin(), m_Flock->cend(), a_Agent);

		// Was this agent found?
		if (Get != m_Flock->cend())
		{
			// Remove this agent
			m_Flock->erase(Get);
		}
	}

	float IFlock::Distance() const
	{
		// Return the distance
		return m_Distance;
	}

	bool IFlock::Empty() const
	{
		// Is there a flock?
		if (m_Flock != nullptr)
		{
			// Return if the flock is empty
			return m_Flock->empty();
		}

		// Return there is no flock
		return false;
	}
}