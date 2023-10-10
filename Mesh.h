#pragma once
#include "vertex_info.h"
#include <vector>

class Mesh {
public:
	Mesh(class Renderer* renderer);
	~Mesh();

private:
	std::vector<Vertex> m_verticies{ };

	std::vector<unsigned int> m_vertexIndicies{ };
	std::vector<unsigned int> m_vertexNormalIndicies{ };
	std::vector<unsigned int> m_textureIndicies{ };

	void ReadObject(const char* filePath);
	void TestPrint(std::vector<glm::vec3>& verticies, std::vector<unsigned int>& indicies);

	// test
	float m_xRad{ };
	float m_yRad{ };
	float m_zRad{ };

	glm::mat4 m_scale{ 1.f };
	glm::mat4 m_rotate{ 1.f };
	glm::mat4 trans{ 1.f };

public:
	void Update();
	void Render(class Renderer* renderer);
};