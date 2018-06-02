#pragma once

#ifndef Michaels_Behaviour_Flock
#define Michaels_Behaviour_Flock

#include "Behaviours\Steering\ISteer.h"

#include <vector>

namespace Behaviour
{
	class IFlock : public ISteer
	{
	public:

		using avector = std::vector<Agent*>;

	public:

		// Public destructor
		virtual ~IFlock() = default;

	public:

		// Set the flock
		void Set(avector* a_Flock);

		// Set the flock distance
		void Distance(float a_Distance);

		// Get the flock
		avector* Get();

		// Remove a flock member
		void Remove(Agent* a_Agent);

		// Get the flock distance
		float Distance() const;

	protected:

		// Default constructor for flock behaviours
		// Protected since behaviour must be inherited from
		IFlock(const std::string& a_Tag);

		// Helper function for derived classes
		// Returns true if flock is empty or nullptr
		bool Empty() const;

		// Pointer to a flock of agents
		avector* m_Flock;

		// Distance for agents to flock
		float m_Distance;
	};
}

#endif // Michaels_Behaviour_Group