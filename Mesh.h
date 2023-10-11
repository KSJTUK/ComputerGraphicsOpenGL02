#pragma once
#include "vertex_info.h"
#include <vector>
#include <memory>

class Mesh {
public:
	Mesh(std::shared_ptr<class Renderer>& renderer);
	~Mesh();

	Mesh(const Mesh& other) = delete;
	Mesh* operator=(const Mesh& other) = delete;

private:
	std::shared_ptr<class Renderer> m_renderer{ };

	std::vector<Vertex> m_verticies{ };

	std::vector<unsigned int> m_vertexIndicies{ };
	std::vector<unsigned int> m_vertexNormalIndicies{ };
	std::vector<unsigned int> m_textureIndicies{ };

	// test
	float m_xRad{ };
	float m_yRad{ };
	float m_zRad{ };

	glm::mat4 m_scale{ 1.f };
	glm::mat4 m_rotate{ 1.f };
	glm::mat4 trans{ 1.f };

public:
	void ReadObject(const char* filePath);
	void TestPrint(std::vector<glm::vec3>& verticies, std::vector<unsigned int>& indicies);

public:
	void Update();
	void Render();

public:
	void RenderingFace(int faceIndex);

	void RenderSideFace(int faceIndex);
};