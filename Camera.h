#pragma once

#include "gl_headers.h"
#include <memory>

class Camera {
public:
	Camera() { } 
	~Camera() { } 

private:
	// ī�޶��� ���� �Ķ����
	glm::vec3 m_EYE{ 0.f, 0.f, 0.f };
	glm::vec3 m_AT{ 0.f, 0.f, -1.f };
	glm::vec3 m_UP{ 0.f, 1.f, 0.f };

	// �亯ȯ ���
	glm::mat4 m_view{ 1.f };

public:
	void Init();
	void Update();
};

