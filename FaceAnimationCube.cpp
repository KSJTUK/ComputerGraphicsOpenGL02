#include "FaceAnimationCube.h"
#include "ModelList.h"
#include "Model.h"
#include "Object.h"

void CubeFace::Animation(bool dir) {
	switch (m_myFaceNumber) {
	case 1:
	case 3:
		m_deltaPosition.y += m_animationDir * 0.001f;
		if (m_deltaPosition.y >= 1.f) {
			m_deltaPosition.y = 1.f;
			m_animationDir = -1.f;
		}
		else if (m_deltaPosition.y <= 0.f){
			m_deltaPosition.y = 0.f;
			m_animationDir = 1.f;
		}
		break;

	case 2:
	case 0:
		m_scale += -m_animationDir * glm::vec3{ 0.001f };
		if (m_scale.x >= 1.f) {
			m_scale.x = 1.f;
			m_animationDir = 1.f;
		}
		else if (m_scale.x <= 0.f) {
			m_scale.x = 0.f;
			m_animationDir = -1.f;
		}
		break;

	case 5:
		m_rotate.x += m_animationDir * 0.1f;
		if (m_rotate.x >= 90.f) {
			m_rotate.x = 90.f;
			m_animationDir = -1.f;
		}
		else if ( m_rotate.x < 0.f) {
			m_rotate.x = 0.f;
			m_animationDir = 1.f;
		}
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
	switch (m_myFaceNumber) {
	case 1:
	case 3:
	case 5:
		m_centerPosition.y -= 0.5f;
		break;

	case 2:
		m_centerPosition.z -= 0.5f;
		break;

	case 0:
		m_centerPosition.y += 0.5f;
		break;

	default:
		break;
	}

	for (auto& vertex : m_vertex) {
		vertex.position -= m_centerPosition;
	}

	m_graphicBuffers->SetVerticies(m_vertex);
	m_graphicBuffers->SetIndexBuffer(m_index);
}


void CubeFace::Update(float deltaTime) {

}

void CubeFace::Render() {
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

void FaceAnimationCube::Init(unsigned int shaderProgramID) {
	for (int i = 0; i < 6; ++i) {
		m_cubeFaces[i].Init(shaderProgramID, i);
	}
}

void FaceAnimationCube::Update(float deltaTime) {
	for (auto& face : m_cubeFaces) {
		face.Animation(1);
	}
}

void FaceAnimationCube::Render() {
	for (auto& face : m_cubeFaces) {
		face.Render();
	}
}
