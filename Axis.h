#pragma once

#include <memory>
#include <vector>
#include "vertex_info.h"

class Axis {
public:
	Axis();
	~Axis();

private:
	std::unique_ptr<class GraphicBuffers> m_axisBuffer{ };

	std::vector<Vertex> m_axisVertex{ };
	std::vector<unsigned int> m_axisVertexIndex{ };

public:
	void Init(unsigned int shaderProgramID);
	void DrawAxis();
};