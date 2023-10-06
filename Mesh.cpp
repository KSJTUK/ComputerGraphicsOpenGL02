#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <vector>

Mesh::Mesh() { }

Mesh::~Mesh() { }

void Mesh::ReadObject(const char* filePath) {
	std::ifstream objFile{ filePath, std::ios::in };

	std::vector<glm::vec3> vertexVec{ };
	std::vector<unsigned int> indiciesVec[3]{ }; // cnt: 0 == vertex, 1 == texture, 2 == nomal

	if (objFile.is_open()) {
		assert(0);
	}

	std::string line{ " " };
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
			}
		}
		else if (line[0] == 'f') {         // �� �� ���ڰ� f�̸� face(��)�� ���� �����̴�
			std::string face[3]{ };        // f a/b/c -> a == ���� �ε���, b == �ؽ�ó �ε���, c == ��� �ε���
			int num1{ };
			std::string temp{ };
			for (int i = 0; i < 3; ++i) {
				int cnt{ };
				for (int c = 0; face[0].size(); ++c) {
					if (face[0][c] == '\0') {
						indiciesVec[cnt].push_back(std::stoi(temp));
						break;
					}

					if (face[0][c] == '/') {
						if (!temp.empty()) {
							indiciesVec[cnt].push_back(std::stoi(temp));
						}
						cnt++;
						temp.clear();
					}
					else {
						temp += face[0][c];
					}
				}
			}
		}
	}
}
