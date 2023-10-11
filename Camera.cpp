#include "Camera.h"

glm::mat4 Camera::GetViewMat() const {
	return m_view;
}

void Camera::Init() {

}

void Camera::Update() {

}

void Camera::Render() {
	m_view = glm::lookAt(m_EYE, m_AT, m_UP);
}
