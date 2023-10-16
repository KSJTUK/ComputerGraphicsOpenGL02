#include "Spiral.h"

void Spiral::Init(unsigned int shaderProgramID) {
	m_spiralBuffer = std::make_unique<GraphicBuffers>();
	m_spiralBuffer->Init(shaderProgramID);
}

void Spiral::MakeSpiral(int numOfPoints, const glm::vec3& center, float stepRadius, int angleDir) {
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
	m_spiralBuffer->SetTransformMat(glm::mat4{ 1.f });
	m_spiralBuffer->SetDrawMode(GL_LINE_STRIP);
	m_spiralBuffer->Render();
}
