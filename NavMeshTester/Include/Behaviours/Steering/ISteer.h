#pragma once

#ifndef Michaels_Behaviour_Steering
#define Michaels_Behaviour_Steering

#include "Behaviours\Interface\IBehaviour.h"

#include "Math\Vectors\Vector2.h"

class GameObject;

namespace Behaviour
{
	class ISteer : public IBehaviour
	{
	public:

		// Public destructor
		virtual ~ISteer() = default;

		// Update function, can still be derived from but is not neccessary
		// Returns a successfull update by default
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime);

		// Calculate force function, executes derived calculation on given agent
		virtual Vector2 Calculate(Agent* a_Agent) = 0;

	public:

		// Set the target for this force
		void Target(GameObject* a_Target);

		// Set the max velocity of this force
		void MaxVelocity(float a_MaxVelocity);

		// Set the weight of this force
		void Weight(float a_Weight);

		// Get the target for this force
		GameObject const* Target() const;

		// Get the max velocity of this force
		float MaxVelocity() const;

		// Get the weight of this force
		float Weight() const;
	
	protected:

		friend class Steerer;

		// Default constructor for steering behaviours
		// Protected since behaviour must be inherited from
		ISteer(const std::string& a_Tag, GameObject* a_Target = nullptr, float a_MaxVelocity = 100.f, float a_Weight = 1.f);

		// Helper function for cloning, clones all variables into given behaviour
		void CloneInto(ISteer* a_Behaviour) const;

		// Target of this steering force
		GameObject* m_Target;

		// The maximum velocity of this steering force
		float m_MaxVelocity;

		// The weight of this steering force
		float m_Weight;
	};
}

#endif // Michaels_Behaviour_Steering