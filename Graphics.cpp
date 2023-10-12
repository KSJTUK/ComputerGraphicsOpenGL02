﻿#include "Graphics.h"
#include "gl_headers.h"
#include "window_info.h"
#include "Shader.h"
#include "ModelList.h"
#include "Camera.h"
#include "Model.h"
#include "Axis.h"

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

void Graphics::CameraMove(const glm::vec3& moveVec) {
	m_camera->Move(moveVec);
}

void Graphics::CameraViewPointFix() {
	m_camera->ViewPointFix();
}

void Graphics::CameraViewPointUnFix() {
	m_camera->ViewPointUnFix();
}

void Graphics::Init() {
	// 쉐이더 프로그램 생성
	m_shader = std::make_unique<Shader>();
	m_shader->CreateShaderProgram();

	// 쉐이더 프로그램이 각종 정점 정보, 행렬들을 등록, 전송할 수 있도록 프로그램 사용 설정
	m_shader->UseProgram();

	// 카메라 생성
	m_camera = std::make_unique<Camera>();
	m_camera->Init();

	// 모델리스트를 생성하고 모델 불러오기
	m_modelList = std::make_unique<ModelList>();
	m_modelList->Init(m_shader->GetShaderProgramID());

	m_modelList->LoadModel("cube.obj");

	testModel = m_modelList->GetModel("cube").get();

	m_axisSystem = std::make_unique<Axis>();
	m_axisSystem->Init(m_shader->GetShaderProgramID());

	// 투영 변환 행렬 계산 및 전송
	SetPerspectiveMat();
	// 쉐이더 프로그램 사용 종료
	m_shader->UnUseProgram();
}

void Graphics::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_camera->Update(deltaTime);
}

void Graphics::Render() {
	m_shader->UseProgram();

	// 변환 행렬들 계산
	m_camera->Render();
	m_shader->SetViewMat(m_camera->GetViewMat());

	// rendering code 
	m_axisSystem->DrawAxis();
	testModel->Render();
	

	m_shader->UnUseProgram();
}