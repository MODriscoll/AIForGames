#include "Enemy.h"

#include "Behaviours\Steering\Steerer.h"
#include "Behaviours\Steering\Seek.h"
#include "Behaviours\Steering\Wander.h"

Enemy::Enemy(Agent* target)
{
	BehaveTree = new BehaviourTree();

	auto steerer = std::make_shared<Behaviour::Steerer>();

	steerer->MaxForce(400.f);

	auto seeker = std::make_shared<Behaviour::Seek>();

	seeker->MaxVelocity(400.f);
	seeker->Target(target);
	seeker->Weight(1.f);

	auto wanderer = std::make_shared<Behaviour::Wander>();

	wanderer->MaxVelocity(150.f);
	wanderer->Jitter(90.f);
	wanderer->Distance(50.f);
	wanderer->Radius(100.f);
	wanderer->Weight(2.f);

	steerer->Insert(wanderer);
	steerer->Insert(seeker);

	BehaveTree->SetRoot(steerer);
}

Enemy::~Enemy()
{
	delete BehaveTree;
}