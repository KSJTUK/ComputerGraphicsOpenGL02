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
	// VAO, VBO, EBO�� ������ ��ü
	std::unique_ptr<class GraphicBuffers> m_graphicsBuffer{ };

	// ���� �Ӽ����� ������ vector
	std::vector<Vertex> m_verticies{ };

	// ���� ��ֵ��� ������ vector
	std::vector<glm::vec3> m_vertexNormals{ };

	// ������ ���� �ε����� ������ vector
	std::vector<unsigned int> m_vertexIndicies{ };

	// ���� ��ֿ� ���� �ε����� ������ vector
	std::vector<unsigned int> m_vertexNormalIndicies{ };

	// �ؽ�ó ��ǥ �ε����� ������ vector
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