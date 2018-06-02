#include "AI\Behaviours\Keyboard.h"

#include <Input.h>

#include "Objects\Agent.h"

Keyboard::Keyboard(int a_kUp, int a_kDown, int a_kLeft, int a_kRight)
	: IBehaviour("Keyboard"), m_Speed(100.f), m_bRotationBased(false)
{
	SetKeys(a_kUp, a_kDown, a_kLeft, a_kRight);
}

Keyboard::Keyboard(const std::string& a_Tag, int a_kUp, int a_kDown, int a_kLeft, int a_kRight)
	: IBehaviour(a_Tag), m_Speed(100.f), m_bRotationBased(false)
{
	SetKeys(a_kUp, a_kDown, a_kLeft, a_kRight);
}

Behaviour::eBehaviourResult Keyboard::Execute(Agent* a_Agent, float deltaTime)
{
	Transform2D& tra = a_Agent->GetTransform();
	RigidBody2D& rig = a_Agent->GetRigidBody();

	Vector2 directionX(1.f, 0.f);
	Vector2 directionY(0.f, 1.f);

	if (m_bRotationBased)
	{
		float rads = radf(tra.Rotation);

		directionX(0.f, 0.f);//(-sinf(rads), cosf(rads));
		directionY = Vector2::Direction(rads);
	}

	auto input = aie::Input::getInstance();

	Vector2 force;
	if (input->isKeyDown(m_kLeft))
	{
		force += directionX * -m_Speed * deltaTime;
	}
	if (input->isKeyDown(m_kRight))
	{
		force += directionX * m_Speed * deltaTime;
	}
	if (input->isKeyDown(m_kUp))
	{
		force += (directionY * m_Speed) * deltaTime;
	}
	if (input->isKeyDown(m_kDown))
	{
		force -= (directionY * m_Speed) * deltaTime;
	}

	rig.AddImpulse(force);

	if (force != Vector2())
	{
		return Behaviour::eBehaviourResult::Success;
	}
	else
	{
		return Behaviour::eBehaviourResult::Failure;
	}
}

void Keyboard::SetKeys(int a_kUp, int a_kDown, int a_kLeft, int a_kRight)
{
	if (a_kUp < 0) { m_kUp = aie::INPUT_KEY_W; }
	if (a_kDown < 0) { m_kDown = aie::INPUT_KEY_S; }
	if (a_kLeft < 0) { m_kLeft = aie::INPUT_KEY_A; }
	if (a_kRight < 0) { m_kRight = aie::INPUT_KEY_D; }
}

void Keyboard::SetSpeed(float a_Speed)
{
	m_Speed = a_Speed;
}

void Keyboard::RotationBased(bool a_bBased)
{
	m_bRotationBased = a_bBased;
}

void Keyboard::GetKeys(int& a_kUp, int& a_kDown, int& a_kLeft, int& a_kRight) const
{
	a_kUp = m_kUp;
	a_kDown = m_kDown;
	a_kLeft = m_kLeft;
	a_kRight = m_kRight;
}

float Keyboard::GetSpeed() const
{
	return m_Speed;
}

bool Keyboard::RotationBased() const
{
	return m_bRotationBased;
}
