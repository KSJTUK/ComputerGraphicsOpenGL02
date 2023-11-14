#pragma once

#include "gl_headers.h"

class Physics {
public:
	Physics();
	~Physics();

private:
	glm::vec3 m_power{ };
	glm::vec3 m_velopcity{ };

	float m_weight{ };
	float m_mess{ };

	float m_deltaTime{ };
	float m_timeScale{ 1.f };

	float m_gravity{ 9.8f };

public:
	void Jump(float jumpPower);
	void Gravity();

public:
	void ResetPhysics();
	void SetPower(const glm::vec3& power);
	void Update(float deltaTime);

};