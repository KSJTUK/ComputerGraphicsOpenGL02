#pragma once
#include "vertex_info.h"
#include <vector>
#include <memory>

class Mesh {
public:
	Mesh(std::shared_ptr<class Renderer>& renderer, const char* objFilePath);
	~Mesh();

	Mesh(const Mesh& other) = delete;
	Mesh* operator=(const Mesh& other) = delete;

private:
	std::shared_ptr<class Renderer> m_renderer{ };

	std::vector<Vertex> m_verticies{ };

	std::vector<unsigned int> m_vertexIndicies{ };
	std::vector<unsigned int> m_drawVertexIndicies{ };

	std::vector<unsigned int> m_vertexNormalIndicies{ };
	std::vector<unsigned int> m_textureIndicies{ };

	// test
	float m_xRad{ };
	float m_yRad{ };
	float m_zRad{ };

	glm::vec3 m_pos{ 0.f };

public:
	void ReadObject(const char* filePath);
	void TestPrint(std::vector<glm::vec3>& verticies, std::vector<unsigned int>& indicies);

	void SetPos(glm::vec3& pos);
	void SetPos(glm::vec3&& pos);

public:
	void Update();
	void Render();

public:
	void RenderingFace(int faceIndex);
	void RenderingFace(unsigned int faceIdx, unsigned int faceVertexSize);

	void RenderingTwoFace(int faceIndex1, int faceIndex2, unsigned int faceVertexSize);

	void ResetRender();
};