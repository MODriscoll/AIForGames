#include "Behaviours\Steering\Follow.h"

#include "Objects\Agent.h"

namespace Behaviour
{
	Follow::Follow(const std::string& a_Tag)
		: ISteer(a_Tag), m_Path(nullptr), m_Index(0), m_bBacktrack(false), m_Radius(100.f), m_Direction(1)
	{

	}

	eBehaviourResult Follow::Execute(Agent* a_Agent, float deltaTime)
	{
		// Is path empty?
		if (Empty())
		{
			// Return failed result
			return eBehaviourResult::Failure;
		}
		else
		{
			// Has the path been traversed?
			if (Finished())
			{
				// Return successfull result
				return eBehaviourResult::Success;
			}
			else
			{
				// Calculate the following force, apply it to the agent
				a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));

				// Return pending result
				return eBehaviourResult::Pending;
			}
		}

		// Reaching here should not be possible, return invalid result
		return eBehaviourResult::Invalid;
	}

	Vector2 Follow::Calculate(Agent* a_Agent)
	{
		// Set the desired velocity to zero
		Vector2 Des;

		// Is the path not empty?
		// If not, has the path not been traversed?
		if (!Empty() && !Finished())
		{
			// Get reference to agents position and velocity
			const Vector2& APos = a_Agent->GetTransform().Position;
			const Vector2& AVel = a_Agent->GetRigidBody().Velocity;

			// Get the current node to nagivate to
			const Vector2& Node = m_Path->at(m_Index);

			// Get the displacement between the node and position
			Vector2 Dis = Node - APos;

			// Is this agent within range?
			if (Dis.Magnitude() < m_Radius)
			{
				// Increment the index based on direction
				m_Index += m_Direction;

				// Was the path traversed? Is back tracking allowed?
				if ((m_Index < 0 || m_Index >= static_cast<int>(m_Path->size())) && m_bBacktrack)
				{
					// Negate the direction, increment once
					m_Index += (m_Direction = -m_Direction);
				}
			}

			// Normalise the displacement
			Dis.Normalise();

			// Scale the normalised displacement by the maximum velocity
			Des = Dis * m_MaxVelocity;

			// Subtract the current velocity from the desired velocity
			Des -= AVel;
		}

		// Return the desired velocity
		return Des;
	}

	void Follow::Set(pvector* a_Path)
	{
		// Set the path
		m_Path = a_Path;
	}

	void Follow::Index(size_t a_Index)
	{
		// Set the path index to navigate to
		m_Index = static_cast<int>(a_Index);
	}

	void Follow::Backtrack(bool a_bBacktrack)
	{
		// Set if backtracking is allowed
		m_bBacktrack = a_bBacktrack;
	}

	void Follow::Radius(float a_Radius)
	{
		// Set the in-range radius
		m_Radius = a_Radius;
	}

	std::vector<Vector2>* Follow::Get()
	{
		// Return the path
		return m_Path;
	}

	size_t Follow::Index() const
	{
		// Return the index to navigate to
		return static_cast<size_t>(m_Index);
	}

	bool Follow::Backtrack() const
	{
		// Return if backtracking is allowed
		return m_bBacktrack;
	}

	float Follow::Radius() const
	{
		// Return the in-range radius
		return m_Radius;
	}

	void Follow::Reset()
	{
		// Set index to first node
		m_Index = 0;

		// Set direction to go forward
		m_Direction = 1;
	}

	bool Follow::Empty() const
	{
		// Is there a path set?
		if (m_Path != nullptr)
		{
			// Return if the path is empty
			return m_Path->empty();
		}
		else
		{
			// Return there is no path
			return true;
		}
	}

	bool Follow::Finished() const
	{
		// Can't be finished if path is empty or backtracking is allowed
		if (Empty() || m_bBacktrack)
		{
			// Return path has not been traversed
			return false;
		}

		// Return if index is at the last node
		return m_Index == static_cast<int>(m_Path->size());
	}
}