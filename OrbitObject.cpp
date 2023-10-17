#include "vertex_info.h"
#include "OrbitObject.h"
#include "GraphicBuffers.h"
#include "Model.h"

std::unique_ptr<GraphicBuffers> CircleEffect::m_circleBuffer{ };
std::vector<Vertex> CircleEffect::m_circleVertex{ };
std::vector<unsigned int> CircleEffect::m_circleVertexIndex{ };

OrbitObject::OrbitObject(const std::string& modelTag, const glm::vec3& orbitCenter, const glm::vec3& orbitAxis, float orbitRadius, float orbitSpeed) : Object{ modelTag } {
	float EPSILON{ 0.000001f };
	m_orbitAxis = glm::normalize(orbitAxis);
	m_orbitCenter = orbitCenter;
	if (glm::all(glm::lessThan(glm::abs(m_orbitAxis - glm::vec3{ 0.f, 1.f, 0.f }), glm::vec3(EPSILON)))) {
		m_orbitAxis = glm::vec3{ 1.f, 0.f, 0.f };
		m_position = orbitCenter + glm::normalize(glm::cross(m_orbitAxis, glm::vec3{ 0.f, 1.f, 0.f })) * orbitRadius;
	}
	else {
		m_position = orbitCenter + glm::normalize(glm::cross(m_orbitAxis, glm::vec3{ 0.f, 1.f, 0.f })) * orbitRadius;
	}
	m_orbitRadius = orbitRadius;
	m_orbitSpeed = orbitSpeed;
	m_circle.SetPosition(m_orbitCenter);
	m_circle.SetRadius(m_orbitRadius);
	m_circle.SetAxis(m_orbitAxis);
}

OrbitObject::~OrbitObject() { }

void OrbitObject::Update(float deltaTime, const glm::vec3& centerObjectDeltaPosition) {
	m_orbitCenter += centerObjectDeltaPosition;
	m_position += centerObjectDeltaPosition;
	ObjectMove::OrbitMove(m_position, m_orbitSpeed, m_orbitAxis, m_orbitCenter);
}

void OrbitObject::Render() {
	Object::Render();
	m_circle.DrawCircle();
}

void CircleEffect::SetRadius(float radius) {
	m_scale.x = radius;
	m_scale.y = 1.f;
	m_scale.z = radius;
}

void CircleEffect::SetPosition(const glm::vec3& position) {
	m_position = position;
}

void CircleEffect::SetAxis(const glm::vec3& axis) {
	//glm::vec3 right{ glm::normalize(glm::cross(axis, glm::vec3{ 0.f, 1.f, 0.f })) };
	glm::vec3 normal{ glm::normalize(axis) };

	m_rotAngle = std::acosf(glm::dot(normal, glm::vec3{ 0.f, 1.f, 0.f}));
	m_rotateAxis = glm::normalize(glm::cross(glm::vec3{ 0.f, 1.f, 0.f }, normal));
	//m_rotateAxis = glm::normalize(glm::cross(normal, glm::vec3{ 0.f, -1.f, 0.f }));
}

void CircleEffect::Init(unsigned int shaderProgramID) {
	m_circleBuffer = std::make_unique<GraphicBuffers>();
	m_circleBuffer->Init(shaderProgramID);
}

void CircleEffect::MakeCircle(float angleStep) {
	float angle{ 0.f };
	for (; angle < 360.f; angle += angleStep) {
		Vertex v{ };

		v.position.x = std::cosf(angle);
		v.position.y = 0.f;
		v.position.z = std::sinf(angle);

		v.color = { 1.f, 0.f, 0.f };
		m_circleVertex.push_back(v);
	}

	size_t loopSize{ m_circleVertex.size() };
	for (auto i = 0; i < loopSize; ++i) {
		m_circleVertexIndex.push_back(i);
	}

	m_circleBuffer->SetVerticies(m_circleVertex);
	m_circleBuffer->SetIndexBuffer(m_circleVertexIndex);
}

void CircleEffect::DrawCircle() {
	glm::mat4 transform{ 1.f };
	glm::mat4 scale = glm::scale(transform, m_scale);
	//glm::mat4 rot{ glm::yawPitchRoll(m_rotate.y, m_rotate.x, m_rotate.z) };

	glm::mat4 rot = glm::rotate(glm::mat4{ 1.f }, m_rotAngle, m_rotateAxis);
	/*rot = glm::rotate(rot, m_rotate.z, glm::vec3{ 0.f, 0.f, 1.f });
	rot = glm::rotate(rot, m_rotate.y, glm::vec3{ 0.f, 1.f, 0.f });*/
	//rot = glm::rotate(rot, m_rotate.x, glm::vec3{ 1.f, 0.f, 0.f });
	glm::mat4 trans= glm::translate(transform, m_position);

	transform = trans * rot * scale;

	m_circleBuffer->SetTransformMat(transform);
	m_circleBuffer->SetDrawMode(GL_LINE_STRIP);
	m_circleBuffer->Render();
}
