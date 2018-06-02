#pragma once

#ifndef Michaels_Behaviour_Wander
#define Michaels_Behaviour_Wander

#include "ISteer.h"

namespace Behaviour
{
	class Wander final : public ISteer
	{
	public:

		// Public constructor with default tag
		Wander();
		// Public constructor with optional tag
		Wander(const std::string& a_Tag);

		// Default destructor
		virtual ~Wander() = default;

		// Wanders the agent around using set variables
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed to help the agent wander around
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this wander behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;

	public:

		// Set the distance of the random circle
		void Distance(float a_Distance);

		// Set the jitter amount for randomisation
		void Jitter(float a_Jitter);

		// Set the radius of the random circle
		void Radius(float a_Radius);

		// Get the distance of the random circle
		float Distance() const;

		// Get the jitter amount for randomisation
		float Jitter() const;

		// Get the radius of the random circle
		float Radius() const;

	private:

		// Distance from the circle
		float m_Distance;

		// Jitter amount to help randomisation
		float m_Jitter;

		// Radius of the circle
		float m_Radius;

		// Previous target angle
		float m_Previous;
	};
}

#endif // Michaels_Behaviour_Wander