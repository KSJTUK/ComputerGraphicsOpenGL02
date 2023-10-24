#pragma once
#include "vertex_info.h"
#include "gl_headers.h"
#include "GraphicBuffers.h"
#include <vector>
#include <array>
#include <memory>

class CubeFace {
public:
	CubeFace() { }
	~CubeFace() { }

private:
	std::vector<unsigned int> m_index{ };

	glm::vec3 m_centerPosition{ };
	glm::vec3 m_deltaPosition{ };
	glm::vec3 m_scale{ 1.f };
	glm::vec3 m_rotate{ };
	float m_rotateAllY{ };

	std::unique_ptr<GraphicBuffers> m_graphicBuffers{ };

	int m_myFaceNumber{ };
	float m_animationDir{ 1.f };

private:
	std::vector<Vertex> m_vertex{ };

public:
	bool Animation(bool dir, bool start);
	void Orbit();

public:
	void Init(unsigned int shaderProgramID, int faceNumber);
	void Update(float deltaTime);
	void Render();
};

class FaceAnimationCube {
public:
	FaceAnimationCube() { }
	~FaceAnimationCube() { }

private:
	std::array<CubeFace, 6> m_cubeFaces{ };
	std::array<bool, 6> m_faceAnimationFlag{ false };
	bool m_rotateY{ false };

public:
	void Init(unsigned int shaderProgramID);
	void Input(unsigned char key, bool down);
	void Update(float deltaTime);
	void Render();
};