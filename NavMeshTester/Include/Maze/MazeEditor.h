#pragma once

#include <array>

#include <InputLibrary.h>

#include "Maze.h"

class Camera;

namespace aie
{
	class Renderer2D;
	class Font;
}

class MazeEditor final
{
public:

	using node = Maze::node;

	using button = Input_Button_ID;
	using key = Input_Key_ID;

public:

	// Default constructor, requires initial pointer to a maze and camera
	MazeEditor(Maze* a_Maze, Camera* a_Camera);

	// Default constructor
	~MazeEditor() = default;

public:

	// Updates the editor
	void Update(float deltaTime);

	// Renders the editor
	void Render(aie::Renderer2D* renderer);

public:

	// Get the selected node
	node* GetSelectedNode();

	// Render a path
	void RenderPath(aie::Renderer2D* renderer, const Maze::path& a_Path);

	// Render a flow field
	void RenderFlowField(aie::Renderer2D* renderer, const Maze::field& a_Field, bool a_bDrawBlocked = true);

public:

	// Set the maze to edit, resets everything
	// Asserts if maze is nullptr
	void SetMaze(Maze* a_Maze);

	// Set the camera to move
	// Asserts if camera is nullptr
	void SetCamera(Camera* a_Camera);

	// Set the speed to move the camera
	void SetCameraSpeed(float a_Speed);

	// Set up key for camera
	void SetUpKey(key a_keUp);
	// Set down key for camera
	void SetDownKey(key a_keDown);
	// Set left key for camera
	void SetLeftKey(key a_keLeft);
	// Set right key for camera
	void SetRightKey(key a_keRight);

	// Set the focus key
	void SetFocusKey(key a_keFoucus);

	// Set all controls for the camera
	void SetCameraControls(key a_keUp, key a_keDown, key a_keLeft, key a_keRight);

	// Set select button for editing
	void SetSelectButton(button a_buSelect);
	// Set block button for editing
	void SetBlockButton(button a_buBlock);

	// Set all controls for editing
	void SetEditingControls(button a_buSelect, button a_buBlock);

	// Get the maze being edited
	Maze* GetMaze();

	// Get the camera being used
	Camera* GetCamera();

	// Get the speed of the camera
	float GetCameraSpeed() const;

	// Get up key for camera
	key GetUpKey() const;
	// Get down key for camera
	key GetDownKey() const;
	// Get left key for camera
	key GetLeftKey() const;
	// Get right key for camera
	key GetRightKey() const;

	// Get the focus key
	key GetFocusKey() const;

	// Get all of the controls for the camera
	void GetCameraControls(key& out_keUp, key& out_keDown, key& out_keLeft, key& out_keRight) const;

	// Get select button for editing
	button GetSelectButton() const;
	// Get block button for editing
	button GetBlockButton() const;

	// Get all of the controls for editing
	void GetEditingControls(button& out_buSelect, button& out_buBlock);

private:

	// Update the camera
	void UpdateCamera(float deltaTime);

	// Update the maze editing
	void UpdateEditing(float deltaTime);

	// Update the grid menu
	void UpdateGridMenu(float deltaTime);
	// Update the node menu
	void UpdateNodeMenu(float deltaTime);

private:

	// Draw the grid
	void DrawGrid(aie::Renderer2D* renderer);

	// Draw the nodes based on type
	void DrawNodes(aie::Renderer2D* renderer);

	// Draw information relating to the selected node
	void DrawSelectedNode(aie::Renderer2D* renderer);

private:

	// Helper function for getting the mouse's world position
	Vector2 MousePosition(const Vector2& a_CameraPosition) const;

	// Helper function for setting node type and spawn type index of selected node
	void IndexTypes();

	// Helper function for setting the index string of selected node
	void IndexString();

	// Helper function for setting the vector of selected node's connections
	void ConnectionsString();

	// Helper function for getting colour based on a nodes type
	size_t NodeColour(const MazeNode& a_Node);

private:

	// Pointer to the maze to edit
	Maze* m_Maze;

	// Pointer to the cameras location
	Camera* m_Camera;

	// Speed of the camera 
	float m_CameraSpeed;

	// Keys to move the camera
	key m_keUp, m_keDown, m_keLeft, m_keRight;

	// Key to focus the camera on the maze
	key m_keFocus;

	// Buttons to select nodes with
	// Block auto selects the node
	button m_buSelect, m_buBlock;

private:

	// Buffer for the name of the maze
	std::array<char, Maze::MaxNameLength> buf_Name;

	// Buffer for the grid structure ( matrix ) of the maze
	std::array<int, 2> buf_Matrix;

	// Buffer for the maze position
	std::array<float, 2> buf_Position;

	// Buffer for the maze size
	std::array<float, 2> buf_Size;

	// Buffer for the modifiers when linking
	std::array<float, 8> buf_Modifiers;

	// Pointer to the selected node
	node* m_Node;

	// Index ( as string ) of selected node
	std::string m_NodeIndex;

	// Vector of all the selected nodes connections ( with weights )
	std::vector<std::string> m_NodeConnections;

private:

	// String for setting the path to save at ( saves as .dat )
	std::array<char, Maze::MaxNameLength> m_Path;

	// Const array for the list box of node types
	std::array<const char*, 3> m_NodeTypes{ "Default", "Spawn", "Exit" };

	// Const array for the list box of spawn types
	std::array<const char*, 4> m_SpawnTypes{ "Nothing", "Player", "Survivour", "Monster" };

	// Current selected type ( node and spawn )
	int m_NodeTypeIndex, m_SpawnTypeIndex;
};