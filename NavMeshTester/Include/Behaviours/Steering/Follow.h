#pragma once

#ifndef Michaels_Behaviour_Follow
#define Michaels_Behaviour_Follow

#include "ISteer.h"

#include <vector>

namespace Behaviour
{
	class Follow final : public ISteer
	{
	public:

		using pvector = std::vector<Vector2>;

	public:

		// Public constructor requires tag
		Follow(const std::string& a_Tag);

		// Public destructor
		~Follow() = default;

		// Guides given agent along the set path, can still be derived from but is not neccessary
		virtual eBehaviourResult Execute(Agent* a_Agent, float deltaTime);

		// Calculates the force needed guide the given agent along the set path
		virtual Vector2 Calculate(Agent* a_Agent);
			
	public:

		// Set the path
		void Set(pvector* a_Path);

		// Set the index to navigate to
		void Index(size_t a_Index);

		// Set if backtracking is allowed
		void Backtrack(bool a_bBacktrack);

		// Set the in-range radius
		void Radius(float a_Radius);

		// Get the path
		pvector* Get();

		// Get the index to navigate to
		size_t Index() const;

		// Get if backtracking is allowed
		bool Backtrack() const;

		// Get the in-range radius
		float Radius() const;

		// Reset the navigation variables
		void Reset();

		// Get if the path is empty
		// Returns false if no path is set
		bool Empty() const;

		// Get if index is at end of path
		// Returns false if path is empty
		// Returns false if backtracking is allowed
		bool Finished() const;

	protected:

		// Pointer to the path of points
		pvector* m_Path;

		// The index of the path being changed
		int m_Index;

		// To determine if to backtrack when finished
		bool m_bBacktrack;

		// Radius for agents to be in-range
		float m_Radius;

		// The direction the agent is travelling in
		int m_Direction;
	};
}

#endif // Michaels_Behaviour_Follow