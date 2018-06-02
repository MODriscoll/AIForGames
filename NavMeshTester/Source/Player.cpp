#include "Player.h"

#include "AI\Behaviours\Keyboard.h"
#include "Behaviours\Composite\Selector.h"

Player::Player()
{
}

Player::~Player()
{
	
}

void Player::Update(float deltaTime)
{
	Agent::Update(deltaTime);
}
