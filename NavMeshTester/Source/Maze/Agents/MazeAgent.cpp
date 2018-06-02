#include "Maze\Agents\MazeAgent.h"

#include <Renderer2D.h>

MazeAgent::MazeAgent()
	: Agent("MazeAgent"), m_Radius(10.f)
{

}

void MazeAgent::Render(aie::Renderer2D* renderer)
{
	// Set the render colour to zero
	renderer->setRenderColour(1.f, 1.f, 1.f);

	// Draw a circle to represent the agent
	renderer->drawCircle(Transform.Position.x, Transform.Position.y, m_Radius, 1.f);

	// Set render colour to green
	renderer->setRenderColour(0.f, 1.f, 0.f);

	// Get the agents rotation as a radians value
	float Rads = radf(Transform.Rotation);

	// Draw an arrow to represent this agent's rotation
	//renderer->drawArrowFromPoint(Transform.Position.x, Transform.Position.y, 
	//	m_Radius * 2.5f, Rads, pif * 0.5f, m_Radius, m_Radius * 0.2f, 0.f);

	// Set render colour to red
	renderer->setRenderColour(1.f, 0.5f, 0.5f);

	// Get the sum of the agents position and velocity
	Vector2 Sum = Transform.Position + RigidBody.Velocity;

	// Draw an arrow to represents this agent's velocity
	renderer->drawArrowToPoint(Transform.Position.x, Transform.Position.y, Sum.x, Sum.y,
		pif * 0.5f, m_Radius, m_Radius * 0.2f, 0.f);
}

void MazeAgent::Clamp(const Vector2& a_LowerLeft, const Vector2& a_UpperRight)
{
	// Clamp this agents position
	Transform.Position.Clamp(a_LowerLeft, a_UpperRight);
}

void MazeAgent::SetRadius(float a_Radius)
{
	// Set the radius
	m_Radius = a_Radius;
}

float MazeAgent::GetRadius() const
{
	// Get the radius
	return m_Radius;
}
