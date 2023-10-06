#include "Mesh.h"

Mesh::Mesh() : m_drawMode{ GL_TRIANGLES } { }

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_elementBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Init() {
	// VAO 객체 생성 및 바인드
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// VBO 객체 생성 및 바인드
	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	// EBO 객체 생성 및 바인드
	glGenBuffers(1, &m_elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
}

void Mesh::SetVerticis(const Vertex* verticies, unsigned int dataSize) {
	// Vertex객체의 정보를 VBO에 넘겨줌
	glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(Vertex), verticies, GL_DYNAMIC_DRAW);

	// location 1번에 Vertex객체의 position정보를 넘겨줌
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// location 2번에 Vertex객체의 color정보를 넘겨줌
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
}

void Mesh::SetIndexBuffer(unsigned int* indexBuffer, size_t bufferSize) {
	// 인덱스 버퍼 내용 저장
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize * sizeof(unsigned int), indexBuffer, GL_DYNAMIC_DRAW);
}

void Mesh::SetDrawMode(unsigned int mode) {
	m_drawMode = mode;
}

void Mesh::Render() {
	// shaderProgram 에서 UseProgram을 활성화 했다는 가정하에 수행
	glBindVertexArray(m_vertexArray);
	glDrawElements(m_drawMode, m_vertexPositionSize, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0); // Array 바인드 해제
}
