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
		std::string delTag{ };     // 앞에 있는 v, vn, f와 같은 태그 제거용

		if (line[0] == 'v') {              // 맨 앞 문자가 v이면 정점에 대한 정보이다
			if (line[1] == 'n');           // vn == 정점 노멀
			else if (line[1] == 't');      // vt == 텍스쳐 좌표
			else if (line[1] == ' ') {     // v == 정점 좌표
				glm::vec3 tempVec{ };      // 정점 좌표 저장
				sstream >> delTag >> tempVec.x >> tempVec.y >> tempVec.z;
			}
		}
		else if (line[0] == 'f') {         // 맨 앞 문자가 f이면 face(면)에 대한 정보이다
			std::string face[3]{ };        // f a/b/c -> a == 정점 인덱스, b == 텍스처 인덱스, c == 노멀 인덱스
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
