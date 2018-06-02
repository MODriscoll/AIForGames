#pragma once

#include "MazeInfo.h"

#include "Math\Vectors\Vector2.h"

class MazeNode final
{
public:

	// Default constructor, required for the grid
	// Sets position to center and type to none
	MazeNode();

	// Default copy constructor
	MazeNode(const MazeNode& copy) = default;

	// Default move constructor
	MazeNode(MazeNode&& move) = default;
	
	// Public destructor
	~MazeNode() = default;

public:

	// Set the type of this node
	void Type(mNodeType a_Type);

	// Set the type this node will spawn
	void Spawns(mSpawnType a_Spawns);

	// Get the position of this node
	const Vector2& Position() const;

	// Get the type of this node
	mNodeType Type() const;

	// Get the type this node can spawn
	mSpawnType Spawns() const;

public:

	// Comparision operator, required for the grid
	// Returns true if positions are equal
	bool operator == (const MazeNode& rhs) const;

	// Comparision operator against a position
	// Returns true if positions are equal
	bool operator == (const Vector2& rhs) const;

	// Comparision operator against a nodes type
	// Returns true if nodes types are equal
	bool operator == (const mNodeType& rhs) const;

private:

	// Set the position of this node
	// Only allow maze grid to set the position
	void Position(const Vector2& a_Position);

private:

	friend class Maze;

	// Position of this node
	Vector2 m_Position;

	// This nodes type
	mNodeType m_Type;

	// Type this node can spawn
	mSpawnType m_Spawns;
};
