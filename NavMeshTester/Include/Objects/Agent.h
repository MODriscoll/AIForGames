#pragma once

#include "GameObject.h"

#include "Behaviours\Tree\BehaviourTree.h"

// Improve later
class Agent : public GameObject
{
public:

	using BehaviourTree = Behaviour::BehaviourTree;

	Agent()
		: GameObject("Agent"), BehaveTree(nullptr) { }
	Agent(const std::string& a_Tag)
		: GameObject(a_Tag), BehaveTree(nullptr) { }
	virtual ~Agent() = default;

	virtual void Update(float deltaTime)
	{
		if (BehaveTree != nullptr)
		{
			BehaveTree->Execute(this, deltaTime);
		}

		GameObject::Update(deltaTime);
	}

	void SetBehaviourTree(BehaviourTree* a_BehaviourTree)
	{
		BehaveTree = a_BehaviourTree;
	}

	BehaviourTree* GetBehaviourTree()
	{
		return BehaveTree;
	}

protected:

	BehaviourTree* BehaveTree;
};