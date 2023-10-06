#pragma once
#include "vertex_info.h"

// VAO, VBO, EBO를 바인딩해서 삼각형을 그려줄 클래스
class Mesh {
public:
	Mesh();
	~Mesh();

private:
	// Vertex Buffer Object ID
	unsigned int m_vertexBuffer{ };
	unsigned int m_vertexColorBuffer{ };
	// Vertex Array Object ID
	unsigned int m_vertexArray{ };
	// Element Buffer OBject ID
	unsigned int m_elementBuffer{ };

	unsigned int m_vertexPositionSize{ };
	unsigned int m_vertexColorSize{ };

	// 그리기 모드 점, 선, 삼각형 등
	// default값은 삼각형(생성자에서 설정)
	unsigned int m_drawMode{ };

	// 변환 행렬들
	glm::mat4 m_scaleMat{ glm::mat4{ 1.f } };
	glm::mat4 m_rotateMat{ glm::mat4{ 1.f } };
	glm::mat4 m_transMat{ glm::mat4{ 1.f } };

public:
	void Init();

	void SetTransformMat();
	void SetVerticis(const Vertex* verticies, unsigned int dataSize);
	void SetIndexBuffer(unsigned int* indexBuffer, size_t bufferSize);
	void SetDrawMode(unsigned int mode);
	void Render();
};