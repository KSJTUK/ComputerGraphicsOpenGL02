#pragma once
#include "vertex_info.h"
#include "gl_headers.h"
#include "GraphicBuffers.h"
#include <vector>
#include <memory>

class CubeFace {
	std::vector<Vertex> m_vertex{ };
	std::vector<unsigned int> m_index{ };

	glm::vec3 m_position{ };
	glm::vec3 m_scale{ };
	glm::vec3 m_rotate{ };
};

class FaceAnimationCube {
public:
	FaceAnimationCube() { }
	~FaceAnimationCube() { }

private:
	std::vector<Vertex> m_faces{ };
	std::vector<unsigned int> m_faceIndex{ };

public:
	void Update();
};