#include "FaceAnimationCube.h"
#include "ModelList.h"
#include "Model.h"
#include "Object.h"

void CubeFace::Animation(bool dir) {
	float moveDir = dir ? 1.f : -1.f;

	switch (m_myFaceNumber) {
	case 0:
		m_rotate.x += moveDir * 1.f;
		break;

	default:
		break;
	}
}

void CubeFace::Init(unsigned int shaderProgramID, int faceNumber) {
	if (faceNumber >= 6) {
		return;
	}

	m_myFaceNumber = faceNumber;

	m_graphicBuffers = std::make_unique<GraphicBuffers>();
	m_graphicBuffers->Init(shaderProgramID);

	auto cubeModel = ModelList::GetInst()->GetModel("cube");
	
	std::vector<int> notSameIndex{ };
	for (auto i = 0; i < 6; ++i) {
		unsigned int inputIndex = cubeModel->m_vertexIndicies[faceNumber * 6 + i];
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
		m_vertex.push_back(cubeModel->m_verticies[vIndex]);
	}

	std::vector<unsigned int> copyed_m_index{ m_index };

	int i{ 0 };
	int j{ 0 };
	for (; j < 6;) {
		if (notSameIndex[i] == copyed_m_index[j]) {
			m_index[j] = i;
			j += 1;
		}
		else {
			i = (i + 1) % 4;
		}
	}

	for (auto& vertex : m_vertex) {
		m_centerPosition += vertex.position;
	}

	m_centerPosition /= static_cast<float>(m_vertex.size());

	for (auto& vertex : m_vertex) {
		vertex.position -= m_centerPosition;
	}

	m_graphicBuffers->SetVerticies(m_vertex);
	m_graphicBuffers->SetIndexBuffer(m_index);
}


void CubeFace::Update(float deltaTime) {
	
}

void CubeFace::Render() {
	glm::mat4 transformMat{ 1.f };
	glm::mat4 translateMat{ glm::translate(glm::mat4{ 1.f }, m_centerPosition) };
	m_graphicBuffers->SetDrawMode(GL_TRIANGLES);
	m_graphicBuffers->SetTransformMat(translateMat);
	m_graphicBuffers->Render();
}

void FaceAnimationCube::Init(unsigned int shaderProgramID) {
	for (int i = 0; i < 6; ++i) {
		m_cubeFaces[i].Init(shaderProgramID, i);
	}
}

void FaceAnimationCube::Update(float deltaTime) {
}

void FaceAnimationCube::Render() {
	for (auto& face : m_cubeFaces) {
		face.Render();
	}
}
