#include "Sphere.h"
#include "Model.h"
#include "ModelList.h"

Sphere::Sphere(const ModelList* const modelList) {
	m_model = modelList->GetModel("sphere");
}

Sphere::Sphere(const ModelList* const modelList, const glm::vec3& initPosition) {
	m_model = modelList->GetModel("sphere");
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
	m_position = glm::rotate(unit, glm::radians(m_orbitSpeed * m_deltaTime), glm::vec3{ 1.f, 0.f, 0.f }) * glm::vec4{ m_position, 1.f };
}

void Sphere::OrbitY() {
	m_position = glm::rotate(unit, glm::radians(m_orbitSpeed * m_deltaTime), glm::vec3{ 0.f, 1.f, 0.f }) * glm::vec4{ m_position, 1.f };
}

void Sphere::OrbitZ() {
	m_position = glm::rotate(unit, glm::radians(m_orbitSpeed * m_deltaTime), glm::vec3{ 0.f, 0.f, 1.f }) * glm::vec4{ m_position, 1.f };
}

void Sphere::Update(float deltaTime) {
	m_deltaTime = deltaTime;
}

void Sphere::Render() {
	glm::mat4 transform{ 1.f };
	//glm::vec3 orbitAngle{ m_orbitAngle.x,m_orbitAngle.z, m_orbitAngle.y };
	//glm::mat4 orbit = glm::orientate4(orbitAngle);
	glm::mat4 rot = glm::orientate4(m_rotAngle);
	glm::mat4 trans = glm::translate(unit, m_position);
	glm::mat4 scale = glm::scale(unit, m_sizeScale);


	transform = trans * rot * scale;

	m_model->SetTransformMat(transform);
	m_model->Render();
}
