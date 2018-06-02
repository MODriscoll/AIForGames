#include "Maze\Maze.h"

#include <fstream>

#include "Math\Maths.h"

using base = Containers::Grid<MazeNode, float>;
using node = typename base::City;

Maze::Maze()
	: m_Size(100.f, 100.f), m_Exit(nullptr)
{
	
}

Vector2 Maze::NodeSize() const
{
	// Clone the size of the maze
	Vector2 Size = m_Size;

	// Scale the axes by the rows and columns
	Size.x /= static_cast<float>(Width());
	Size.y /= static_cast<float>(Height());

	// Return the size
	return Size;
}

// Can unintentionally return valid result if two parameters are met
// 1. Grid is not empty
// 2. Position would be not be less than 'index -1' after calculating
// The index will return zero, so it is safe to use
bool Maze::NodeIndex(const Vector2& a_Position, size_t& out_X, size_t& out_Y) const
{
	// Get the size of a node
	Vector2 Size = NodeSize();

	// Get the 'index' of this position
	// Casting to int rounds the number down
	size_t x = static_cast<size_t>((a_Position.x - m_Position.x) / Size.x);
	size_t y = static_cast<size_t>((a_Position.y - m_Position.y) / Size.y);

	// Set the valid bool
	// If either index is out of range, set it to false
	bool Valid = ((x >= 0) && (x < Width()) && (y >= 0) && (y < Height()));

	// Set the outputs to the calculated indexes
	out_X = x;
	out_Y = y;

	// Return if index is valid
	return Valid;
}

bool Maze::NodeIndex(node* a_Node, size_t& out_X, size_t& out_Y) const
{
	// Use the position to calculate the index
	return NodeIndex(a_Node->Node().m_Position, out_X, out_Y);
}

node* Maze::Node(const Vector2& a_Position)
{
	// Declare the variables to capture the node index
	size_t x, y;

	// Get the index. Was the position valid?
	if (NodeIndex(a_Position, x, y))
	{
		// Return the node at this index
		return &(m_Vertices[x][y]);
	}

	// Return nullptr if position isn't valid
	return nullptr;
}

const base::Matrix& Maze::Nodes() const
{
	// Return the nodes
	return m_Vertices;
}

void Maze::Resize(size_t a_Width, size_t a_Height)
{
	// Resize the grid
	base::Resize(a_Width, a_Height);

	// Re-initialise the positions
	InitialisePositions();
}

void Maze::Name(const std::string& a_Name)
{
	// Set the name of the maze
	m_Name = a_Name;
}

void Maze::Position(const Vector2& a_Position)
{
	// Set the position of the maze
	m_Position = a_Position;

	// Re-initialise the positions
	InitialisePositions();
}

void Maze::Size(const Vector2& a_Size)
{
	// Set the size of the maze
	m_Size = a_Size;

	// Re-initialise the positions
	InitialisePositions();
}

const base::Modifier& Maze::Modifiers() const
{
	// Return the modifiers of the maze
	return m_Modifiers;
}

const std::string& Maze::Name() const
{
	// Return the name of the maze
	return m_Name;
}

const Vector2& Maze::Position() const
{
	// Return the position of the maze
	return m_Position;
}

const Vector2& Maze::Size() const
{
	// Return the size of the maze
	return m_Size;
}

std::vector<node*>& Maze::Spawners()
{
	// Return the spawners in this maze
	return m_Spawners;
}

node* Maze::Exit()
{
	// Return the exit of the spawner
	return m_Exit;
}

void Maze::Construct()
{
	// Link the grid
	Link();

	// Initialise components
	InitialisePositions();
	InitialiseSpawners();
	InitialiseExit();
}

void Maze::Construct(const Modifier& a_Modifier)
{
	// Link the grid
	Link(a_Modifier);

	// Initialise components
	InitialisePositions();
	InitialiseSpawners();
	InitialiseExit();
}

void Maze::Save(const std::string& a_Path)
{
	// Construct the grid first so everything is linked and in position
	Construct(m_Modifiers);

	// Detect whether this file exists and make one if not
	std::ofstream fout(a_Path, std::ios::out | std::ios::binary);

	// Was the file unable to be opened?
	if ((fout.rdstate() & std::ifstream::failbit) != 0)
	{
		// Close the file
		fout.close();

		// End this function
		return;
	}

	// Re-assure file is good to write to
	if (fout.good())
	{
		// ORDER:
		// Name
		// Structure ( Rows then columns )
		// Position ( x then y )
		// Size ( x then y )
		// Modifiers
		// Nodes

		// Write the name of the maze first
		fout.write(m_Name.c_str(), MaxNameLength);

		// Get the width and height of the grid
		size_t buf_Struc[2] = { Width(), Height() };

		// Write the structure to the file
		fout.write((char*)&buf_Struc[0], sizeof(size_t) * 2);

		// Write the position of the maze to the file
		fout.write((char*)((float*)m_Position), sizeof(Vector2));

		// Write the size of the maze to the file
		fout.write((char*)((float*)m_Size), sizeof(Vector2));

		// Write the modifiers to the file
		fout.write((char*)m_Modifiers.data(), (sizeof(Modifier::value_type) * m_Modifiers.size()));

		// Cyclce through the rows
		for (auto& row : m_Vertices)
		{
			// Cycle through the vertices
			for (auto& vertex : row)
			{
				// NODES ORDER
				// Node type
				// Spawn type
				// Weight
				// Blocked

				// Get reference to maze node
				const MazeNode& Ref = vertex.Node();

				// Get the node type and spawn type of this node ( as their base )
				mNodeTypeBase NType = static_cast<mNodeTypeBase>(Ref.Type());
				mSpawnTypeBase SType = static_cast<mSpawnTypeBase>(Ref.Spawns());

				// Get the weight and block status of this node
				float Weight = vertex.Weight();
				bool Blocked = vertex.Blocked();

				// Write the node's type to file
				fout.write((char*)&NType, sizeof(mNodeTypeBase));
				
				// Write the node's spawn type to file
				fout.write((char*)&SType, sizeof(mSpawnTypeBase));

				// Write the node's weight to file
				fout.write((char*)&Weight, sizeof(float));

				// Write the node's blocked status to file
				fout.write((char*)&Blocked, sizeof(bool));
			}
		}
	}

	// Close the file
	fout.close();
}

void Maze::Load(const std::string& a_Path)
{
	// Open the file using the path given
	std::ifstream fin(a_Path, std::ios::in | std::ios::binary);

	// Was the file unable to be opened?
	if ((fin.rdstate() & std::ifstream::failbit) != 0)
	{
		// Close the file
		fin.close();

		// End this function
		return;
	}

	// Re-assure file is good to read
	if (fin.good())
	{
		// Assure file size isn't surpassed
		if (!fin.eof() && fin.peek() != EOF)
		{
			// Clear the name
			m_Name.clear();

			// Clear current maze
			m_Vertices.clear();

			// ORDER:
			// Name
			// Structure ( Rows then columns )
			// Position ( x then y )
			// Size ( x then y )
			// Modifiers
			// Nodes

			// Create buffer to capture the maze's name
			char buf_Name[MaxNameLength];

			// Get the maze's name from the file, store it in the buffer
			fin.read(buf_Name, MaxNameLength);

			// Create buffer to capture the maze's structure
			size_t buf_Struc[2];

			// Get the maze's structure from the file, store it in the buffer
			fin.read((char*)buf_Struc, sizeof(buf_Struc));

			// Get the position of the maze from the file
			fin.read((char*)&m_Position, sizeof(Vector2));

			// Get the size of the maze from the file
			fin.read((char*)&m_Size, sizeof(Vector2));

			// Get the modifiers of the maze from the file
			fin.read((char*)m_Modifiers.data(), (sizeof(Modifier::value_type) * m_Modifiers.size()));

			// Set the name
			m_Name = buf_Name;

			// Resize the grid
			Resize(buf_Struc[0], buf_Struc[1]);

			// Cyclce through the rows
			for (auto& row : m_Vertices)
			{
				// Cycle through the vertices
				for (auto& vertex : row)
				{
					// Assure file size isn't surpassed
					// Assure file size isn't surpassed
					if (!fin.eof() && fin.peek() != EOF)
					{
						// NODES ORDER
						// Node type
						// Spawn type
						// Weight
						// Blocked

						// Get reference to maze node
						MazeNode& Ref = vertex.Node();

						// Create buffers for node type and spawn type
						mNodeTypeBase buf_NType;
						mSpawnTypeBase buf_SType;

						// Create the buffers for node weight and blocked status
						float Weight;
						bool Blocked;

						// Get the nodes type from the file, store it in the buffer
						fin.read((char*)&buf_NType, sizeof(mNodeTypeBase));

						// Get the nodes spawn type from the file, store it in the buffer
						fin.read((char*)&buf_SType, sizeof(mSpawnTypeBase));

						// Get the nodes weight from the file, store it in the buffer
						fin.read((char*)&Weight, sizeof(float));

						// Get the node's blocked status from file, store it in the buffer
						fin.read((char*)&Blocked, sizeof(bool));

						// Set the nodes type and spawn type
						Ref.Type(static_cast<mNodeType>(buf_NType));
						Ref.Spawns(static_cast<mSpawnType>(buf_SType));

						// Set the nodes weight and blocked status
						vertex.Weight() = Weight;
						vertex.Block(Blocked);
					}
				}
			}
		}
	}

	// Close the file
	fin.close();

	// Construct the maze
	Construct(m_Modifiers);
}

node* Maze::operator[](const Vector2& position)
{
	// Return the node containing the position
	return Node(position);
}

void Maze::InitialisePositions()
{
	// Get the size and half size of a node
	Vector2 FSize = NodeSize();
	Vector2 HSize = FSize * 0.5f;

	// Cycle through each row
	for (size_t x = 0; x < m_Vertices.size(); ++x)
	{
		// Get reference to column
		auto& col = m_Vertices[x];

		// Cycle through the column
		for (size_t y = 0; y < col.size(); ++y)
		{
			// Calculate the position of this node
			Vector2 Pos = m_Position + ((FSize * Vector2(static_cast<float>(x), static_cast<float>(y))) + HSize);

			// Set this nodes position
			col[static_cast<size_t>(y)].Node().Position(Pos);
		}
	}
}

void Maze::InitialiseSpawners()
{
	// Clear the current spawner array
	m_Spawners.clear();

	// Cycle through every row
	for (auto& row : m_Vertices)
	{
		// Cycle through the column
		for (auto& vertex : row)
		{
			// Is this node a spawner?
			if (vertex.Node().m_Type == mNodeType::Spawn)
			{
				// Is this node not blocked?
				if (!vertex.Blocked())
				{
					// Add this spawner
					m_Spawners.push_back(&vertex);
				}
			}
		}
	}
}

void Maze::InitialiseExit()
{
	// Set the exit to nullptr
	m_Exit = nullptr;

	// Cycle through every row
	for (auto& row : m_Vertices)
	{
		// Cycle through the column
		for (auto& vertex : row)
		{
			// Is this node an exit?
			if (vertex.Node().m_Type == mNodeType::Exit)
			{
				// Is this node not blocked?
				if (!vertex.Blocked())
				{
					// Set the exit node
					m_Exit = &vertex;
					
					// End this function
					return;
				}
			}
		}
	}
}
