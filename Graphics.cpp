#include "Graphics.h"
#include "gl_headers.h"
#include "Shader.h"
#include "ModelList.h"
#include "Camera.h"

Graphics::Graphics() { }

Graphics::~Graphics() { }

void Graphics::Init() {
	m_shader = std::make_unique<Shader>();
	m_shader->RoadVertexShaderFile("vertex_shader.glsl");
	m_shader->RoadFragmentShaderFile("fragment_shader.glsl");
}

void Graphics::Render() {

}
