#include "Mesh.h"
#include "Renderer.h"
#include "pch.h"
#include <fstream>
#include <sstream>
#include <vector>

Mesh::Mesh(std::shared_ptr<Renderer>& renderer) {
	m_renderer = renderer;

	ReadObject("skull.obj");

	glm::mat4 iMat{ 1.f };
	glm::mat4 s = glm::scale(iMat, glm::vec3{ 0.05f, 0.05f, 0.05f });
	glm::mat4 t = glm::translate(iMat, glm::vec3{ 0.f, 0.f, -10.f });
	glm::mat4 r = glm::rotate(iMat, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));

	glm::mat4 tr = s * r * t;

	// test line draw
	renderer->SetDrawMode(GL_LINE_LOOP);

	renderer->SetVerticis(m_verticies);
	renderer->SetIndexBuffer(m_vertexIndicies);
	renderer->SetTransformMat(tr);
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
		std::string delTag{ };     // 앞에 있는 v, vn, f와 같은 태그 제거용

		if (line[0] == 'v') {              // 맨 앞 문자가 v이면 정점에 대한 정보이다
			if (line[1] == 'n');           // vn == 정점 노멀
			else if (line[1] == 't');      // vt == 텍스쳐 좌표
			else if (line[1] == ' ') {     // v == 정점 좌표
				glm::vec3 tempVec{ };      // 정점 좌표 저장
				sstream >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
				m_verticies.push_back(Vertex{ tempVec, glm::vec3{ }, glm::vec2{ } });
			}
		}
		else if (line[0] == 'f') {         // 맨 앞 문자가 f이면 face(면)에 대한 정보이다
			std::string face[3]{ };        // f a/b/c -> a == 정점 인덱스, b == 텍스처 인덱스, c == 노멀 인덱스
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

void Mesh::TestPrint(std::vector<glm::vec3>& verticies, std::vector<unsigned int>& indicies) {
	size_t vertexSize = m_verticies.size();
	for (size_t i = 0; i < vertexSize; ++i) {
		std::cout << "vertex[" << i << "]: " << 
			m_verticies[i].position.x << " " 
			<< m_verticies[i].position.y << " " 
			<< m_verticies[i].position.z << std::endl;
	}

	// 테스트를 위한 인덱스 정보 출력
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

void Mesh::Update() {

}

void Mesh::Render() {
	m_renderer->Render();
}

void Mesh::RenderingFace(int faceIndex) {
	unsigned int* faceIndicies = new unsigned int[6];

	memcpy(faceIndicies, &m_vertexIndicies[0] + (faceIndex * 6), 6 * sizeof(unsigned int));

	m_renderer->SetIndexBuffer(faceIndicies, 6);
}
