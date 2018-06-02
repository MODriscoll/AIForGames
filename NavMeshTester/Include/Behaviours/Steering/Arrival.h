#pragma once

#ifndef Michaels_Behaviour_Arrival
#define Michaels_Behaviour_Arrival

#include "ISteer.h"

namespace Behaviour
{
	class Arrival final : public ISteer
	{
	public:

		// Public constructor with default tag
		Arrival();
		// Public constructor with optional tag
		Arrival(const std::string& a_Tag);

		// Default destructor
		virtual ~Arrival() = default;

		// Guides given agent towards the set target
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed to guide the given agent towards the set target
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this arrival behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;

	public:

		// Set the radius of the slowing circle
		void Radius(float a_Radius);

		// Get the radius of the slowing circle
		float Radius() const;

	private:

		// Radius of the slowing circle
		float m_Radius;
	};
}

#endif // Michaels_Behaviour_Arrival