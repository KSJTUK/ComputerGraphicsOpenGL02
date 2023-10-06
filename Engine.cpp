#include "pch.h"
#include "Engine.h"
#include "call_backs.h"
#include "Shader.h"
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
	m_windowTitle = new char[size + 1] {};
	memcpy(m_windowTitle, title.c_str(), size + 1);
}

Engine::~Engine() {
	// 동적할당 객체들 메모리 할당 해제
	//if (m_timer) delete m_timer;
	//m_timer = nullptr;
	SafeDeletePointer(m_shader);
	SafeDeleteArrayPointer(m_windowTitle);
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
	glutCreateWindow(m_windowTitle);

	// glew 라이브러리 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw "GLEW 라이브러리 초기화 실패";
	}

	SubscribeCallbacks();

	// 타이머 초기화
	m_timer = new Timer{ };
	m_timer->Init();

	// 쉐이더 프로그램 초기화
	m_shader = new Shader{ };
	m_shader->CreateShaderProgram();

	m_renderer = new Renderer{ };
	m_renderer->Init(m_shader->GetShaderProgramID());

	testMesh = new Mesh{ };
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
	testMesh->Render(m_renderer);
}

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
