#pragma once

#include "gl_headers.h"
#include <memory>

class Camera {
public:
	Camera() { } 
	~Camera() { } 

private:
	// ī�޶��� ���� �Ķ����
	glm::vec3 m_EYE{ 0.f, 0.f, -3.f };
	glm::vec3 m_AT{ 0.f, 0.f, -1.f };
	glm::vec3 m_UP{ 0.f, 1.f, 0.f };

	// �亯ȯ ���
	glm::mat4 m_view{ 1.f };

	// ī�޶� ������Ʈ�� ���� �ð� �� ����
	float m_deltaTime{ };

	// ī�޶� �������� ���� ������
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

