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
	glm::vec3 m_AT{ 0.f, 0.f, 1.f };
	glm::vec3 m_UP{ 0.f, 1.f, 0.f };

	// �亯ȯ ���
	glm::mat4 m_view{ 1.f };

	// ī�޶� ������Ʈ�� ���� �ð� �� ����
	float m_deltaTime{ };

	// ī�޶� �������� ���� ������
	float m_moveSpeed{ 50.f };
	float m_angleSpeed{ 100.f };

	float m_fixAt{ 1.f };

	// ī�޶� ������ ����, ī�޶��� �� ���� ���͵��� ������ ����
	glm::vec3 m_cameraAxisX{ };
	glm::vec3 m_cameraAxisY{ };
	glm::vec3 m_cameraAxisZ{ };

	float m_cameraAngleX{ };
	float m_cameraAngleY{ };

public:
	// getter
	glm::mat4 GetViewMat() const;

	// setter
	void CameraPositionSet(const glm::vec3& position);

	void ViewPointFix();
	void ViewPointUnFix();

public:
	// �ܺ� Ű�Է��� ī�޶� ��ü������ ó���ϰ� ��
	void Input(unsigned char key);
	void SpecialInput(int key);

	void Move(const glm::vec3& moveVec);
	void ViewPointMove(float moveAngle, const glm::vec3& axis);

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

