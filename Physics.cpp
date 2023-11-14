#include "Physics.h"

Physics::Physics() { }

Physics::~Physics() { }

void Physics::Jump(float jumpPower) {
	m_power.y = jumpPower;
}

void Physics::Gravity() {
	m_power.y -= m_gravity * m_deltaTime * m_deltaTime;
}

void Physics::ResetPhysics() {
	m_power = glm::vec3{ };
}

void Physics::SetPower(const glm::vec3& power) {
	m_power = power;
}

void Physics::Update(float deltaTime) {
	m_deltaTime = deltaTime;
}
