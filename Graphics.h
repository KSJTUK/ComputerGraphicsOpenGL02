#pragma once

#include <memory>

class Graphics {
public:
	Graphics();
	~Graphics();

private:
	std::unique_ptr<class Shader> m_shader{ };

	std::unique_ptr<class Camera> m_camera{ };

	std::unique_ptr<class Model> m_model{ };

public:
	void Render();

};

