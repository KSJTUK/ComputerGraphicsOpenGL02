#pragma once

#include "gl_headers.h"
#include <memory>

class Cone {
public:
	Cone(std::shared_ptr<class Mesh> model);
	~Cone() { }

private:
	std::shared_ptr<class Mesh> m_model{ };

public:
	void RenderFace(unsigned int faceIdx);
	void RenderTwoFace(unsigned int faceIdx1, unsigned int faceIdx2);
	void ResetRender();

public:
	void Init();
	void Update();
	void Render();
};

