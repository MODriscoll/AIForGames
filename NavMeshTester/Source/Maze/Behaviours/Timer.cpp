#include "Maze\Behaviours\Timer.h"

Timer::Timer(const std::string& a_Tag, const Behaviour::behaviour_ptr& a_Child)
	: IDecorator(a_Tag, a_Child), m_Time(0.f), m_Limit(0.f)
{
}

Behaviour::eBehaviourResult Timer::Execute(Agent* a_Agent, float deltaTime)
{
	// Increase the time
	m_Time += deltaTime;

	// Has the limit been surpassed?
	if (m_Time >= m_Limit)
	{
		// Reset the time
		Reset();

		// Execute the child and return the result
		return m_Child->Execute(a_Agent, deltaTime);
	}
	
	// Return failure
	return Behaviour::eBehaviourResult::Failure;
}

void Timer::Reset()
{
	// Set current time to zero
	m_Time = 0.f;
}

void Timer::Tick()
{
	// Set current time to limit
	m_Time = m_Limit;
}

void Timer::Limit(float a_Limit)
{
	// Set the limit
	m_Limit = a_Limit;
}

float Timer::Time() const
{
	// Return the time
	return m_Time;
}

float Timer::Limit() const
{
	// Return the limit
	return m_Limit;
}

Behaviour::behaviour_ptr Timer::Clone(const std::string & a_Tag, const Behaviour::behaviour_ptr & a_Child) const
{
	return nullptr;
}
