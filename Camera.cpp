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

void Camera::Input(unsigned char key) {
	switch (key) {
	case 'w':
		Move(-m_cameraAxisZ);
		break;
		
	case 's':
		Move(m_cameraAxisZ);
		break;

	case 'a':
		Move(-m_cameraAxisX);
		break;

	case 'd':
		Move(m_cameraAxisX);
		break;

	case 'm':
		Move(-m_cameraAxisY);
		break;

	case 'n':
		Move(m_cameraAxisY);
		break;
	}
}

void Camera::SpecialInput(int key) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		ViewPointMove(1.f, m_cameraAxisY);
		break;

	case GLUT_KEY_LEFT:
		ViewPointMove(-1.f, m_cameraAxisY);
		break;

	case GLUT_KEY_UP:
		ViewPointMove(-1.f, m_cameraAxisX);
		break;

	case GLUT_KEY_DOWN:
		ViewPointMove(1.f, m_cameraAxisX);
		break;
	}
}

void Camera::Move(const glm::vec3& moveVec) {
	glm::vec3 m = moveVec * m_moveSpeed * m_deltaTime;
	m_EYE += m;
	m_AT += m * m_fixAt;
}

void Camera::ViewPointMove(float moveAngle, const glm::vec3& axis) {
	glm::vec4 at{ m_AT, 1.f };
	m_AT = glm::rotate(glm::mat4{ 1.f }, glm::radians(moveAngle), axis) * at;
}

void Camera::Init() {

}

void Camera::Update(float deltaTime) {
	m_deltaTime = deltaTime;

	// ī�޶� ���� ��� ���� -> n, u, v -> ī�޶� z, x, y��
	m_cameraAxisZ = glm::normalize(m_EYE - m_AT);
	m_cameraAxisX = glm::normalize(glm::cross(m_UP, m_cameraAxisZ));
	m_cameraAxisY = glm::normalize(glm::cross(m_cameraAxisZ, m_cameraAxisX));
}

void Camera::Render() {
	m_view = glm::lookAt(m_EYE, m_AT, m_UP);
}
