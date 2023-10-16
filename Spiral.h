#pragma once

#include <memory>
#include <vector>
#include "vertex_info.h"
#include "GraphicBuffers.h"

class Spiral {
public:
	Spiral() { }
	~Spiral() { }

private:
	std::unique_ptr<GraphicBuffers> m_spiralBuffer{ };

	std::vector<Vertex> m_spiralVertex{ };
	std::vector<unsigned int> m_spiralVertexIndex{ };

public:
	void Init(unsigned int shaderProgramID);
	void MakeSpiral(int numOfPoints, const glm::vec3& center, float stepRadius, int angleDir);
	void DrawSpiral();
};

