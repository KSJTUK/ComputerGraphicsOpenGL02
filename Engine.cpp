#include "pch.h"
#include "Engine.h"
#include "call_backs.h"
#include "Timer.h"
#include "Graphics.h"
#include "window_info.h"

Engine::Engine() {
	m_windowInfo = std::make_shared<WindowInfo>();

	m_windowInfo->x = 100;
	m_windowInfo->y = 100;
	m_windowInfo->width = 800;
	m_windowInfo->height = 600;
	m_windowInfo->fWidth = static_cast<float>(m_windowInfo->width);
	m_windowInfo->fHeight = static_cast<float>(m_windowInfo->height);

	std::string title{ "OpenGL Project 02" };
	std::string::size_type size = title.size();
	m_windowInfo->windowTitle = new char[size + 1] {};
	memcpy(m_windowInfo->windowTitle, title.c_str(), size + 1);
}

Engine::~Engine() {
	// 동적할당 객체들 메모리 할당 해제
	SafeDeleteArrayPointer(m_windowInfo->windowTitle);
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

size_t Engine::GetWindowWidth() const {
	return m_windowInfo->width;
}

size_t Engine::GetWindowHeight() const {
	return m_windowInfo->height;
}

float Engine::GetWindowWidthF() const {
	return m_windowInfo->fWidth;
}

float Engine::GetWindowHeightF() const {
	return m_windowInfo->fHeight;
}

void Engine::SetWindowSize(int windowWidth, int windowHeight) {
	m_windowInfo->width = static_cast<size_t>(windowWidth);
	m_windowInfo->height = static_cast<size_t>(windowHeight);
	m_windowInfo->fWidth = static_cast<float>(windowWidth);
	m_windowInfo->fHeight = static_cast<float>(windowHeight);
}


void Engine::Init(int* argc, char** argv) {
	// glut라이브러리 초기화
	glutInit(argc, argv);

	// 윈도우 출력모드 설정(더블버퍼링, RGBA, 깊이버퍼)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// 윈도우 크기, 좌표 설정
	glutInitWindowPosition(m_windowInfo->x, m_windowInfo->y);
	glutInitWindowSize(m_windowInfo->width, m_windowInfo->height);

	// 윈도우 생성
	glutCreateWindow(m_windowInfo->windowTitle);

	// glew 라이브러리 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw "GLEW 라이브러리 초기화 실패";
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	SubscribeCallbacks();

	// 타이머 초기화
	m_timer = std::make_unique<Timer>();
	m_timer->Init();

	m_grapics = std::make_unique<Graphics>();
	m_grapics->SetWindowInfo(m_windowInfo);
	m_grapics->Init();
}

void Engine::ReSizeWindow(int w, int h) {
	m_windowInfo->width = w;
	m_windowInfo->height = h;
	m_windowInfo->fWidth = static_cast<float>(m_windowInfo->width);
	m_windowInfo->fHeight = static_cast<float>(m_windowInfo->height);


	m_grapics->SetPerspectiveMat();

	glViewport(0, 0, w, h);
}

void Engine::Update() {
	m_timer->Update();
	m_deltaTime = m_timer->GetDeltaTime();
	m_grapics->Update(m_deltaTime);
}

void Engine::Render() {
	m_grapics->Render();
}

void Engine::Input(unsigned char key) {
	switch (key) {
	case 'w':
		m_grapics->CameraMove(glm::vec3{ 0.f, 0.f, 1.f });
		break;

	case 'a':
		m_grapics->CameraMove(glm::vec3{ 1.f, 0.f, 0.f });
		break;

	case 's':
		m_grapics->CameraMove(glm::vec3{ 0.f, 0.f, -1.f });
		break;

	case 'd':
		m_grapics->CameraMove(glm::vec3{ -1.f, 0.f, 0.f });
		break;

	case 'm':
		m_grapics->CameraMove(glm::vec3{ 0.f, 1.f, 0.f });
		break;

	case 'n':
		m_grapics->CameraMove(glm::vec3{ 0.f, -1.f, 0.f });
		break;

	case 'v':
		m_grapics->CameraViewPointFix();
		break;

	case 'b':
		m_grapics->CameraViewPointUnFix();
		break;
	}
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
