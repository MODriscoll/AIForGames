#pragma once

#include "MazeNode.h"

#include "Containers\Grid.h"

class Maze : public Containers::Grid<MazeNode, float>
{
public:

	using base = Containers::Grid<MazeNode, float>;
	using node = typename City;

	using path = City_Vector;
	using field = Flow_Field<Vector2>;

	static const size_t MaxNameLength = 255;

public:

	// Default constructor
	Maze();

	// Default destructor
	virtual ~Maze() = default;

public:

	// Get the size of nodes
	Vector2 NodeSize() const;

	// Returns the index of the containing the position
	// Returns true if index was found, false otherwise
	bool NodeIndex(const Vector2& a_Position, size_t& out_X, size_t& out_Y) const;
	// Returns the index of the node given
	// Returns true if index was found, false otherwise
	bool NodeIndex(node* a_Node, size_t& out_X, size_t& out_Y) const;

	// Get the node that contains this point
	// If no node is found, nullptr is returned
	node* Node(const Vector2& a_Position);

	// Get every node in the maze
	const Matrix& Nodes() const;

public:
	
	// Sets the grid size to given valus
	// Initialises matrix
	void Resize(size_t a_Width, size_t a_Height);

	// Set the name of the maze
	void Name(const std::string& a_Name);

	// Set the position of the maze
	// Initialises positions
	void Position(const Vector2& a_Position);

	// Set the size of the maze
	// Initialises positions
	void Size(const Vector2& a_Size);

	// Get the modifiers of the grid
	const Modifier& Modifiers() const;

	// Get the name of the maze
	const std::string& Name() const;

	// Get the position of the maze
	const Vector2& Position() const;

	// Get the size of the maze
	const Vector2& Size() const;

	// Get the spawners in this maze
	std::vector<node*>& Spawners();

	// Get the exit of this maze
	node* Exit();

public:
	
	// Construct the maze, intialise spawn points and exit
	void Construct();
	// Constructs the maze with new modifiers, initialise spawn points and exit
	void Construct(const Modifier& a_Modifier);

	// TODO:
	// Make operators for << and >> to make saving/loading easier

	// Save the current maze using the given path
	void Save(const std::string& a_Path);
	// Load a maze using the given map
	void Load(const std::string& a_Path);

public:

	// Index a node using a position, returns node containing point
	// If no node is found, nullptr is returned
	node* operator [] (const Vector2& position);

private:

	// Calculate the position of each node
	void InitialisePositions();

	// Finds and stores all nodes marked as spawners ( not blocked )
	void InitialiseSpawners();

	// Finds and stores the first node marked as an exit ( not blocked )
	void InitialiseExit();

	// Name of this maze
	std::string m_Name;

	// The position of this maze
	// Position marks bottom left of maze
	Vector2 m_Position;

	// Size of this grid
	Vector2 m_Size;

	// Vector that contains pointers to all
	// nodes that have been marked as spawners
	std::vector<node*> m_Spawners;

	// Pointer to the exit node
	node* m_Exit;

private:

	// So editor can access variables to edit
	friend class MazeEditor;
};