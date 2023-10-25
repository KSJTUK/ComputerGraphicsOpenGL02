#include "Bullet.h"

Bullet::Bullet(const glm::vec3& initPos, const glm::vec3& dir, float speed) : m_bullet{ new Object{ "sphere", initPos }} {
	m_direction = dir;
	m_speed = speed;
	m_bullet->SetScaleFactor(glm::vec3{ 0.1f, 0.1f, 0.1f });
}

void Bullet::Update(float deltaTime) {
	if (m_bullet) {
		m_bullet->Update(deltaTime);
		m_bullet->Move(m_direction, m_speed);
	}
}

void Bullet::SetPosition(const glm::vec3& pos) {
	if (m_bullet) {
		m_bullet->SetPosition(pos);
	}
}

void Bullet::Render() {
	if (m_bullet) {
		m_bullet->Render();
	}
}
