#include "Maze\Behaviours\AtExit.h"

#include "Maze\Agents\MazeAgent.h"

#include "Maze\Maze.h"

AtExit::AtExit(const std::string& a_Tag)
	: IBehaviour(a_Tag)
{
}

Behaviour::eBehaviourResult AtExit::Execute(Agent* a_Agent, float deltaTime)
{
	// Get reference to the blackboard
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Get the maze from the blackboard
	Maze* Maz = static_cast<Maze*>(Board->GetAs_Pointer("Maze"));

	// Get reference to agents position
	const Vector2& APos = a_Agent->GetTransform().Position;

	// Is the agent inside of the exit node
	if (Maz->Node(APos) == Maz->Exit())
	{
		// PUT FINISH LIST STUFF HERE

		// Return successfull result
		return Behaviour::eBehaviourResult::Success;
	}

	// Return failed result
	return Behaviour::eBehaviourResult::Failure;
}
