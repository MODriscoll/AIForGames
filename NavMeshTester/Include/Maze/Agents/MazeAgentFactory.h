#pragma once

#include "MazeAgent.h"

#include <vector>

class Maze;
class Camera;

class MazeAgentFactory final
{
public:

	MazeAgentFactory() = default;

	~MazeAgentFactory() = default;

public:

	// Makes a player based on maze's variables
	// Requires a pointer to the camera's position
	static MazeAgent* MakePlayer(Maze* a_Maze, Camera* a_Camera);

	// Makes surviours based on maze's variables
	// Variables for blackboards are set into the given blackboards
	// Spawn points specifiers how many agents will be created
	static std::vector<MazeAgent*> MakeSurvivours(Maze* a_Maze, Blackboard& a_Board, const std::vector<Vector2>& a_SpawnPoints);

	// Makes a monster based on maze's variables
	// Variables for blackboards are set into the given blackboards
	static MazeAgent* MakeMonster(Maze* a_Maze, Blackboard& a_Board);

	// Deletes a maze agent
	static void DeleteAgent(MazeAgent*& a_Agent);
	
public:

	const Behaviour::BehaviourTree& GetPlayerSteeringTree() const;
	
	const Behaviour::BehaviourTree& GetSurvivourSteeringTree() const;

	const Behaviour::BehaviourTree& GetMonsterSteeringTree() const;

private:

	Behaviour::BehaviourTree m_PlayerTree;

	Behaviour::BehaviourTree m_SurviourTree;

	Behaviour::BehaviourTree m_MonsterTree;
};