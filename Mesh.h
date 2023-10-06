#pragma once
#include "vertex_info.h"

class Mesh {
public:
	Mesh();
	~Mesh();

private:
	Vertex* m_verticies{ };
	unsigned int m_indicies{ };

	void ReadObject(const char* filePath);

public:
	void Init();
	void Update();
	void Render();
};

