#include "Engine.h"
#include "pch.h"
#include "call_backs.h"
#include "Shader.h"

extern class Engine e;

// 그리기 콜백함수
void renderFunc()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// rendering function
	e.Render();

	glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
	e.ReSizeWindow(x, y);
}

void idleFunc()
{
	// Frame객체의 Update함수 사용
	e.Update();

	glutPostRedisplay();
}


void keyboardFunc(unsigned char key, int x, int y)
{
	e.Input(key);
}

void keyboardUpFunc(unsigned char key, int x, int y)
{
	
}

void specialkeyFunc(int key, int x, int y)
{
	e.SpecialInput(key);
}

void mouseFunc(int button, int state, int x, int y)
{
}

void mouseLeftDown(int state, int x, int y)
{
}

void mouseRightDown(int state, int x, int y)
{
}

void mouseMotion(int x, int y)
{
}

void mousePassiveMotion(int x, int y)
{
}

void mouseWheel(int dir, int x, int y)
{
}
