#pragma once

#include "Maze\Agents\MazeAgent.h"

#include "MazeEditor.h"

class Arrival;

class MazeGame final
{
public:
	
	// Maze game requires maze to work
	MazeGame(Camera* a_Camera, const std::string& a_MazePath = "default.dat");

	// Destroys the editing
	~MazeGame();

	// Update called once per frame
	void Update(float deltaTime);
	// Render called once per frame
	void Render(aie::Renderer2D* renderer);

	// If game is active
	bool IsActive() const { return !m_bEditing; }

private:

	// Updates all editing components
	void UpdateEditing(float deltaTime);
	// Updates all simulation components
	void UpdateSimulation(float deltaTime);

	// Set everything needed for simulation
	// Sets editing to false is maze is valid
	void StartSimulation();

	// Ends the simulation if simulating
	// Deletes the player, survivours and monster
	// This function must be called before restarting simulation
	void EndSimulation();

	// Reset variables for editing
	void ResetEditing();
	// Reset variables for simulation
	void ResetSimulation();

private:

	// Maze of this game
	Maze m_Maze;

	// Pointer to the editor
	MazeEditor* m_Editor;

	// Records if editing or simulating
	bool m_bEditing;

	// Time since simulation started
	// Time before increasing the field length
	float m_SimulationTime;
	float m_FieldTime;

	// Pointer to the player
	MazeAgent* m_Player;
	MazeAgent* AltPlayer;

	// Vector of all the survivors
	// The player is included in this vector as the first agent
	std::vector<MazeAgent*> m_Survivours;

	// Blackboard for the survivours to share
	Blackboard m_SBoard;

	// Blackboard for the monster
	Blackboard m_MBoard;

	// The flow field for the surviours
	Maze::field m_Field;

	// The current path of the monster
	Maze::path m_Path;

	// Pointer to the monster
	MazeAgent* m_Monster;

	// Pointer to the camera
	Camera* m_Camera;
};