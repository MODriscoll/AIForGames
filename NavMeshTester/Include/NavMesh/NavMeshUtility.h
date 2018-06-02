#pragma once

#ifndef Michaels_NavMesh_Utilities
#define Michaels_NavMesh_Utilities

#include <Math\Vectors\Vector2.h>

#include <vector>

namespace NavMesh
{
	// Forward declerations
	class Node;
	class Obstacle;

	// Performs GJK on obstacles using padded vertices
	bool ObstaclesCollide(const Obstacle& a_O1, const Obstacle& a_O2);

	namespace GJK
	{
		// Not to be used elsewhere
		struct Simplex
		{
		public:

			Simplex() : m_Size(0) { }
			~Simplex() = default;

			Simplex(const Simplex& copy) = default;
			Simplex(Simplex&& move) = default;

			Simplex& operator = (const Simplex& rhs) = default;
			Simplex& operator = (Simplex&& rhs) = default;

			void Add(const Vector2& a_Vertex)
			{
				if (m_Size < 3) { m_Vertices[m_Size++] = a_Vertex; }
			}

			void Remove(bool a_VB)
			{
				if (m_Size == 3)
				{
					if (a_VB)
					{
						m_Vertices[1] = m_Vertices[--m_Size];	
					}
					else
					{
						m_Vertices[0] = m_Vertices[1];
					}
				}
			}

			Vector2& Back()
			{
				return m_Vertices[m_Size - 1];
			}

			Vector2& operator[] (size_t idx) { return m_Vertices[idx]; }

			size_t Size() const { return m_Size; }

		private:

			Vector2 m_Vertices[3];

			size_t m_Size;
		};

		Vector2 AveragePoint(const std::vector<Vector2>& a_Vertices);
		Vector2 FurthestVertex(const std::vector<Vector2>& a_Vertices, const Vector2& a_Direction);
		Vector2 Support(const std::vector<Vector2>& a_V1, const std::vector<Vector2>& a_V2, const Vector2& a_Direction);

		bool ContainsOrigin(Simplex& a_Simplex, Vector2& a_Direction);
	}

	// Checks if point is within a triangle
	bool ContainsPoint(const Node& a_Node, const Vector2& a_Point);

	// Smooth an existing node path using stupid funnel algorithm
	// Source: http://digestingduck.blogspot.com.au/2010/03/simple-stupid-funnel-algorithm.html
	std::vector<Vector2> SmoothPath(const std::vector<Node*>& a_Path);

	namespace StupidFunnel
	{
		using PEdge = std::pair<Vector2, Vector2>;

		std::vector<Vector2> StringPull(const PEdge* a_Portals, const size_t a_PortalsSize);

		float TriArea2(const Vector2& a_v1, const Vector2& a_v2, const Vector2& a_v3);
	}
}

#endif // Michaels_NavMesh_Utilities