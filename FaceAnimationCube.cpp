#include "FaceAnimationCube.h"
#include "ModelList.h"
#include "Model.h"
#include "Object.h"

bool CubeFace::Animation(bool dir, bool start) {
	if (!start) {
		return false;
	}

	switch (m_myFaceNumber) {
	case 1:
	case 3:
		m_deltaPosition.y += m_animationDir * 0.001f;
		if (m_deltaPosition.y >= 1.f) {
			m_deltaPosition.y = 1.f;
			m_animationDir = -1.f;
			return false;
		}
		else if (m_deltaPosition.y <= 0.f){
			m_deltaPosition.y = 0.f;
			m_animationDir = 1.f;
			return false;
		}
		break;

	case 0:
	case 4:
		m_scale += -m_animationDir * glm::vec3{ 0.001f };
		if (m_scale.x >= 1.f) {
			m_scale.x = 1.f;
			m_animationDir = 1.f;
			return false;
		}
		else if (m_scale.x <= 0.3f) {
			m_scale.x = 0.3f;
			m_animationDir = -1.f;
			return false;
		}
		break;

	case 5:
		m_rotate.x += m_animationDir * 0.1f;
		if (m_rotate.x >= 90.f) {
			m_rotate.x = 90.f;
			m_animationDir = -1.f;
			return false;
		}
		else if ( m_rotate.x < 0.f) {
			m_rotate.x = 0.f;
			m_animationDir = 1.f;
			return false;
		}
		break;

	case 2:
		m_rotate.x += 0.1f;
		break;

	default:
		break;
	}

	return true;
}

void CubeFace::Orbit() {
	m_rotateAllY += 0.1f;
}

glm::vec3 CubeFace::GetColor() const {
	return m_color;
}

void CubeFace::SetColor(const glm::vec3& color) {
	m_color = color;
}

void CubeFace::Init(unsigned int shaderProgramID, int faceNumber, const glm::vec3& color) {
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
		m_centerPosition.y -= 0.5f;
		break;

	case 5:
		m_centerPosition.x -= 0.5f;
		break;

	case 4:
		m_centerPosition.z -= 0.5f;
		break;

	case 0:
		m_centerPosition.y -= 0.5f;
		break;

	case 2:
		m_centerPosition.x -= 0.5f;
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
		m_centerPosition.y -= 0.5f;
		break;

	case 5:
		m_centerPosition.x -= 0.5f;
		break;

	case 4:
		m_centerPosition.z -= 0.5f;
		break;

	case 0:
		m_centerPosition.y -= 0.5f;
		break;

	case 2:
		m_centerPosition.x -= 0.5f;
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
	glm::mat4 rotationAll{ glm::yawPitchRoll(glm::radians(m_rotateAllY), 0.f, 0.f) };
	glm::mat4 afterScale{ glm::scale(transformMat, m_afterScale) };

	transformMat = rotationAll * afterScale * translateMat * rotationMat * scaleMat;

	m_graphicBuffers->SetColor(m_color);
	m_graphicBuffers->SetDrawMode(GL_TRIANGLES);
	m_graphicBuffers->SetTransformMat(transformMat);
	m_graphicBuffers->Render();
}

void FaceAnimationCube::Init(unsigned int shaderProgramID) {
	for (int i = 0; i < 6; ++i) {
		m_cubeFaces[i].Init(shaderProgramID, i);
		m_cubeFaces[i].SetColor(glm::linearRand(glm::vec3{ 0.f }, glm::vec3{ 1.f }));
	}
}

void FaceAnimationCube::Input(unsigned char key, bool down) {
	if (!down) {
		return;
	}

	switch (key) {
	case 't':
		m_faceAnimationFlag[2] = !m_faceAnimationFlag[2];
		break;

	case 'f':
		m_faceAnimationFlag[5] = true;
		break;

	case 's':
		m_faceAnimationFlag[1] = true;
		m_faceAnimationFlag[3] = true;
		break;

	case 'b':
		m_faceAnimationFlag[0] = true;
		m_faceAnimationFlag[4] = true;
		break;

	case 'y':
		m_rotateY = !m_rotateY;
		break;
		
	}
}

void FaceAnimationCube::Update(float deltaTime) {
	for (auto i = 0; i < 6; ++i) {
		if (!m_cubeFaces[i].Animation(1, m_faceAnimationFlag[i])) {
			m_faceAnimationFlag[i] = false;
		}

		if (m_rotateY) {
			m_cubeFaces[i].Orbit();
		}
	}
}

void FaceAnimationCube::Render() {
	for (auto& face : m_cubeFaces) {
		face.Render();
	}
}

TheaterBox::TheaterBox() {

}

TheaterBox::~TheaterBox() { }

void TheaterBox::SetBoxAnimationFlag() {
	m_boxAnimation = !m_boxAnimation;
}

void TheaterBox::Init(unsigned int shaderProgramID) {
	// colorSet
	m_cubeFaces[0].Init(shaderProgramID, 0, glm::vec3{ 1.f, 0.f, 0.f });
	m_cubeFaces[1].Init(shaderProgramID, 1, glm::vec3{ 0.f, 1.f, 0.f });
	m_cubeFaces[2].Init(shaderProgramID, 2, glm::vec3{ 1.f, 0.f, 1.f });
	m_cubeFaces[3].Init(shaderProgramID, 3, glm::vec3{ 0.f, 0.f, 1.f });
	m_cubeFaces[4].Init(shaderProgramID, 4, glm::vec3{ 0.f, 1.f, 1.f });
	m_cubeFaces[5].Init(shaderProgramID, 5, glm::vec3{ 1.f, 1.f, 0.f });
	m_cubeFaces[6].Init(shaderProgramID, 5, glm::vec3{ 1.f, 1.f, 0.f });

	m_cubeFaces[5].m_centerPosition.x += 1.f;

	m_cubeFaces[5].m_rotate.y = 180.f;

	m_cubeFaces[5].m_animationDir = 1.f;
	m_cubeFaces[6].m_animationDir = -1.f;


	m_cubeFaces[5].m_scale = glm::vec3{ 0.5f, 1.f, 1.f };
	m_cubeFaces[6].m_scale = glm::vec3{ 0.5f, 1.f, 1.f };
	for (int i = 0; i < 7; ++i) {
		m_cubeFaces[i].m_afterScale = glm::vec3{ 40.f, 40.f, 40.f };
		m_cubeFaces[i].m_centerPosition += glm::vec3{ 0.f, 0.5f, 0.f };
		m_cubeFaces[i].SetColor(glm::linearRand(glm::vec3{ 0.f }, glm::vec3{ 1.f }));
	}
}

void TheaterBox::Update(float deltaTime) {
	if (m_boxAnimation) {
		if (m_cubeFaces[5].m_rotate.y < 180.f) {
			m_cubeFaces[5].m_rotate.y = 180.f;
			m_cubeFaces[5].m_animationDir = 1.f;
			m_boxAnimation = false;
		}
		else if (m_cubeFaces[5].m_rotate.y > 360.f) {
			m_cubeFaces[5].m_rotate.y = 360.f;
			m_cubeFaces[5].m_animationDir = -1.f;
			m_boxAnimation = false;
		}

		if (m_cubeFaces[6].m_rotate.y < -180.f) {
			m_cubeFaces[6].m_rotate.y = -180.f;
			m_cubeFaces[6].m_animationDir = 1.f;
			m_boxAnimation = false;
		}
		else if (m_cubeFaces[6].m_rotate.y > 0.f) {
			m_cubeFaces[6].m_rotate.y = 0.f;
			m_cubeFaces[6].m_animationDir = -1.f;
			m_boxAnimation = false;
		}

		m_cubeFaces[5].m_rotate.y += m_cubeFaces[5].m_animationDir * 0.1f;
		m_cubeFaces[6].m_rotate.y += m_cubeFaces[6].m_animationDir * 0.1f;
	}
}

void TheaterBox::Render() {
	for (auto& face : m_cubeFaces) {
		face.Render();
	}
}
