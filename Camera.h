#pragma once

#include <memory>
#include "gl_headers.h"

class Camera {
public:
	Camera();
	~Camera();

private:
	// 카메라의 내부 파라미터
	glm::vec3 m_EYE{ 0.f, 0.f, 0.f };
	glm::vec3 m_AT{ 0.f, 0.f, -1.f };
	glm::vec3 m_UP{ 0.f, 1.f, 0.f };

public:
	void Init();
	void Update();
};

