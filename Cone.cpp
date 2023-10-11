#include "Cone.h"
#include "Mesh.h"

Cone::Cone(std::shared_ptr<class Mesh> model) {
	m_model = model;
	m_model->SetPos(glm::vec3{ -1.f, -1.f, 0.f });
}

void Cone::RenderFace(unsigned int faceIdx) {
	m_model->RenderingFace(faceIdx - 1, 3);
}

void Cone::RenderTwoFace(unsigned int faceIdx1, unsigned int faceIdx2) {
	m_model->RenderingTwoFace(faceIdx1 - 1, faceIdx2 - 1, 3);
}

void Cone::ResetRender() {
	m_model->ResetRender();
}

void Cone::Init() {

}

void Cone::Update() {

}

void Cone::Render() {
	m_model->Render();
}
