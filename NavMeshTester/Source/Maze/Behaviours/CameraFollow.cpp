#include "Maze\Behaviours\CameraFollow.h"

#include "Maze\Agents\MazeAgent.h"

#include "Camera.h"

CameraFollow::CameraFollow(const std::string& a_Tag)
	: IBehaviour(a_Tag), m_Camera(nullptr), m_bInterpolate(true)
{
}

Behaviour::eBehaviourResult CameraFollow::Execute(Agent* a_Agent, float deltaTime)
{
	// Get the agent's position
	const Vector2& APos = a_Agent->GetTransform().Position;

	// Get reference to the camera
	Vector2& Cam = m_Camera->m_Position;

	// Are we interpolating?
	if (m_bInterpolate)
	{
		// Lerp the camera closer to the agent
		Cam = Vector2::Lerp(Cam, APos, deltaTime);
	}
	else
	{
		// Set camera to hover above agent
		Cam = APos;
	}

	// Return successfull result
	return Behaviour::eBehaviourResult::Success;
}

void CameraFollow::SetCamera(Camera* a_Camera)
{
	m_Camera = a_Camera;
}

Camera* CameraFollow::GetCamera()
{
	return m_Camera;
}
