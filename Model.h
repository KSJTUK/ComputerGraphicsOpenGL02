#pragma once
#include "vertex_info.h"
#include <vector>
#include <memory>
#include <string>

class Model {
public:
	Model(const std::string& objectFilePath);
	~Model();

	Model(const Model& other) = delete;
	Model* operator=(const Model& other) = delete;

private:
	// VAO, VBO, EBO를 가지는 객체
	std::unique_ptr<class GraphicBuffers> m_graphicsBuffer{ };

	// 정점 속성들을 저장할 vector
	std::vector<Vertex> m_verticies{ };

	// 정점 노멀들을 저장할 vector
	std::vector<glm::vec3> m_vertexNormals{ };

	// 정점에 대한 인덱스를 저장할 vector
	std::vector<unsigned int> m_vertexIndicies{ };

	// 정점 노멀에 대한 인덱스를 저장할 vector
	std::vector<unsigned int> m_vertexNormalIndicies{ };

	// 텍스처 좌표 인덱스를 저장할 vector
	std::vector<unsigned int> m_textureIndicies{ };

	void ReadObject(const char* filePath);

private:
	glm::mat4 m_modelTransform{ 1.f };

public:
	glm::mat4 GetModelTransformMat() const;

	// setter
	void SetColor(const glm::vec3& color);
	void SetRandomColor();
	void SetTransformMat(const glm::mat4& transformMat);

public:
	void Init(unsigned int shaderProgramID);
	void Update();
	void Render();
};