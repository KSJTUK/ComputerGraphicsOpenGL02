#include "Camera.h"
#include "Object.h"

glm::mat4 Camera::GetViewMat() const {
	return m_view;
}

void Camera::CameraPositionSet(const glm::vec3& position) {
	m_EYE = position;
}

void Camera::CameraViewPointSet(const glm::vec3& at) {
	m_AT = at;
	if (m_AT == glm::vec3{ 0.f }) {
		m_AT = glm::vec3{ 0.f, 0.f, 1.f };
	}
}

void Camera::ViewPointFix() {
	m_fixAt = 0.f;
}

void Camera::ViewPointUnFix() {
	m_fixAt = 1.f;
}

void Camera::Input(unsigned char key, bool down) {
	switch (key) {
	case 'l':
		Move(-m_cameraAxisZ);
		break;
		
	case '.':
		Move(m_cameraAxisZ);
		break;

	case ',':
		Move(-m_cameraAxisX);
		break;

	case '/':
		Move(m_cameraAxisX);
		break;

	case 'm':
		Move(m_cameraAxisY);
		break;

	case 'n':
		Move(-m_cameraAxisY);
		break;

	case 'v':
		if (m_fixAt > 0.f) {
			ViewPointFix();
		}
		else {
			ViewPointUnFix();
		}
	}
}

void Camera::SpecialInput(int key, bool down) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		ViewPointMove(-m_angleSpeed, m_cameraAxisY);
		break;

	case GLUT_KEY_LEFT:
		ViewPointMove(m_angleSpeed, m_cameraAxisY);
		break;

	case GLUT_KEY_UP:
		ViewPointMove(m_angleSpeed, m_cameraAxisX);
		break;

	case GLUT_KEY_DOWN:
		ViewPointMove(-m_angleSpeed, m_cameraAxisX);
		break;
	}
}

void Camera::Move(const glm::vec3& moveVec) {
	glm::vec3 m = moveVec * m_moveSpeed * m_deltaTime;
	m_EYE += m;
	//m_AT += m * m_fixAt;
}

void Camera::ViewPointMove(float moveAngle, const glm::vec3& axis) {
	glm::vec4 at{ m_AT, 1.f };
	m_AT = glm::rotate(glm::mat4{ 1.f }, glm::radians(moveAngle), axis) * at;
	m_AT = glm::normalize(m_AT);
}

void Camera::OrbitY() {
	if (m_orbitY == 0) {
		m_orbitY = 1;
	}
	else if (m_orbitY == 1) {
		m_orbitY = -1;
	}
	else {
		m_orbitY = 0;
	}
}

void Camera::RotateY() {
	if (m_rotateY == 0) {
		m_rotateY = 1;
	}
	else if (m_rotateY == 1) {
		m_rotateY = -1;
	}
	else {
		m_rotateY = 0;
	}
}

void Camera::Init() {

}

void Camera::Update(float deltaTime) {
	m_deltaTime = deltaTime;

	// 카메라 기저 계산 순서 -> n, u, v -> 카메라 z, x, y축
	m_cameraAxisZ = glm::normalize(-m_AT);
	m_cameraAxisX = glm::normalize(glm::cross(m_UP, m_cameraAxisZ));
	m_cameraAxisY = glm::normalize(glm::cross(m_cameraAxisZ, m_cameraAxisX));

	ObjectMove::OrbitMove(m_AT, m_rotateY * 0.01f, m_cameraAxisY);
	ObjectMove::OrbitMove(m_EYE, m_orbitY * 0.01f, m_UP);
}

void Camera::Render() {
	m_view = glm::lookAt(m_EYE, m_EYE + m_AT, m_UP);
}
