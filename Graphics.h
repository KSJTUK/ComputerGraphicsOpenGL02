#pragma once

#include "gl_headers.h"
#include <memory>

class Graphics {
public:
	Graphics();
	~Graphics();

private:
	std::unique_ptr<class Shader> m_shader{ };

	std::unique_ptr<class Camera> m_camera{ };

	std::unique_ptr<class ModelList> m_modelList{ };

	std::unique_ptr<class Axis> m_axisSystem{ };

private:
	// 카메라 외부파라미터 (투영행렬을 생성할 떄 쓰일 변수들)
	float m_fovy{ 90.f }; // 수직 시야각

	// 스크린 화면의 크기를 알아내기 위한 WindowInfo객체 참조
	std::shared_ptr<struct WindowInfo> m_windowInfo{ }; // aspect(종횡비) = width / height

	float m_near{ 0.1f };           // 시야 절두체의 가까운 평면과의 거리
	float m_far{ 100.f };           // 시야 절두체의 먼 평면과의 거리

	// 업데이트를 위한 시간값 저장
	float m_deltaTime{ };

public:
	// getter

	// 테스트용
	class Model* testModel{ };

	// setter
	void SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo);
	void SetPerspectiveMat();

public:
	// 외부 키 입력 이벤트에 의해 수행될 카메라 업데이트 함수들
	void CameraMove(const glm::vec3& moveVec);

	void CameraViewPointFix();
	void CameraViewPointUnFix();

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

