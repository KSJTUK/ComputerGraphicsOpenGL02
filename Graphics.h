#pragma once

#include <memory>

class Graphics {
public:
	Graphics();
	~Graphics();

private:
	std::unique_ptr<class Shader> m_shader{ };

	std::unique_ptr<class Camera> m_camera{ };

	std::unique_ptr<class ModelList> m_modelList{ };

public:
	// getter

	// 테스트용
	class Model* testModel{ };

public:
	void Init();
	void Update(float deltaTime);
	void Render();
};

