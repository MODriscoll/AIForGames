#include "Maze\Behaviours\SeekClosest.h"

#include "Maze\Agents\MazeAgent.h"

SeekClosest::SeekClosest(const std::string& a_Tag)
	: IBehaviour(a_Tag)
{
}

Behaviour::eBehaviourResult SeekClosest::Execute(Agent* a_Agent, float deltaTime)
{
	// Get the blackboard from the agent
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Get the closest from the blackboard
	MazeAgent* Closest = static_cast<MazeAgent*>(Board->GetAs_Pointer("Closest"));

	// Get the speed of the agent
	float MaxVelocity = Board->GetAs_Float("Speed");

	// Get reference to agents rigidbody
	RigidBody2D& ARig = a_Agent->GetRigidBody();

	// Get reference to targets and agents position
	const Vector2& APos = a_Agent->GetTransform().Position;
	const Vector2& TPos = Closest->GetTransform().Position;

	// Get reference to agents velocity
	const Vector2& AVel = a_Agent->GetRigidBody().Velocity;

	// Get the desired velocity subtracting the positions
	Vector2 Des = TPos - APos;

	// Normalise the velocity
	Des.Normalise();

	// Scale the normalised velocity by the maximum velocity
	Des *= MaxVelocity;

	// Subtract the current velocity from the desired velocity
	Des -= AVel;

	// Apply the seek force to the agent
	ARig.AddForce(Des);

	// Return success
	return Behaviour::eBehaviourResult::Success;
}
