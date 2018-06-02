#pragma once

#include "Math\Vectors\Vector2.h"

namespace aie
{
	class Renderer2D;
}

class Camera final
{
public:

	// Default constructor
	Camera() = default;

	// Default destructor
	~Camera() = default;

	// Position of the camera
	Vector2 m_Position;

	// Set the size of the camera
	void SetSize(size_t a_X, size_t a_Y);

	// Set the renderers camera position
	void SetCamera(aie::Renderer2D* renderer);

	// Gets the bottom left position of the character
	Vector2 GetBottomLeft() const;

private:

	// Size of the camera
	size_t m_X, m_Y;
};