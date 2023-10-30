﻿#pragma once
#include "gl_headers.h"
#include "vertex_info.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

class Model {
public:
	Model(const std::string& objectFilePath);
	~Model();

	Model(const Model& other) = delete;
	Model& operator=(const Model& other) = delete;

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

	// 정점좌표들 중 최대 최소인 x, y, z 값을 저장할 변수들
	glm::vec3 m_maxCoord{ };
	glm::vec3 m_minCoord{ };

	std::pair<glm::vec3, glm::vec3> m_boundingBox{ };

	void CalcMinMaxVertexElem();
	void MakeBoundingBox();
	void ReadObject(const char* filePath);

private:
	glm::mat4 m_modelTransform{ 1.f };

public:
	glm::mat4 GetModelTransformMat() const;

	// setter
	void SetColor(const glm::vec3& color);
	void SetRandomColor();
	void SetDrawMode(int drawMode);
	void SetTransformMat(const glm::mat4& transformMat);

	std::pair<glm::vec3, glm::vec3> GetBoundingBox() const { return m_boundingBox; }

public:
	void Init(unsigned int shaderProgramID);
	void Update();
	void Render();

private:
	// 실습 18번을 풀기 위한 임시 friend 선언
	friend class CubeFace;
	friend class ConeFace;
};