#include "Maze\Behaviours\MazeAvoider.h"

#include "Objects\Agent.h"

#include "Maze\Maze.h"

#include <Renderer2D.h>

MazeAvoider::MazeAvoider(const std::string& a_Tag)
	: ISteer(a_Tag), m_MaxAvoidForce(100.f)
{

}

Behaviour::eBehaviourResult MazeAvoider::Execute(Agent* a_Agent, float deltaTime)
{
	// Get reference to the agents blackboard
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Does this blackboard contain the maze?
	if (Board->GetAs_Pointer("Maze") != nullptr)
	{
		// Calculate and apply the force
		a_Agent->GetRigidBody().AddForce(Calculate(a_Agent));

		// Return successfull result
		return Behaviour::eBehaviourResult::Success;
	}
	
	// Return failed result
	return Behaviour::eBehaviourResult::Failure;
}

Vector2 MazeAvoider::Calculate(Agent* a_Agent)
{
	// Get reference to the agents blackboard
	Blackboard* Board = a_Agent->GetBehaviourTree()->GetBlackboard();

	// Get a pointer to the maze and flowfield
	Maze* Maz = static_cast<Maze*>(Board->GetAs_Pointer("Maze"));

	// Set the initial force
	Vector2 Force;

	// Is there no maze?
	if (Maz == nullptr)
	{
		// Return initial force
		return Force;
	}

	// Get reference to agents transform and rigidbody
	const Transform2D& ATra = a_Agent->GetTransform();
	const RigidBody2D& ARig = a_Agent->GetRigidBody();

	// Calculate the dynamic length using velocities
	float DLen = ARig.Velocity.Magnitude() / m_MaxVelocity;

	// Get the agents heading
	float Head = atan2f(ARig.Velocity.y, ARig.Velocity.x);

	count = 0;

	// Perform three raycasts
	// One to the left,
	// One straight ahead and
	// One to the right
	for (float i = -1.f; i < 2.f; ++i)
	{
		// Get the direction vector
		Vector2 Dir = (Vector2::Direction((Head + (RayDifference * i))) * m_MaxRange) * DLen;

		// Calculate the check points
		Vector2 CP1 = ATra.Position + Dir;
		Vector2 CP2 = ATra.Position + (Dir * 0.5f);

		cps[count++] = CP1;
		cps[count++] = CP2;

		// Determine the force to add, add it to the final force
		Force += DetermineForce(Maz, CP1, CP2);
	}

	// Was some force calculated
	if (Force != Vector2())
	{
		// Normalise the force
		Force.Normalise();

		// Scale the normalised force by the maximum velocity
		Force *= m_MaxVelocity;

		// Subtract the current velocity from the force
		Force -= ARig.Velocity;
	}

	// Return the force
	return Force;
}

void MazeAvoider::Render(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(0.8f, 0.6f, 1.f);
	for (size_t i = 0; i < 6; ++i)
	{
		const Vector2& pos = cps[i];

		renderer->drawCircle(pos.x, pos.y, 2.f);
	}
}

void MazeAvoider::SetMaxRange(float a_MaxRange)
{
	m_MaxRange = a_MaxRange;
}

void MazeAvoider::SetMaxAvoidForce(float a_MaxAvoidForce)
{
	m_MaxAvoidForce = a_MaxAvoidForce;
}

float MazeAvoider::GetMaxRange() const
{
	return m_MaxRange;
}

float MazeAvoider::GetMaxAvoidForce() const
{
	return m_MaxAvoidForce;
}

Vector2 MazeAvoider::DetermineForce(Maze* a_Maze, const Vector2& a_CP1, const Vector2& a_CP2)
{
	// Get the node containing the half point
	auto Nod = a_Maze->Node(a_CP2);

	// Was there a node?
	// If so, is it blocked?
	if (Nod != nullptr && Nod->Blocked())
	{
		// Get this nodes position
		const Vector2& NPos = Nod->Node().Position();

		// Calculate the force
		Vector2 Force = a_CP1 - NPos;

		// Normalise the force
		Force.Normalise();

		// Scale the force by the avoid force
		Force *= m_MaxAvoidForce;

		// Return the force
		return Force;
	}

	// Get the node containing the full point
	Nod = a_Maze->Node(a_CP1);

	// Was there a node?
	// If so, is it blocked?
	if (Nod != nullptr && Nod->Blocked())
	{
		// Get this nodes position
		const Vector2& NPos = Nod->Node().Position();

		// Calculate the force
		Vector2 Force = a_CP1 - NPos;

		// Normalise the force
		Force.Normalise();

		// Scale the force by the avoid force
		Force *= m_MaxAvoidForce;

		// Return the force
		return Force;
	}

	// Return no force
	return Vector2();
}
