#include "Camera.h"

glm::mat4 Camera::GetViewMat() const {
	return m_view;
}

void Camera::ViewPointFix() {
	m_fixAt = 0.f;
}

void Camera::ViewPointUnFix() {
	m_fixAt = 1.f;
}

void Camera::Move(const glm::vec3& moveVec) {
	glm::vec3 m = moveVec * m_moveSpeed * m_deltaTime;
	m_EYE += m;
	m_AT += m * m_fixAt;
}

void Camera::Init() {

}

void Camera::Update(float deltaTime) {
	m_deltaTime = deltaTime;
}

void Camera::Render() {
	m_view = glm::lookAt(m_EYE, m_AT, m_UP);
}
