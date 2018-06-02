#include "Maze\Behaviours\FreshPath.h"

#include "Maze\Agents\MazeAgent.h"

#include "Maze\MazeGame.h"

FreshPath::FreshPath(const std::string& a_Tag)
	: IBehaviour(a_Tag)
{

}

Behaviour::eBehaviourResult FreshPath::Execute(Agent* a_Agent, float deltaTime)
{
	// Get the agents blackboard
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Get the maze from the board
	Maze* Maz = static_cast<Maze*>(Board->GetAs_Pointer("Maze"));

	// Get the closest from the board
	MazeAgent* Closest = static_cast<MazeAgent*>(Board->GetAs_Pointer("Closest"));

	// Get the current path from the board ( as a reference )
	Maze::path& Path = *(static_cast<Maze::path*>(Board->GetAs_Pointer("Path")));

	// Get this agents index and closests index from the maze
	Maze::node* AIdx = Maz->Node(a_Agent->GetTransform().Position);
	Maze::node* CIdx = Maz->Node(Closest->GetTransform().Position);

	// Create the lambda to calculate the heuristic ( set as static )
	static auto Heuristic = [](const MazeNode& n1, const MazeNode& n2)->float
	{
		// Return the distance between these nodes
		return Vector2::Distance(n1.Position(), n2.Position());
	};

	// Calculate and save the new path
	Path = Maz->AStar(AIdx->Node(), CIdx->Node(), Heuristic);

	// Reset the path index
	Board->SetAs_UInt("PathIdx", 0);

	// Return success
	return Behaviour::eBehaviourResult::Success;
}
