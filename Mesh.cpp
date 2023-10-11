#include "Mesh.h"
#include "Renderer.h"
#include "pch.h"
#include <fstream>
#include <sstream>
#include <vector>

Mesh::Mesh(std::shared_ptr<Renderer>& renderer, const char* objFilePath) {
	m_renderer = renderer;

	ReadObject(objFilePath);
}

Mesh::~Mesh() { }

void Mesh::ReadObject(const char* filePath) {
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
			if (line[1] == 'n');           // vn == ���� ���
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

	for (auto& v : m_verticies) {
		v.color = glm::vec3{ glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f) };
	}

	m_vertexIndicies = indiciesVec[0];
	m_vertexNormalIndicies = indiciesVec[1];
	m_drawVertexIndicies = indiciesVec[0];
	m_textureIndicies = indiciesVec[2];
}

void Mesh::TestPrint(std::vector<glm::vec3>& verticies, std::vector<unsigned int>& indicies) {
	size_t vertexSize = m_verticies.size();
	for (size_t i = 0; i < vertexSize; ++i) {
		std::cout << "vertex[" << i << "]: " << 
			m_verticies[i].position.x << " " 
			<< m_verticies[i].position.y << " " 
			<< m_verticies[i].position.z << std::endl;
	}

	// �׽�Ʈ�� ���� �ε��� ���� ���
	size_t indiciesSize = m_vertexIndicies.size();
	for (size_t i = 0; i < indiciesSize; ++i) {
		if (i % 3 == 0) {
			std::cout << "face[" << i / 3 << "]: ";
		}
		std::cout << " " << m_vertexIndicies[i];
		if (i % 3 == 2) {
			std::cout << "\n";
		}
	}
}

void Mesh::RenderingFace(unsigned int faceIdx, unsigned int faceVertexSize) {
	m_drawVertexIndicies.clear();
	for (auto i = 0; i < faceVertexSize; ++i) {
		m_drawVertexIndicies.push_back(m_vertexIndicies[faceIdx * faceVertexSize + i]);
	}
}

void Mesh::RenderingTwoFace(int faceIndex1, int faceIndex2, unsigned int faceVertexSize) {
	m_drawVertexIndicies.clear();
	int f1{ faceIndex1 }, f2{ faceIndex2 };
	if (f1 > f2) {
		std::swap(f1, f2);
	}
	else if (f1 == f2) {
		f2 = (f2 + 2) % faceVertexSize;
	}

	for (auto i = 0; i < faceVertexSize; ++i) {
		m_drawVertexIndicies.push_back(m_vertexIndicies[f1 * faceVertexSize + i]);
	}

	for (auto i = 0; i < faceVertexSize; ++i) {
		m_drawVertexIndicies.push_back(m_vertexIndicies[f2 * faceVertexSize + i]);
	}
}

void Mesh::ResetRender() {
	m_drawVertexIndicies = m_vertexIndicies;
}

void Mesh::Update() {

}

void Mesh::Render() {
	glm::mat4 iMat{ 1.f };
	glm::mat4 s = glm::scale(iMat, glm::vec3{ 0.5f, 0.5f, 0.5f });
	glm::mat4 t = glm::translate(iMat, glm::vec3{ 0.f, 0.f, 0.f });
	glm::mat4 r = glm::rotate(iMat, glm::radians(10.f), glm::vec3(1.f, 0.f, 0.f));
	r = glm::rotate(r, glm::radians(-10.f), glm::vec3(0.f, 1.f, 0.f));

	glm::mat4 tr = s * r * t;

	// test line draw
	m_renderer->SetDrawMode(GL_TRIANGLES);

	m_renderer->SetVerticis(m_verticies);
	m_renderer->SetIndexBuffer(m_drawVertexIndicies);
	m_renderer->SetTransformMat(tr);

	m_renderer->Render();
}