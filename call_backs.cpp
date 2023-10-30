#include "Engine.h"
#include "pch.h"
#include "call_backs.h"
#include "Shader.h"

extern class Engine e;

// 그리기 콜백함수
void renderFunc()
{
	// rendering function
	e.Render();
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
	e.Input(key, true);
}

void keyboardUpFunc(unsigned char key, int x, int y)
{
	e.Input(key, false);
}

void specialkeyFunc(int key, int x, int y)
{
	e.SpecialInput(key, true);
}

void specialKeyUpFunc(int key, int x, int y)
{
	e.SpecialInput(key, false);

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
	e.MouseMotionInput(x, y);
}

void mousePassiveMotion(int x, int y)
{
	e.MousePassiveMotionInpit(x, y);
}

void mouseWheel(int dir, int x, int y)
{
}
