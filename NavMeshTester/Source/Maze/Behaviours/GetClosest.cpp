#include "Maze\Behaviours\GetClosest.h"

#include "Maze\Agents\MazeAgent.h"

#include "Maze\MazeGame.h"

// temp include
#include "Maze\Behaviours\Timer.h"

GetClosest::GetClosest(const std::string& a_Tag)
	: IBehaviour(a_Tag)
{
}

Behaviour::eBehaviourResult GetClosest::Execute(Agent* a_Agent, float deltaTime)
{
	// Get the blackboard from the agent
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Get the current closest survivour to the agent
	MazeAgent* Closest = static_cast<MazeAgent*>(Board->GetAs_Pointer("Closest"));

	// Get the range to search for
	float Range = Board->GetAs_Float("Range");

	// Get reference to this agents position
	const Vector2& APos = a_Agent->GetTransform().Position;

	// Is there a current closest?
	if (Closest != nullptr)
	{
		// Get reference to closest's position
		const Vector2& CPos = Closest->GetTransform().Position;

		// Get the displacement between the points
		Vector2 Dis = CPos - APos;

		// Get the distance between the two
		float Mag = Dis.Magnitude();

		// Is the closest no longer in range?
		if (Mag > Range)
		{
			// Set to not having a closest
			Closest = nullptr;
		}
	}

	// Is there no closest
	if (Closest == nullptr)
	{
		// Get the survivours from the board
		std::vector<MazeAgent*>* Survivours = static_cast<std::vector<MazeAgent*>*>(Board->GetAs_Pointer("Survivours"));

		// Float to capture distance between current closest
		float Clo = Maze::ELimits::max();

		// Cycle through the survivours
		for (auto& Sur : *Survivours)
		{
			// Get reference to survivours position
			const Vector2& SPos = Sur->GetTransform().Position;

			// Get the displacement between the points
			Vector2 Dis = SPos - APos;

			// Get the distance between the two
			float Mag = Dis.Magnitude();

			// Is this agent within range?
			// Is this agent closer than the current closest?
			if (Mag < Range && Mag < Clo)
			{
				// Set this survivour as the closest
				Closest = Sur;

				// Set the closest distance
				Clo = Mag;
			}
		}

		// temp
		if (Closest != nullptr)
		{
			a_Agent->GetBehaviourTree()->GetBehaviour<Timer>("PathTimer")->Tick();
		}
	}

	// Set the closet into the blackboard
	Board->SetAs_Pointer("Closest", Closest);

	// Return success if a survivour is within range, otherwise false
	return Closest != nullptr ? Behaviour::eBehaviourResult::Success : Behaviour::eBehaviourResult::Failure;
}
