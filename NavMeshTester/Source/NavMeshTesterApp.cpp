#include "NavMeshTesterApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <imgui.h>

#include "Maze\MazeGame.h"

#include "Math\Maths.h"

NavMeshTesterApp::NavMeshTesterApp()
{

}

NavMeshTesterApp::~NavMeshTesterApp() {

}

bool NavMeshTesterApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_Game = new MazeGame(&m_Camera, "default.dat");

	m_NavMesh.Position(Vector2(640.f, 360.f));
	m_NavMesh.Size(Vector2(1280.f, 720.f));
	m_NavMesh.Construct();
	m_bDrawAStar = m_bDrawSSFA = m_bDrawNodes = true;
	m_bDrawDijk = false;

	m_Node1 = nullptr;
	m_Node2 = nullptr;

	m_bShowMazeGame = true;

	return true;
}

void NavMeshTesterApp::shutdown() {

	delete m_Game;
	delete m_font;
	delete m_2dRenderer;
}

void NavMeshTesterApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_F1) && !m_Game->IsActive())
	{
		if (m_bShowMazeGame)
		{
			// recenter camera
			m_Camera.m_Position = Vector2((float)getWindowWidth(), (float)getWindowHeight()) * 0.5f;
		}

		m_bShowMazeGame = !m_bShowMazeGame;
	}

	m_Camera.SetSize(getWindowWidth(), getWindowHeight());

	if (m_bShowMazeGame)
	{
		m_Game->Update(deltaTime);
	}
	else
	{
		UpdateNavMesh();
	}

	m_Camera.SetCamera(m_2dRenderer);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void NavMeshTesterApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	Vector2 bl = m_Camera.GetBottomLeft();

	if (m_bShowMazeGame)
	{
		m_Game->Render(m_2dRenderer);

		std::string camstr = std::string("Camera - X: ") + std::to_string(m_Camera.m_Position.x) + std::string(" Y: ") + std::to_string(m_Camera.m_Position.y);

		m_2dRenderer->setRenderColour(1.f, 1.f, 1.f);
	
		if (m_Game->IsActive())
			m_2dRenderer->drawText(m_font, "Press P to Stop", bl.x, bl.y + 36.f);
		else
			m_2dRenderer->drawText(m_font, "Press O to Start", bl.x, bl.y + 36.f);
	}
	else
	{
		DrawNavMesh();
	}

	m_2dRenderer->setRenderColour(1.f, 1.f, 1.f);
	m_2dRenderer->drawText(m_font, "Press F1 to switch modes", bl.x, bl.y);

	// done drawing sprites
	m_2dRenderer->end();
}

void NavMeshTesterApp::UpdateNavMesh()
{
	ImGui::Begin("Help");
	ImGui::Text("Press Left Mouse to add a new vertex");
	ImGui::Text("Press Enter to add your shape");
	ImGui::Text("Press 1 to set start of path");
	ImGui::Text("Press 2 to set end of path");
	ImGui::Text("Press 3 to generate a random path");
	ImGui::Text("Press S to generate path between start and end");
	ImGui::Text("Press C to construct the navmesh");
	ImGui::Text("Press R to clear the navmesh");
	ImGui::Separator();
	ImGui::Checkbox("Draw Nodes", &m_bDrawNodes);
	ImGui::Checkbox("Draw Dijkstra Path", &m_bDrawDijk);
	ImGui::Checkbox("Draw AStar Path", &m_bDrawAStar);
	ImGui::Checkbox("Draw Simple Stupid Funnel Alogrithm", &m_bDrawSSFA);

	aie::Input* input = aie::Input::getInstance();
	Vector2 mousepos((float)input->getMouseX(), (float)input->getMouseY());

	// Add new vertex to shape
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT) &&
		!ImGui::IsMouseHoveringWindow())
	{
		m_CurrentShape.push_back(mousepos);
	}

	// Add current shape to nav mesh
	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		m_NavMesh.Add_Obstacle(m_CurrentShape, 0.f);
		m_CurrentShape.clear();
	}

	// Set first waypoint
	if (input->wasKeyPressed(aie::INPUT_KEY_1))
	{
		m_Node1 = m_NavMesh.Get_Node(mousepos);

		m_DijkPath.clear();
		m_AStarPath.clear();
		m_SSFAPath.clear();
	}

	// Set second waypoint
	if (input->wasKeyPressed(aie::INPUT_KEY_2))
	{
		m_Node2 = m_NavMesh.Get_Node(mousepos);

		m_DijkPath.clear();
		m_AStarPath.clear();
		m_SSFAPath.clear();
	}

	// Generate random path
	if (input->wasKeyPressed(aie::INPUT_KEY_3))
	{
		const std::vector<Node>& nodes = m_NavMesh.Get_Nodes();

		if (!nodes.empty())
		{
			m_Node1 = &nodes[rand() % nodes.size()];
			m_Node2 = &nodes[rand() % nodes.size()];

			m_DijkPath = m_NavMesh.Dijkstra(*m_Node1, *m_Node2);
			m_AStarPath = m_NavMesh.AStar(*m_Node1, *m_Node2, NavMesh::EuclideanDistance, 2.f);
			m_SSFAPath = m_NavMesh.Smooth(m_AStarPath);
		}
	}

	// Link current waypoints
	if (input->wasKeyPressed(aie::INPUT_KEY_S))
	{
		if (m_Node1 != nullptr && m_Node2 != nullptr)
		{
			m_DijkPath = m_NavMesh.Dijkstra(*m_Node1, *m_Node2);
			m_AStarPath = m_NavMesh.AStar(*m_Node1, *m_Node2, NavMesh::EuclideanDistance, 2.f);
			m_SSFAPath = m_NavMesh.Smooth(m_AStarPath);
		}
	}

	// Clear the navmesh
	if (input->wasKeyPressed(aie::INPUT_KEY_R))
	{
		m_NavMesh.Clear();
		m_Node1 = nullptr;
		m_Node2 = nullptr;
		m_DijkPath.clear();
		m_AStarPath.clear();
		m_SSFAPath.clear();
		m_NavMesh.Construct();
	}

	// Construct navmesh
	if (input->wasKeyPressed(aie::INPUT_KEY_C))
	{
		m_Node1 = nullptr;
		m_Node2 = nullptr;
		m_DijkPath.clear();
		m_AStarPath.clear();
		m_SSFAPath.clear();
		m_NavMesh.Construct();
	}

	ImGui::End();
}

void NavMeshTesterApp::DrawNavMesh()
{
	// Draw start of path
	if (m_Node1 != nullptr)
	{
		m_2dRenderer->setRenderColour(1.f, 0.f, 1.f);
		m_2dRenderer->drawCircle(m_Node1->Position().x, m_Node1->Position().y, 10.f);
	}

	// Draw end of path
	if (m_Node2 != nullptr)
	{
		m_2dRenderer->setRenderColour(0.f, 1.f, 1.f);
		m_2dRenderer->drawCircle(m_Node2->Position().x, m_Node2->Position().y, 10.f);
	}

	// Draw dijkstra
	if (m_bDrawDijk && !m_DijkPath.empty())
	{
		m_2dRenderer->setRenderColour(1.f, 1.f, 0.f);
		for (size_t i = 0; i < m_DijkPath.size() - 1; ++i)
		{
			const Vector2& p1 = m_DijkPath[i]->Position();
			const Vector2& p2 = m_DijkPath[i + 1]->Position();

			m_2dRenderer->drawLine(p1.x, p1.y, p2.x, p2.y, 5.f, 1);
		}
	}

	// Draw AStar
	if (m_bDrawAStar && !m_AStarPath.empty())
	{
		m_2dRenderer->setRenderColour(0.8f, 0.2f, 0.5f);
		for (size_t i = 0; i < m_AStarPath.size() - 1; ++i)
		{
			const Vector2& p1 = m_AStarPath[i]->Position();
			const Vector2& p2 = m_AStarPath[i + 1]->Position();

			m_2dRenderer->drawLine(p1.x, p1.y, p2.x, p2.y, 5.f, 1);
		}
	}

	// Draw SmoothPath
	if (m_bDrawSSFA && !m_SSFAPath.empty())
	{
		m_2dRenderer->setRenderColour(0.f, 1.f, 0.f);
		for (size_t i = 0; i < m_SSFAPath.size() - 1; ++i)
		{
			const Vector2& p1 = m_SSFAPath[i];
			const Vector2& p2 = m_SSFAPath[i + 1];

			m_2dRenderer->drawLine(p1.x, p1.y, p2.x, p2.y, 5.f);
		}
	}

	// Draw nodes
	if (m_bDrawNodes)
	{
		m_2dRenderer->setRenderColour(1.f, 1.f, 0.f);
		for (auto& node : m_NavMesh.Get_Nodes())
		{
			m_2dRenderer->drawLine(node.Vertices()[0].x, node.Vertices()[0].y, node.Vertices()[1].x, node.Vertices()[1].y);
			m_2dRenderer->drawLine(node.Vertices()[1].x, node.Vertices()[1].y, node.Vertices()[2].x, node.Vertices()[2].y);
			m_2dRenderer->drawLine(node.Vertices()[2].x, node.Vertices()[2].y, node.Vertices()[0].x, node.Vertices()[0].y);
		}
	}

	// Draw current shape
	m_2dRenderer->setRenderColour(0.2f, 0.8f, 0.8f);
	for (int i = 0; i != m_CurrentShape.size(); ++i)
	{
		m_2dRenderer->setRenderColour(0.2f, 0.8f, 0.8f);

		if (i == m_CurrentShape.size() - 1)
		{
			m_2dRenderer->drawLine(m_CurrentShape[i].x, m_CurrentShape[i].y, m_CurrentShape[0].x, m_CurrentShape[0].y, 5.f, 1);
		}
		else
		{
			m_2dRenderer->drawLine(m_CurrentShape[i].x, m_CurrentShape[i].y, m_CurrentShape[i + 1].x, m_CurrentShape[i + 1].y, 5.f, 1);
		}
	}

	// Draw obstacles
	m_2dRenderer->setRenderColour(1.f, 0.f, 0.f);
	for (auto& obstacle : m_NavMesh.Get_Obstacles())
	{
		const std::vector<Vector2>& verts = obstacle.Vertices();

		for (int i = 0; i != verts.size(); ++i)
		{
			if (i == verts.size() - 1)
			{
				m_2dRenderer->drawLine(verts[i].x, verts[i].y, verts[0].x, verts[0].y, 5.f);
			}
			else
			{
				m_2dRenderer->drawLine(verts[i].x, verts[i].y, verts[i + 1].x, verts[i + 1].y, 5.f);
			}
		}
	}
}

void NavMeshTesterApp::movecamera(float deltaTime, float a_Speed)
{
	// get the cameras position
	Vector2 pos;
	m_2dRenderer->getCameraPos(pos.x, pos.y);

	// get access to inputs
	auto input = aie::Input::getInstance();

	// calculate frame speed
	float fspeed = a_Speed * deltaTime;

	// Move the camera according to keys pressed
	if (input->isKeyDown(aie::INPUT_KEY_W))
		pos.y += fspeed;
	if (input->isKeyDown(aie::INPUT_KEY_S))
		pos.y -= fspeed;
	if (input->isKeyDown(aie::INPUT_KEY_A))
		pos.x -= fspeed;
	if (input->isKeyDown(aie::INPUT_KEY_D))
		pos.x += fspeed;

	// set the cameras position
	m_2dRenderer->setCameraPos(pos.x, pos.y);
}

Vector2 NavMeshTesterApp::getmouseposition() const
{
	// get the cameras position
	Vector2 cpos;
	m_2dRenderer->getCameraPos(cpos.x, cpos.y);

	// get access to inputs
	auto input = aie::Input::getInstance();

	// get mouse pos
	Vector2 mpos((float)input->getMouseX(), (float)input->getMouseY());

	// add and return pos
	return cpos + mpos;
}
