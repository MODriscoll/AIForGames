#include "Maze\MazeGame.h"

#include "Maze\Agents\MazeAgentFactory.h"

#include "Maze\Behaviours\MazeAvoider.h"

MazeGame::MazeGame(Camera* a_Camera, const std::string& a_MazePath)
	: m_Editor(nullptr), m_bEditing(true), m_Player(nullptr), m_Monster(nullptr), m_SimulationTime(0.f), m_FieldTime(0.f), m_Camera(a_Camera)
{
	// Load the given map first
	m_Maze.Load(a_MazePath);

	// Create the editor with the camera and pointer to maze
	m_Editor = new MazeEditor(&m_Maze, a_Camera);

	// Set camera speed for the editor
	m_Editor->SetCameraSpeed(400.f);
	
	// Set maze into the blackboard
	m_SBoard.SetAs_Pointer("Maze", &m_Maze);
	m_MBoard.SetAs_Pointer("Maze", &m_Maze);

	// Set alternative camera keys
	m_Editor->SetUpKey(MazeEditor::key::Key_W);
	m_Editor->SetDownKey(MazeEditor::key::Key_S);
	m_Editor->SetLeftKey(MazeEditor::key::Key_A);
	m_Editor->SetRightKey(MazeEditor::key::Key_D);
}

MazeGame::~MazeGame()
{
	// End simulation that might be active
	EndSimulation();

	// Delete the editor
	delete m_Editor;
}

void MazeGame::Update(float deltaTime)
{
	// Was start simulation button pressed?
	if (InputLibrary::Instance()->WasKeyPressed(Input_Key_ID::Key_O))
	{
		// Start the simulation
		StartSimulation();
	}

	// Was end simulation button pressed?
	if (InputLibrary::Instance()->WasKeyPressed(Input_Key_ID::Key_P))
	{
		// End the simulation
		EndSimulation();
	}

	// Is the mode set to edit
	if (m_bEditing)
	{
		// Update editing
		UpdateEditing(deltaTime);
	}
	else
	{
		// Update simulation
		UpdateSimulation(deltaTime);
	}
}

void MazeGame::Render(aie::Renderer2D* renderer)
{
	// Render the editor
	m_Editor->Render(renderer);

	// Is simulation active?
	if (m_bEditing == false)
	{
		// Render field ( debugging )
		//m_Editor->RenderFlowField(renderer, m_Field, false);

		// Render player
		m_Player->Render(renderer);

		// Cycle through survivours
		for (auto& Sur : m_Survivours)
		{
			// Render this survivour
			Sur->Render(renderer);

			// Render survivours avoidance behaviour ( debugging )
			//Sur->GetBehaviourTree()->GetBehaviour<MazeAvoider>("SurvivourAvoid")->Render(renderer);
		}

		// Render path ( debugging )
		//m_Editor->RenderPath(renderer, m_Path);

		// Render the monster
		m_Monster->Render(renderer);

		// Render survivours avoidance behaviour ( debugging )
		m_Monster->GetBehaviourTree()->GetBehaviour<MazeAvoider>("MonsterAvoiding")->Render(renderer);
	}
}

void MazeGame::UpdateEditing(float deltaTime)
{
	// Update the editor
	m_Editor->Update(deltaTime);
}

void MazeGame::UpdateSimulation(float deltaTime)
{
	// Get bounds of the maze
	Vector2 BL = m_Maze.Position();
	Vector2 UR = BL + m_Maze.Size();

	// Update the player
	m_Player->Update(deltaTime);
	
	// Clamp the player
	m_Player->Clamp(BL, UR);

	// Cycle through survivours
	for (auto& Sur : m_Survivours)
	{
		// Update this survivour
		Sur->Update(deltaTime);

		// Clamp this survivour
		Sur->Clamp(BL, UR);
	}

	// Update the monster
	m_Monster->Update(deltaTime);

	// Clamp the monster
	m_Monster->Clamp(BL, UR);
}

void MazeGame::StartSimulation()
{
	// Was simulation requested to be reset
	if (m_bEditing == false)
	{
		// End simulation first
		EndSimulation();
	}

	// Construct the maze
	m_Maze.Construct();

	// Get the spawning points
	const Maze::City_Vector& Spawners = m_Maze.Spawners();

	// Create vector to capture survivour spawn points
	std::vector<Vector2> Points;

	// Cycle through each spawner
	for (auto& Spawn : Spawners)
	{
		// Get reference to the maze node
		const MazeNode& MNode = Spawn->Node();

		// Get what this node spawns
		mSpawnType SType = MNode.Spawns();

		// Is this spawn for the player
		// Has the player not already been spawned?
		if (SType == mSpawnType::Player && m_Player == nullptr)
		{
			// Make and set the player
			m_Player = MazeAgentFactory::MakePlayer(&m_Maze, m_Camera);

			// Set position of the player
			m_Player->GetTransform().Position = MNode.Position();
		}
		// Is this a spawn for a survivour?
		else if (SType == mSpawnType::Survivour)
		{
			// Add this point
			Points.push_back(MNode.Position());
		}
		// Is this spawn for the monster?
		// Has the monster not already been spawned
		else if (SType == mSpawnType::Monster && m_Monster == nullptr)
		{	
			// Make and set the monster
			m_Monster = MazeAgentFactory::MakeMonster(&m_Maze, m_MBoard);

			// Set position of the monster
			m_Monster->GetTransform().Position = MNode.Position();

			// Set pointer to path vector
			m_MBoard.SetAs_Pointer("Path", &m_Path);

			// Reset the path
			m_Path.clear();

			// Reset other variables in blackboard
			m_MBoard.SetAs_Pointer("Closest", nullptr);
			m_MBoard.SetAs_UInt("PathIdx", 0);
		}
	}

	// Make sure there is at least a player and a monster
	if (m_Player == nullptr || m_Monster == nullptr)
	{
		// End simulation
		EndSimulation();
	}

	// Create the survivours
	m_Survivours = MazeAgentFactory::MakeSurvivours(&m_Maze, m_SBoard, Points);

	// Set pointer to survivours for monster
	m_MBoard.SetAs_Pointer("Survivours", &m_Survivours);

	// Get the exit of the map
	Maze::City* Exit = m_Maze.Exit();

	// Set the exit into the survivours blackboard
	m_SBoard.SetAs_Pointer("Exit", Exit);

	// Is there an exit?
	if (Exit != nullptr)
	{
		// Flow field function requires to maze nodes
		// Type of the flow field can be specified by the return type
		auto Func = [](const MazeNode& n1, const MazeNode& n2)->Vector2
		{
			// Get the displacement between the nodes
			Vector2 Dis = n2.Position() - n1.Position();

			// Normalise the displacement
			Dis.Normalise();

			// Return the normalised displacement
			return Dis;
		};

		// Generate the flowfield for this maze
		// See definition ( and lambda func ) for more info
		m_Field = m_Maze.FlowField(Exit->Node(), Func);
		
		// Set the flowfield into the surviours blackboard
		m_SBoard.SetAs_Pointer("FlowField", &m_Field);
	}
	else
	{
		// Set to editing
		m_bEditing = false;

		// End simulation
		EndSimulation();

		// End this function
		return;
	}

	// Set the flow fields variables to start times
	m_SimulationTime = 0.f;
	m_FieldTime = 0.f;

	// Set the flow fields influence
	// length to the length of a node
	m_SBoard.SetAs_Float("FieldLength", m_Maze.NodeSize().Magnitude());

	// Set simulation to active
	m_bEditing = false;
}

void MazeGame::EndSimulation()
{
	// Is simulation not active
	if (m_bEditing)
	{
		// End this function
		return;
	}

	// Delete the player
	MazeAgentFactory::DeleteAgent(m_Player);

	// Cycle through the survivours
	for (auto& Sur : m_Survivours)
	{
		// Delete this survivour
		MazeAgentFactory::DeleteAgent(Sur);
	}

	// Clear the survivours
	m_Survivours.clear();

	// Delete the monster
	MazeAgentFactory::DeleteAgent(m_Monster);

	// Set to editing
	m_bEditing = true;
}

void MazeGame::ResetEditing()
{
}

void MazeGame::ResetSimulation()
{
}
