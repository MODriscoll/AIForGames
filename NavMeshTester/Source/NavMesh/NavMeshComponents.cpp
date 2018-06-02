#include "NavMesh\NavMeshComponents.h"

#include "Math\Matrices\Matrix2.h"

#include <numeric>

#include <cassert>

namespace NavMesh
{
	Node::Node()
		: m_sVisited(false), m_sQueued(false), m_sFrom(nullptr), 
		m_sGScore(WLimits::max()), m_sFScore(WLimits::max()) { }

	Node::Node(const std::vector<Vector2>& a_Vertices)
		: m_Vertices(std::move(a_Vertices)), m_sVisited(false), m_sQueued(false),
		m_sFrom(nullptr), m_sGScore(WLimits::max()), m_sFScore(WLimits::max())
	{
		// Assert if there isn't exactly three vertices
		assert(m_Vertices.size() == 3 && "NavMesh Node can only have three vertices");

		// Calculate this nodes position
		m_Position = (std::accumulate(m_Vertices.cbegin(), m_Vertices.cend(), m_Position) / (float)m_Vertices.size());
	}

	Node::Node(const std::initializer_list<Vector2>& a_Vertices)
		: m_Vertices(a_Vertices), m_sVisited(false), m_sQueued(false),
		m_sFrom(nullptr), m_sGScore(WLimits::max()), m_sFScore(WLimits::max())
	{
		// Assert if there isn't exactly three vertices
		assert(m_Vertices.size() == 3 && "NavMesh Node can only have three vertices");

		// Calculate this nodes position
		m_Position = (std::accumulate(m_Vertices.cbegin(), m_Vertices.cend(), m_Position) / (float)m_Vertices.size());
	}

	Obstacle::Obstacle(const std::vector<Vector2>& a_Vertices, float a_Padding)
		: m_Vertices(std::move(a_Vertices)), m_Padding(a_Padding)
	{
		// Assert if the vector is empty
		assert(m_Vertices.size() > 2u && "NavMesh Obstacle must at least have three vertices");

		// Assert if padding is less than zero
		assert(!std::signbit(m_Padding) && "NavMesh Obstacle padding must have a positive value");
	}

	Obstacle::Obstacle(const std::initializer_list<Vector2>& a_Vertices, float a_Padding)
		: m_Vertices(a_Vertices), m_Padding(a_Padding)
	{
		// Assert if the vector is empty
		assert(m_Vertices.size() > 2u && "NavMesh Obstacle must at least have three vertices");

		// Assert if padding is less than zero
		assert(!std::signbit(m_Padding) && "NavMesh Obstacle padding must have a positive value");
	}

	std::vector<Vector2> Obstacle::GetPaddedVertices() const
	{
		// Create vector to return
		std::vector<Vector2> PVertices;

		// Calculate the directions for the first vertex
		Vector2 D1 = m_Vertices.front() - m_Vertices.back();
		Vector2 D2 = m_Vertices.front() - m_Vertices[1];

		Vector2 DF = D1 + D2;

		// Normalise the final direction
		DF.Normalise();

		// Calculate the final position and add it into the array
		PVertices.push_back(m_Vertices.front() + (DF * m_Padding));

		// Cycle through each vertex in between the first and last
		for (int i = 1; i < (int)m_Vertices.size() - 1; ++i)
		{
			// Calculate the directions for this vertex
			D1 = m_Vertices[i] - m_Vertices[i - 1];
			D2 = m_Vertices[i] - m_Vertices[i + 1];

			DF = D1 + D2;

			// Normalise the final direction
			DF.Normalise();

			// Calculate the final position and add it into the array
			PVertices.push_back(m_Vertices[i] + (DF * m_Padding));
		}

		// Calculate the directions for the last vertex
		D1 = m_Vertices.back() - m_Vertices[m_Vertices.size() - 2];
		D2 = m_Vertices.back() - m_Vertices.front();

		DF = D1 + D2; DF.Normalise();

		// Normalise the final direction
		DF.Normalise();

		// Calculate the final position and add it into the array
		PVertices.push_back(m_Vertices.back() + (DF * m_Padding));

		// Return the vertices
		return PVertices;
	}
}