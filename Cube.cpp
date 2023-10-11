#include "Cube.h"
#include "Mesh.h"

Cube::Cube(std::shared_ptr<class Mesh> model) {
	m_model = model;
}

Cube::~Cube() {
}

void Cube::RenderFace(unsigned int faceIdx) {
	m_model->RenderingFace(faceIdx - 1, 6, 6);
}

void Cube::RenderTwoFace(unsigned int faceIdx1, unsigned int faceIdx2) {
	m_model->RenderingTwoFace(faceIdx1 - 1, faceIdx2 - 1, 6, 6);
}

void Cube::ResetRender() {
	m_model->ResetRender();
}

void Cube::Init() {

}

void Cube::Update() {

}

void Cube::Render() {
	m_model->Render();
}
