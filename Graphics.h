#pragma once

#include "gl_headers.h"
#include <memory>
#include <vector>

class Graphics {
public:
	Graphics();
	~Graphics();

private:
	std::unique_ptr<class Shader> m_shader{ };

	std::unique_ptr<class Camera> m_camera{ };

	std::unique_ptr<class Axis> m_axisSystem{ };

private:
	// 카메라 외부파라미터 (투영행렬을 생성할 떄 쓰일 변수들)
	float m_fovy{ 90.f }; // 수직 시야각

	// 스크린 화면의 크기를 알아내기 위한 WindowInfo객체 참조
	std::shared_ptr<struct WindowInfo> m_windowInfo{ }; // aspect(종횡비) = width / height

	float m_near{ 0.1f };           // 시야 절두체의 가까운 평면과의 거리
	float m_far{ 1000.f };           // 시야 절두체의 먼 평면과의 거리

	// 업데이트를 위한 시간값 저장
	float m_deltaTime{ };

	// 은면 제거를 위한 플래그
	bool m_culling{ true };

	// 와이어 / 솔리드 객체 변환을 위한 플래그
	bool m_drawSolid{ true };

public:
	// getter

	// setter
	void SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo);
	void SetPerspectiveMat();

public:
	// 외부 키입력을 카메라에게 전해주는 함수
	void Input(unsigned char key);
	void SpecialInput(int key);

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

