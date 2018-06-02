#pragma once

#include "NavMesh\NavMesh2D.h"

namespace aie
{
	class Renderer2D;
}

namespace NavMesh
{
	class NavMeshEditor final
	{
	public:

		using Mesh = NavMesh2D;

		NavMeshEditor() = default;
		~NavMeshEditor() = default;
	
		void SetPosition(Mesh* a_Mesh, const Vector2& a_Position);
		void SetSize(Mesh* a_Mesh, const Vector2& a_Size);

		void AddObstacle(Mesh* a_Mesh, float a_Padding);
		void AddPoint(Mesh* a_Mesh, const Vector2& a_Point);
		void AddPointToObstacle(Mesh* a_Mesh, const Vector2& a_Point);

		void Construct(Mesh* a_Mesh);

		void ClearMesh(Mesh* a_Mesh);
		void ClearObstacles(Mesh* a_Mesh);
		void ClearPoints(Mesh* a_Mesh);
		void ClearObstacle();

		void Render(aie::Renderer2D* renderer, Mesh* a_Mesh, const Vector2& a_MousePos);

	private:
		
		bool ValidateAll(Mesh* a_Mesh, const Vector2& a_Point);

		bool ValidateRange(Mesh* a_Mesh, const Vector2& a_Point);
		bool ValidateObstacles(Mesh* a_Mesh, const Vector2& a_Point);
		bool ValidatePoints(Mesh* a_Mesh, const Vector2& a_Point);

		bool ValidateObstacle(const Vector2& a_Point);

		void DrawBoundary(aie::Renderer2D* renderer, Mesh* a_Mesh);
		void DrawNodes(aie::Renderer2D* renderer, Mesh* a_Mesh);
		void DrawObstacles(aie::Renderer2D* renderer, Mesh* a_Mesh);
		void DrawPoints(aie::Renderer2D* renderer, Mesh* a_Mesh);
		void DrawCurrentObstacle(aie::Renderer2D* renderer, const Vector2& a_MousePos);

		// Obstacle being built
		std::vector<Vector2> m_CObstacle;
	};

}