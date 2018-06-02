#pragma once

#ifndef Michaels_Containers_Graph
#define Michaels_Containers_Graph

#include <deque>
#include <list>
#include <map>
#include <queue>
#include <stack>	
#include <vector>

#include <cassert>

namespace Containers
{
	// Forward declerations
	template <typename Vertex_Type, typename Edge_Type>
	class Edge;
	template <typename Vertex_Type, typename Edge_Type>
	class Vertex;
	template <typename Vertex_Type, typename Edge_Type>
	class Graph;


	template <typename Vertex_Type, typename Edge_Type>
	class Edge
	{
	public:

		// Cut-down names of template types
		using VType = Vertex_Type;
		using EType = Edge_Type;

		// Graph components
		using Path = Edge<Vertex_Type, Edge_Type>;
		using City = Vertex<Vertex_Type, Edge_Type>;

	public:

		Edge() = delete;

		Edge(const EType& a_Weight, City* a_From, City* a_To)
			: m_Weight(a_Weight), m_From(a_From), m_To(a_To) { }

		Edge(EType&& a_Weight, City* a_From, City* a_To)
			: m_Weight(std::forward<EType>(a_Weight)), m_From(a_From), m_To(a_To) { }

		Edge(const Path& copy) = default;
		Edge(Path&& move) = default;

		~Edge() = default;

		bool operator == (const Path& rhs) const
		{
			return (m_From == rhs.m_From && m_To == rhs.m_To);
		}

		bool operator != (const Path& rhs) const
		{
			return !(this == rhs);
		}

		Path& operator = (const Path& rhs) = default;
		Path& operator = (Path&& rhs) = default;

		EType& Weight()
		{
			return m_Weight;
		}

		const EType& Weight() const
		{
			return m_Weight;
		}

		City* Source() const
		{
			return m_From;
		}

		City* Destination() const
		{
			return m_To;
		}

	private:

		friend Graph<VType, EType>;

		EType m_Weight;

		City* m_From;
		City* m_To;
	};


	template <typename Vertex_Type, typename Edge_Type>
	class Vertex
	{
	public:

		// Cut-down names of template types
		using VType = Vertex_Type;
		using EType = Edge_Type;

		// Graph components
		using Path = Edge<Vertex_Type, Edge_Type>;
		using City = Vertex<Vertex_Type, Edge_Type>;

		// Container for edges
		using Edges = std::list<Path>;

		// Numeric limits of Edge_Type
		using ELimits = std::numeric_limits<EType>;

	public:

		Vertex() = delete;

		Vertex(const VType& a_Node)
			: m_Node(a_Node), m_sVisited(false), m_sQueued(false), m_sFrom(nullptr),
			m_sGScore(ELimits::max()), m_sFScore(ELimits::max()) { }

		Vertex(VType&& a_Node)
			: m_Node(std::forward<VType>(a_Node)), m_sVisited(false), m_sQueued(false),
			m_sFrom(nullptr), m_sGScore(ELimits::max()), m_sFScore(ELimits::max()) { }

		Vertex(const City& copy) = default;
		Vertex(City&& move) = default;

		~Vertex() = default;

		City& operator = (const City& rhs) = default;
		City& operator = (City&& rhs) = default;

		VType& Node()
		{
			return m_Node;
		}

		const VType& Node() const
		{
			return m_Node;
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

		EType GScore() const
		{
			return m_sGScore;
		}

		EType FScore() const
		{
			return m_sFScore;
		}

		const Edges& Paths() const
		{
			return m_Edges;
		}

	private:

		void Add_Edge(Path&& a_Path)
		{
			auto it = std::find(m_Edges.begin(), m_Edges.end(), a_Path);

			if (it == m_Edges.end())
			{
				m_Edges.insert(it, std::forward<Path>(a_Path));
			}
			else
			{
				it->Weight() = a_Path.Weight();
			}
		}

		friend Graph<VType, EType>;

		VType m_Node;

		Edges m_Edges;

		// Search variables
		bool m_sVisited;
		bool m_sQueued;

		City* m_sFrom;

		EType m_sGScore;
		EType m_sFScore;
	};


	template <typename Vertex_Type, typename Edge_Type>
	class Graph
	{
	public:

		// Cut-down names of template types
		using VType = Vertex_Type;
		using EType = Edge_Type;

		// Graph components
		using Path = Edge<Vertex_Type, Edge_Type>;
		using City = Vertex<Vertex_Type, Edge_Type>;

		// Container for vertices
		using Vertices = std::list<City>;

		// Containers that are used during
		// calculations and returned 
		using City_List = std::list<City*>;
		using City_Que = std::queue<City*>;
		using City_Stack = std::stack<City*>;
		using City_Vector = std::vector<City*>;

		// Numeric limits of Edge_Type
		using ELimits = std::numeric_limits<EType>;

	public:

		Graph()
		{
			static_assert(ELimits::is_specialized, "Graph only supports arithmetic edge types");
		}

		Graph(const Graph& copy) = delete;
		Graph(Graph&& move) = default;

		virtual ~Graph() = default;

		Graph& operator = (const Graph& rhs) = delete;
		Graph& operator = (Graph&& rhs) = default;

		void Add_Vertex(const VType& a_Node)
		{
			// Add this vertex
			m_Vertices.push_back(City(a_Node));
		}

		void Remove_Vertex(const VType& a_Node)
		{
			// Find this vertex
			auto Get = std::find_if(m_Vertices.begin(), m_Vertices.end(),
				[&a_Node](const City& v)->bool { return a_Node == v.Node(); });

			// Assert if the value wasn't found
			assert(Get != m_Vertices.end() && "Failed to find city");

			// Get the pointer to this vertex
			City* Ptr = &*Get;

			// Cycle through every vertex
			for (auto it = m_Vertices.begin(); it != m_Vertices.end(); ++it)
			{
				// Is this the vertex
				// being removed?
				if (it == Get)
				{
					// Skip the rest
					continue;
				}

				// Remove any edge from this
				// vertex that leads to the
				// vertex being removed now
				it->m_Edges.remove_if([Ptr](City::Path& v)->bool { return Ptr == v.Destination(); });
			}

			// Erase this vertex from the graph
			m_Vertices.erase(Get);
		}

		void Add_Directed_Edge(const VType& a_From, const VType& a_To, const EType& a_Weight)
		{
			// Find the source and
			// destination vertex
			auto From = FindVertex(a_From);
			auto To = FindVertex(a_To);

			// Add a new edge to the source vertex
			From->Add_Edge(Path(a_Weight, From, To));
		}

		void Add_NonDirected_Edge(const VType& a_From, const VType& a_To, const EType& a_Weight)
		{
			// Add one edge for the source and
			// another for the destination vertex
			Add_Directed_Edge(a_From, a_To, a_Weight);
			Add_Directed_Edge(a_To, a_From, a_Weight);
		}

		City_Vector Reachable(const VType& a_From)
		{
			// Cycle through every vertex
			for (auto& vertex : m_Vertices)
			{
				// Reset this vertex
				vertex.m_sVisited = false;
				vertex.m_sQueue = false;
			}

			// Create the que
			City_Que Queue;

			// Push the prime city and
			// set it to being queued
			City* CurCity = FindVertex(a_From);
			Queue.push(CurCity);
			CurCity->m_sQueued = true;

			// Repeat until queue is empty
			while (!Queue.empty())
			{
				// Set the current city to
				// visited and remove it
				CurCity = Queue.front();
				Queue.pop();
				CurCity->m_sVisited = true;

				// Cycle through the cities paths
				for (auto& edge : CurCity->Paths())
				{
					// Has this paths destination
					// not been added to the que
					if (!edge.Destination()->m_sQueued)
					{
						// Push the destination and
						// set it to being queued
						edge.Destination()->m_sQueued = true;
						Queue.push(edge.Destination());
					}
				}
			}

			// Create the vector
			City_Vector ReachedCities;

			// Cycle through all cities
			for (auto& vertex : m_Vertices)
			{
				// Was this city visited ( don't
				// include the source city )
				if (vertex.m_sVisited && vertex.Node() != a_From)
				{
					// Add this city to the vector
					ReachedCities.push_back(&vertex);
				}
			}

			// Return the reached cities
			return ReachedCities;
		}

		City_Vector Dijkstra(const VType& a_From, const VType& a_To)
		{
			// Cycle through every vertex
			for (auto& vertex : m_Vertices)
			{
				// Reset this vertex
				vertex.m_sVisited = false;
				vertex.m_sGScore = ELimits::max();
				vertex.m_sFrom = nullptr;
			}

			// Create the list
			City_List Queue;

			// Get the city to start from
			City* StartCity = FindVertex(a_From);

			// Set this city as the first city
			StartCity->m_sVisited = true;
			StartCity->m_sGScore = static_cast<EType>(0);

			// Declare needed variables
			City* CurCity = nullptr;

			// Cycle through the city's paths
			for (const auto& edge : StartCity->Paths())
			{
				// Set the current city to
				// this paths destination
				CurCity = edge.Destination();

				// Set the initial start
				// and cost for this city
				CurCity->m_sGScore = edge.Weight();
				CurCity->m_sFrom = StartCity;

				// Make sure cities don't get
				// added twice to the queue
				if (!CurCity->Visited())
				{
					// Add this city to the
					// queue and set it to visited
					Queue.push_back(CurCity);
					CurCity->m_sVisited = true;
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
					return GeneratePath(FindVertex(a_From), FindVertex(a_To));
				}
				else
				{
					// Get the next city from the queue
					// and set it to being traversed
					City* Next = Queue.front();
					Queue.pop_front();
					Next->m_sVisited = true;

					// Is this the city to find?
					if (Next->Node() == a_To)
					{
						// Generate the path and return it
						return GeneratePath(FindVertex(a_From), FindVertex(a_To));
					}

					// Cycle through city's paths
					for (auto& edge : Next->Paths())
					{
						// Get the destination of this path
						City* Connected = edge.Destination();

						// Has this city not been visited?
						if (!Connected->m_sVisited)
						{
							// Calculate the GScore for this edge
							EType GScore = edge.Weight() + edge.Source()->m_sGScore;

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
			return City_Vector();
		}

		// Source: https://www.youtube.com/watch?v=lAXZGERcDf4
		// Second draft ( originally didn't use variables from vertex )
		City_Vector Dijkstra_alt(const VType& a_From, const VType& a_To)
		{
			// Type defines for containers
			using CityPtrs = std::deque<City*>;
			using Generations = std::map<City*, City*>;

			// Create the heap and generations containers
			CityPtrs Heap;
			Generations Parents;

			// Cycle through every vertex
			for (auto& city : m_Vertices)
			{
				// Reset this vertex
				city.m_sVisited = false;
				city.m_sGScore = ELimits::max();

				// Add this vertex to the heap
				Heap.push_back(&city);
			}

			// Get the vertex to start from
			auto Start = std::find_if(Heap.begin(), Heap.end(), [&a_From](auto& v)->bool { return v->Node() == a_From; });

			// Assert if this vertex does not exist
			assert(Start != Heap.end() && "Source city not in graph");

			// Set this city as the first city
			(*Start)->m_sGScore = static_cast<EType>(0);
			(*Start)->m_sVisited = true;

			// Add this vertex as the grand parent
			Parents[*Start] = nullptr;

			// Create the comparision to compare with
			auto Closer = [](auto& v1, auto& v2)->bool { return v1->m_sGScore < v2->m_sGScore; };

			// Repeat until the heap is empty
			while (!Heap.empty())
			{
				// Is the target node no longer in the heap?
				if (std::find_if(Heap.begin(), Heap.end(), [&a_To](auto& v)->bool { return v->Node() == a_To; }) == Heap.end())
				{
					// Break from the loop
					break;
				}

				// Get a reference to the current
				// city and set it to visited
				City*& CurCity = Heap.front();
				CurCity->m_sVisited = true;

				// Cycle through this city's paths
				for (auto& edge : CurCity->Paths())
				{
					// Find this edges destination in the heap
					auto Index = std::find_if(Heap.begin(), Heap.end(), [&](auto& v)->bool { return edge.Destination() == v; });

					// Was the destination found?
					if (Index != Heap.end())
					{
						// Calculate the GScore for the step
						EType GScore = CurCity->m_sGScore + edge.Weight();

						// Is the new GScore lower than
						// the destinations current GScore?
						if (GScore < (*Index)->m_sGScore)
						{
							// Set this destionation's GScore
							(*Index)->m_sGScore = GScore;

							// Add the destination to the family
							// and set its parent to the current city
							Parents[*Index] = CurCity;
						}
					}
				}

				// Pop from the front of the array
				Heap.pop_front();

				// Sort the heap
				std::sort(Heap.begin(), Heap.end(), Closer);
			}

			// Create the path to return
			City_Vector Path;

			// Get the target node from the generation map
			auto Target = Parents.find(FindVertex(a_To));

			// Was the target
			// node not reachable?
			if (Target == Parents.end())
			{
				// Return the empty vector
				return Path;
			}

			// Add the target to the path
			Path.push_back(Target->first);

			// Start the path from the second last vertex
			City* NextInPath = Target->second;

			// Set which path lead to the target node
			Target->first->m_sFrom = NextInPath;

			// Repeat until there are no
			// longer any vertices in path
			while (NextInPath != nullptr)
			{
				// Add the vertex to the path
				Path.push_back(NextInPath);

				// Set which vertex lead to the current vertex
				NextInPath->m_sFrom = Parents[NextInPath];

				// Continue onto the next vertex
				NextInPath = NextInPath->m_sFrom;
			}

			// Reverse the path
			std::reverse(Path.begin(), Path.end());

			// Return the path
			return Path;
		}

		// Predicate should return an edge type
		// Needs to be function that takes in at least two nodes
		template <typename Function, typename... Args>
		City_Vector AStar(const VType& a_From, const VType& a_To, const Function& a_Predicate, Args... a_PredicateArgs)
		{
			// Cycle through every vertex
			for (auto& vertex : m_Vertices)
			{
				// Reset this vertex
				vertex.m_sVisited = false;
				vertex.m_sGScore = ELimits::max();
				vertex.m_sFScore = ELimits::max();
				vertex.m_sFrom = nullptr;
			}

			// Create the list
			City_List Queue;

			// Get the city to start from
			City* StartCity = FindVertex(a_From);

			// Set this city as the first city
			StartCity->m_sVisited = true;
			StartCity->m_sGScore = static_cast<EType>(0);

			// Add this city to the queue
			Queue.push_back(StartCity);

			// Create the comparison to compare
			auto Closer = [](auto& v1, auto& v2)->bool { return v1->m_sFScore < v2->m_sFScore; };

			// Keep repeating until broken out of
			while (true)
			{
				// Is the queue empty?
				if (Queue.empty())
				{
					// Generate and return the path
					return GeneratePath(FindVertex(a_From), FindVertex(a_To));
				}

				// Get the current city and
				// set it to being visited.
				// Remove it from the queue
				City* CurCity = Queue.front();
				Queue.pop_front();
				CurCity->m_sVisited = true;

				// Is this the target node?
				if (CurCity->Node() == a_To)
				{
					// Generate and return the path
					return GeneratePath(FindVertex(a_From), FindVertex(a_To));
				}

				// Cycle through this city's edges
				for (auto& edge : CurCity->Paths())
				{
					// Get the edges destination
					City* Target = edge.Destination();

					// Has the city not been visited?
					if (!Target->m_sVisited)
					{
						// Calculate the scores for this vertex
						EType GScore = CurCity->m_sGScore + edge.Weight();
						EType HScore = a_Predicate(Target->Node(), FindVertex(a_To)->Node(), a_PredicateArgs...);
						EType FScore = GScore + HScore;

						// Is the calculated final score
						// lower than its current final score?
						if (FScore < Target->m_sFScore)
						{
							// Set this vertices new scores
							Target->m_sFrom = CurCity;
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
			return City_Vector();
		}

		City* Get(const VType& a_Node)
		{
			return FindVertex(a_Node);
		}

		template <typename Function>
		City* Get(const Function& a_Predicate)
		{
			return FindVertex(a_Predicate);
		}

		const Vertices& Get_All() const
		{
			return m_Vertices;
		}

		size_t Cities() const
		{
			return m_Vertices.size();
		}

	protected:

		City* FindVertex(const VType& a_Node)
		{
			// Find this value
			auto Get = std::find_if(m_Vertices.begin(), m_Vertices.end(),
				[&a_Node](const City& v)->bool { return a_Node == v.Node(); });

			// Assert if the value wasn't found
			assert(Get != m_Vertices.end() && "Failed to find city");

			// Return the pointer to the vertex
			return &*Get;
		}

		template <typename Function>
		City* FindVertex(const Function& a_Predicate)
		{
			// Find this value
			auto Get = std::find_if(m_Vertices.begin(), m_Vertices.end(), a_Predicate);

			// Assert if the value wasn't found
			assert(Get != m_Vertices.end() && "Failed to find city");

			// Return the pointer to this vertex
			return &*Get;
		}

		City_Vector GeneratePath(City* a_From, City* a_To)
		{
			// Create the path to return
			City_Vector Path;

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

		Vertices m_Vertices;
	};
}

#endif // Michaels_Containers_Graph
