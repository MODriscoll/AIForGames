#include "NavMesh\NavMeshUtility.h"

#include "Math\Maths.h"
#include "NavMesh\NavMeshComponents.h"

#include <algorithm>
#include <numeric>

#include <cassert>

namespace NavMesh
{

	bool NavMesh::ObstaclesCollide(const Obstacle& a_O1, const Obstacle& a_O2)
	{
		using namespace GJK;

		// For this check, use padded vertices
		std::vector<Vector2> V1 = a_O1.GetPaddedVertices();
		std::vector<Vector2> V2 = a_O2.GetPaddedVertices();

		// Declare the simplex
		Simplex Sim;

		// Set the initial direction using average points
		Vector2 Direction = AveragePoint(V1) - AveragePoint(V2);

		// Assure the direction is flat zero
		if (Direction == Vector2()) { Direction.x = 1.f; }

		// Calculate the initial vertex of the simplex
		Sim.Add(Support(V1, V2, Direction));

		// Is initial dp of vertex and direction negative?
		if (Vector2::Dot(Sim.Back(), Direction) <= 0.f)
		{
			// If dp is negative
			// There is no collision
			return false;
		}

		// Negate the direction
		Direction.Negate();

		// Declare security now ( might get stuck )
		size_t Security = 16;

		// Repeat until security break is triggered
		while (--Security != 0)
		{
			// Calculate the next vertex of the simplex
			Sim.Add(Support(V1, V2, Direction));

			// Is next dp of vertex and direction negative?
			if (Vector2::Dot(Sim.Back(), Direction) <= 0.f)
			{
				// If dp is negative
				// There is no collision
				return false;
			}
			else
			{
				// Check if the simplex contains the origin
				if (ContainsOrigin(Sim, Direction))
				{
					// Simplex contains origin
					// There is collision
					return true;
				}
			}

		}

		// Security was triggered
		// Return false by default
		return false;
	}

	// Source: https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
	bool ContainsPoint(const Node& a_Node, const Vector2& a_Point)
	{
		// Get reference to nodes vertices
		const std::vector<Vector2>& Vertices = a_Node.Vertices();

		// Get reference to each individual vertex
		const Vector2& V1 = Vertices[0];
		const Vector2& V2 = Vertices[1];
		const Vector2& V3 = Vertices[2];

		float A = 0.5f * (-V2.y * V3.x + V1.y * (-V2.x + V3.x) + V1.x * (V2.y - V3.y) + V2.x * V3.y);

		float Sign = A < 0.f ? -1.f : 1.f;

		float S = (V1.y * V3.x - V1.x * V3.y + (V3.y - V1.y) * a_Point.x + (V1.x - V3.x) * a_Point.y) * Sign;
		float T = (V1.x * V2.y - V1.y * V2.x + (V1.y - V2.y) * a_Point.x + (V2.x - V1.x) * a_Point.y) * Sign;

		return S > 0.f && T > 0.f && (S + T) < (2.f * A * Sign);
	}

	// Source: http://digestingduck.blogspot.com.au/2010/03/simple-stupid-funnel-algorithm.html
	std::vector<Vector2> SmoothPath(const std::vector<Node*>& a_Path)
	{
		using namespace StupidFunnel;

		// Assert if given path is empty
		assert(!a_Path.empty() && "Path must not be empty");

		// Declare variables needed now
		size_t Index = 0;
		PEdge* Portals = new PEdge[a_Path.size() + 1];

		// Add start position to the portal
		Portals[Index++] = { a_Path.front()->Position(), a_Path.front()->Position() };

		// Set the previous node to the initial node
		Node* Previous = a_Path.front();

		// Starting from the second, cycle through every node
		for (auto it = ++a_Path.begin(); it != a_Path.end(); ++it)
		{
			// Get current node as pointer
			Node* Current = *it;

			// Declare array to store adjacent vertices
			Vector2 Adjacent[2];
			size_t AdjacentCount = 0;

			// Cycle through the previous node's vertices
			for (auto& V1 : Previous->Vertices())
			{
				// Cycle through the current node's vertices
				for (auto& V2 : Current->Vertices())
				{
					// Do the nodes share this vertex?
					if (V1 == V2)
					{
						// Add this vertex to adjacency array
						Adjacent[AdjacentCount++] = V1;

						// Break from this loop
						break;
					}
				}
			}

			// Assert if nodes don't connect
			assert(AdjacentCount == 2 && "Invalid path ( path does not link )");

			// Get reference to nodes positions
			const Vector2& P1 = Current->Position();
			const Vector2& P2 = Previous->Position();

			// Vector to help calculate
			Vector2 Cal = P1 - P2;

			// Get the length squared between the current and previous node
			float Leg = Cal.Squared();

			// Declare the from previous vector
			Vector2 FP;

			// Is the length greater than zero?
			if (Leg > 0.f)
			{
				// Set the previous vector to be
				// displacement divided by magnitude
				FP = Cal / sqrtf(Leg);
			}

			// Recalculate
			Cal = Adjacent[0] - P2;

			// Get the length squared between the first adjacent and previous node
			Leg = Cal.Squared();

			// Declare the to adjacent ( index 0 ) vector
			Vector2 TA;

			// Is the length greater than zero?
			if (Leg > 0.f)
			{
				// Set the to vector to be
				// displacement divided by magnitude
				TA = Cal / sqrtf(Leg);
			}

			// Is the triangle facing the right way?
			if (Vector2::CrossZ(FP, TA) > 0.f)
			{
				// Add the adjacent vertices in current order
				Portals[Index++] = { Adjacent[0], Adjacent[1] };
			}
			else
			{
				// Add the adjacent vertices in reverse order
				Portals[Index++] = { Adjacent[1], Adjacent[0] };
			}

			// Set the current node to previous node
			Previous = Current;
		}

		// Add final position to the portal
		Portals[Index++] = { a_Path.back()->Position(), a_Path.back()->Position() };

		// Calculate and recieve the funnel
		std::vector<Vector2> Funnel = StringPull(Portals, Index);

		// Delete the portals array
		delete[] Portals;

		// Return the smoothed path
		return Funnel;
	}

	namespace GJK
	{
		Vector2 AveragePoint(const std::vector<Vector2>& a_Vertices)
		{
			// Calculate the average of all the vertices and return it
			return (std::accumulate(a_Vertices.cbegin(), a_Vertices.cend(), Vector2()) / static_cast<float>(a_Vertices.size()));
		}

		Vector2 FurthestVertex(const std::vector<Vector2>& a_Vertices, const Vector2& a_Direction)
		{
			// Create the vertex to return
			// Set it to the first vertex by default
			Vector2 RVec = a_Vertices.front();

			// Declare extra variables needed now
			float FD = Vector2::Dot(a_Direction, RVec);
			float CD = 0.f;

			// Starting from the second vertex, cycle
			// through all the remaining vertices
			for (auto it = ++a_Vertices.cbegin(); it != a_Vertices.cend(); ++it)
			{
				// Calculate the dot product
				CD = Vector2::Dot(*it, a_Direction);

				// Is this vertex further away?
				if (CD > FD)
				{
					// Set this vertex to be
					// the furthest vertex
					RVec = *it;
					FD = CD;
				}
			}

			// Return the furthest vertex
			return RVec;
		}

		Vector2 Support(const std::vector<Vector2>& a_V1, const std::vector<Vector2>& a_V2, const Vector2& a_Direction)
		{
			// Get the furthest point from the first polygon
			Vector2 P1 = FurthestVertex(a_V1, a_Direction);

			// Get the furthest point from the second polygon using the negated direction
			Vector2 P2 = FurthestVertex(a_V2, a_Direction.GetNegate());

			// Return the minkowski difference
			return P1 - P2;
		}

		bool ContainsOrigin(Simplex& a_Simplex, Vector2& a_Direction)
		{
			// Get point A and A to origin from the simplex
			Vector2 A = a_Simplex.Back();
			Vector2 AO = A.GetNegate();

			// Is the simplex only a line
			if (a_Simplex.Size() < 3)
			{
				// Set point B to be first vertex of the simplex
				Vector2 B = a_Simplex[0];

				// Get A to B
				Vector2 AB = B - A;

				// Re-set the direction to be tp of displacements
				a_Direction = Vector2::TripleProduct(AB, AO, AB);

				// Assure direction squared is not zero
				if (a_Direction.Squared() == 0.f) { a_Direction = AB.GetPerpendicular(); }

				// Since simplex is a line, no
				// collision is possible yet
				return false;
			}

			// If at this point, simplex has been formed
			// Everything from here will assume simplex has three vertices

			// Get point B and C from the simplex
			Vector2 B = a_Simplex[1];
			Vector2 C = a_Simplex[0];

			// Get A to B and A to C
			Vector2 AB = B - A;
			Vector2 AC = C - A;

			// Calculate triple product of displacements
			Vector2 ACP = Vector2::TripleProduct(AB, AC, AC);

			// Is the dp of ACP and AO positive?
			if (Vector2::Dot(ACP, AO) >= 0.f)
			{
				// Reset the direction
				a_Direction = ACP;
			}
			else
			{
				// Calculate triple product of displacements
				Vector2 ABP = Vector2::TripleProduct(AC, AB, AB);

				// Is the dp of ABP and AO negative?
				if (Vector2::Dot(ABP, AO) < 0.f)
				{
					// Origin is within simplex
					// This means there is collision
					return true;
				}
				else
				{
					// Reset the direction
					a_Direction = ABP;
				}
				
				// Remove point C from simplex
				a_Simplex.Remove(false);
			}

			// Remove point B from simplex
			a_Simplex.Remove(true);

			// Origin is outside of simplex
			// Return no collision
			return false;
		}
	}

	namespace StupidFunnel
	{
		std::vector<Vector2> StringPull(const PEdge* a_Portals, const size_t a_PortalsSize)
		{
			// Create the vector to return
			std::vector<Vector2> RFunnel;

			// Declare variables needed here
			size_t Points = 0, AIdx = 0, LIdx = 0, RIdx = 0;
			Vector2 APortal = a_Portals[0].first, LPortal = a_Portals[0].first, RPortal = a_Portals[0].second;

			// Add the initial point
			RFunnel.push_back(APortal);

			// Repeat until one of the sides has been surpassed
			for (size_t i = 1; i < a_PortalsSize; ++i)
			{
				// Get reference to left and right portal
				const Vector2& Left = a_Portals[i].first;
				const Vector2& Right = a_Portals[i].second;

				// Update the right vertex
				if (TriArea2(APortal, RPortal, Right) <= 0.f)
				{
					// Are portals equal?
					// If not is area greater than zero?
					if (APortal == RPortal || TriArea2(APortal, LPortal, Right) > 0.f)
					{
						// Tighten the funnel
						RPortal = Right;
						RIdx = i;
					}
					else
					{
						// The right portal is over the left portal
						// Insert the left portal and restart
						RFunnel.push_back(LPortal);

						// Set the left portal to be the new apex
						APortal = LPortal;
						AIdx = LIdx;

						// Reset the portal
						RPortal = APortal;
						RIdx = AIdx;

						// Reset the scan
						i = AIdx;

						// Skip the rest
						continue;
					}
				}

				// Update the left vertex
				if (TriArea2(APortal, LPortal, Left) >= 0.f)
				{
					// Are portals equal?
					// If not is area less than zero?
					if (APortal == LPortal || TriArea2(APortal, RPortal, Left) < 0.f)
					{
						// Tighten the funnel
						LPortal = Left;
						LIdx = i;
					}
					else
					{
						// The left portal is over the right portal
						// Insert the right portal and restart
						RFunnel.push_back(RPortal);

						// Set the right portal to be the new apex
						APortal = RPortal;
						AIdx = RIdx;

						// Reset the portal
						LPortal = APortal;
						LIdx = AIdx;

						// Reset the scan
						i = AIdx;

						// Skip the rest
						continue;
					}
				}
			}

			// Insert the final destination ( chance of being excluded )
			RFunnel.push_back(a_Portals[a_PortalsSize - 1].second);

			// Get rid of duplicates ( duplicates should already be next to each other )
			auto Last = std::unique(RFunnel.begin(), RFunnel.end());

			// Get rid of un-needed points
			RFunnel.erase(Last, RFunnel.end());

			// Return the funnel
			return RFunnel;
		}

		float TriArea2(const Vector2& a_v1, const Vector2& a_v2, const Vector2& a_v3)
		{
			Vector2 AB = a_v2 - a_v1;
			Vector2 AC = a_v3 - a_v1;

			return Vector2::CrossZ(AC, AB);
		}
	}
}