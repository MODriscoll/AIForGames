#pragma once

#include "Behaviours\Interface\IBehaviour.h"

class Camera;

class CameraFollow : public Behaviour::IBehaviour
{
public:

	// Camera follow requires tag
	CameraFollow(const std::string& a_Tag);

	// Public destructor
	virtual ~CameraFollow() = default;

	// Moves the camera to follow the given agent
	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

public:

	// Set the camera to manipulate
	void SetCamera(Camera* a_Camera);

	// Get the camera being manipulated
	Camera* GetCamera();

public:

	// If camera should interpolate
	bool m_bInterpolate;

private:

	// The camera being manipulated
	Camera* m_Camera;
};