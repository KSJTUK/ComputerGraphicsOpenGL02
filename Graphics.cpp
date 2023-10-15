#include "Graphics.h"
#include "gl_headers.h"
#include "window_info.h"
#include "Shader.h"
#include "ModelList.h"
#include "Camera.h"
#include "Model.h"
#include "Axis.h"
#include "Object.h"

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

void Graphics::Input(unsigned char key, bool down) {
	if (key == 'w') {
		m_drawSolid = !m_drawSolid;
		if (m_drawSolid) {
			ModelList::GetInst()->SetDrawModes(GL_TRIANGLES);
		}
		else {
			ModelList::GetInst()->SetDrawModes(GL_LINE_LOOP);
		}
	}

	if (key == 'h') {
		m_culling = !m_culling;
		if (m_culling) {
			glEnable(GL_CULL_FACE);
		}
		else {
			glDisable(GL_CULL_FACE);
		}
	}

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

	if (controlDowned) {
		m_camera->SpecialInput(key, down);
	}
	else {
		if (key == GLUT_KEY_RIGHT) {
			m_object->MoveX(-1);
		}

		if (key == GLUT_KEY_LEFT) {
			m_object->MoveX();
		}

		if (key == GLUT_KEY_UP) {
			m_object->MoveY();
		}

		if (key == GLUT_KEY_DOWN) {
			m_object->MoveY(-1);
		}
	}
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
	m_camera->CameraPositionSet(glm::vec3{ 0.f, 0.f, -10.f });

	// 모델리스트를 생성하고 모델 불러오기
	ModelList::GetInst()->Init(m_shader->GetShaderProgramID());

	ModelList::GetInst()->LoadModel("sphere.obj");
	ModelList::GetInst()->LoadModel("cube.obj");
	ModelList::GetInst()->LoadModel("cone.obj");

	m_axisSystem = std::make_unique<Axis>();
	m_axisSystem->Init(m_shader->GetShaderProgramID());

	m_object = new Object{ ModelList::GetInst()->GetModel("cube") };

	// 투영 변환 행렬 계산 및 전송
	SetPerspectiveMat();
	// 쉐이더 프로그램 사용 종료
	m_shader->UnUseProgram();
}

void Graphics::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_camera->Update(m_deltaTime);
	m_object->Update(m_deltaTime);
}

void Graphics::Render() {
	m_shader->UseProgram();

	// 변환 행렬들 계산
	m_camera->Render();
	m_shader->SetViewMat(m_camera->GetViewMat());

	// rendering code 
	m_axisSystem->DrawAxis();

	m_object->Render();

	m_shader->UnUseProgram();
}