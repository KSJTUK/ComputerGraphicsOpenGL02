#include "Mesh.h"
#include "Renderer.h"
#include "pch.h"
#include <fstream>
#include <sstream>
#include <vector>

Mesh::Mesh() {
	ReadObject("cube.obj");
}

Mesh::~Mesh() {
	SafeDeleteArrayPointer(m_verticies);
	SafeDeleteArrayPointer(m_vertexIndicies);
	SafeDeleteArrayPointer(m_vertexNormalIndicies);
	SafeDeleteArrayPointer(m_textureIndicies);
}

void Mesh::ReadObject(const char* filePath) {
	std::ifstream objFile{ filePath, std::ios::in };

	std::vector<glm::vec3> vertexVec{ };
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
			if (line[1] == 'n');           // vn == ���� ���
			else if (line[1] == 't');      // vt == �ؽ��� ��ǥ
			else if (line[1] == ' ') {     // v == ���� ��ǥ
				glm::vec3 tempVec{ };      // ���� ��ǥ ����
				sstream >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
				vertexVec.push_back(tempVec);
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
						indiciesVec[cnt].push_back(std::stoi(temp));
						break;
					}

					if (face[i][c] == '/') {
						if (!temp.empty()) {
							indiciesVec[cnt].push_back(std::stoi(temp));
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

	MakeVertexAndIndicies(vertexVec, indiciesVec);
}

void Mesh::MakeVertexAndIndicies(std::vector<glm::vec3>& verticies, std::vector<unsigned int>* indicies) {
	m_verticiesDataSize = static_cast<unsigned int>(verticies.size());
	m_verticies = new Vertex[m_verticiesDataSize];

	for (unsigned int i = 0; i < m_verticiesDataSize; ++i) {
		m_verticies[i].position = verticies[i];
		m_verticies[i].color = glm::vec3{ glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f) };
		std::cout << "vertex[" << i << "]: " << m_verticies[i].position.x << " " << m_verticies[i].position.y << " " << m_verticies[i].position.z << std::endl;
	}

	m_vertexIndiciesSize = static_cast<unsigned int>(indicies[0].size());
	m_vertexIndicies = new unsigned int[m_vertexIndiciesSize];
	
	for (unsigned int i = 0; i < m_vertexIndiciesSize; ++i) {
		if (i % 3 == 0) {
			std::cout << "face[" << i / 3 << "]: ";
		}
		m_vertexIndicies[i] = indicies[0][i] - 1;
		std::cout << " " << m_vertexIndicies[i];
		if (i % 3 == 2) {
			std::cout << "\n";
		}
	}
}

void Mesh::Update() {
}

void Mesh::Render(class Renderer* renderer) {
	glm::mat4 iMat{ 1.f };
	glm::mat4 s = glm::scale(iMat, glm::vec3{ 0.25f, 0.25f, 0.25f });
	glm::mat4 t = glm::translate(iMat, glm::vec3{ 0.f, 0.f, 0.f });
	glm::mat4 r = glm::rotate(iMat, glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 tr = s* r * t;
	renderer->SetVerticis(m_verticies, m_verticiesDataSize);
	renderer->SetIndexBuffer(m_vertexIndicies, m_vertexIndiciesSize);
	renderer->SetTransformMat(tr);
	renderer->Render();
}
