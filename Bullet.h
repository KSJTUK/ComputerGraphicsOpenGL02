#pragma once

#include "Object.h"
#include "gl_headers.h"

class Bullet {
public:
	Bullet(const glm::vec3& initPos, const glm::vec3& dir, float speed);
	~Bullet() { delete m_bullet; } 

private:
	Object* m_bullet{ };

	glm::vec3 m_direction{ };

	float m_speed{ };

public:
	void Update(float deltaTime);
	void SetPosition(const glm::vec3& pos);
	void Render();
};