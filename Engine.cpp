#include "pch.h"
#include "Engine.h"
#include "call_backs.h"
#include "Camera.h"
#include "Shader.h"
#include "Cone.h"
#include "Cube.h"
#include "Renderer.h"
#include "Timer.h"
#include "Mesh.h"

Engine::Engine() {
	m_windowInfo.x = 100;
	m_windowInfo.y = 100;
	m_windowInfo.width = 800;
	m_windowInfo.height = 600;
	m_windowInfo.fWidth = static_cast<float>(m_windowInfo.width);
	m_windowInfo.fHeight = static_cast<float>(m_windowInfo.height);

	std::string title{ "OpenGL Project 02" };
	std::string::size_type size = title.size();
	m_windowInfo.windowTitle = new char[size + 1] {};
	memcpy(m_windowInfo.windowTitle, title.c_str(), size + 1);
}

Engine::~Engine() {
	// 동적할당 객체들 메모리 할당 해제
	SafeDeleteArrayPointer(m_windowInfo.windowTitle);
}

// 콜백함수들 등록
void Engine::SubscribeCallbacks() {
	glutDisplayFunc(renderFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutIdleFunc(idleFunc);
	glutSpecialFunc(specialkeyFunc);
}

void Engine::SetWindowSize(int windowWidth, int windowHeight) {
	m_windowInfo.width = static_cast<size_t>(windowWidth);
	m_windowInfo.height = static_cast<size_t>(windowHeight);
	m_windowInfo.fWidth = static_cast<float>(windowWidth);
	m_windowInfo.fHeight = static_cast<float>(windowHeight);
}


void Engine::Init(int* argc, char** argv) {
	// glut라이브러리 초기화
	glutInit(argc, argv);

	// 윈도우 출력모드 설정(더블버퍼링, RGBA)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	// 윈도우 크기, 좌표 설정
	glutInitWindowPosition(m_windowInfo.x, m_windowInfo.y);
	glutInitWindowSize(m_windowInfo.width, m_windowInfo.height);

	// 윈도우 생성
	glutCreateWindow(m_windowInfo.windowTitle);

	// glew 라이브러리 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw "GLEW 라이브러리 초기화 실패";
	}

	SubscribeCallbacks();

	// 타이머 초기화
	m_timer = std::make_unique<Timer>();
	m_timer->Init();

	// 쉐이더 프로그램 초기화
	m_shader = std::make_unique<Shader>();
	m_shader->CreateShaderProgram();

	m_renderer = std::make_shared<Renderer>();
	m_renderer->Init(m_shader->GetShaderProgramID());

	m_shader->UseProgram();
	m_cubeModel = std::make_shared<class Mesh>(m_renderer, "cube.obj");

	m_coneModel = std::make_shared<class Mesh>(m_renderer, "cone.obj");

	m_cube = new Cube{ m_cubeModel };
	m_cone = new Cone{ m_coneModel };
}

void Engine::ReSizeWindow(int w, int h) {
	m_windowInfo.width = w;
	m_windowInfo.height = h;
	m_windowInfo.fWidth = static_cast<float>(m_windowInfo.width);
	m_windowInfo.fHeight = static_cast<float>(m_windowInfo.height);
}

void Engine::Update() {
	m_timer->Update();
	m_deltaTime = m_timer->GetDeltaTime();
}

void Engine::Render() {
	m_shader->UseProgram();
	m_cube->Render();
	m_cone->Render();
}






// --------------------------------------------------------------------
void Engine::SubscribeMouseMotionFunc(void(*func)(int, int)) {
	glutMotionFunc(func);
}

void Engine::SubscribeDrawFunc(void(*func)(void)) {
	glutDisplayFunc(func);
}

void Engine::SubscribeMouseFunc(void(*func)(int, int, int, int)) {
	glutMouseFunc(func);
}

void Engine::SubscribeKeyboardUpfunc(void(*func)(unsigned char, int, int)) {
	glutKeyboardUpFunc(func);
}

void Engine::SubscribePassiveMotionFunc(void(*func)(int, int)) {
	glutPassiveMotionFunc(func);
}

void Engine::SubscribeKeyboardFunc(void(*func)(unsigned char, int, int)) {
	glutKeyboardFunc(func);
}

void Engine::SubscribeReshapeFunc(void(*func)(int, int)) {
	glutReshapeFunc(func);
}

void Engine::SubscribeIdleFUnc(void(*func)(void)) {
	glutIdleFunc(func);
}

void Engine::Loop() {
	glutMainLoop();
}

void Engine::LoopEnd() {
	glutLeaveMainLoop();
}

void Engine::Input(unsigned char key) {
	switch (key) {
	case '1':
		m_cube->RenderFace(1);
		break;

	case '2':
		m_cube->RenderFace(2);
		break;

	case '3':
		m_cube->RenderFace(3);
		break;

	case '4':
		m_cube->RenderFace(4);
		break;

	case '5':
		m_cube->RenderFace(5);
		break;

	case '6':
		m_cube->RenderFace(6);
		break;

	case '7':
		m_cone->RenderFace(1);
		break;

	case '8':
		m_cone->RenderFace(2);
		break;

	case '9':
		m_cone->RenderFace(3);
		break;

	case '0':
		m_cone->RenderFace(4);
		break;

	case 'r':
		m_cube->ResetRender();
		break;

	case 'c':
		m_cube->RenderTwoFace(glm::linearRand(1, 6), glm::linearRand(1, 6));
		break;

	case 't':
		m_cone->RenderTwoFace(glm::linearRand(1, 4), glm::linearRand(1, 4));
		break;

	default:
		break;

	}
}
