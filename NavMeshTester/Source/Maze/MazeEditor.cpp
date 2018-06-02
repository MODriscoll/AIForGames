#include "Maze\MazeEditor.h"

#include <imgui.h>
#include <Renderer2D.h>

#include <cassert>

#include "Math\Maths.h"
#include "Camera.h"

using node = Maze::node;

using button = Input_Button_ID;
using key = Input_Key_ID;

MazeEditor::MazeEditor(Maze* a_Maze, Camera* a_Camera)
	: m_Maze(a_Maze), m_Camera(a_Camera), m_CameraSpeed(100.f), m_keUp(key::Key_Up), m_keDown(key::Key_Down), m_keLeft(key::Key_Left), m_keRight(key::Key_Right), m_keFocus(key::Key_F),
	m_buSelect(button::Mouse_Left), m_buBlock(button::Mouse_Right), buf_Name(), buf_Matrix({ 0, 0 }), buf_Position({ 0.f, 0.f }), buf_Size({ 0.f, 0.f }), 
	m_Node(nullptr), m_Path(), m_NodeTypeIndex(0), m_SpawnTypeIndex(0)
{
	// Assert if maze or camera is nullptr
	assert(m_Maze != nullptr && m_Camera != nullptr && "Editor requires maze and camera");

	// Set the name buffer to maze's name
	//a_Maze->Name().copy(buf_Name.data(), buf_Name.size());
	memcpy(buf_Name.data(), a_Maze->Name().data(), a_Maze->Name().size() * sizeof(char));

	// Set the matrix buffer to maze's structure
	buf_Matrix[0] = a_Maze->Width();
	buf_Matrix[1] = a_Maze->Height();

	// Get the position and size of maze
	const Vector2& Position = a_Maze->Position();
	const Vector2& Size = a_Maze->Size();

	// Set the position buffer to maze's position
	buf_Position[0] = Position.x;
	buf_Position[1] = Position.y;

	// Set the size buffer to maze's size
	buf_Size[0] = Size.x;
	buf_Size[1] = Size.y;

	// Set the modifiers buffer to maze's modifiers
	buf_Modifiers = a_Maze->Modifiers();
}

void MazeEditor::Update(float deltaTime)
{
	// Update the camera
	UpdateCamera(deltaTime);

	// Prepare the menu
	ImGui::Begin("Editor");

	// First, update the editing tools
	UpdateEditing(deltaTime);

	// Second, update the grids menu
	UpdateGridMenu(deltaTime);

	// Last, update the nodes menu
	UpdateNodeMenu(deltaTime);

	// Conclude the menu
	ImGui::End();
}

void MazeEditor::Render(aie::Renderer2D* renderer)
{
	// Draw the grid
	DrawGrid(renderer);

	// Draw the nodes
	DrawNodes(renderer);

	// Draw the selected node
	DrawSelectedNode(renderer);
}

node* MazeEditor::GetSelectedNode()
{
	// Return the selected node
	return m_Node;
}

void MazeEditor::RenderPath(aie::Renderer2D* renderer, const Maze::path& a_Path)
{
	// Is path empty?
	if (a_Path.empty())
	{
		// End this function
		return;
	}

	// Get the size of the path
	size_t Size = a_Path.size() - 1;

	// Set the current index to 0
	size_t Index = 0;

	// Get the scaled length of the size of a node
	float Mag = m_Maze->NodeSize().Magnitude() * 0.25f;

	// Set the render colour
	renderer->setRenderColour(0.5f, 1.f, 0.f);

	// Repeat until index matches size
	while (Index < Size)
	{
		// Get reference to current point and next point
		const Vector2& Cur = a_Path[Index++]->Node().Position();
		const Vector2& Nex = a_Path[Index]->Node().Position();

		// Draw circles representing the points
		renderer->drawCircle(Cur.x, Cur.y, Mag, 1.f);
		renderer->drawCircle(Nex.x, Nex.y, Mag, 1.f);

		// Draw a line between the points
		renderer->drawLine(Cur.x, Cur.y, Nex.x, Nex.y, 5.f, 0.f);
	}
}

void MazeEditor::RenderFlowField(aie::Renderer2D* renderer, const Maze::field& a_Field, bool a_bDrawBlocked)
{
	// Is field empty?
	if (a_Field.empty() || a_Field.front().empty())
	{
		// End this function
		return;
	}

	// Get the nodes from the maze
	const Maze::Matrix& Nodes = m_Maze->Nodes();

	// Get the size of a node
	Vector2 Size = m_Maze->NodeSize();

	// Get the scaled length of the size
	float SMag = Size.Magnitude() * 0.25f;

	// Scale the length again
	float HSMag = SMag * 0.5f;

	// Get width and height of the grid
	size_t Width = m_Maze->Width();
	size_t Height = m_Maze->Height();

	// Get half of pi ( set as static since it will always be used )
	static const float hpi = pif * 0.5f;

	// Set the render colour
	renderer->setRenderColour(0.5f, 0.5f, 0.5f);

	// Cycle through the row
	for (size_t i = 0; i < Width; ++i)
	{
		// Get reference to this rows vertices
		const Maze::Vertices& Verts = Nodes[i];

		// Cycle through the vertices
		for (size_t j = 0; j < Height; ++j)
		{
			// Skip if we are ignoring blocked vertices
			// and this node is also blocked
			if (Verts[j].Blocked() && !a_bDrawBlocked)
				continue;

			// Get reference this nodes position
			const Vector2& NPos = Verts[j].Node().Position();

			// Get reference to the flow fields direction
			const Vector2& FDir = a_Field[i][j];

			// Get the rotation from the direction
			float Rot = atan2f(FDir.y, FDir.x);

			// Draw an arrow to represent this node
			renderer->drawArrowFromPoint(NPos.x, NPos.y, SMag, Rot, hpi, HSMag, 5.f, 1.f);
		}
	}
}

void MazeEditor::SetMaze(Maze* a_Maze)
{
	// Set the maze
	m_Maze = a_Maze;

	// Assert if maze was set to nullptr
	assert(m_Maze != nullptr && "Editor requires maze");

	// Set the name buffer to maze's name
	//m_Maze->Name().copy(buf_Name.data(), buf_Name.size());
	memcpy(buf_Name.data(), a_Maze->Name().data(), a_Maze->Name().size() * sizeof(char));

	// Set the matrix buffer to maze's structure
	buf_Matrix[0] = m_Maze->Width();
	buf_Matrix[1] = m_Maze->Height();

	// Get the position and size of maze
	const Vector2& Position = m_Maze->Position();
	const Vector2& Size = m_Maze->Size();

	// Set the position buffer to maze's position
	buf_Position[0] = Position.x;
	buf_Position[1] = Position.y;

	// Set the size buffer to maze's size
	buf_Size[0] = Size.x;
	buf_Size[1] = Size.y;

	// Set the modifiers buffer to maze's modifiers
	buf_Modifiers = m_Maze->Modifiers();

	// Set selected node to nullptr
	m_Node = nullptr;
}

void MazeEditor::SetCamera(Camera* a_Camera)
{
	// Set the camera
	m_Camera = a_Camera;

	// Assert if camera was set to nullptr
	assert(m_Camera != nullptr && "Editor requires camera");
}

void MazeEditor::SetCameraSpeed(float a_Speed)
{
	// Set the camera speed
	m_CameraSpeed = a_Speed;
}

void MazeEditor::SetUpKey(key a_keUp)
{
	// Set the up key
	m_keUp = a_keUp;
}

void MazeEditor::SetDownKey(key a_keDown)
{
	// Set the down key
	m_keDown = a_keDown;
}

void MazeEditor::SetLeftKey(key a_keLeft)
{
	// Set the left key
	m_keLeft = a_keLeft;
}

void MazeEditor::SetRightKey(key a_keRight)
{
	// Set the right key
	m_keRight = a_keRight;
}

void MazeEditor::SetFocusKey(key a_keFoucus)
{
	// Set the focus key
	m_keFocus = a_keFoucus;
}

void MazeEditor::SetCameraControls(key a_keUp, key a_keDown, key a_keLeft, key a_keRight)
{
	// Set all the keys
	m_keUp = a_keUp;
	m_keDown = a_keDown;
	m_keLeft = a_keLeft;
	m_keRight = a_keRight;
}

void MazeEditor::SetSelectButton(button a_buSelect)
{
	// Set the select button
	m_buSelect = a_buSelect;
}

void MazeEditor::SetBlockButton(button a_buBlock)
{
	// Set the block button
	m_buBlock = a_buBlock;
}

void MazeEditor::SetEditingControls(button a_buSelect, button a_buBlock)
{
	// Set all the buttons
	m_buSelect = a_buSelect;
	m_buBlock = a_buBlock;
}

Maze* MazeEditor::GetMaze()
{
	// Return the maze
	return m_Maze;
}

Camera* MazeEditor::GetCamera()
{
	// Return the camera
	return m_Camera;
}

float MazeEditor::GetCameraSpeed() const
{
	// Return the camera speed
	return m_CameraSpeed;
}

key MazeEditor::GetUpKey() const
{
	// Return this key
	return m_keUp;
}

key MazeEditor::GetDownKey() const
{
	// Return this key
	return m_keDown;
}

key MazeEditor::GetLeftKey() const
{
	// Return this key
	return m_keLeft;
}

key MazeEditor::GetRightKey() const
{
	// Return this key
	return m_keRight;
}

key MazeEditor::GetFocusKey() const
{
	// Return this key
	return m_keFocus;
}

void MazeEditor::GetCameraControls(key& out_keUp, key& out_keDown, key& out_keLeft, key& out_keRight) const
{
	// Return all of the controls
	out_keUp = m_keUp;
	out_keDown = m_keDown;
	out_keLeft = m_keLeft;
	out_keRight = m_keRight;
}

button MazeEditor::GetSelectButton() const
{
	// Return this button
	return m_buSelect;
}

button MazeEditor::GetBlockButton() const
{
	// Return this button
	return m_buBlock;
}

void MazeEditor::GetEditingControls(button& out_buSelect, button& out_buBlock)
{
	// Return all of the controls
	out_buSelect = m_buSelect;
	out_buBlock = m_buBlock;
}

void MazeEditor::UpdateCamera(float deltaTime)
{
	// Get reference to camera position
	Vector2& Pos = m_Camera->m_Position;

	// Get access to inputs
	auto input = InputLibrary::Instance();

	// Calculate speed for this frame
	float spd = m_CameraSpeed * deltaTime;

	// Move camera based on keys
	if (input->IsKeyDown(m_keUp))
		Pos.y += spd;
	if (input->IsKeyDown(m_keDown))
		Pos.y -= spd;
	if (input->IsKeyDown(m_keLeft))
		Pos.x -= spd;
	if (input->IsKeyDown(m_keRight))
		Pos.x += spd;

	// Was the focus key pressed?
	if (input->WasKeyPressed(m_keFocus))
	{
		// Set the camera position to maze's position
		Pos = m_Maze->Position();
	}
}

void MazeEditor::UpdateEditing(float deltaTime)
{
	// Is the mouse over the menu?
	if (ImGui::IsRootWindowOrAnyChildHovered() || ImGui::IsWindowHovered())
	{
		// End this function
		return;
	}

	// Get reference to mouse position
	Vector2& Pos = MousePosition(m_Camera->GetBottomLeft());

	// Get access to inputs
	auto input = InputLibrary::Instance();

	// Was the select button pressed?
	if (input->WasButtonPressed(m_buSelect))
	{
		// Request and capture the node containing this point
		m_Node = m_Maze->Node(Pos);

		// Set the type indexes
		IndexTypes();

		// Stringify the index
		IndexString();

		// Stringify the connections
		ConnectionsString();
	}

	// Was the block button pressed?
	if (input->WasButtonPressed(m_buBlock))
	{
		// Request and capture the node containing this point
		m_Node = m_Maze->Node(Pos);

		// Was the node found?
		if (m_Node != nullptr)
		{
			// Inverse this nodes blocked status
			m_Node->Block(!(m_Node->Blocked()));
		}

		// Set the type indexes
		IndexTypes();

		// Stringify the index
		IndexString();

		// Stringify the connections
		ConnectionsString();
	}

	// Get the scroll of mouse wheel
	float Scroll = static_cast<float>(input->GetMouseScroll());

	// Was the mouse wheel used?
	if (Scroll != 0.f)
	{
		// Calculate how much to scale by
		float Scale = 100.f * Scroll;

		// Scale the size of the maze
		buf_Size[0] += Scale;
		buf_Size[1] += Scale;

		// Set the size of the maze
		m_Maze->Size(Vector2(buf_Size[0], buf_Size[1]));
	}
}

void MazeEditor::UpdateGridMenu(float deltaTime)
{
	ImGui::Text("Press O to Start");
	ImGui::Text("Press P to Stop");

	// Start with initial separator
	ImGui::Separator();

	// Draw info on next tool
	ImGui::Text("The name of this maze");

	// Allow for editing of the name
	// Keep range with max name length
	ImGui::InputText("Name", buf_Name.data(), buf_Name.size());

	// Create some space
	ImGui::Spacing();

	// Draw info on next tool
	ImGui::Text("The amount of rows and columns of the maze");

	// Allow for editing of the grid
	ImGui::InputInt2("Matrix", buf_Matrix.data());

	// Create some space
	ImGui::Spacing();

	// Draw info on the next tool
	ImGui::Text("The position of the maze");

	// Allow for editing of the size
	ImGui::InputFloat2("Position", buf_Position.data());

	// Create some space
	ImGui::Spacing();

	// Draw info on the next tool
	ImGui::Text("The size of the maze");

	// Allow for editing of the size
	ImGui::InputFloat2("Size", buf_Size.data());

	// Create some space
	ImGui::Spacing();

	// Draw info on the next tool
	ImGui::Text("Set the modifier for linking");

	// Allow for editing of each modifier
	ImGui::InputFloat("Up", &buf_Modifiers[0]);
	ImGui::InputFloat("Up Right", &buf_Modifiers[1]);
	ImGui::InputFloat("Right", &buf_Modifiers[2]);
	ImGui::InputFloat("Down Right", &buf_Modifiers[3]);
	ImGui::InputFloat("Down", &buf_Modifiers[4]);
	ImGui::InputFloat("Down Left", &buf_Modifiers[5]);
	ImGui::InputFloat("Left", &buf_Modifiers[6]);
	ImGui::InputFloat("Up Left", &buf_Modifiers[7]);

	// Create some space
	ImGui::Spacing();

	// Was the set name button pressed?
	if (ImGui::Button("Set Name"))
	{
		// Set the name
		m_Maze->Name(std::string(buf_Name.begin(), buf_Name.end()));
	}

	// Was the set matrix button pressed?
	if (ImGui::Button("Set Matrix"))
	{
		// Is there a selected node?
		if (m_Node != nullptr)
		{
			// Declare variables to capture index
			size_t x, y;

			// Get this nodes index
			m_Maze->NodeIndex(m_Node, x, y);

			// Will this node no longer be in range?
			if (!((x < (size_t)buf_Matrix[0]) && (y < (size_t)buf_Matrix[1])))
			{
				// Set selected node to nullptr
				m_Node = nullptr;
			}
		}

		m_Node = nullptr;

		// Resize the maze
		m_Maze->Resize(buf_Matrix[0], buf_Matrix[1]);
	}

	// Was the set position button pressed?
	if (ImGui::Button("Set Position"))
	{
		// Reposition the maze
		m_Maze->Position(Vector2(buf_Position[0], buf_Position[1]));
	}

	// Was the set size button pressed?
	if (ImGui::Button("Set Size"))
	{
		// Resize the maze
		m_Maze->Size(Vector2(buf_Size[0], buf_Size[1]));
	}

	// Was the construct button pressed?
	if (ImGui::Button("Construct"))
	{
		// Construct the maze
		m_Maze->Construct(buf_Modifiers);
	}

	// Create some space
	ImGui::Spacing();

	// Draw info on next tool
	ImGui::Text("Path to save this maze as ( don't set file type )");

	// Allow for editing of the name
	// Keep range with max name length
	ImGui::InputText("Path", m_Path.data(), m_Path.size());

	// Was the save button pressed?
	if (ImGui::Button("Save"))
	{
		// Get the path as a string
		std::string SPath(m_Path.begin(), std::find(m_Path.begin(), m_Path.end(), '\0'));

		// Add the file type to the end
		SPath += ".dat";

		// Save this maze
		m_Maze->Save(SPath);

		// Un-select node
		m_Node = nullptr;
	}

	// Was the load button pressed?
	if (ImGui::Button("Load"))
	{
		// Get the path as a string
		std::string LPath(m_Path.begin(), std::find(m_Path.begin(), m_Path.end(), '\0'));

		// Add the file type to the end
		LPath += ".dat";

		// Load this maze
		m_Maze->Load(LPath);

		// Re-set this maze
		SetMaze(m_Maze);
	}

	// Create some space
	ImGui::Spacing();

	// End with a seperator
	ImGui::Separator();
}

void MazeEditor::UpdateNodeMenu(float deltaTime)
{
	// Is there no selected node?
	if (m_Node == nullptr)
	{
		// End this function
		return;
	}

	// Create some space
	ImGui::Spacing();

	// Draw the index of the string
	ImGui::Text(m_NodeIndex.c_str());

	// Create some space
	ImGui::Spacing();

	// Draw info on the next tool
	ImGui::Text("Set the weight of this node");

	// Allow for editing of the node's weight
	ImGui::InputFloat("Weight", &m_Node->Weight());

	// Create some space
	ImGui::Spacing();

	// Draw info on the next tool
	ImGui::Text("Set if this node will not be traversable");

	// Get if this node is blocked or not
	bool Blo = m_Node->Blocked();

	// Allow for editing of node's blocked status
	ImGui::Checkbox("Blocked", &Blo);

	// Set this node's blocked status
	m_Node->Block(Blo);

	// Create some space
	ImGui::Spacing();

	// Get reference to maze node
	MazeNode& Ref = m_Node->Node();

	// Draw info on the next tool
	ImGui::Text("Set the type of this node");

	// Allow for selection of the node's type
	ImGui::ListBox("Type", &m_NodeTypeIndex, m_NodeTypes.data(), static_cast<int>(m_NodeTypes.size()));

	// Set the nodes type
	Ref.Type(GetNodeType(m_NodeTypeIndex));

	// Is the type set to spawn?
	if (m_NodeTypeIndex == GetNodeType(mNodeType::Spawn))
	{
		// Create some space
		ImGui::Spacing();

		// Draw info on next tool
		ImGui::Text("Set the spawn type of this node");

		// Allow for selection of the node's spawn type
		ImGui::ListBox("Spawns", &m_SpawnTypeIndex, m_SpawnTypes.data(), static_cast<int>(m_SpawnTypes.size()));

		// Set the nodes spawn type
		Ref.Spawns(GetSpawnType(m_SpawnTypeIndex));
	}

	// Create some space
	ImGui::Spacing();

	// Cycle through the connection strings
	for (auto& info : m_NodeConnections)
	{
		// Print the info of this edge
		ImGui::Text(info.c_str());
	}

	// End with a seperator
	ImGui::Separator();
}

void MazeEditor::DrawGrid(aie::Renderer2D* renderer)
{
	// Get the position and size of the maze
	const Vector2 MPos = m_Maze->Position();
	const Vector2 MSize = m_Maze->Size();

	// Calculate the upper right corner of the grid
	Vector2 URPos = MPos + MSize;

	// Get the size of a node
	Vector2 NSize = m_Maze->NodeSize();

	// Set the render colour
	renderer->setRenderColour(0.f, 0.f, 1.f);

	// Cycle through rows
	for (size_t i = 0; i <= m_Maze->Width(); ++i)
	{
		// Get the level to draw at
		float XLevel = MPos.x + (NSize.x * static_cast<float>(i));

		// Draw the vertical line
		renderer->drawLine(XLevel, MPos.y, XLevel, URPos.y, 5.f, 3.f);
	}

	// Cycle through columns
	for (size_t i = 0; i <= m_Maze->Height(); ++i)
	{
		// Get the level to draw at
		float YLevel = MPos.y + (NSize.y * static_cast<float>(i));

		// Draw the vertical line
		renderer->drawLine(MPos.x, YLevel, URPos.x, YLevel, 5.f, 3.f);
	}
}

void MazeEditor::DrawNodes(aie::Renderer2D* renderer)
{
	// Get a reference to the grid
	const Maze::Matrix& Nodes = m_Maze->Nodes();

	// Get the size of a node
	Vector2 NSize = m_Maze->NodeSize();

	// Cycle through rows
	for (size_t i = 0; i < Nodes.size(); ++i)
	{
		// Get reference to column
		const Maze::Vertices& col = Nodes[i];

		// Cycle through the column
		for (size_t j = 0; j < col.size(); ++j)
		{
			// Get reference to maze node
			const MazeNode& ref = col[j].Node();

			// Get the center of this node
			const Vector2& pos = ref.Position();

			// Set the colour to red if node is blocked
			renderer->setRenderColour(col[j].Blocked() ? 0xFF0000FF : NodeColour(ref));

			// Draw this node
			renderer->drawBox(pos.x, pos.y, NSize.x, NSize.y, 0.f, 4.f);
		}
	}
}

void MazeEditor::DrawSelectedNode(aie::Renderer2D* renderer)
{
	// Is there no selected node?
	if (m_Node == nullptr)
	{
		// End this function
		return;
	}

	// Get the node's position and size
	const Vector2& NPos = m_Node->Node().Position();
	Vector2 FSize = m_Maze->NodeSize();

	// Get half the size of the node
	Vector2 HSize = FSize * 0.5f;

	// Set the render colour to green
	renderer->setRenderColour(0.f, 1.f, 0.f);

	// Highligh this node by outlining it
	renderer->drawLine(NPos.x - HSize.x, NPos.y + HSize.y, NPos.x + HSize.x, NPos.y + HSize.y, 5.f, 2.f);
	renderer->drawLine(NPos.x + HSize.x, NPos.y + HSize.y, NPos.x + HSize.x, NPos.y - HSize.y, 5.f, 2.f);
	renderer->drawLine(NPos.x + HSize.x, NPos.y - HSize.y, NPos.x - HSize.x, NPos.y - HSize.y, 5.f, 2.f);
	renderer->drawLine(NPos.x - HSize.x, NPos.y - HSize.y, NPos.x - HSize.x, NPos.y + HSize.y, 5.f, 2.f);

	// Set the render colour to yellow
	renderer->setRenderColour(1.f, 1.f, 0.f);

	// Get half of pi ( set as static since it will always be used
	static const float hpi = pif * 0.5f;

	// Get the scaled value of the node's magnitude
	float SMag = m_Maze->NodeSize().Magnitude() * 0.2f;

	// Cycle through this nodes connections
	for (auto& edge : m_Node->Connections())
	{
		// Get reference to the destinations position
		const Vector2& DPos = edge.first->Node().Position();

		// Draw an arrow from the selected node to its neighbour
		renderer->drawArrowToPoint(NPos.x, NPos.y, DPos.x, DPos.y, hpi, SMag, 5.f, 1.f);
	}
}

Vector2 MazeEditor::MousePosition(const Vector2& a_CameraPosition) const
{
	// Get access to inputs
	auto input = InputLibrary::Instance();

	// Get the mouse position
	Vector2 MousePos(static_cast<float>(input->GetMouseX()), static_cast<float>(input->GetMouseY()));

	// Add the mouse position to the camera position and return
	return a_CameraPosition + MousePos;
}

void MazeEditor::IndexTypes()
{
	// Was the node found?
	if (m_Node != nullptr)
	{
		// Set the index of the node and spawn type
		m_NodeTypeIndex = GetNodeType(m_Node->Node().Type());
		m_SpawnTypeIndex = GetSpawnType(m_Node->Node().Spawns());
	}
	else
	{
		// Default the index
		m_NodeTypeIndex = 0;
		m_SpawnTypeIndex = 0;
	}
}

void MazeEditor::IndexString()
{
	// Was the node found?
	if (m_Node != nullptr)
	{
		// Create variables to capture index
		size_t x, y;

		// Get this node's index
		m_Maze->NodeIndex(m_Node, x, y);

		// Clear the current string
		m_NodeIndex.clear();

		// Add initial text
		m_NodeIndex += "Node Index - X: ";

		// Convert X index to string and add it
		m_NodeIndex += std::to_string(x);

		// Add spacing text
		m_NodeIndex += " Y: ";

		// Convert Y index to string and add it
		m_NodeIndex += std::to_string(y);
	}
	else
	{
		// Clear the index string
		m_NodeIndex.clear();
	}
}

void MazeEditor::ConnectionsString()
{
	// Clear the connections vector
	m_NodeConnections.clear();

	// Was the node found?
	if (m_Node != nullptr)
	{
		// Get reference to this node's connections
		const Maze::City::Edges& Connections = m_Node->Connections();

		// Are there no connections?
		if (Connections.empty())
		{
			// End this function
			return;
		}

		// Set first string of connections to inform how many links there are
		m_NodeConnections.push_back(std::string("Total connections: ") + std::to_string(Connections.size()));

		// Cycle through the connections
		for (auto& edge : Connections)
		{
			// Get reference to destinations position
			const Vector2& Pos = edge.first->Node().Position();

			// Get reference to edges weight
			const float& Wei = edge.second;

			// Start the string informing start position
			std::string Info("Links to ( ");

			// Add the X position of the destination
			Info += std::to_string(static_cast<int>(Pos.x));

			// Continue with info
			Info += " , ";

			// Add the Y position of the destination
			Info += std::to_string(static_cast<int>(Pos.y));

			// Continue with info
			Info += " ) with a weight of ";

			// Add the weight of the edge
			Info += std::to_string(Wei);

			// Add this string to the vector
			m_NodeConnections.push_back(Info);
		}
	}
}

size_t MazeEditor::NodeColour(const MazeNode& a_Node)
{
	// Get reference to nodes type and spawn type
	const mNodeType& NType = a_Node.Type();
	const mSpawnType& SType = a_Node.Spawns();

	// Switch based on nodes type
	switch (NType)
	{
		// Is this node of default type?
		case mNodeType::Default:
		{
			// Return black
			return 0x000000FF;
		}
		// Is this node of spawn type?
		case mNodeType::Spawn:
		{
			// Return purple
			return 0xFF0FFFFF;
		}
		case mNodeType::Exit:
		{
			// Return orange
			return 0xFF8000FF;
		}
		default:
		{

		}
	}

	// Return white
	return 0xFFFFFFFF;
}
