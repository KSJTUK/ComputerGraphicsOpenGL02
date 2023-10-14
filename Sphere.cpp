#include "Sphere.h"
#include "Model.h"
#include "ModelList.h"

glm::vec3 ObjectMove::origin = glm::vec3{ 0.f };
glm::mat4 ObjectMove::unit = glm::mat4{ 1.f };
glm::vec3 ObjectMove::axisX = glm::vec3{ 1.f, 0.f, 0.f };
glm::vec3 ObjectMove::axisY = glm::vec3{ 0.f, 1.f, 0.f };
glm::vec3 ObjectMove::axisZ = glm::vec3{ 0.f, 0.f, 1.f };

Sphere::Sphere(const std::shared_ptr<class Model>& model) {
	m_model = model;
}

Sphere::Sphere(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition) {
	m_model = model;
	m_position = initPosition;
}

Sphere::~Sphere() { }

void Sphere::RotateX() {
	m_rotAngle.x += m_angleSpeed * m_deltaTime;
}

void Sphere::RotateY() {
	m_rotAngle.y += m_angleSpeed * m_deltaTime;
}

void Sphere::RotateZ() {
	m_rotAngle.z += m_angleSpeed * m_deltaTime;
}

void Sphere::OrbitX() {
	ObjectMove::OrbitMove(m_position, m_orbitSpeed * m_deltaTime, ObjectMove::axisX);
}

void Sphere::OrbitY() {
	ObjectMove::OrbitMove(m_position, m_orbitSpeed * m_deltaTime, ObjectMove::axisY);
}

void Sphere::OrbitZ() {
	ObjectMove::OrbitMove(m_position, m_orbitSpeed * m_deltaTime, ObjectMove::axisZ);
}

glm::vec3 Sphere::Orbit(const float& angle, const glm::vec3& axis, const glm::vec3& center) {
	glm::vec3 rtVec{ m_position };
	ObjectMove::OrbitMove(m_position, angle, axis, center);
	rtVec = m_position - rtVec;
	return rtVec;
}

glm::vec3 Sphere::GetPosition() const {
	return m_position;
}

void Sphere::SetPosition(const glm::vec3& position) {
	m_position = position;
}

void Sphere::Update(float deltaTime) {
	m_deltaTime = deltaTime;
}

void Sphere::Render() {
	glm::mat4 transform{ 1.f };
	glm::mat4 rot = glm::orientate4(glm::radians(m_rotAngle));
	glm::mat4 trans = glm::translate(unit, m_position);
	glm::mat4 scale = glm::scale(unit, m_sizeScale);

	transform = trans * rot * scale;

	m_model->SetTransformMat(transform);
	m_model->Render();
}

void ObjectMove::OrbitMove(glm::vec3& position, const float& angle, const glm::vec3& axis, const glm::vec3& origin) {
	glm::vec4 rotPos{ position - origin, 1.f };
	position = glm::orientate4(glm::radians(angle * axis)) *  rotPos;
	position += origin;
}

void ObjectMove::Move(glm::vec3& position, const glm::vec3& direction, const float speed) {
	position += direction * speed;
}
