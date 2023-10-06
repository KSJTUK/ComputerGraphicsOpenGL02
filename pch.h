#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

// 자주쓰이는 클래스, 전역함수, 라이브러리등을 정의, 선언할 파일
// 표준 라이브러리
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// 사용자 정의 라이브러리

// 클래스, 구조체
inline void SafeDeletePointer(void* pointer)
{
	if (pointer) {
		delete pointer;
	}
}

inline void SafeDeleteArrayPointer(void* pointer)
{
	if (pointer) {
		delete[] pointer;
	}
}