#include "NavMesh\NavMesh2D.h"

#include "NavMesh\NavMeshUtility.h"
#include "poly2tri\poly2tri.h"

#include <numeric>
#include <queue>

#include <cassert>

namespace NavMesh
{

	NavMesh2D::NavMesh2D() { }

	NavMesh2D::NavMesh2D(const Vector2& a_Position, const Vector2& a_Size)
		: m_Position(a_Position), m_Size(a_Size) { }

	bool NavMesh2D::Add_Obstacle(const std::vector<Vector2>& a_Vertices, float a_Padding)
	{
		// Create the new obstacle
		Obstacle NOb(a_Vertices, a_Padding);

		// Cycle through every existing obstacle
		//for (auto& Ob : m_Obstacles)
		//{
		//	// Do these obstacles collide?
		//	if (ObstaclesCollide(NOb, Ob))
		//	{
		//		// Return this obstacle cannot be added
		//		return false;
		//	}
		//}

		// Add this obstacle
		m_Obstacles.push_back(NOb);

		// Return that the obstacle was added
		return true;
	}

	bool NavMesh2D::Add_Obstacle(const std::initializer_list<Vector2>& a_Vertices, float a_Padding)
	{
		// Add this obstacle
		return Add_Obstacle(std::vector<Vector2>(a_Vertices), a_Padding);
	}

	bool NavMesh2D::Add_Point(const Vector2& a_Point)
	{
		// for now...
		m_Points.push_back(a_Point);
		return true;
	}

	bool NavMesh2D::Add_Point(float a_X, float a_Y)
	{
		// Add this point
		return Add_Point(Vector2(a_X, a_Y));
	}

	bool NavMesh2D::Construct()
	{
		using namespace p2t;

		// Clear all current nodes
		m_Nodes.clear();

		// Vector to capture all points
		std::vector<Point*> AllPoints;

		// Get half extents of boundary
		Vector2 HE = m_Size * 0.5f;

		// Add initial surrounding box of the navmesh
		AllPoints.push_back(new Point((double)(m_Position.x - HE.x), (double)(m_Position.y + HE.y)));
		AllPoints.push_back(new Point((double)(m_Position.x + HE.x), (double)(m_Position.y + HE.y)));
		AllPoints.push_back(new Point((double)(m_Position.x + HE.x), (double)(m_Position.y - HE.y)));
		AllPoints.push_back(new Point((double)(m_Position.x - HE.x), (double)(m_Position.y - HE.y)));

		// Get initial surrounding box of the navmesh
		std::vector<Point*> Boundary = AllPoints;

		// Create the CDT instance
		m_CDT = new CDT(Boundary);

		// Cycle through every obstacle
		for (auto& Ob : m_Obstacles)
		{
			// Create the polyline
			std::vector<Point*> Polyline;

			// Get the padded vertices
			std::vector<Vector2> Vertices = Ob.GetPaddedVertices();

			// Cycle through every vertex
			for (auto& V : Vertices)
			{
				// Add this vertex to all the points
				AllPoints.push_back(new Point((double)V.x, (double)V.y));

				// Add the vertex to the polyline
				Polyline.push_back(AllPoints.back());
			}

			// Add this polyline to the mesh
			m_CDT->AddHole(Polyline);
		}

		// Cycle through every point
		for (auto& Po : m_Points)
		{
			// Add this point to the all points
			AllPoints.push_back(new Point((double)Po.x, (double)Po.y));

			// Add the point to the mesh
			m_CDT->AddPoint(AllPoints.back());
		}

		// Triangulate the mesh
		m_CDT->Triangulate();

		// Get the newly formed triangles
		std::vector<Triangle*> Triangles = m_CDT->GetTriangles();

		// Cycle through every triangle
		for (auto& Tri : Triangles)
		{
			// Create the new node
			Node N;

			// Cycle through each vertex of the triangle
			for (int i = 0; i < 3; ++i)
			{
				// Get pointer to vertex
				Point* P = Tri->GetPoint(i);

				// Add this vertex to the node
				N.Add_Vertex(Vector2((float)P->x, (float)P->y));
			}

			// Calculates the nodes position
			N.m_Position = (std::accumulate(N.m_Vertices.cbegin(), N.m_Vertices.cend(), Vector2()) / (float)N.m_Vertices.size());

			// Add this node
			m_Nodes.push_back(N);
		}

		// Cycle through every node
		for (auto it = m_Nodes.begin(); it != m_Nodes.end(); ++it)
		{
			// Cycle through every node again
			for (auto that = m_Nodes.begin(); that != m_Nodes.end(); ++that)
			{
				// Skip if nodes are same
				if (it == that) { continue; }

				// Default shared vertices to zero
				size_t SV = 0;

				// Cycle through the first nodes vertices
				for (auto& V1 : it->m_Vertices)
				{
					// Cycle through the second nodes vertices
					for (auto& V2 : that->m_Vertices)
					{
						// Are these vertices equal?
						if (V1 == V2)
						{
							// Increase shared vertices
							++SV;

							// Break from this loop
							break;
						}
					}

					// Break if two vertices are shared
					if (SV == 2) { break; }
				}

				// Do these nodes share an edge?
				if (SV == 2)
				{
					// Get the distance between these nodes
					float Distance = Vector2::Distance(that->m_Position, it->m_Position);

					// Link these two nodes together
					it->Add_Edge(Edge(Distance, &*it, &*that));
				}
			}
		}

		// Cycle through every point
		for (auto& P : AllPoints)
		{
			// Delete this point
			delete P;
		}
		
		// Reset the CDT
		delete m_CDT; m_CDT = nullptr;

		// Return a successfull construction
		return true;
	}

	// Needs improvements ( stop using findnode all the time )
	std::vector<Node*> NavMesh2D::Dijkstra(const Node& a_From, const Node& a_To)
	{
		// Cycle through every node
		for (auto& node : m_Nodes)
		{
			// Reset this vertex
			node.m_sVisited = false;
			node.m_sGScore = WLimits::max();
			node.m_sFrom = nullptr;
		}

		// Create the list
		std::list<Node*> Queue;

		// Assure this node is from this 
		Node* StartNode = FindNode(a_From);

		// Set this node as the first node
		StartNode->m_sVisited = true;
		StartNode->m_sGScore = 0.f;

		// Declare needed variables
		Node* CurNode = nullptr;

		// Cycle through the node's paths
		for (const auto& edge : StartNode->Edges())
		{
			// Set the current node to
			// this paths destination
			CurNode = edge.Destination();

			// Set the initial start
			// and cost for this node
			CurNode->m_sGScore = edge.Weight();
			CurNode->m_sFrom = StartNode;

			// Make sure nodes don't get
			// added twice to the queue
			if (!CurNode->Visited())
			{
				// Add this node to the
				// queue and set it to visited
				Queue.push_back(CurNode);
				CurNode->m_sVisited = true;
			}
		}

		// Create the comparison to compare with
		auto Closer = [](auto& v1, auto& v2)->bool { return v1->m_sGScore < v2->m_sGScore; };

		// Sort the queue
		Queue.sort(Closer);

		// Keep repeating until queue is empty
		while (true)
		{
			// Has every path been traversed?
			if (Queue.empty())
			{
				// Generate the path and return it
				return GeneratePath(FindNode(a_From), FindNode(a_To));
			}
			else
			{
				// Get the next node from the queue
				// and set it to being traversed
				Node* Next = Queue.front();
				Queue.pop_front();
				Next->m_sVisited = true;

				// Is this the Node to find?
				if (Next == FindNode(a_To))
				{
					// Generate the path and return it
					return GeneratePath(FindNode(a_From), FindNode(a_To));
				}

				// Cycle through node's edges
				for (auto& edge : Next->Edges())
				{
					// Get the destination of this edge
					Node* Connected = edge.Destination();

					// Has this city not been visited?
					if (!Connected->m_sVisited)
					{
						// Calculate the GScore for this edge
						WType GScore = edge.Weight() + edge.Source()->m_sGScore;

						// Is this cost cheaper to get to
						// than than the destinations cost?
						if (GScore < Connected->m_sGScore)
						{
							// Set up this city
							// for the next loop
							Connected->m_sFrom = edge.Source();
							Connected->m_sVisited = true;
							Connected->m_sGScore = GScore;
							Queue.push_back(Connected);
						}
					}
				}

				// Sort the queue
				Queue.sort(Closer);
			}
		}

		// Return an empty vector
		return std::vector<Node*>();
	}

	std::vector<Vector2> NavMesh2D::Smooth(const std::vector<Node*>& a_Path)
	{
		return SmoothPath(a_Path);
	}

	Node* NavMesh2D::Get_Node(const Vector2& a_Position)
	{
		// Cycle through every node
		for (auto& N : m_Nodes)
		{
			// Is the point within this node?
			if (ContainsPoint(N, a_Position))
			{
				// Return this node
				return &N;
			}
		}

		// If no node is found, return null
		return nullptr;
	}

	Node* NavMesh2D::Get_Node(const Vector2& a_Position, float a_Range)
	{
		// Set the current closest node to none
		// and distance to maximum possible value
		Node* CNode = nullptr;
		float CDistance = std::numeric_limits<float>::max();

		// Cycle through every node
		for (auto& N : m_Nodes)
		{
			// Get the distance between the given position and this node
			float NDistance = std::fabsf(Vector2::Distance(N.m_Position, a_Position));

			// Is this node within the given range
			if (NDistance < a_Range)
			{
				// Is this node closer than the current closest
				if (NDistance < CDistance)
				{
					// Set this node as the current closest
					CNode = &N;
					CDistance = NDistance;
				}
			}
		}

		// Return the closest node
		return CNode;
	}

	void NavMesh2D::Position(const Vector2& a_Position)
	{
		// for now, would like to make it so everything adjusts
		m_Position = a_Position;

		Clear();
	}

	void NavMesh2D::Size(const Vector2& a_Size)
	{
		// for now, would like to make it so everything adjusts
		m_Size = a_Size;

		Clear();
	}

	Node* NavMesh2D::FindNode(const Node& a_Node)
	{
		// Get the nodes address
		const Node* NAddress = &a_Node;

		// Cycle through every node
		for (auto& N : m_Nodes)
		{
			// Get the current nodes address
			Node* CAddress = &N;

			// Do the nodes share the same address?
			if (CAddress == NAddress)
			{
				// Return this node
				return CAddress;
			}
		}

		// Assert if node wasn't found
		assert(false && "Failed to find node");

		// Return nullptr by default
		return nullptr;
	}

	std::vector<Node*> NavMesh2D::GeneratePath(Node* a_From, Node* a_To)
	{
		// Create the path to return
		std::vector<Node*> Path;

		// Cycle through backwards
		// until no more cities left
		while (a_To->m_sFrom != nullptr)
		{
			// Add this city and increment
			Path.push_back(a_To);
			a_To = a_To->m_sFrom;
		}

		// Are we now at the
		// source city to get?
		if (a_To == a_From)
		{
			// Add this city
			Path.push_back(a_From);

			// Since we went through backwards,
			// we need to reverse the array so
			// the path is in the correct order
			std::reverse(Path.begin(), Path.end());
		}

		// Return the path
		return Path;
	}
}
