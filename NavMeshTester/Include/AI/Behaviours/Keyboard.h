#pragma once

#include "Behaviours\Interface\IBehaviour.h"

class Keyboard : public Behaviour::IBehaviour
{
public:

	Keyboard(int a_kUp = -1, int a_kDown = -1, int a_kLeft = -1, int a_kRight = -1);
	Keyboard(const std::string& a_Tag, int a_kUp = -1, int a_kDown = -1, int a_kLeft = -1, int a_kRight = -1);
	~Keyboard() = default;

	virtual Behaviour::eBehaviourResult Execute(Agent* a_Agent, float deltaTime) override;

	void SetKeys(int a_kUp, int a_kDown, int a_kLeft, int a_kRight);

	void SetSpeed(float a_Speed);

	void RotationBased(bool a_bBased);

	void GetKeys(int& a_kUp, int& a_kDown, int& a_kLeft, int& a_kRight) const;

	float GetSpeed() const;

	bool RotationBased() const;

private:

	int m_kUp;
	int m_kDown;
	int m_kLeft;
	int m_kRight;

	float m_Speed;

	bool m_bRotationBased;
};