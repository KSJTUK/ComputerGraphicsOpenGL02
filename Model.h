#pragma once
#include "vertex_info.h"
#include <vector>
#include <memory>
#include <string>

class Mesh {
public:
	Mesh(const std::string& objectFilePath);
	~Mesh();

	Mesh(const Mesh& other) = delete;
	Mesh* operator=(const Mesh& other) = delete;

private:
	std::unique_ptr<class Renderer> m_renderer{ };

	std::vector<Vertex> m_verticies{ };

	std::vector<unsigned int> m_vertexIndicies{ };
	std::vector<unsigned int> m_vertexNormalIndicies{ };
	std::vector<unsigned int> m_textureIndicies{ };

	void ReadObject(const char* filePath);
	void TestPrint(std::vector<glm::vec3>& verticies, std::vector<unsigned int>& indicies);

private:
	glm::mat4 m_modelTransform{ 1.f };

public:
	glm::mat4 GetModelTransformMat() const;

public:
	void Init(unsigned int shaderProgramID);
	void Update();
	void Render();
};