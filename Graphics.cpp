#include "Graphics.h"
#include "gl_headers.h"
#include "window_info.h"
#include "Shader.h"
#include "ModelList.h"
#include "Camera.h"
#include "Model.h"

Graphics::Graphics() { }

Graphics::~Graphics() { }

void Graphics::SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo) {
	m_windowInfo = winInfo;
}

void Graphics::SetPerspectiveMat() {
	float aspect = m_windowInfo->fWidth / m_windowInfo->fHeight;
	float halfFovy = m_fovy / 2.f;

	m_shader->SetPerspectiveMat(glm::perspective(glm::radians(halfFovy), aspect, m_near, m_far));
}

void Graphics::Init() {
	// 쉐이더 프로그램 생성
	m_shader = std::make_unique<Shader>();
	m_shader->CreateShaderProgram();

	// 카메라 생성
	//m_camera = std::make_unique<Camera>();
	//m_camera->Init(m_shader->GetShaderProgramID)

	// 모델리스트를 생성하고 모델 불러오기
	m_modelList = std::make_unique<ModelList>();
	m_modelList->Init(m_shader->GetShaderProgramID());

	m_modelList->LoadModel("cube.obj");

	testModel = m_modelList->GetModel("cube").get();

	SetPerspectiveMat();
}

void Graphics::Update(float deltaTime) {
	// m_camera->Update(deltaTime);
}

void Graphics::Render() {
	m_shader->UseProgram();

	// 변환 행렬들 계산
	testModel->Render();
	
	// rendering code 
}