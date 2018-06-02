#pragma once

#ifndef Michaels_Behaviour_Trail
#define Michaels_Behaviour_Trail

#include "ISteer.h"

namespace Behaviour
{
	class Trail final : public ISteer
	{
	public:

		// Public constructor with default tag
		Trail();
		// Public constructor with optional tag
		Trail(const std::string& a_Tag);

		// Default destructor
		virtual ~Trail() = default;

		// Guides given agent to trail behind the set target
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

		// Calculates the force needed to guide the given agent to behind the set target
		virtual Vector2 Calculate(Agent* a_Agent) override;

		// Clone this trail behaviour with a new tag
		virtual behaviour_ptr Clone(const std::string& a_Tag) const;

	public:

		// Set the trail distance
		void Distance(float a_Distance);

		// Set the radius of the slowing circle
		void Radius(float a_Radius);

		// Get the trail distance
		float Distance() const;

		// Get the radius of the slowing circle
		float Radius() const;

	private:

		// Follow distance to stay behind
		float m_Distance;

		// Radius of the slowing circle
		float m_Radius;
	};
}

#endif // Michaels_Behaviour_Trail