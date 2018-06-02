#pragma once

#include "Application.h"
#include "Renderer2D.h"

class MazeGame;

#include "Camera.h"
#include "NavMesh\NavMesh2D.h"
#include "NavMesh\NavMeshHeuristics.h"

using namespace NavMesh;

class NavMeshTesterApp : public aie::Application {
public:

	NavMeshTesterApp();
	virtual ~NavMeshTesterApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void UpdateNavMesh();
	void DrawNavMesh();

	void movecamera(float deltaTime, float a_Speed);

	Vector2 getmouseposition() const;

protected:

	MazeGame* m_Game;
	NavMesh2D m_NavMesh;

	// For Navmesh
	const Node* m_Node1;
	const Node* m_Node2;
	std::vector<Node*> m_DijkPath;
	std::vector<Node*> m_AStarPath;
	std::vector<Vector2> m_SSFAPath;
	std::vector<Vector2> m_CurrentShape;
	bool m_bDrawDijk, m_bDrawAStar, m_bDrawSSFA, m_bDrawNodes;

	bool m_bShowMazeGame;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	Camera m_Camera;
};