#pragma once

#include "gl_headers.h"
#include <memory>

class Sphere {
public:
	Sphere(const class ModelList* const modelList);
	Sphere(const ModelList* const modelList, const glm::vec3& initPosition);
	~Sphere();

private:
	// 모델
	std::shared_ptr<class Model> m_model{ };

	// 위치, 회전 변수들
	glm::vec3 m_sizeScale{ 1.f };
	glm::vec3 m_position{ 0.f };
	glm::vec3 m_rotAngle{ 0.f };

	glm::vec3 m_orbitAngle{ 0.f };

	float m_angleSpeed{ 10.f };
	float m_orbitSpeed{ 2.f };

	float m_deltaTime{ };

	// test
	glm::mat4 unit{ 1.f };

	glm::mat4 scale{ 1.f };
	glm::mat4 rotate{ 1.f };
	glm::mat4 trans{ 1.f };

public:
	void RotateX();
	void RotateY();
	void RotateZ();
	void OrbitX();
	void OrbitY();
	void OrbitZ();

public:
	void Update(float deltaTime);
	void Render();
};

