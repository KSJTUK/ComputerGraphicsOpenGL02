#include "Solutions.h"
#include "ModelList.h"
#include "Model.h"
#include "Object.h"

void Solution15::Init() {
	m_object = new Object{ ModelList::GetInst()->GetModel("cube"), glm::vec3{ 0.f }, "cube" };
}

void Solution15::ReInit() {
	if (m_object) {
		delete m_object;
	}
	m_object = new Object{ ModelList::GetInst()->GetModel("cube"), glm::vec3{ 0.f }, "cube" };
	m_culling = true;
	m_drawSolid = true;
	m_deltaTime = 0.f;
	rotateX = 0;
	rotateY = 0;
}

void Solution15::Input(unsigned char key, bool down) {
	if (down) {
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

		if (key == 'x') {
			if (rotateX == 0) {
				rotateX = 1;
			}
			else if (rotateX == 1) {
				rotateX = -1;
			}
			else {
				rotateX = 0;
			}
		}

		if (key == 'y') {
			if (rotateY == 0) {
				rotateY = 1;
			}
			else if (rotateY == 1) {
				rotateY = -1;
			}
			else {
				rotateY = 0;
			}
		}

		if (key == 's') {
			m_object->SetPosition(glm::vec3{ 0.f });
			rotateX = 0;
			rotateY = 0;
		}

		if (key == 'p') {
			glm::vec3 position{ m_object->GetPosition() };
			std::string prevTag{ m_object->GetModelTag() };
			if (m_object) {
				delete m_object;
			}

			if (prevTag == "cube") {
				m_object->SetModel("cone");
			}
			else {
				m_object->SetModel("cube");
			}
		}
	}
}

void Solution15::SpecialInput(int key, bool down) {
	if (down) {
		if (key == GLUT_KEY_RIGHT) {
			m_object->MoveX(1);
		}

		if (key == GLUT_KEY_LEFT) {
			m_object->MoveX(-1);
		}

		if (key == GLUT_KEY_UP) {
			m_object->MoveY(1);
		}

		if (key == GLUT_KEY_DOWN) {
			m_object->MoveY(-1);
		}
	}
}

void Solution15::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	m_object->Update(m_deltaTime);
	m_object->RotateX(rotateX);
	m_object->RotateZ(-rotateY);
}

void Solution15::Render() {
	m_object->Render();
}
