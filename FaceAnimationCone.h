#pragma once
#include "vertex_info.h"
#include "gl_headers.h"
#include "GraphicBuffers.h"
#include <vector>
#include <array>
#include <memory>

class ConeFace {
public:
	ConeFace() { }
	~ConeFace() { }

private:
	std::vector<unsigned int> m_index{ };

	glm::vec3 m_centerPosition{ };
	glm::vec3 m_deltaPosition{ };
	glm::vec3 m_scale{ 1.f };
	glm::vec3 m_rotate{ };

	std::unique_ptr<GraphicBuffers> m_graphicBuffers{ };

	int m_myFaceNumber{ };
	float m_animationDir{ 1.f };

private:
	std::vector<Vertex> m_vertex{ };

public:
	bool Animation(bool dir, bool start);

public:
	void Init(unsigned int shaderProgramID, int faceNumber);
	void Update(float deltaTime);
	void Render();
};

class FaceAnimationCone {
public:
	FaceAnimationCone() { }
	~FaceAnimationCone() { }

private:
	std::array<ConeFace, 5> m_coneFaces{ };
	std::array<bool, 5> m_faceAnimationFlag{ false };

public:
	void Init(unsigned int shaderProgramID);
	void Input(unsigned char key, bool down);
	void Update(float deltaTime);
	void Render();
};

