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

	// 카메라 업데이트를 위한 시간 값 저장
	float m_deltaTime{ };

	// 카메라 움직임을 위한 변수들
	float m_moveSpeed{ 20.f };

public:
	glm::mat4 GetViewMat() const;

public:
	void Move(const glm::vec3& moveVec);

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

