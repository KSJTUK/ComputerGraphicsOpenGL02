#pragma once
#include "vertex_info.h"
#include <vector>

class Mesh {
public:
	Mesh();
	~Mesh();

private:
	Vertex* m_verticies{ };
	unsigned int m_verticiesDataSize{ };

	unsigned int* m_vertexIndicies{ };
	unsigned int m_vertexIndiciesSize{ };

	unsigned int* m_vertexNormalIndicies{ };
	unsigned int* m_textureIndicies{ };

	void ReadObject(const char* filePath);
	void MakeVertexAndIndicies(std::vector<glm::vec3>& verticies, std::vector<unsigned int>* indicies);

public:
	void Update();
	void Render(class Renderer* renderer);
};

