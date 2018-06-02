#pragma once

// IDEA ON HOW TO USE A BLACKBOARD
// USE A BLACKBOARD THAT STORES THE INRANGE DISTANCE
// AN AGENT NEEDS TO BE IN TO FOLLOW THE FLOW FIELD
// THE GAME CAN GRADUALLY INCREASE THE LENGTH AND DURING
// EXECUTE THE LENGTH CAN JUST BE RETRIEVED. THE EXECUTE
// CAN THEN CHECK IF AGENT IS IN RANGE AND APPLY FORCE ACCORDINGLY
// MAYBE ALSO HAVE AN INFLUENCE VALUE SO THE LONGER THE GAME
// HAS BEEN ACTIVE THE GREATER THE FORCE CALCULATED WILL BE

// MAKE ANOTHER BEHAVIOUR THAT DETECTS IF A SURVIVOUR HAS REACHED THE
// END. IF THEY HAVE, THEY WILL POST TO THE BLACKBOARD THAT THEY HAVE
// COMPLETED.
// ALSO MAYBE IF THEY COME ACCROSS THE MONSTER, THEY WILL POST THE MONSTERS
// LAST KNOWN POSITION

#include "Behaviours\Steering\ISteer.h"

#include <vector>

class Maze;

class MazeGuider final : public Behaviour::ISteer
{
public:

	// Guider requires a tag
	MazeGuider(const std::string& a_Tag);

	// Default destructor
	virtual ~MazeGuider() = default;

	// Guides agent through the maze using set flow field
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

	// Executes force to traverse the maze
	virtual Vector2 Calculate(Agent* a_Agent) override;
};