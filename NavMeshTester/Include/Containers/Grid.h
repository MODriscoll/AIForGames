#pragma once

#ifndef Michaels_Containers_Grid
#define Michaels_Containers_Grid

#include <array>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <stack>	
#include <vector>

#include <cassert>

namespace Containers
{
	// TODO: Implement flags for linking
	//		 Write documentation for grid
	//		 Put both grid and graph into respective namespaces
	//		 Try to implement a jump point search

	/*
	enum class Grid_Link_Flags : size_t
	{
		AllVertices			= 1 << 0,			// Links all available neighbours
		NotBlocked			= 1 << 1,			// Links vertices if not blocked	
	
		Diagonal			= 1 << 2,			// Will attempt to link diagonal neighbours	
		AxisLocked			= 1 << 3,			// Will only link neighbours on same axis

		NoModify			= 1 << 4,			// Does not use set modifier when calculating weights

		Default				= NotBlocked | Diagonal
	};

	void Link(Grid_Link_Flags a_Flags = Grid_Link_Flags::Default)
	void Link(const Modifiers& a_Modifiers, Grid_Link_Flags a_Flags = Grid_Link_Flags::Default)

	template <typename Function>
	void Link(const Function& a_Predicate, Grid_Link_Flags a_Flags = Grid_Link_Flags::Default)

	*/

	// Forward declerations
	template <typename Vertex_Type, typename Edge_Type>
	class Vertex;
	template <typename Vertex_Type, typename Edge_Type>
	class Grid;


	template <typename Vertex_Type, typename Edge_Type>
	class Vertex
	{
	public:

		// Cut-down names of template types
		using VType = Vertex_Type;
		using EType = Edge_Type;

		// Grid vertex component
		using City = Vertex<VType, EType>;

		// Link ( edge ) and container for links
		using Link = std::pair<City*, EType>;
		using Edges = std::list<Link>;

		// Numeric limits of Edge_Type
		using ELimits = std::numeric_limits<EType>;

	public:

		Vertex()
			: m_Weight(static_cast<EType>(1)), m_Blocked(false), m_sVisited(false), m_sQueued(false),
			m_sFrom(nullptr), m_sGScore(ELimits::max()), m_sFScore(ELimits::max()) { }

		Vertex(const VType& a_Node, const EType& a_Weight)
			: m_Node(a_Node), m_Weight(a_Weight), m_Blocked(false), m_Visited(false),
			m_Queued(false), m_sFrom(nullptr), m_sGScore(ELimits::max()), m_sFScore(ELimits::max()) { }

		Vertex(VType&& a_Node, EType&& a_Weight)
			: m_Node(std::forward<VType>(a_Node)), m_Weight(std::forward<EType>(a_Weight)), m_Blocked(false),
			m_Visited(false), m_Queued(false), m_sFrom(nullptr), m_sGScore(ELimits::max()), m_sFScore(ELimits::max()) { }

		Vertex(const City& copy) = default;
		Vertex(City&& move) = default;

		~Vertex()
		{
			// Cycle through every vertex
			for (auto& edge : m_Edges)
			{
				// Remove the connection between these vertices
				edge.first->Remove(this);
			}
		}

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

		EType& Weight()
		{
			return m_Weight;
		}

		const EType& Weight() const
		{
			return m_Weight;
		}

		void Block(bool a_Block)
		{
			m_Blocked = a_Block;
		}

		bool Blocked() const
		{
			return m_Blocked;
		}

		void Visit(bool a_Visit)
		{
			m_Visited = a_Visit;
		}

		bool Visited() const
		{
			return m_Visited;
		}

		void Queue(bool a_Queue)
		{
			m_Queued = a_Queue;
		}

		bool Queued() const
		{
			return m_Queued;
		}

		EType GScore() const
		{
			return m_sGScore;
		}

		EType FScore() const
		{
			return m_sFScore;
		}

		const Edges& Connections() const
		{
			return m_Edges;
		}

	private:

		void Remove(City* a_Destination)
		{
			// Cycle through the edges
			for (auto it = m_Edges.begin(); it != m_Edges.end(); ++it)
			{
				// Is this the vertex wanting to be removed?
				if (it->first == a_Destination)
				{
					// Remove this edge
					m_Edges.erase(it);

					// End this function
					return;
				}
			}
		}

		friend Grid<VType, EType>;

		VType m_Node;
		EType m_Weight;

		bool m_Blocked;

		Edges m_Edges;

		// Search variables
		bool m_sVisited;
		bool m_sQueued;

		City* m_sFrom;

		EType m_sGScore;
		EType m_sFScore;
	};


	// Make an alternate version that works with indexes
	// so heuristic and such can be built in most of the time
	// ( Heuristic still takes in current node and finish node )

	// For the alternate version, implement these methods for heuristics
	// When searching, a function can take in a flag parameter specifying
	// which heuristic they want ( even maybe a predicate too )

	/*
	enum class Grid_Heuristic_Flags : size_t
	{
		Manhattan		= 1 << 0,		// Next three: http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#S7
		Diagonal		= 1 << 1,
		Euclidean		= 1 << 2,		
		Inadmissible	= 1 << 3,		// On dashbord

		Default			= Diagonal		// Diagonal since grid supports 8 way traversing
	};

	// Uses indexes to find path
	City_Vector AStar(const VType& a_From, const VType& a_To, Grid_Heuristic_Flags a_Flags = Grid_Heuristic_Flags::Default)

	// Uses nodes ( passed into predicate ) to find path
	template <typename Function, typename... Args>
	City_Vector AStar(const VType& a_From, const VType& a_To, const Function& a_Predicate, Args... a_PredicateArgs)

	// Uses indexes to find path
	City_Vector TStar(const VType& a_From, const VType& a_To, Grid_Heuristic_Flags a_Flags = Grid_Heuristic_Flags::Default)

	// Uses nodes ( passed into predicate ) to find path
	template <typename Function, typename... Args>
	City_Vector TStar(const VType& a_From, const VType& a_To, const Function& a_Predicate, Args... a_PredicateArgs)

	*/

	template <typename Vertex_Type, typename Edge_Type>
	class Grid
	{
	public:

		// Cut-down names of template types
		using VType = Vertex_Type;
		using EType = Edge_Type;

		// Grid vertex component
		using City = Vertex<Vertex_Type, Edge_Type>;

		// Containers to be used by the grid
		using Vertices = std::vector<City>;
		using Matrix = std::vector<Vertices>;
		using Modifier = std::array<EType, 8>;

		// Type define for a vertex's index
		using City_Index = std::pair<int, int>;

		// Containers that are used during
		// calculations and returned
		using City_List = std::list<City*>;
		using City_Que = std::queue<City*>;
		using City_Stack = std::stack<City*>;
		using City_Vector = std::vector<City*>;

		template <typename Return_Type>
		using Flow_Field = std::vector<std::vector<Return_Type>>;

		// Numeric limits of Edge_Type
		using ELimits = std::numeric_limits<EType>;

	public:

		Grid()
		{
			static_assert(std::is_default_constructible<VType>::value, "Grid only supports default constructable vertex types");
			static_assert(ELimits::is_specialized, "Grid only supports arithmetic edge types");

			// Fill in the modifiers with default value
			m_Modifiers.fill(static_cast<EType>(1));
		}

		Grid(size_t a_Width, size_t a_Height)
		{
			static_assert(std::is_default_constructible<VType>::value, "Grid only supports default constructable vertex types");
			static_assert(ELimits::is_specialized, "Grid only supports arithmetic edge types");

			// Fill in the modifiers with default value
			m_Modifiers.fill(static_cast<EType>(1));

			// Resize the grid uisng size given
			ResizeGrid(a_Width, a_Height, City());
		}

		Grid(size_t a_Width, size_t a_Height, const VType& a_Node, const EType& a_Weight)
		{
			static_assert(std::is_default_constructible<VType>::value, "Grid only supports default constructable vertex types");
			static_assert(ELimits::is_specialized, "Grid only supports arithmetic edge types");

			// Fill in the modifiers with default value
			m_Modifiers.fill(static_cast<EType>(1));

			// Resize the grid using size given
			// Fill in each vertex with default value
			ResizeGrid(a_Width, a_Height, City(a_Node, a_Weight));

			// Link all the vertices
			LinkVertices();
		}

		Grid(const Grid& copy) = delete;
		Grid(Grid&& move) = default;

		virtual ~Grid() = default;

		Grid& operator = (const Grid& rhs) = delete;
		Grid& operator = (Grid&& rhs) = default;

		City_Vector Reachable(const VType& a_From)
		{
			// Cycle through every row
			for (auto& row : m_Vertices)
			{
				// Cycle throught this row
				for (auto& vertex : row)
				{
					// Reset this vertex
					vertex.m_sVisited = false;
					vertex.m_sQueued = false;
				}
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

				// Cycle through the cities connections
				for (auto& edge : CurCity->Connections())
				{
					// Has this paths destination
					// not been added to the que
					if (!edge.first->m_sQueued)
					{
						// Push the destination and
						// set it to being queued
						edge.first->m_sQueued = true;
						Queue.push(edge.first);
					}
				}
			}

			// Create the vector
			City_Vector ReachedCities;

			// Cycle through every row
			for (auto& row : m_Vertices)
			{
				// Cycle throught this row
				for (auto& vertex : row)
				{
					// Was this city visited ( don't
					// include the source city )
					if (vertex.m_sVisited && vertex.Node() != a_From)
					{
						// Add this city to the vector
						ReachedCities.push_back(&vertex);
					}
				}
			}

			// Return the reached cities
			return ReachedCities;
		}

		City_Vector Dijkstra(const VType& a_From, const VType& a_To)
		{
			// Cycle through every row
			for (auto& row : m_Vertices)
			{
				// Cycle through every vertex
				for (auto& vertex : row)
				{
					// Reset this vertex
					vertex.m_sVisited = false;
					vertex.m_sGScore = ELimits::max();
					vertex.m_sFrom = nullptr;
				}
			}

			// Create the list
			City_List Queue;

			// Get the city to start from
			City* StartCity = FindVertex(a_From);

			// Set this city as the first city
			StartCity->m_sVisited = true;
			StartCity->m_sGScore = static_cast<EType>(0);

			// Cycle through this city's connections
			for (auto& edge : StartCity->Connections())
			{
				// Set the initial start
				// and cost for this city
				edge.first->m_sGScore = edge.second;
				edge.first->m_sFrom = StartCity;

				// Add this city to the queue
				Queue.push_back(edge.first);

				// Set this city as visited
				edge.first->m_sVisited = true;
			}

			// Create the comparision to compare
			auto Closer = [](auto& v1, auto& v2)->bool { return v1->m_sGScore < v2->m_sGScore; };

			// Sort the queue
			Queue.sort(Closer);

			// Keep repeating until queue is empty
			while (true)
			{
				// Has everything been traversed?
				if (Queue.empty())
				{
					// Generate the path and return
					return GeneratePath(FindVertex(a_From), FindVertex(a_To));
				}

				// Get the next city from the queue
				// and set it to being traversed
				City* Next = Queue.front();
				Queue.pop_front();
				Next->m_sVisited = true;

				// Is this the city to find?
				if (Next->Node() == a_To)
				{
					// Generate the path and return
					return GeneratePath(FindVertex(a_From), FindVertex(a_To));
				}

				// Cycle through this city's connections
				for (auto& edge : Next->Connections())
				{
					// Has the destination not been visited?
					if (!edge.first->m_sVisited)
					{
						// Calculate the GScore for this edge
						EType GScore = edge.second + Next->m_sGScore;

						// Is this cost cheaper to get to
						// than than the destinations cost?
						if (GScore < edge.first->m_sGScore)
						{
							// Set up this city
							// for the next loop
							edge.first->m_sFrom = Next;
							edge.first->m_sGScore = GScore;
							edge.first->m_sVisited = true;
							Queue.push_back(edge.first);
						}
					}
				}

				// Sort the queue
				Queue.sort(Closer);
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

			// Cycle through every row
			for (auto& row : m_Vertices)
			{
				// Cycle through this row
				for (auto& vertex : row)
				{
					// Reset this vertex
					vertex.m_sVisited = false;
					vertex.m_sGScore = ELimits::max();

					// Add this vertex to the heap
					Heap.push_back(&vertex);
				}
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

				// Cycle through this city's connections
				for (auto& edge : CurCity->Connections())
				{
					// Find this edges destination in the heap
					auto Index = std::find_if(Heap.begin(), Heap.end(), [&](auto& v)->bool { return edge.first == v; });

					// Was the destination found?
					if (Index != Heap.end())
					{
						// Calculate the GScore for the step
						EType GScore = CurCity->m_sGScore + edge.second;

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

		template <typename Function, typename... Args>
		City_Vector AStar(const VType& a_From, const VType& a_To, const Function& a_Predicate, Args... a_PredicateArgs)
		{
			// Cycle through every row
			for (auto& row : m_Vertices)
			{
				// Cycle throught this row
				for (auto& vertex : row)
				{
					// Reset this vertex
					vertex.m_sVisited = false;
					vertex.m_sGScore = ELimits::max();
					vertex.m_sFScore = ELimits::max();
					vertex.m_sFrom = nullptr;
				}
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

			// Create the comparision to compare
			auto Closer = [](City* v1, City* v2) { return v1->m_sFScore < v2->m_sFScore; };

			// Keep repeating till broken out of
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

				// Cycle through this city's connections
				for (auto& edge : CurCity->Connections())
				{
					// Get the target city
					City* Target = edge.first;

					// Has the target not been visited?
					if (!Target->m_sVisited)
					{
						// Calculate the scores for this vertex
						EType GScore = CurCity->m_sGScore + edge.second;
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

		// Theta* ( TStar ) can be found in the flowfields solution
		// TODO:	ThetaLazy	( set name to TLazy, rename TStar to TBasic )
		//			JumpPoint	
		//			Fix TStar 
		//			Implement smooth path function ( stupid funnel algorithm )

		// Generates flow field, takes in a predicate with
		// extra arguements for generating the actual field
		// The type that the field will consist of is specified
		// by the return type of the predicate.
		// NEEDS WORK ( need to implement Local Optima )
		template <typename Function, typename... Args>
		Flow_Field<std::result_of_t<Function(VType, VType, Args...)>> FlowField(const VType& a_Origin, const Function& a_Predicate, Args... a_PredicateArgs)
		{
			// Cycle through every row
			for (auto& row : m_Vertices)
			{
				// Cycle through every vertex
				for (auto& vertex : row)
				{
					// Reset this vertex
					vertex.m_sVisited = false;
					vertex.m_sGScore = ELimits::max();
				}
			}

			// Create the list
			City_List Queue;

			// Get the city to start from
			City* StartCity = FindVertex(a_Origin);

			// Set this city as the first city
			StartCity->m_sGScore = static_cast<EType>(0);

			// Add the start to the que
			Queue.push_back(StartCity);

			// Keep repeating until queue is empty
			while (!Queue.empty())
			{
				// Get the next city from the queue
				// and set it to being traversed
				City* Next = Queue.front();
				Queue.pop_front();
				Next->m_sVisited = true;

				// Cycle through this city's connections
				for (auto& edge : Next->Connections())
				{
					// Has the destination not been visited?
					if (!edge.first->m_sVisited)
					{
						// Calculate the GScore for this edge
						EType GScore = edge.second + Next->m_sGScore;

						// Is this cost cheaper to get to
						// than than the destinations cost?
						if (GScore < edge.first->m_sGScore)
						{
							// Set up this city
							// for the next loop
							edge.first->m_sGScore = GScore;
							Queue.push_back(edge.first);
						}
					}
				}
			}

			// Return the generated flow field
			return GenerateField(a_Predicate, a_PredicateArgs...);
		}

		void Resize(size_t a_Width, size_t a_Height)
		{
			ResizeGrid(a_Width, a_Height, City());
		}

		void Resize(size_t a_Width, size_t a_Height, const VType& a_Node, const EType& a_Weight)
		{
			ResizeGrid(a_Width, a_Height, City(a_Node, a_Weight));
		}

		void Link()
		{
			LinkVertices(ModifyPredicate());
		}

		void Link(const Modifier& a_Modifiers)
		{
			// Set the new modifiers
			m_Modifiers = a_Modifiers;

			// Link the vertices
			LinkVertices(ModifyPredicate());
		}

		template <typename Function>
		void Link(const Function& a_Predicate)
		{
			LinkVertices(a_Predicate);
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

		Vertices& operator[] (size_t idx)
		{
			return m_Vertices[idx];
		}

		const Vertices& operator[] (size_t idx) const
		{
			return m_Vertices[idx];
		}

		void Clear()
		{
			m_Vertices.clear();
		}

		bool Empty() const
		{
			return m_Vertices.empty() ? true : m_Vertices.front.empty();
		}

		size_t Width() const
		{
			return m_Vertices.size();
		}

		size_t Height() const
		{
			return m_Vertices.empty() ? 0 : m_Vertices.front().size();
		}

	protected:

		auto FindPredicate(const VType& a_Node) const
		{
			// Default find vertex predicate
			// Is vertex node equal to search node
			return [&a_Node](const City& v)->bool { return a_Node == v.Node(); };
		}

		auto ModifyPredicate() const
		{
			// Default modify weight predicate
			// Get average of path weights times by modifier
			return [this](const EType& e1, const EType& e2, const int& idx)->EType { return (((e1 + e2) / static_cast<EType>(2)) * m_Modifiers[idx]); };
		}

		City* FindVertex(const VType& a_Node)
		{
			return FindVertex(FindPredicate(a_Node));
		}

		template <typename Function>
		City* FindVertex(const Function& a_Predicate)
		{
			// Cycle through every row
			for (size_t i = 0; i < m_Vertices.size(); ++i)
			{
				// Try to find this vertex in this row
				City* Get = FindVertex(a_Predicate, i);

				// Was the vertex found?
				if (Get != nullptr)
				{
					// Return this vertex
					return Get;
				}
			}

			// Assert if the value wasn't found
			assert(false && "Failed to find city");

			// Return nullptr
			return nullptr;
		}

		template <typename Function>
		City* FindVertex(const Function& a_Predicate, size_t a_Index)
		{
			// Get a reference to the indexed row
			std::vector<City>& Row = m_Vertices[a_Index];

			// Find the vertex using the predicate
			auto Get = std::find_if(Row.begin(), Row.end(), a_Predicate);

			// Was the value found?
			if (Get != Row.end())
			{
				// Return a pointer to this vertex
				return &*Get;
			}
			else
			{
				// Return a nullptr
				return nullptr;
			}
		}

	private:

		void ResizeGrid(size_t a_Width, size_t a_Height, const City& a_Vertex)
		{
			// Clear all vertices
			//m_Vertices.clear();

			// Resize the main vector
			m_Vertices.resize(a_Width, {});

			// Cycle through the rows
			for (auto& row : m_Vertices)
			{
				// Resize this row, set all vertices to the given value
				row.resize(a_Height, a_Vertex);

				// Shrink this row
				//row.shrink_to_fit();
			}

			// Shrink the main vector
			m_Vertices.shrink_to_fit();
		}

		template <typename Function>
		void LinkVertices(const Function& a_Predicate)
		{
			// Type define for adjust arrays
			using Adjuster = std::array<int, 8>;

			// Adjust arrays for X and Y indexes
			Adjuster XAdjust{ 0, 1, 1, 1, 0, -1, -1, -1 };
			Adjuster YAdjust{ 1, 1, 0, -1, -1, -1, 0, 1 };

			// Get size of main array
			int Width = static_cast<int>(m_Vertices.size());

			// Declare extra variables now
			int Height = 0;
			int CXA = 0;
			int CYA = 0;

			// Cycle through every row
			for (int i = 0; i < Width; ++i)
			{
				// Get size of this array
				Height = static_cast<int>(m_Vertices[i].size());

				// Cycle through this row
				for (int j = 0; j < Height; ++j)
				{
					// Get a reference to current vertex
					City& Index = m_Vertices[i][j];

					// Clear the edges of this vertex
					Index.m_Edges.clear();

					// Is this vertex not blocked?
					if (!Index.Blocked())
					{
						// Cycle through each adjust
						for (int a = 0; a < 8; ++a)
						{
							// Get the current adjusts
							CXA = i + XAdjust[a];
							CYA = j + YAdjust[a];

							// Are either of the adjusts out of range
							if ((CXA < 0 || CXA >= Width) || (CYA < 0 || CYA >= Height))
							{
								// Skip this cycle
								continue;
							}

							// Get reference to adjusted vertex
							City& VAdjust = m_Vertices[CXA][CYA];

							// Is the adjusted vertex not blocked?
							if (!VAdjust.Blocked())
							{
								// Create a path between these vertices
								Index.m_Edges.push_back(std::make_pair(&VAdjust, a_Predicate(Index.Weight(), VAdjust.Weight(), a)));
							}
						}
					}
				}
			}
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

		template <typename Function, typename... Args>
		auto GenerateField(const Function& a_Predicate, Args... a_PredicateArgs)
		{
			using RType = std::result_of_t<Function(VType, VType, Args...)>;

			// Declare the flow field to return, set size to match main grid vector
			Flow_Field<RType> Field(Width());

			// Get the grids height
			size_t Amount = Height();

			// Cycle through the rows
			for (auto& row : Field)
			{
				// Reserve the amount to match grid height
				row.reserve(Amount);
			}

			// Declare variables needed now
			EType LCost;
			City* Closest;

			// Set the current row of the flow field
			auto Current = Field.begin();

			// Cycle through the rows
			for (auto& row : m_Vertices)
			{
				// Cycle through the vertices
				for (auto& vertex : row)
				{
					// Reset the lowest cost
					LCost = ELimits::max();

					// Set the closest city to this vertex
					Closest = &vertex;

					// Cycle through this city's connections
					for (auto& edge : vertex.Connections())
					{
						// Is this edges cost cheaper
						// than the current lowest?
						if (LCost >= edge.first->m_sGScore)
						{
							// Set this as the closest city
							Closest = edge.first;

							// Set the newest lowest cost
							LCost = edge.first->m_sGScore;
						}
					}

					// Determine this indexes field by using the predicate
					// Push this value into the back of the flow field
					Current->push_back(a_Predicate(vertex.Node(), Closest->Node(), a_PredicateArgs...));
				}

				// Increment the row
				++Current;
			}

			// Return the flow field
			return Field;
		}

	protected:

		Matrix m_Vertices;

		Modifier m_Modifiers;
	};
}

#endif // Michaels_Containers_Grid
