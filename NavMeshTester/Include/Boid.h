#pragma once

#include "Objects\Agent.h"

class Boid : public Agent
{
public:

	Boid(BehaviourTree* a_Tree)
	{
		BehaveTree = a_Tree;
	}
};