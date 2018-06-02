#pragma once

#include "Behaviours\Interface\IDecorator.h"

// In future, when making actual timer have reset option
// Everytime limit is surpassed, timer is reset if option is on
// Otherwise the time is never reset

class Timer : public Behaviour::IDecorator
{
public:

	// Constructor requires tag and child behaviour
	Timer(const std::string& a_Tag, const Behaviour::behaviour_ptr& a_Child);

	// Public destructor
	virtual ~Timer() = default;

	// Executes child once time surpasses limit
	// Time is reset when limit is surpassed
	// Returns failure if child is not executed, otherwise, returns child's result
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

public:

	// Reset time back to zero
	void Reset();

	// Sets time to limit
	void Tick();

	// Set the limit of the timer
	void Limit(float a_Limit);

	// Get the current time of the timer
	float Time() const;

	// Get the limit of the timer
	float Limit() const;

private:

	// Current timer of the timer
	float m_Time;

	// The limit of the timer
	float m_Limit;

	// Inherited via IDecorator
	virtual Behaviour::behaviour_ptr Clone(const std::string& a_Tag, const Behaviour::behaviour_ptr& a_Child) const override;
};