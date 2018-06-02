#include "Maze\Behaviours\FollowPath.h"

#include "Maze\Agents\MazeAgent.h"

#include "Maze\MazeGame.h"

FollowPath::FollowPath(const std::string& a_Tag)
	: IBehaviour(a_Tag), m_Radius(0.f)
{

}

Behaviour::eBehaviourResult FollowPath::Execute(Agent* a_Agent, float deltaTime)
{
	// Get the board from the agent
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Get the path from the board ( as a reference )
	Maze::path& Path = *(static_cast<Maze::path*>(Board->GetAs_Pointer("Path")));

	// Get the current index from the board
	size_t Index = Board->GetAs_UInt("PathIdx");

	// Get the speed from the board
	float MaxVelocity = Board->GetAs_Float("Speed");

	// Set the desired velocity to zero
	Vector2 Des;

	// Has index not reached end
	if (Index < Path.size())
	{
		// Get reference to agents position and velocity
		const Vector2& APos = a_Agent->GetTransform().Position;
		const Vector2& AVel = a_Agent->GetRigidBody().Velocity;

		// Get the current nodes position to nagivate to
		const Vector2& Node = Path[Index]->Node().Position();

		// Get the displacement between the node and position
		Vector2 Dis = Node - APos;

		// Is this agent within range?
		if (Dis.Magnitude() < m_Radius)
		{
			// Increment the index
			++Index;
		}

		// Normalise the displacement
		Dis.Normalise();

		// Scale the normalised displacement by the maximum velocity
		Des = Dis * MaxVelocity;

		// Subtract the current velocity from the desired velocity
		Des -= AVel;
	}

	// Set the index
	Board->SetAs_UInt("PathIdx", Index);

	// Apply the force to agent
	a_Agent->GetRigidBody().AddForce(Des);

	// Return success
	return Behaviour::eBehaviourResult::Success;
}

void FollowPath::Radius(float a_Radius)
{
	// Set the radius
	m_Radius = a_Radius;
}

float FollowPath::Radius() const
{
	// Return the radius
	return m_Radius;
}
