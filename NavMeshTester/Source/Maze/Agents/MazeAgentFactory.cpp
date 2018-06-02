#include "Maze\Agents\MazeAgentFactory.h"

#include "Maze\Maze.h"

#include "Behaviours\Composite\Selector.h"
#include "Behaviours\Composite\Sequence.h"

#include "AI\Behaviours\Keyboard.h"
#include "Maze\Behaviours\CameraFollow.h"

#include "Behaviours\Steering\Steerer.h"
#include "Maze\Behaviours\MazeAvoider.h"
#include "Maze\Behaviours\MazeGuider.h"

#include "Maze\Behaviours\FollowPath.h"
#include "Maze\Behaviours\FreshPath.h"
#include "Maze\Behaviours\GetClosest.h"
#include "Maze\Behaviours\InShortRange.h"
#include "Maze\Behaviours\SeekClosest.h"
#include "Maze\Behaviours\Successor.h"
#include "Maze\Behaviours\Timer.h"
#include "Behaviours\Steering\Wander.h"

MazeAgent* MazeAgentFactory::MakePlayer(Maze* a_Maze, Camera* a_Camera)
{
	using namespace Behaviour;

	// Get the nodes size
	Vector2 NSize = a_Maze->NodeSize();

	// Calculate size to set player to
	float Size = (NSize.x > NSize.y ? NSize.y : NSize.x) * 0.25f;

	// Calculate speed to set player to
	float Speed = NSize.Magnitude();

	// Make the maze agent
	MazeAgent* Player = new MazeAgent();
	Player->SetRadius(Size);
	//Player->bResetVelocity = true;
	//Player->GetRigidBody().FakeFriction = 0.f;

	// Create the behaviour tree for the player
	BehaviourTree* Tree = new BehaviourTree();

	// Create the behaviours for the player
	auto Seq = std::make_shared<Sequence>("PlayerSequence");

	auto Key = std::make_shared<Keyboard>("PlayerKeyBoard");
	Key->SetSpeed(Speed);

	auto Cam = std::make_shared<CameraFollow>("PlayerCameraFollow");
	Cam->SetCamera(a_Camera);
	//Cam->m_bInterpolate = false;

	// Insert leaves into the sequence
	Seq->Insert(Cam);
	Seq->Insert(Key);

	// Set the root of the tree
	Tree->SetRoot(Seq);

	// Set the tree for the player
	Player->SetBehaviourTree(Tree);

	// Return the player
	return Player;
}

std::vector<MazeAgent*> MazeAgentFactory::MakeSurvivours(Maze* a_Maze, Blackboard& a_Board, const std::vector<Vector2>& a_SpawnPoints)
{
	using namespace Behaviour;

	// Create the array
	std::vector<MazeAgent*> Agents;

	// Get the nodes size
	Vector2 NSize = a_Maze->NodeSize();

	// Calculate size to set survivours to
	float Size = (NSize.x > NSize.y ? NSize.y : NSize.x) * 0.25f;

	// Calculate speed to set survivours to
	float Speed = NSize.Magnitude();

	// Cycle through each spawn point
	for (auto& Point : a_SpawnPoints)
	{
		// Make the maze agent
		MazeAgent* Surviviour = new MazeAgent();
		Surviviour->SetRadius(Size);

		// Create the behaviour tree for the survivour
		BehaviourTree* Tree = new BehaviourTree();

		// Create the behaviours for the survivour
		auto Ste = std::make_shared<Steerer>("SurvivourSteerer");
		Ste->MaxForce(NSize.Magnitude() * 4.f);

		auto Avo = std::make_shared<MazeAvoider>("SurvivourAvoid");
		Avo->MaxVelocity(NSize.Magnitude() * 0.75f);
		Avo->SetMaxAvoidForce(NSize.Magnitude() * 0.75f);
		Avo->Weight(1.f);
		Avo->SetMaxRange(NSize.Magnitude() * 0.5f);

		auto Gui = std::make_shared<MazeGuider>("SurvivourGuide");
		Gui->MaxVelocity(NSize.Magnitude() * 0.75f);
		Gui->Weight(1.f);

		// Insert leaves into the steerer
		Ste->Insert(Avo);
		Ste->Insert(Gui);

		// Set the root of the tree
		Tree->SetRoot(Ste);

		// Set the tree for the surviour
		Surviviour->SetBehaviourTree(Tree);

		// Set the blackboard of the survivour
		Tree->SetBlackboard(&a_Board);

		// Set surviours initial position
		Surviviour->GetTransform().Position = Point;

		// Add surviviour to the array
		Agents.push_back(Surviviour);
	}

	// Return the agents
	return Agents;
}

MazeAgent* MazeAgentFactory::MakeMonster(Maze* a_Maze, Blackboard& a_Board)
{
	using namespace Behaviour;

	// Get the nodes size
	Vector2 NSize = a_Maze->NodeSize();

	// Calculate size to set monster to
	float Size = (NSize.x > NSize.y ? NSize.y : NSize.x) * 0.5f;

	// Calculate speed to set monster to
	float Speed = NSize.Magnitude() * 1.25f;

	// Calculate the range of the monster
	float Range = NSize.Magnitude() * 10.f;

	// Make the maze agent
	MazeAgent* Monster = new MazeAgent();
	Monster->SetRadius(Size);

	// Create the behaviour tree for the monster
	BehaviourTree* Tree = new BehaviourTree();

	// Create the behaviours for the monster
	auto Seq1 = std::make_shared<Sequence>("Monster Steering");

	auto Avo = std::make_shared<MazeAvoider>("MonsterAvoiding");
	Avo->SetMaxAvoidForce(NSize.Magnitude() * 0.75f);
	Avo->SetMaxRange(NSize.Magnitude());
	Avo->MaxVelocity(Speed);

	auto Sel1 = std::make_shared<Selector>("Chase Survivour");

	Seq1->Insert(Avo);
	Seq1->Insert(Sel1);

	auto Seq2 = std::make_shared<Sequence>("DetermineClosest");

	auto Wan = std::make_shared<Wander>("Wander");
	Wan->Distance(NSize.Magnitude() * 0.5f);
	Wan->Radius(NSize.Magnitude());
	Wan->Jitter(5.f);
	Wan->MaxVelocity(Speed * 0.75f);

	Sel1->Insert(Seq2);
	Sel1->Insert(Wan);

	auto Clo = std::make_shared<GetClosest>("GetClosest");
	
	auto Sel2 = std::make_shared<Selector>("SeekOrFollow");

	Seq2->Insert(Clo);
	Seq2->Insert(Sel2);

	auto Seq3 = std::make_shared<Sequence>("ShouldSeek");

	auto Sho = std::make_shared<InShortRange>("InShortRange");
	
	auto Seek = std::make_shared<SeekClosest>("SeekClosest");
	
	Seq3->Insert(Sho);
	Seq3->Insert(Seek);

	auto Seq4 = std::make_shared<Sequence>("ShouldFollow");

	auto Fre = std::make_shared<FreshPath>("FreshPath");
	
	auto Tim = std::make_shared<Timer>("PathTimer", Fre);
	Tim->Limit(5.f);

	auto Scr = std::make_shared<Successor>("PathSuccessor", Tim);
	
	auto Flw = std::make_shared<FollowPath>("FollowPath");
	Flw->Radius(NSize.Magnitude() * 0.75f);

	Seq4->Insert(Scr);
	Seq4->Insert(Flw);

	Sel2->Insert(Seq3);
	Sel2->Insert(Seq4);

	// Set the root of the tree
	Tree->SetRoot(Seq1);

	// Set the tree for the surviour
	Monster->SetBehaviourTree(Tree);

	// Set the blackboard of the survivour
	Tree->SetBlackboard(&a_Board);

	// Set variables into the blackboard
	a_Board.SetAs_Float("Speed", Speed);
	a_Board.SetAs_Float("Range", Range);

	// Return the monster
	return Monster;
}

void MazeAgentFactory::DeleteAgent(MazeAgent*& a_Agent)
{
	using namespace Behaviour;

	// Is the given agent nullptr
	if (a_Agent == nullptr)
	{
		// End this function
		return;
	}

	// Get the tree from the agent
	BehaviourTree* Tree = a_Agent->GetBehaviourTree();

	// Delete the tree
	delete Tree;

	// Delete the agent
	delete a_Agent;

	// Set pointer to nullptr
	a_Agent = nullptr;
}
