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
	static std::unique_ptr<GraphicBuffers> m_spiralBuffer;

	static std::vector<Vertex> m_spiralVertex;
	static std::vector<unsigned int> m_spiralVertexIndex;

	glm::vec3 m_position{ 0.f };
	glm::mat4 m_transformMat{ 1.f };

public:
	void SetPosition(const glm::vec3& position);
	size_t GetSpiralSize() const;

	Vertex operator[](size_t index) const;

public:
	static void Init(unsigned int shaderProgramID);
	static void MakeSpiral(int numOfPoints, const glm::vec3& center, float stepRadius, int angleDir);
	void DrawSpiral();
};

