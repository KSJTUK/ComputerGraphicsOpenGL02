#include "Model.h"
#include "GraphicBuffers.h"
#include "pch.h"
#include <fstream>
#include <sstream>
#include <vector>

Model::Model(const std::string& objectFilePath) {
	ReadObject(objectFilePath.c_str());
}

Model::~Model() { }

void Model::ReadObject(const char* filePath) {
	std::ifstream objFile{ filePath, std::ios::in };

	std::vector<unsigned int> indiciesVec[3]{ }; // cnt: 0 == vertex, 1 == texture, 2 == nomal

	if (!objFile.is_open()) {
		assert(0);
	}

	std::string line{ "" };
	while (!objFile.eof()) {
		std::getline(objFile, line);
		std::stringstream sstream{ line };
		std::string delTag{ };     // �տ� �ִ� v, vn, f�� ���� �±� ���ſ�

		if (line[0] == 'v') {              // �� �� ���ڰ� v�̸� ������ ���� �����̴�
			if (line[1] == 'n') {          // vn == ���� ���
				glm::vec3 tempVec{ };      // ���� ��� ����
				sstream >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
				m_vertexNormals.push_back(tempVec);
			}
			else if (line[1] == 't');      // vt == �ؽ��� ��ǥ
			else if (line[1] == ' ') {     // v == ���� ��ǥ
				glm::vec3 tempVec{ };      // ���� ��ǥ ����
				sstream >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
				m_verticies.push_back(Vertex{ tempVec, glm::vec3{ }, glm::vec2{ } });
			}
		}
		else if (line[0] == 'f') {         // �� �� ���ڰ� f�̸� face(��)�� ���� �����̴�
			std::string face[3]{ };        // f a/b/c -> a == ���� �ε���, b == �ؽ�ó �ε���, c == ��� �ε���
			sstream >> delTag >> face[0] >> face[1] >> face[2];

			for (int i = 0; i < 3; ++i) {
				std::string temp{ };
				int cnt{ };
				int faceSize{ static_cast<int>(face[i].size()) };
				for (int c = 0; faceSize; ++c) {
					if (face[i][c] == '\0') {
						indiciesVec[cnt].push_back(std::stoi(temp) - 1);
						break;
					}

					if (face[i][c] == '/') {
						if (!temp.empty()) {
							indiciesVec[cnt].push_back(std::stoi(temp) - 1);
						}
						cnt++;
						temp.clear();
					}
					else {
						temp += face[i][c];
					}
				}
			}
		}
	}

	m_vertexIndicies = indiciesVec[0];
	m_vertexNormalIndicies = indiciesVec[1];
	m_textureIndicies = indiciesVec[2];
}

glm::mat4 Model::GetModelTransformMat() const {
	return m_modelTransform;
}

void Model::SetColor(const glm::vec3& color) {
	for (auto& v : m_verticies) {
		v.color = color;
	}
	m_graphicsBuffer->SetVerticies(m_verticies);
}

void Model::SetRandomColor() {
	for (auto& v : m_verticies) {
		v.color = glm::vec3{ glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f) };
	}
	m_graphicsBuffer->SetVerticies(m_verticies);
}

void Model::SetTransformMat(const glm::mat4& transformMat) {
	m_modelTransform = transformMat;
}

void Model::Init(unsigned int shaderProgramID) {
	m_graphicsBuffer = std::make_unique<class GraphicBuffers>();
	m_graphicsBuffer->Init(shaderProgramID);

	m_graphicsBuffer->SetVerticies(m_verticies);
	m_graphicsBuffer->SetIndexBuffer(m_vertexIndicies);
}

void Model::Update() {
}

void Model::Render() {
	m_graphicsBuffer->SetTransformMat(m_modelTransform);
	m_graphicsBuffer->Render();
	m_graphicsBuffer->SetTransformMat(glm::mat4{ 1.f });
}
