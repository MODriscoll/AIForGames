#pragma once

#ifndef Michaels_NavMesh_Components
#define Michaels_NavMesh_Components

#include <Math\Vectors\Vector2.h>

#include <vector>

namespace NavMesh
{
	// Forward declerations
	class Edge;
	class Node;
	class Obstacle;
	class Polygon;
	class NavMesh2D;

	// Type define for edge weights
	using WType = float;
	// Numeric limits of weight type
	using WLimits = std::numeric_limits<WType>;

	class Edge
	{
	public:

		Edge() = delete;

		Edge(const WType& a_Weight, Node* a_From, Node* a_To)
			: m_Weight(a_Weight), m_From(a_From), m_To(a_To) { }

		Edge(const Edge& copy) = default;
		Edge(Edge&& move) = default;

		~Edge() = default;

		Edge& operator = (const Edge& rhs) = default;
		Edge& operator = (Edge&& rhs) = default;

		WType& Weight()
		{
			return m_Weight;
		}

		const WType& Weight() const
		{
			return m_Weight;
		}

		Node* Source() const
		{
			return m_From;
		}

		Node* Destination() const
		{
			return m_To;
		}

	private:

		friend NavMesh2D;

		WType m_Weight;

		Node* m_From;
		Node* m_To;
	};


	class Node
	{
	public:

		Node(const std::vector<Vector2>& a_Vertices);
		Node(const std::initializer_list<Vector2>& a_Vertices);

		Node(const Node& copy) = default;
		Node(Node&& move) = default;

		~Node() = default;

		Node& operator = (const Node& rhs) = default;
		Node& operator = (Node&& rhs) = default;

		const Vector2& Position() const
		{
			return m_Position;
		}

		void Visit(bool a_Visit)
		{
			m_sVisited = a_Visit;
		}

		bool Visited() const
		{
			return m_sVisited;
		}

		void Queue(bool a_Queue)
		{
			m_sQueued = a_Queue;
		}

		bool Queued() const
		{
			return m_sQueued;
		}

		WType GScore() const
		{
			return m_sGScore;
		}

		WType FScore() const
		{
			return m_sFScore;
		}

		const std::vector<Edge>& Edges() const
		{
			return m_Edges;
		}

		const std::vector<Vector2>& Vertices() const
		{
			return m_Vertices;
		}

	private:

		Node();

		void Add_Edge(const Edge& a_Edge)
		{
			m_Edges.push_back(a_Edge);
		}

		void Add_Vertex(const Vector2& a_Vertex)
		{
			m_Vertices.push_back(a_Vertex);
		}

		friend NavMesh2D;

		Vector2 m_Position;

		std::vector<Edge> m_Edges;
		std::vector<Vector2> m_Vertices;

		// Search variables
		bool m_sVisited;
		bool m_sQueued;

		Node* m_sFrom;

		WType m_sGScore;
		WType m_sFScore;
	};

	// Only supports simple polygons
	class Obstacle
	{
	public:

		Obstacle() = delete;

		Obstacle(const std::vector<Vector2>& a_Vertices, float a_Padding);
		Obstacle(const std::initializer_list<Vector2>& a_Vertices, float a_Padding);

		Obstacle(const Obstacle& copy) = default;
		Obstacle(Obstacle&& move) = default;

		~Obstacle() = default;

		Obstacle& operator = (const Obstacle& rhs) = default;
		Obstacle& operator = (Obstacle&& rhs) = default;

		std::vector<Vector2> GetPaddedVertices() const;

		const std::vector<Vector2>& Vertices() const
		{
			return m_Vertices;
		}

		const float& Padding() const
		{
			return m_Padding;
		}

	private:

		friend NavMesh2D;

		std::vector<Vector2> m_Vertices;

		float m_Padding;
	};
}

#endif // Michaels_NavMesh_Components