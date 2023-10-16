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
			std::string prevTag{ m_object->GetModelTag() };
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

void Solution16::Init() {
	m_objects.push_back(Object{ ModelList::GetInst()->GetModel("cube"), glm::vec3{ 5.f, 0.f, 0.f }, "cube" });
	m_objects.push_back(Object{ ModelList::GetInst()->GetModel("sphere"), glm::vec3{ -5.f, 0.f, 0.f }, "sphere" });
	for (auto i = 0; i < m_objects.size(); ++i) {
		m_rotateX.push_back(0);
		m_rotateY.push_back(0);
	}

	oribit = 0;
}

void Solution16::ReInit() {
	m_objects.clear();
	m_rotateX.clear();
	m_rotateY.clear();
	Init();
}

void Solution16::Input(unsigned char key, bool down) {
	if (down) {
		if (key == 'x') {
			for (auto& rot : m_rotateX) {
				if (rot == 0) {
					rot = 1;
				}
				else if (rot == 1) {
					rot = -1;
				}
				else {
					rot = 0;
				}
			}
		}

		if (key == 'y') {
			for (auto& rot : m_rotateY) {
				if (rot == 0) {
					rot = 1;
				}
				else if (rot == 1) {
					rot = -1;
				}
				else {
					rot = 0;
				}
			}
		}

		if (key == '1') {
			size_t loopSize{ m_objects.size() };
			for (auto i = 0; i < loopSize; ++i) {
				if (m_objects[i].GetPosition().x < 0.f) {
					m_rotateX[i] = 1;
					m_rotateY[i] = 1;
				}
				else {
					m_rotateX[i] = 0;
					m_rotateY[i] = 0;
				}
			}
		}
		else if (key == '2') {
			size_t loopSize{ m_objects.size() };
			for (auto i = 0; i < loopSize; ++i) {
				if (m_objects[i].GetPosition().x > 0.f) {
					m_rotateX[i] = 1;
					m_rotateY[i] = 1;
				}
				else {
					m_rotateX[i] = 0;
					m_rotateY[i] = 0;
				}
			}
		}
		else if (key == '3') {
			for (auto& rot : m_rotateX) {
				if (rot == 0) {
					rot = 1;
				}
				else if (rot == 1) {
					rot = -1;
				}
				else {
					rot = 0;
				}
			}

			for (auto& rot : m_rotateY) {
				if (rot == 0) {
					rot = 1;
				}
				else if (rot == 1) {
					rot = -1;
				}
				else {
					rot = 0;
				}
			}
		}

		if (key == 'r') {
			if (oribit == 0) {
				oribit = 1;
			}
			else if (oribit == 1) {
				oribit = -1;
			}
			else {
				oribit = 0;
			}
		}

		if (key == 's') {
			ReInit();
		}

		if (key == 'c') {
			std::string tags[3]{ "cone", "cube", "sphere" };
			for (auto& e : m_objects) {
				e.SetModel(tags[glm::linearRand(0, 2)]);
			}

			size_t loopSize{ m_orbitObject.size() };
			for (auto i = 0; i < loopSize; ++i) {
				m_orbitObject[i].SetModel(m_objects[i].GetModelTag());
			}
		}

		if (key == 'o') {
			if (m_orbitObject.empty()) {
				size_t loopSize{ m_objects.size() };
				for (auto i = 0; i < loopSize; ++i) {
					glm::vec3 initPos{ m_objects[i].GetPosition() };
					initPos.x += 10.f;
					m_orbitObject.push_back(Object{ m_objects[i].GetModelTag(), initPos });
				}
			}
			else {
				m_orbitObject.clear();
			}
		}
	}
}

void Solution16::SpecialInput(int key, bool down)
{
}

void Solution16::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	size_t loopSize{ m_objects.size() };
	std::vector<glm::vec3> prevPos{ };
	for (auto i = 0; i < loopSize; ++i) {
		m_objects[i].Update(m_deltaTime);
		m_objects[i].RotateX(m_rotateX[i]);
		m_objects[i].RotateY(m_rotateY[i]);
		prevPos.push_back(m_objects[i].OrbitZ(oribit));
	}
	
	loopSize = m_orbitObject.size();
	for (auto i = 0; i < loopSize; ++i) {
		glm::vec3 pos{ m_objects[i].GetPosition() };
		m_orbitObject[i].SetPosition(prevPos[i] + m_orbitObject[i].GetPosition());
		m_orbitObject[i].Orbit(0.01f, glm::vec3{ 0.f, 0.f, 1.f }, pos);
	}
}

void Solution16::Render() {
	for (auto& object : m_objects) {
		object.Render();
	}

	for (auto& orbitObject : m_orbitObject) {
		orbitObject.Render();
	}
}
