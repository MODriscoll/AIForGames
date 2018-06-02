#pragma once

#ifndef Michaels_NavMesh2D
#define Michaels_NavMesh2D

#include "NavMeshComponents.h"

#include <list>

// Forward declerations
namespace p2t
{
	class CDT;

	struct Point;
}


namespace NavMesh
{
	// NavMesh utilises poly2tri
	class NavMesh2D
	{
	public:

		NavMesh2D();
		NavMesh2D(const Vector2& a_Position, const Vector2& a_Size);

		bool Add_Obstacle(const std::vector<Vector2>& a_Vertices, float a_Padding);
		bool Add_Obstacle(const std::initializer_list<Vector2>& a_Vertices, float a_Padding);

		bool Add_Point(const Vector2& a_Point);
		bool Add_Point(float a_X, float a_Y);

		bool Construct();

		// Maybe make version that takes in positions then find them
		// Will use range search for effiency Get_Node(position, range )
		// For now though, use nodes. ( Assert if node is not from this mesh )
		// Get rid of all the find nodes
		std::vector<Node*> Dijkstra(const Node& a_From, 
									const Node& a_To);

		// Same as above
		template <typename Function, typename... Args>
		std::vector<Node*> AStar(const Node& a_From, 
								 const Node& a_To, 
								 const Function& a_Heuristic, 
								 Args... a_HeuristicArgs);

		static std::vector<Vector2> Smooth(const std::vector<Node*>& a_Path);

		void Clear_Nodes()
		{
			m_Nodes.clear();
		}

		void Clear_Obstacles()
		{
			m_Obstacles.clear();
		}

		void Clear_Points()
		{
			m_Points.clear();
		}

		void Clear()
		{
			Clear_Nodes();
			Clear_Obstacles();
			Clear_Points();
		}

		Node* Get_Node(const Vector2& a_Position);
		Node* Get_Node(const Vector2& a_Position, float a_Range);

		// Const so no new nodes can be added
		const std::vector<Node>& Get_Nodes() const
		{
			return m_Nodes;
		}

		// Const so no new obstacles can be added
		const std::vector<Obstacle>& Get_Obstacles() const
		{
			return m_Obstacles;
		}

		// Const so no new points can be added
		const std::vector<Vector2>& Get_Points() const
		{
			return m_Points;
		}

		size_t Nodes() const
		{
			return m_Nodes.size();
		}

		size_t Obstacles() const
		{
			return m_Obstacles.size();
		}

		size_t Points() const
		{
			return m_Points.size();
		}

		
		void Position(const Vector2& a_Position);
		void Size(const Vector2& a_Size);

		const Vector2& Position() const
		{
			return m_Position;
		}
		
		const Vector2& Size() const
		{
			return m_Size;
		}

	private:

		// Finds if node is apart of this mesh by comparing address
		Node* FindNode(const Node& a_Node);

		std::vector<Node*> GeneratePath(Node* a_From, Node* a_To);

		std::vector<Node> m_Nodes;
		std::vector<Obstacle> m_Obstacles;
		std::vector<Vector2> m_Points;

		p2t::CDT* m_CDT;

		Vector2 m_Position, m_Size;
	};

	// Needs improvements ( stop using findnode all the time )
	template<typename Function, typename... Args>
	inline std::vector<Node*> NavMesh2D::AStar(const Node& a_From, const Node& a_To, const Function& a_Heuristic, Args ...a_HeuristicArgs)
	{
		// Cycle through every node
		for (auto& node : m_Nodes)
		{
			// Reset this node
			node.m_sVisited = false;
			node.m_sGScore = WLimits::max();
			node.m_sFScore = WLimits::max();
			node.m_sFrom = nullptr;
		}

		// Create the list
		std::list<Node*> Queue;

		// Get the node to start from
		Node* StartNode = FindNode(a_From);

		// Set this node as the first city
		StartNode->m_sVisited = true;
		StartNode->m_sGScore = 0.f;

		// Add this node to the queue
		Queue.push_back(StartNode);

		// Create the comparison to compare
		auto Closer = [](auto& v1, auto& v2)->bool { return v1->m_sFScore < v2->m_sFScore; };

		// Keep repeating until broken out of
		while (true)
		{
			// Is the queue empty?
			if (Queue.empty())
			{
				// Generate and return the path
				return GeneratePath(FindNode(a_From), FindNode(a_To));
			}

			// Get the current node and
			// set it to being visited.
			// Remove it from the queue
			Node* CurNode = Queue.front();
			Queue.pop_front();
			CurNode->m_sVisited = true;

			// Is this the target node?
			if (CurNode == FindNode(a_To))
			{
				// Generate and return the path
				return GeneratePath(FindNode(a_From), FindNode(a_To));
			}

			// Cycle through this node's edges
			for (auto& edge : CurNode->Edges())
			{
				// Get the edges destination
				Node* Target = edge.Destination();

				// Has the node not been visited?
				if (!Target->m_sVisited)
				{
					// Calculate the scores for this vertex
					WType GScore = CurNode->m_sGScore + edge.Weight();
					WType HScore = a_Heuristic(Target->Position(), FindNode(a_To)->Position(), a_HeuristicArgs...);
					WType FScore = GScore + HScore;

					// Is the calculated final score
					// lower than its current final score?
					if (FScore < Target->m_sFScore)
					{
						// Set this vertices new scores
						Target->m_sFrom = CurNode;
						Target->m_sGScore = GScore;
						Target->m_sFScore = FScore;

						// Find the destination in the queue
						auto Contains = std::find(Queue.begin(), Queue.end(), Target);

						// Is the target not in the queue?
						if (Contains == Queue.end())
						{
							// Add the target to the queue
							Queue.push_back(Target);
						}
					}
				}
			}

			// Sort the queue
			Queue.sort(Closer);
		}

		// Return an empty vector
		return std::vector<Node*>();
	}

}

#endif // Michaels_NavMesh2D