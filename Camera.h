#pragma once

#include "gl_headers.h"
#include <memory>

class Camera {
public:
	Camera() { } 
	~Camera() { } 

private:
	// 카메라의 내부 파라미터
	glm::vec3 m_EYE{ 0.f, 0.f, -3.f };
	glm::vec3 m_AT{ 0.f, 0.f, -1.f };
	glm::vec3 m_UP{ 0.f, 1.f, 0.f };

	// 뷰변환 행렬
	glm::mat4 m_view{ 1.f };

public:
	glm::mat4 GetViewMat() const;

public:
	void Init();
	void Update();
	void Render();
};

