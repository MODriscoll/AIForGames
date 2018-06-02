#include "Editors\NavMeshEditor.h"

#include <Renderer2D.h>

namespace NavMesh
{
	void NavMeshEditor::SetPosition(Mesh* a_Mesh, const Vector2& a_Position)
	{
		// Set the position of the mesh
		a_Mesh->Position(a_Position);
	}

	void NavMeshEditor::SetSize(Mesh* a_Mesh, const Vector2& a_Size)
	{
		// Set the size of the mesh
		a_Mesh->Size(a_Size);
	}

	void NavMeshEditor::AddObstacle(Mesh* a_Mesh, float a_Padding)
	{
		// Is the obstacle invalid?
		if (m_CObstacle.size() < 3)
		{
			// End this function
			return;
		}

		// temp
		for (auto& p : a_Mesh->Get_Points())
		{
			if (!ValidateObstacle(p))
			{
				m_CObstacle.clear();
				return;
			}
		}

		// Add the obstacle to the mesh
		a_Mesh->Add_Obstacle(m_CObstacle, a_Padding);

		// Clear the current obstacle
		ClearObstacle();
	}

	void NavMeshEditor::AddPoint(Mesh* a_Mesh, const Vector2& a_Point)
	{
		// Validate this point
		if (ValidateAll(a_Mesh, a_Point))
		{
			// Add this point
			a_Mesh->Add_Point(a_Point);
		}
	}

	void NavMeshEditor::AddPointToObstacle(Mesh* a_Mesh, const Vector2& a_Point)
	{
		// Validate this point
		if (ValidateAll(a_Mesh, a_Point))
		{
			// Add this point to the current obstacle
			m_CObstacle.push_back(a_Point);
		}
	}

	void NavMeshEditor::Construct(Mesh* a_Mesh)
	{
		// Construct the mesh
		a_Mesh->Construct();
	}

	void NavMeshEditor::ClearMesh(Mesh* a_Mesh)
	{
		// Clear the mesh
		a_Mesh->Clear();
	}

	void NavMeshEditor::ClearObstacles(Mesh* a_Mesh)
	{
		// Clear the meshes obstacles
		a_Mesh->Clear_Obstacles();
	}

	void NavMeshEditor::ClearPoints(Mesh * a_Mesh)
	{
		// Clear the meshes points
		a_Mesh->Clear_Points();
	}

	void NavMeshEditor::ClearObstacle()
	{
		// Clear the current obstacle
		m_CObstacle.clear();
	}

	void NavMeshEditor::Render(aie::Renderer2D* renderer, Mesh* a_Mesh, const Vector2& a_MousePos)
	{
		// Draw the mesh
		DrawBoundary(renderer, a_Mesh);
		DrawNodes(renderer, a_Mesh);
		DrawObstacles(renderer, a_Mesh);
		DrawPoints(renderer, a_Mesh);
		DrawCurrentObstacle(renderer, a_MousePos);
	}

	bool NavMeshEditor::ValidateAll(Mesh* a_Mesh, const Vector2& a_Point)
	{
		// Return result of all validations
		return ValidateRange(a_Mesh, a_Point) && ValidateObstacles(a_Mesh, a_Point) && ValidatePoints(a_Mesh, a_Point);
	}

	bool NavMeshEditor::ValidateRange(Mesh * a_Mesh, const Vector2 & a_Point)
	{
		// Get meshes position and size
		const Vector2& Position = a_Mesh->Position();
		const Vector2& Size = a_Mesh->Size();

		// Get the meshes half exents
		Vector2 Half = Size * 0.5f;

		// Is the point within the meshes X axis?
		if (a_Point.x > (Position.x - Half.x) && a_Point.x < (Position.x + Half.x))
		{
			// Is the point within the meshes Y axis?
			if (a_Point.y > (Position.y - Half.y) && a_Point.y < (Position.y + Half.y))
			{
				// Return valid point
				return true;
			}
		}

		// Return invalid point
		return false;
	}

	bool NavMeshEditor::ValidateObstacles(Mesh* a_Mesh, const Vector2 & a_Point)
	{
		// Get the meshes obstalces
		const std::vector<Obstacle>& Obstacles = a_Mesh->Get_Obstacles();

		// Cycle through each obstalce
		for (auto& o : Obstacles)
		{
			// Get the padded vertices
			auto PVerts = o.GetPaddedVertices();

			// https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
			int i, j;
			bool c = false;
			for (i = 0, j = (int)PVerts.size() - 1; i < (int)PVerts.size(); j = i++)
			{
				if (((PVerts[i].y > a_Point.y) != (PVerts[j].y > a_Point.y)) &&
					(a_Point.x < (PVerts[j].x - PVerts[i].x) * (a_Point.y - PVerts[i].y) / (PVerts[j].y - PVerts[i].y) + PVerts[i].x))
				{
					c = !c;
				}
			}

			// Is this point inside this obstalce?
			if ((bool)c)
			{
				// Return this point is not valid
				return false;
			}
		}

		// Return point is valid
		return true;
	}

	bool NavMeshEditor::ValidatePoints(Mesh* a_Mesh, const Vector2& a_Point)
	{
		// Get this meshes points
		const std::vector<Vector2>& Points = a_Mesh->Get_Points();

		// Cycle through all the points
		for (auto& p : Points)
		{
			// Are these points the same
			if (p == a_Point)
			{
				// Return this point is not unique
				return false;
			}
		}

		// Return this point is unique
		return true;
	}

	// temp
	bool NavMeshEditor::ValidateObstacle(const Vector2& a_Point)
	{
		// https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
		int i, j;
		bool c = false;
		for (i = 0, j = (int)m_CObstacle.size() - 1; i < (int)m_CObstacle.size(); j = i++)
		{
			if (((m_CObstacle[i].y > a_Point.y) != (m_CObstacle[j].y > a_Point.y)) &&
				(a_Point.x < (m_CObstacle[j].x - m_CObstacle[i].x) * (a_Point.y - m_CObstacle[i].y) / (m_CObstacle[j].y - m_CObstacle[i].y) + m_CObstacle[i].x))
			{
				c = !c;
			}
		}

		return !c;
	}

	void NavMeshEditor::DrawBoundary(aie::Renderer2D* renderer, Mesh* a_Mesh)
	{
		// Get the half extents
		Vector2 Half = a_Mesh->Size() * 0.5f;

		// Get the meshes position
		const Vector2& Pos = a_Mesh->Position();

		// Get each corner of the mesh
		Vector2 UL(Pos.x - Half.x, Pos.y + Half.y);
		Vector2 UR = Pos + Half;
		Vector2 LR(Pos.x + Half.x, Pos.y - Half.y);
		Vector2 LL = Pos - Half;

		// Set render colour
		renderer->setRenderColour(1.f, 1.f, 1.f);

		// Draw the boundary
		renderer->drawLine(UL.x, UL.y, UR.x, UR.y, 5.f);
		renderer->drawLine(UR.x, UR.y, LR.x, LR.y, 5.f);
		renderer->drawLine(LR.x, LR.y, LL.x, LL.y, 5.f);
		renderer->drawLine(LL.x, LL.y, UL.x, UL.y, 5.f);
	}

	void NavMeshEditor::DrawNodes(aie::Renderer2D* renderer, Mesh* a_Mesh)
	{
		// Cycle through every node
		for (auto& node : a_Mesh->Get_Nodes()) 
		{
			// Set colour to yellow
			renderer->setRenderColour(1, 1, 0);

			// Draw this node
			renderer->drawLine(node.Vertices()[0].x, node.Vertices()[0].y, node.Vertices()[1].x, node.Vertices()[1].y);
			renderer->drawLine(node.Vertices()[1].x, node.Vertices()[1].y, node.Vertices()[2].x, node.Vertices()[2].y);
			renderer->drawLine(node.Vertices()[2].x, node.Vertices()[2].y, node.Vertices()[0].x, node.Vertices()[0].y);
		}
	}

	void NavMeshEditor::DrawObstacles(aie::Renderer2D* renderer, Mesh* a_Mesh)
	{
		// Cycle through every obstacle
		for (auto& obstacle : a_Mesh->Get_Obstacles())
		{
			// Set render colour to red
			renderer->setRenderColour(1, 0, 0);

			// Get the obstacles vertices
			const std::vector<Vector2>& verts = obstacle.Vertices();

			// Cycle through every vertex
			for (int i = 0; i != verts.size(); ++i)
			{
				// Is this the last vertex?
				if (i == verts.size() - 1)
				{
					// Draw the last edge
					renderer->drawLine(verts[i].x, verts[i].y, verts[0].x, verts[0].y, 5.f);
				}
				else
				{
					// Draw the edge
					renderer->drawLine(verts[i].x, verts[i].y, verts[i + 1].x, verts[i + 1].y, 5.f);
				}
			}

			// Set renderc colour to green
			renderer->setRenderColour(0, 1, 0);
			
			// Get the obstacles padded vertices
			std::vector<Vector2> pverts = obstacle.GetPaddedVertices();

			// Cycle through every vertex
			for (int i = 0; i != pverts.size(); ++i)
			{
				// Is this the last vertex
				if (i == pverts.size() - 1)
				{
					// Draw the last edge
					renderer->drawLine(pverts[i].x, pverts[i].y, pverts[0].x, pverts[0].y, 5.f);
				}
				else
				{
					// Draw the edge
					renderer->drawLine(pverts[i].x, pverts[i].y, pverts[i + 1].x, pverts[i + 1].y, 5.f);
				}
			}
		}
	}

	void NavMeshEditor::DrawPoints(aie::Renderer2D* renderer, Mesh* a_Mesh)
	{
		// Set render colour
		renderer->setRenderColour(1.f, 0.f, 1.f);

		// Cycle through every point
		for (auto& point : a_Mesh->Get_Points())
		{
			// Draw this point
			renderer->drawCircle(point.x, point.y, 2.5f);
		}
	}

	void NavMeshEditor::DrawCurrentObstacle(aie::Renderer2D* renderer, const Vector2& a_MousePos)
	{
		// Is there no obstacle?
		if (m_CObstacle.empty())
		{
			// End this function
			return;
		}

		// Set render colour
		renderer->setRenderColour(0.2f, 0.8f, 0.8f);

		// Cycle through every vertex
		for (int i = 0; i != m_CObstacle.size(); ++i)
		{
			// Is this the last vertex?
			if (i == m_CObstacle.size() - 1)
			{
				// Draw the last edge
				renderer->drawLine(m_CObstacle[i].x, m_CObstacle[i].y, m_CObstacle[0].x, m_CObstacle[0].y, 5.f, 1);
			}
			else
			{
				// Draw the edge
				renderer->drawLine(m_CObstacle[i].x, m_CObstacle[i].y, m_CObstacle[i + 1].x, m_CObstacle[i + 1].y, 5.f, 1);
			}
		}


		// Draw the potential edge
		renderer->drawLine(m_CObstacle.back().x, m_CObstacle.back().y, a_MousePos.x, a_MousePos.y, 5.f, 1.f);
	}
}