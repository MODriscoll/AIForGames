#include "Camera.h"

#include <Renderer2D.h>

void Camera::SetSize(size_t a_X, size_t a_Y)
{
	m_X = a_X;
	m_Y = a_Y;
}

void Camera::SetCamera(aie::Renderer2D* renderer)
{
	// Get lower left
	Vector2 Lef = GetBottomLeft();

	// Set the renderers camera position
	renderer->setCameraPos(Lef.x, Lef.y);
}

Vector2 Camera::GetBottomLeft() const
{
	// Set the lower left of the screen to the position
	Vector2 Lef = m_Position;

	// Subtract half the size from the camera
	Lef.x -= ((float)m_X * 0.5f);
	Lef.y -= ((float)m_Y * 0.5f);

	// Return the position
	return Lef;
}
