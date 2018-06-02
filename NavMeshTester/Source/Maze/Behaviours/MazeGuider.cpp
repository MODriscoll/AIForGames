#include "Maze\Behaviours\MazeGuider.h"

#include "Maze\Maze.h"

#include "Maze\Agents\MazeAgent.h"

MazeGuider::MazeGuider(const std::string& a_Tag)
	: ISteer(a_Tag)
{

}

Behaviour::eBehaviourResult MazeGuider::Execute(Agent* a_Agent, float deltaTime)
{
	// Get reference to the agents blackboard
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Does this blackboard contain the maze?
	if (Board->GetAs_Pointer("Maze") != nullptr)
	{
		// Calculate force and apply it to the agent
		a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));

		// Return successfull result
		return Behaviour::eBehaviourResult::Success;
	}

	// Return failed result
	return Behaviour::eBehaviourResult::Failure;
}

Vector2 MazeGuider::Calculate(Agent* a_Agent)
{
	// Get reference to the agents blackboard
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Get a pointer to the maze and flowfield
	Maze* Maz = static_cast<Maze*>(Board->GetAs_Pointer("Maze"));
	Maze::field* Field = static_cast<Maze::field*>(Board->GetAs_Pointer("FlowField"));

	// Get the influence length from the board
	float Influ = Board->GetAs_Float("FieldLength");

	// Get reference to agents transform and rigidbody
	const Transform2D& ATra = a_Agent->GetTransform();
	const RigidBody2D& ARig = a_Agent->GetRigidBody();

	// Get pointer to the exit of the maze
	Maze::City* Exit = Maz->Exit();

	// Get the displacement between this agent and the exit
	Vector2 Dis = Exit->Node().Position() - ATra.Position;

	// Create values to capture the index
	size_t x, y;

	// Get the index of this agent
	// Check if index is valid
	// Is the agent also in the influence range?
	if (Maz->NodeIndex(ATra.Position, x, y))//&& Dis.Magnitude() < Influ)
	{
		// Get the direction to move in from the flow field
		Vector2 Dir = (*Field)[x][y];

		// Scale the direction by the maximum velocity
		Dir *= m_MaxVelocity;

		// Subtract the agents current velocity from the direction
		Dir -= ARig.Velocity;

		// Return the force
		return Dir;
	}

	// Return no force
	return Vector2();
}
