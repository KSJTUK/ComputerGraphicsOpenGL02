#include "FaceAnimationCone.h"
#include "ModelList.h"
#include "Model.h"
#include "Object.h"

bool ConeFace::Animation(bool dir, bool start) {
	if (!start) {
		return false;
	}

	// atan 1 / 2 == 26.56f
	float atanHalf{ 26.56f };
	float angle{ 90.f + atanHalf };

	switch (m_myFaceNumber) {
	case 0:
		m_rotate.z += m_animationDir * 0.01f;
		if (m_rotate.z > angle) {
			m_rotate.z = angle;
			m_animationDir = -1.f;
		}
		else if (m_rotate.z <= 0.f){
			m_rotate.z = 0.f;
			m_animationDir = 1.f;
		}
		break;

	case 1:
		m_rotate.x += -m_animationDir * 0.01f;
		if (m_rotate.x >= 0.f) {
			m_rotate.x = 0.f;
			m_animationDir = 1.f;
		}
		else if (m_rotate.x <= -angle) {
			m_rotate.x = -angle;
			m_animationDir = -1.f;
		}
		break;

	case 2:
		m_rotate.z += -m_animationDir * 0.01f;
		if (m_rotate.z >= 0.f) {
			m_rotate.z = 0.f;
			m_animationDir = 1.f;
		}
		else if (m_rotate.z <= -angle) {
			m_rotate.z = -angle;
			m_animationDir = -1.f;
		}
		break;

	case 3:
		m_rotate.x += m_animationDir * 0.01f;
		if (m_rotate.x > angle) {
			m_rotate.x = angle;
			m_animationDir = -1.f;
		}
		else if (m_rotate.x <= 0.f) {
			m_rotate.x = 0.f;
			m_animationDir = 1.f;
		}
		break;

	default:
		break;
	}

	return true;
}

bool ConeFace::AnimationOpenAll(bool start) {
	if (!start) {
		return false;
	}
	float atanHalf{ 26.56f };
	float angle{ 2 * (90.f + atanHalf) };

	switch (m_myFaceNumber) {
	case 0:
		m_rotate.z += m_animationDir * 0.01f;
		if (m_rotate.z > angle) {
			m_rotate.z = angle;
			m_animationDir = -1.f;
		}
		else if (m_rotate.z <= 0.f) {
			m_rotate.z = 0.f;
			m_animationDir = 1.f;
		}
		break;

	case 1:
		m_rotate.x += -m_animationDir * 0.01f;
		if (m_rotate.x >= 0.f) {
			m_rotate.x = 0.f;
			m_animationDir = 1.f;
		}
		else if (m_rotate.x <= -angle) {
			m_rotate.x = -angle;
			m_animationDir = -1.f;
		}
		break;

	case 2:
		m_rotate.z += -m_animationDir * 0.01f;
		if (m_rotate.z >= 0.f) {
			m_rotate.z = 0.f;
			m_animationDir = 1.f;
		}
		else if (m_rotate.z <= -angle) {
			m_rotate.z = -angle;
			m_animationDir = -1.f;
		}
		break;

	case 3:
		m_rotate.x += m_animationDir * 0.01f;
		if (m_rotate.x > angle) {
			m_rotate.x = angle;
			m_animationDir = -1.f;
		}
		else if (m_rotate.x <= 0.f) {
			m_rotate.x = 0.f;
			m_animationDir = 1.f;
		}
		break;

	default:
		break;
	}

	return true;
}

void ConeFace::Init(unsigned int shaderProgramID, int faceNumber) {
	if (faceNumber >= 6) {
		return;
	}

	m_myFaceNumber = faceNumber;

	m_graphicBuffers = std::make_unique<GraphicBuffers>();
	m_graphicBuffers->Init(shaderProgramID);

	auto coneModel = ModelList::GetInst()->GetModel("cone");

	int faceVertexSize = 3;

	std::vector<int> notSameIndex{ };
	for (auto i = 0; i < faceVertexSize; ++i) {
		unsigned int inputIndex = coneModel->m_vertexIndicies[faceNumber * faceVertexSize + i];
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

	switch (m_myFaceNumber) {
	case 0:
		m_centerPosition.x = -0.5f;
		break;

	case 1:
		m_centerPosition.z = -0.5f;
		break;

	case 2:
		m_centerPosition.x = 0.5f;
		break;

	case 3:
		m_centerPosition.z = 0.5f;
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
	for (int i = 0; i < 6; ++i) {
		m_coneFaces[i].Init(shaderProgramID, i);
	}
}

void FaceAnimationCone::Input(unsigned char key, bool down) {

}

void FaceAnimationCone::Update(float deltaTime) {
	for (auto i = 0; i < 6; ++i) {
		if (!m_coneFaces[i].Animation(1, m_faceAnimationFlag[i])) {
			m_faceAnimationFlag[i] = false;
		}

		m_coneFaces[i].AnimationOpenAll(true);
	}
}

void FaceAnimationCone::Render() {
	for (auto& face : m_coneFaces) {
		face.Render();
	}
}
