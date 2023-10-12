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
	m_rotAngle.x += 1.f;
}

void Sphere::RotateY() {
	m_rotAngle.y += 1.f;
}

void Sphere::RotateZ() {
	m_rotAngle.z += 1.f;
}

void Sphere::Update(float deltaTime) {
	m_deltaTime = deltaTime;
}

void Sphere::Render() {
	glm::mat4 transform{ glm::translate(glm::mat4{ 1.f }, m_position) };
	transform = glm::rotate(transform, glm::radians(m_rotAngle.x), glm::vec3{ 1.f, 0.f, 0.f });
	transform = glm::rotate(transform, glm::radians(m_rotAngle.y), glm::vec3{ 0.f, 1.f, 0.f });
	transform = glm::rotate(transform, glm::radians(m_rotAngle.z), glm::vec3{ 0.f, 0.f, 1.f });
	transform = glm::scale(transform, m_sizeScale);
	m_model->SetTransformMat(transform);
	m_model->Render();
}
