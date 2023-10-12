#include "Axis.h"
#include "GraphicBuffers.h"
#include "gl_headers.h"
#include <numeric>

Axis::Axis() {

}

Axis::~Axis() {

}

void Axis::Init(unsigned int shaderProgramID) {
	constexpr float axisLength{ 100.f };

	m_axisBuffer = std::make_unique<GraphicBuffers>();
	m_axisBuffer->Init(shaderProgramID);

	m_axisVertex = {
		Vertex{ glm::vec3{ axisLength, 0.f, 0.f }, glm::vec3{ 1.f, 0.f, 0.f } },
		Vertex{ glm::vec3{ -axisLength, 0.f, 0.f }, glm::vec3{ 1.f, 0.f, 0.f } },
		Vertex{ glm::vec3{ 0.f, axisLength, 0.f }, glm::vec3{ 0.f, 1.f, 0.f } },
		Vertex{ glm::vec3{ 0.f, -axisLength, 0.f }, glm::vec3{ 0.f, 1.f, 0.f } },
		Vertex{ glm::vec3{ 0.f, 0.f, axisLength }, glm::vec3{ 0.f, 0.f, 1.f } },
		Vertex{ glm::vec3{ 0.f, 0.f, -axisLength }, glm::vec3{ 0.f, 0.f, 1.f } },
	};
	
	auto loopSize = m_axisVertex.size();
	for (auto i = 0; i < loopSize; ++i) {
		m_axisVertexIndex.push_back(i);
	}

	m_axisBuffer->SetVerticies(m_axisVertex);
	m_axisBuffer->SetIndexBuffer(m_axisVertexIndex);
}

void Axis::DrawAxis() {
	m_axisBuffer->SetTransformMat(glm::mat4{ 1.f });
	m_axisBuffer->SetDrawMode(GL_LINES);
	m_axisBuffer->Render();
}
