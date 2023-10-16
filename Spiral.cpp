#include "Spiral.h"

std::unique_ptr<GraphicBuffers> Spiral::m_spiralBuffer{ };
std::vector<Vertex> Spiral::m_spiralVertex{ };
std::vector<unsigned int> Spiral::m_spiralVertexIndex{ };

size_t Spiral::GetSpiralSize() const {
	return m_spiralVertex.size();
}

Vertex Spiral::operator[](size_t index) const {
	if (index >= m_spiralVertex.size()) {
		throw "vertex index size over";
	}
	Vertex rtVertex{ m_spiralVertex[index].position + m_position, m_spiralVertex[index].color, m_spiralVertex[index].texture };
	return rtVertex;
}

void Spiral::SetPosition(const glm::vec3& position) {
	m_position = position;
	m_transformMat = glm::translate(glm::mat4{ 1.f }, position);
}

void Spiral::Init(unsigned int shaderProgramID) {
	m_spiralBuffer = std::make_unique<GraphicBuffers>();
	m_spiralBuffer->Init(shaderProgramID);
}

void Spiral::MakeSpiral(int numOfPoints, const glm::vec3& center, float stepRadius, int angleDir) {
	if (!m_spiralVertex.empty()) {
		m_spiralVertex.clear();
	}

	if (!m_spiralVertexIndex.empty()) {
		m_spiralVertexIndex.clear();
	}

	float radius{ 0.f };
	float stepRadian{ glm::radians(360.f / numOfPoints * 6.f) };
	float radianAngle{ 0 };
	for (int i = 0; i < numOfPoints; ++i) {
		glm::vec3 point{ };
		glm::vec3 color{ glm::linearRand(glm::vec3{ 0.f }, glm::vec3{ 1.f }) };

		point.x = center.x + angleDir * std::cosf(radianAngle) * radius;
		point.z = center.z + angleDir * std::sinf(radianAngle) * radius;

		Vertex v{ point, color, glm::vec2{ } };

		m_spiralVertex.push_back(v);
		m_spiralVertexIndex.push_back(i);

		radius += stepRadian;
		radianAngle += stepRadian;
	}

	m_spiralBuffer->SetVerticies(m_spiralVertex);
	m_spiralBuffer->SetIndexBuffer(m_spiralVertexIndex);
}

void Spiral::DrawSpiral() {
	m_spiralBuffer->SetTransformMat(m_transformMat);
	m_spiralBuffer->SetDrawMode(GL_LINE_STRIP);
	m_spiralBuffer->Render();
}