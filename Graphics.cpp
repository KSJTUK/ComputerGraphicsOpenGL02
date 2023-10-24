﻿#include "Graphics.h"
#include "gl_headers.h"
#include "window_info.h"
#include "Shader.h"
#include "ModelList.h"
#include "Camera.h"
#include "Model.h"
#include "Axis.h"
#include "Object.h"
#include "Solutions.h"
#include "OrbitObject.h"

Graphics::Graphics() { }

Graphics::~Graphics() { }

bool Graphics::IsInited() const {
	return m_isInited;
}

void Graphics::SetWindowInfo(std::shared_ptr<struct WindowInfo>& winInfo) {
	m_windowInfo = winInfo;
	if (m_curProjectionMat == CUR_PROJECTION_MAT_ORTHO) {
		SetOrthoMat();
	}
	else {
		SetPerspectiveMat();
	}
}

void Graphics::SetPerspectiveMat() {
	if (!m_isInited) {
		return;
	}

	m_shader->UseProgram();
	float aspect = m_windowInfo->fWidth / m_windowInfo->fHeight;
	float halfFovy = m_fovy / 2.f;

	m_shader->SetPerspectiveMat(glm::perspective(glm::radians(halfFovy), aspect, m_near, m_far));
	m_shader->UnUseProgram();
}

void Graphics::SetOrthoMat() {
	if (!m_isInited) {
		return;
	}

	m_shader->UseProgram();
	m_shader->SetPerspectiveMat(glm::ortho(-100.f, 100.f, -100.f, 100.f, -100.f, 100.f));
	m_shader->UnUseProgram();
}

void Graphics::Input(unsigned char key, bool down) {
	m_solutions[m_curSolutionIndex]->Input(key, down);
	m_camera->Input(key, down);
}

void Graphics::SpecialInput(int key, bool down) {
	if (key == GLUT_KEY_CTRL_L or key == GLUT_KEY_CTRL_R) {
		if (down) {
			controlDowned = true;
		}
		else {
			controlDowned = false;
		}
	}

	if (down) {

		if (controlDowned) {
			m_camera->SpecialInput(key, down);
		}
		else {
			if (key == GLUT_KEY_F2) {
				if (m_curSolutionIndex < m_solutions.size() - 1) {
					++m_curSolutionIndex;
					m_solutions[m_curSolutionIndex]->ReInit();
					//m_camera->CameraPositionSet(glm::vec3{ 0.f, 0.f, -10.f });
					//m_camera->CameraViewPointSet(glm::vec3{ 0.f, 0.f, 1.f });
				}
			}
			else if (key == GLUT_KEY_F3) {
				if (m_curSolutionIndex > 0) {
					--m_curSolutionIndex;
					m_solutions[m_curSolutionIndex]->ReInit();
					//m_camera->CameraPositionSet(glm::vec3{ 0.f, 0.f, -10.f });
					//m_camera->CameraViewPointSet(glm::vec3{ 0.f, 0.f, 1.f });
				}
			}

			else if (key == GLUT_KEY_F11) {
				if (m_curProjectionMat == CUR_PROJECTION_MAT_PERSPECTIVE) {
					SetOrthoMat();
					m_curProjectionMat = CUR_PROJECTION_MAT_ORTHO;
				}
				else {
					SetPerspectiveMat();
					m_curProjectionMat = CUR_PROJECTION_MAT_PERSPECTIVE;
				}
			}

			m_solutions[m_curSolutionIndex]->SpecialInput(key, down);
		}
	}
}

void Graphics::Init() {
	m_curProjectionMat = CUR_PROJECTION_MAT_PERSPECTIVE;
	// 쉐이더 프로그램 생성
	m_shader = std::make_unique<Shader>();
	m_shader->CreateShaderProgram();

	// 쉐이더 프로그램이 각종 정점 정보, 행렬들을 등록, 전송할 수 있도록 프로그램 사용 설정
	m_shader->UseProgram();

	// 카메라 생성
	m_camera = std::make_unique<Camera>();
	m_camera->Init();
	//m_camera->CameraPositionSet(glm::vec3{ 0.f, 0.f, -10.f });

	// 모델리스트를 생성하고 모델 불러오기
	ModelList::GetInst()->Init(m_shader->GetShaderProgramID());

	ModelList::GetInst()->LoadModel("sphere.obj");
	ModelList::GetInst()->LoadModel("cube.obj");
	ModelList::GetInst()->LoadModel("cone.obj");
	ModelList::GetInst()->LoadModel("cylinder.obj");

	m_axisSystem = std::make_unique<Axis>();
	m_axisSystem->Init(m_shader->GetShaderProgramID());

	CircleEffect::Init(m_shader->GetShaderProgramID());
	CircleEffect::MakeCircle(0.1f);

	m_solutions.push_back(new Solution15{ });
	m_solutions.push_back(new Solution16{ });
	Solution17* s{ new Solution17{ } };
	s->SetShaderProgramID(m_shader->GetShaderProgramID());
	m_solutions.push_back(s);
	Solution18* s18{ new Solution18{ } };
	s18->SetShaderProgramID(m_shader->GetShaderProgramID());
	m_solutions.push_back(s18);
	m_solutions.push_back(new Solution19{ });
	Solution20* s20 = { new Solution20{ } };
	s20->SetShaderProgramID(m_shader->GetShaderProgramID());
	m_solutions.push_back(s20);
	
	
	for (auto& solution : m_solutions) {
		solution->Init();
	}

	// test
	//m_curSolutionIndex = m_solutions.size() - 1;

	// 투영 변환 행렬 계산 및 전송
	SetPerspectiveMat();
	// 쉐이더 프로그램 사용 종료
	m_shader->UnUseProgram();
	m_isInited = true;
}

void Graphics::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_camera->Update(m_deltaTime);
	m_solutions[m_curSolutionIndex]->Update(deltaTime);
}

void Graphics::Render() {
	m_shader->UseProgram();

	// 변환 행렬들 계산
	m_camera->Render();
	m_shader->SetViewMat(m_camera->GetViewMat());

	// rendering code 
	m_axisSystem->DrawAxis();

	m_solutions[m_curSolutionIndex]->Render();

	m_shader->UnUseProgram();
}