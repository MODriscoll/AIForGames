#pragma once

#include "Objects\Agent.h"

class Enemy : public Agent
{
public:

	Enemy(Agent* target);
	~Enemy();
};