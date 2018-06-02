#include "Maze\Behaviours\InShortRange.h"

#include "Maze\Agents\MazeAgent.h"

InShortRange::InShortRange(const std::string& a_Tag)
	: IBehaviour(a_Tag)
{
}

Behaviour::eBehaviourResult InShortRange::Execute(Agent * a_Agent, float deltaTime)
{
	// Get the agents blackboard
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Get the closest from the blackboard
	MazeAgent* Closest = static_cast<MazeAgent*>(Board->GetAs_Pointer("Closest"));

	// Get the range and scale it
	float Range = Board->GetAs_Float("Range") * 0.2f;

	// Get reference to agents and closests position
	const Vector2& APos = a_Agent->GetTransform().Position;
	const Vector2& CPos = Closest->GetTransform().Position;

	// Get the displacement between the points
	Vector2 Dis = CPos - APos;

	// Return if the agent is within the short range
	return Dis.Magnitude() < Range ? Behaviour::eBehaviourResult::Success : Behaviour::eBehaviourResult::Failure;
}
