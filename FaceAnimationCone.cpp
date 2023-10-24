#include "FaceAnimationCone.h"
#include "ModelList.h"
#include "Model.h"
#include "Object.h"

bool ConeFace::Animation(bool dir, bool start) {
	return false;
}

void ConeFace::Init(unsigned int shaderProgramID, int faceNumber) {
	if (faceNumber >= 6) {
		return;
	}

	m_myFaceNumber = faceNumber;

	m_graphicBuffers = std::make_unique<GraphicBuffers>();
	m_graphicBuffers->Init(shaderProgramID);

	auto coneModel = ModelList::GetInst()->GetModel("cone");

	int faceVertexSize = m_myFaceNumber == 4 ? 6 : 3;

	std::vector<int> notSameIndex{ };
	for (auto i = 0; i < faceVertexSize; ++i) {
		unsigned int inputIndex = coneModel->m_vertexIndicies[faceNumber * 3 + i];
		m_index.push_back(inputIndex);
		if (notSameIndex.empty()) {
			notSameIndex.push_back(inputIndex);
		}
		else {
			bool isNotSameIndex{ true };
			for (auto index : notSameIndex) {
				if (inputIndex == index) {
					isNotSameIndex = false;
					break;
				}
			}

			if (isNotSameIndex) {
				notSameIndex.push_back(inputIndex);
			}
		}
	}

	for (auto& vIndex : notSameIndex) {
		m_vertex.push_back(coneModel->m_verticies[vIndex]);
	}

	std::vector<unsigned int> copyed_m_index{ m_index };

	int i{ 0 };
	int j{ 0 };
	for (; j < faceVertexSize;) {
		if (notSameIndex[i] == copyed_m_index[j]) {
			m_index[j] = i;
			j += 1;
		}
		else {
			i = (i + 1) % static_cast<int>(m_vertex.size());
		}
	}

	for (auto& vertex : m_vertex) {
		m_centerPosition += vertex.position;
	}

	m_centerPosition /= static_cast<float>(m_vertex.size());

	switch (m_myFaceNumber) {
	case 0:
		break;

	case 1:
		break;

	case 2:
		break;

	case 3:
		break;
	}

	for (auto& vertex : m_vertex) {
		vertex.position -= m_centerPosition;
	}

	m_graphicBuffers->SetVerticies(m_vertex);
	m_graphicBuffers->SetIndexBuffer(m_index);
}

void ConeFace::Update(float deltaTime) {

}

void ConeFace::Render() {
	glm::vec3 yprAngle{ glm::radians(m_rotate) };

	glm::mat4 transformMat{ 1.f };
	glm::mat4 translateMat{ glm::translate(transformMat, m_centerPosition + m_deltaPosition) };
	glm::mat4 rotationMat{ glm::yawPitchRoll(yprAngle.y, yprAngle.x, yprAngle.z) };
	glm::mat4 scaleMat{ glm::scale(transformMat, m_scale) };

	transformMat = translateMat * rotationMat * scaleMat;

	m_graphicBuffers->SetDrawMode(GL_TRIANGLES);
	m_graphicBuffers->SetTransformMat(transformMat);
	m_graphicBuffers->Render();
}

void FaceAnimationCone::Init(unsigned int shaderProgramID) {
	for (int i = 0; i < 5; ++i) {
		m_coneFaces[i].Init(shaderProgramID, i);
	}
}

void FaceAnimationCone::Input(unsigned char key, bool down) {

}

void FaceAnimationCone::Update(float deltaTime) {
	for (auto i = 0; i < 5; ++i) {
		if (!m_coneFaces[i].Animation(1, m_faceAnimationFlag[i])) {
			m_faceAnimationFlag[i] = false;
		}
	}
}

void FaceAnimationCone::Render() {
	for (auto& face : m_coneFaces) {
		face.Render();
	}
}
