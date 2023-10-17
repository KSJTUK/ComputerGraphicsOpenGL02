#pragma once
#include <vector>
#include "Object.h"
#include "gl_headers.h"

class CircleEffect {
public:
	CircleEffect() { }
	~CircleEffect() { } 

private:
	static std::unique_ptr<class GraphicBuffers> m_circleBuffer;

	static std::vector<Vertex> m_circleVertex;
	static std::vector<unsigned int> m_circleVertexIndex;

	glm::vec3 m_scale{ 1.f };
	glm::vec3 m_rotateAxis{ 0.f };
	float m_rotAngle{ 0.f };
	glm::vec3 m_position{ 0.f };
	glm::mat4 m_transformMat{ 1.f };

public:
	void SetRadius(float radius);
	void SetPosition(const glm::vec3& position);
	void SetAxis(const glm::vec3& axis);

public:
	static void Init(unsigned int shaderProgramID);
	static void MakeCircle(float angleStep = 0.01f);
	void DrawCircle();
};

class OrbitObject : public Object {
public:
	OrbitObject(const std::string& modelTag, const glm::vec3& orbitCenter, const glm::vec3& orbitAxis, float orbitRadius, float orbitSpeed);
	~OrbitObject();

private:
	glm::vec3 m_orbitCenter{ };
	glm::vec3 m_orbitAxis{ };
	float m_orbitAngle{ };
	float m_orbitSpeed{ };

	float m_orbitRadius{ };

	CircleEffect m_circle{ };

public:
	glm::vec3 Update(float deltaTime, const glm::vec3& centerObjectDeltaPosition);
	void Render();
};