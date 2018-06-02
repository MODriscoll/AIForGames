#pragma once

#include "Objects\Agent.h"

class Player : public Agent
{
public:

	Player();
	~Player();

	virtual void Update(float deltaTime) override;
};