#include "Solutions.h"
#include "ModelList.h"
#include "Model.h"
#include "Object.h"
#include "Axis.h"
#include "Spiral.h"
#include "GraphicBuffers.h"
#include "Tank.h"

void Solution15::Init() {
	m_object = new Object{ ModelList::GetInst()->GetModel("cylinder"), glm::vec3{ 0.f }, "cylinder" };
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
		prevPos.push_back(m_objects[i].Orbit(0.01f * oribit, glm::vec3{ 0.f, 1.f, 0.f }, glm::vec3{ }));
	}

	loopSize = m_orbitObject.size();
	for (auto i = 0; i < loopSize; ++i) {
		glm::vec3 pos{ m_objects[i].GetPosition() };
		m_orbitObject[i].SetPosition(prevPos[i] + m_orbitObject[i].GetPosition());
		m_orbitObject[i].Orbit(0.01f, glm::vec3{ 0.f, 1.f, 0.f }, pos);
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

void Solution17::SetShaderProgramID(unsigned int shaderProgramID) {
	m_shaderProgramID = shaderProgramID;
}

void Solution17::Init() {
	m_objects.push_back(Object{ ModelList::GetInst()->GetModel("cube"), glm::vec3{ 5.f, 0.f, 0.f }, "cube" });
	m_objects.push_back(Object{ ModelList::GetInst()->GetModel("sphere"), glm::vec3{ -5.f, 0.f, 0.f }, "sphere" });
	for (auto i = 0; i < m_objects.size(); ++i) {
		m_rotateX.push_back(0);
		m_rotateY.push_back(0);
	}

	oribit = 0;

	Spiral::Init(m_shaderProgramID);
	Spiral::MakeSpiral(10000, glm::vec3{ }, 1.f, 1);
}

void Solution17::ReInit() {
	m_objects.clear();
	m_rotateX.clear();
	m_rotateY.clear();
	Init();
}

void Solution17::Input(unsigned char key, bool down) {
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
					initPos.x += 5.f;
					m_orbitObject.push_back(Object{ m_objects[i].GetModelTag(), initPos });
				}
			}
			else {
				m_orbitObject.clear();
			}
		}

		if (key == 't') {
			if (!m_objects.empty()) {
				for (auto& e : m_objects) {
					e.ScaleAll(glm::vec3{ 0.01f, 0.01f, 0.01f });
				}
			}

			if (!m_orbitObject.empty()) {
				for (auto& e : m_orbitObject) {
					e.ScaleAll(glm::vec3{ 0.01f, 0.01f, 0.01f });
				}
			}
		}

		if (key == 'z') {
			if (!m_objects.empty()) {
				for (auto& e : m_objects) {
					e.ScaleAll(glm::vec3{ -0.01f, -0.01f, -0.01f });
				}
			}

			if (!m_orbitObject.empty()) {
				for (auto& e : m_orbitObject) {
					e.ScaleAll(glm::vec3{ -0.01f, -0.01f, -0.01f });
				}
			}
		}

		if (key == 'u') {
			if (!m_objects.empty()) {
				for (auto& e : m_objects) {
					e.Scale(glm::vec3{ 0.01f, 0.01f, 0.01f });
				}
			}

			if (!m_orbitObject.empty()) {
				for (auto& e : m_orbitObject) {
					e.Scale(glm::vec3{ 0.01f, 0.01f, 0.01f });
				}
			}
		}

		if (key == 'i') {
			if (!m_objects.empty()) {
				for (auto& e : m_objects) {
					e.Scale(glm::vec3{ -0.01f, -0.01f, -0.01f });
				}
			}

			if (!m_orbitObject.empty()) {
				for (auto& e : m_orbitObject) {
					e.Scale(glm::vec3{ -0.01f, -0.01f, -0.01f });
				}
			}
		}


	}
}

void Solution17::SpecialInput(int key, bool down) {
	if (down) {
		if (key == GLUT_KEY_F10) {
			drawSpiral = !drawSpiral;
			if (m_spirals.empty()) {
				size_t loopSize{ m_objects.size() };
				for (auto i = 0; i < loopSize; ++i) {
					Spiral newSpiral{ };
					newSpiral.SetPosition(m_objects[i].GetPosition());
					m_spirals.push_back(newSpiral);
				}
			}
			else {
				m_spirals.clear();
			}
		}

		glm::vec3 originpositions[2]{
			m_objects[1].GetPosition(),
			m_objects[0].GetPosition()
		};
		if (key == GLUT_KEY_F6) {
			for (auto& object : m_objects) {
				object.MoveToPoint(2, glm::vec3{ }, object.GetPosition());
			}
		}
		if (key == GLUT_KEY_F7) {
			for (auto i = 0; i < 2; ++i) {
				m_objects[i].MoveToPoint(1, originpositions[i]);
			}
		}

		if (key == GLUT_KEY_F8) {
			float dir{ 1.f };
			for (auto i = 0; i < 2; ++i) {
				m_objects[i].MoveToPoint(2, glm::vec3{ 0.f, 10.f * dir, 0.f }, originpositions[i]);
				dir = -dir;
			}
		}
	}
}

void Solution17::Update(float deltaTime) {
	size_t loopSize{ m_objects.size() };
	std::vector<glm::vec3> prevPos{ };
	for (auto i = 0; i < loopSize; ++i) {
		m_objects[i].Update(deltaTime);
		m_objects[i].RotateX(m_rotateX[i]);
		m_objects[i].RotateY(m_rotateY[i]);
		if (!m_spirals.empty()) {
			prevPos.push_back(m_objects[i].MoveSpiral(m_spirals[i]));
		}
		else {
			prevPos.push_back(glm::vec3{ });
		}
	}


	loopSize = m_orbitObject.size();
	for (auto i = 0; i < loopSize; ++i) {
		glm::vec3 pos{ m_objects[i].GetPosition() };
		m_orbitObject[i].SetPosition(prevPos[i] + m_orbitObject[i].GetPosition());
		m_orbitObject[i].Orbit(0.01f, glm::vec3{ 0.f, 1.f, 0.f }, pos);
	}
}

void Solution17::Render() {
	for (auto& spiral : m_spirals) {
		spiral.DrawSpiral();
	}


	for (auto& object : m_objects) {
		object.Render();
	}

	for (auto& object : m_orbitObject) {
		object.Render();
	}
}

void Solution19::Init() {
	m_originPlanet = new Object{ "sphere", glm::vec3{ } };
	m_originPlanet->SetScaleFactor(glm::vec3{ 3.f });

	for (int i = 0; i < 3; ++i) {
		m_orbitPlanet.push_back(OrbitObject{ "sphere", m_originPlanet->GetPosition(), orbitAxis[i], 25.f, glm::linearRand(0.001f, 0.05f) });
	}

	for (int i = 0; i < 3; ++i) {
		m_orbitPlanetsMoon.push_back(OrbitObject{ "sphere", m_orbitPlanet[i].GetPosition(), orbitAxis[i], 10.f, glm::linearRand(0.001f, 0.05f) });
		m_orbitPlanetsMoon[i].SetScaleFactor(glm::vec3{ 0.3f });
	}
}

void Solution19::ReInit() {
}

void Solution19::Input(unsigned char key, bool down) {
	if (down) {
		if (key == 'p') {

		}

		if (key == 'n') {
			int currentDrawMode = ModelList::GetInst()->GetCurrentDrawMode();
			if (currentDrawMode == GL_LINES) {
				ModelList::GetInst()->SetDrawModes(GL_TRIANGLES);
			}
			else {
				ModelList::GetInst()->SetDrawModes(GL_LINES);
			}
		}

		if (key == 'y') {
			constexpr float EPSILON = 0.0001f;
			if (m_rotateDirOrbitY < EPSILON and m_rotateDirOrbitY > -EPSILON) {
				m_rotateDirOrbitY = 1.f;
			}
			else if (m_rotateDirOrbitY > 1.f - EPSILON) {
				m_rotateDirOrbitY = -1.f;
			}
			else {
				m_rotateDirOrbitY = 0.f;
			}
		}

		if (key == 'z') {
			constexpr float EPSILON = 0.0001f;
			if (m_rotateDirOrbitZ < EPSILON and m_rotateDirOrbitZ > -EPSILON) {
				m_rotateDirOrbitZ = 1.f;
			}
			else if (m_rotateDirOrbitZ > 1.f - EPSILON) {
				m_rotateDirOrbitZ = -1.f;
			}
			else {
				m_rotateDirOrbitZ = 0.f;
			}
		}

		if (key == 'w') {
			m_originPlanet->MoveY();
		}

		if (key == 's') {
			m_originPlanet->MoveY(-1);
		}

		if (key == 'd') {
			m_originPlanet->MoveX();
		}

		if (key == 'a') {
			m_originPlanet->MoveX(-1);
		}

		if (key == '+' or key == '=') {
			m_originPlanet->MoveZ(-1);
		}

		if (key == '-' or key == '_') {
			m_originPlanet->MoveZ();
		}

		if (key == 'x') {
			rotate.x = !rotate.x;
		}

		if (key == 'q') {
			rotate.y = !rotate.y;
		}

		if (key == 'e') {
			rotate.z = !rotate.z;
		}
	}
}

void Solution19::SpecialInput(int key, bool down) {
}

void Solution19::Update(float deltaTime) {
	glm::vec3 originPlanetDeltaPosition = m_originPlanet->GetDeltaPosition();

	m_originPlanet->Update(deltaTime);
	m_originPlanet->Orbit(m_rotateDirOrbitY * 0.01f, glm::vec3{ 0.f, 1.f, 0.f }, glm::vec3{ });

	std::vector<glm::vec3> deltaPositions{ };
	for (int i = 0; i < 3; ++i) {
		deltaPositions.push_back(m_orbitPlanet[i].Update(deltaTime, originPlanetDeltaPosition));
		deltaPositions[i] += m_orbitPlanet[i].Orbit(m_rotateDirOrbitY * 0.01f, glm::vec3{ 0.f, 1.f, 0.f }, m_originPlanet->GetPosition());
		deltaPositions[i] += m_orbitPlanet[i].OrbitAxisRotate(glm::vec3{ 0.f, 0.f, 1.f }, m_rotateDirOrbitZ * 1.f, 0.001f);
	}

	for (int i = 0; i < 3; ++i) {
		m_orbitPlanetsMoon[i].Update(deltaTime, deltaPositions[i]);
		m_orbitPlanetsMoon[i].Orbit(m_rotateDirOrbitY * 0.01f, glm::vec3{ 0.f, 1.f, 0.f }, m_originPlanet->GetPosition());
		m_orbitPlanetsMoon[i].OrbitAxisRotate(glm::vec3{ 0.f, 0.f, 1.f }, m_rotateDirOrbitZ * 1.f, 0.001f);
	}

	if (rotate.x) {
		m_originPlanet->RotateX();
		for (int i = 0; i < 3; ++i) {
			m_orbitPlanet[i].RotateX();
		}

		for (int i = 0; i < 3; ++i) {
			m_orbitPlanetsMoon[i].RotateX();
		}
	}

	if (rotate.y) {
		m_originPlanet->RotateY();
		for (int i = 0; i < 3; ++i) {
			m_orbitPlanet[i].RotateY();
		}

		for (int i = 0; i < 3; ++i) {
			m_orbitPlanetsMoon[i].RotateY();
		}
	}

	if (rotate.z) {
		m_originPlanet->RotateZ();
		for (int i = 0; i < 3; ++i) {
			m_orbitPlanet[i].RotateZ();
		}

		for (int i = 0; i < 3; ++i) {
			m_orbitPlanetsMoon[i].RotateZ();
		}
	}
}

void Solution19::Render() {
	m_originPlanet->Render();
	for (auto& object : m_orbitPlanet) {
		object.Render();
	}

	for (auto& object : m_orbitPlanetsMoon) {
		object.Render();
	}
}

void Solution20::SetShaderProgramID(unsigned int shaderProgramID) {
	m_shaderProgramID = shaderProgramID;
}

void Solution20::Init() {
	m_groundBuffer = std::make_unique<GraphicBuffers>();
	m_groundBuffer->Init(m_shaderProgramID);
	m_groundBuffer->SetVerticies(ground);
	m_groundBuffer->SetIndexBuffer(groundIndex);

	m_tank = new Tank{ glm::vec3{ 0.f, 0.5f, 0.f } };
}

void Solution20::ReInit() {
}

void Solution20::Input(unsigned char key, bool down) {
	if (down) {
		if (key == 'c') {
			delete m_tank;
			m_tank = new Tank{ glm::vec3{ 0.f, 0.5f, 0.f } };
			return;
		}
	}

	m_tank->Input(key, down);
}

void Solution20::SpecialInput(int key, bool down) {
	m_tank->SpecialInput(key, down);
}

void Solution20::Update(float deltaTime) {
	m_tank->Update(deltaTime);
}

void Solution20::Render() {
	m_groundBuffer->SetTransformMat(glm::mat4{ 1.f });
	m_groundBuffer->Render();
	m_tank->Render();
}

#include "FaceAnimationCube.h"
#include "FaceAnimationCone.h"
void Solution18::SetShaderProgramID(unsigned int shaderProgramID) {
	m_shaderProgramID = shaderProgramID;
}

void Solution18::Init() {
	m_faceCube = new FaceAnimationCube{ };
	m_faceCube->Init(m_shaderProgramID);

	m_faceCone = new FaceAnimationCone{ };
	m_faceCone->Init(m_shaderProgramID);
}

void Solution18::ReInit() {
}

void Solution18::Input(unsigned char key, bool down) {
	if (down) {
		if (key == 'c') {
			if (m_mode == 0) {
				m_mode = 1;
			}
			else {
				m_mode = 0;
			}
		}
	}

	if (m_mode) {
		m_faceCube->Input(key, down);
	}
	else {
		m_faceCone->Input(key, down);
	}
}

void Solution18::SpecialInput(int key, bool down) {
	
}

void Solution18::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	if (m_mode) {
		m_faceCube->Update(deltaTime);
	}
	else {
		m_faceCone->Update(deltaTime);
	}
}

void Solution18::Render() {
	if (m_mode) {
		m_faceCube->Render();
	}
	else {
		m_faceCone->Render();
	}
}

void Solution21::SetShaderProgramID(unsigned int shaderProgramID) {
	m_shaderProgramID = shaderProgramID;
}

void Solution21::Init() {
	m_groundBuffer = std::make_unique<GraphicBuffers>();
	m_groundBuffer->Init(m_shaderProgramID);
	m_groundBuffer->SetVerticies(ground);
	m_groundBuffer->SetIndexBuffer(groundIndex);

	m_tank = new Tank{ glm::vec3{ 0.f, 0.5f, 0.f } };
}

void Solution21::ReInit() {
}

void Solution21::Input(unsigned char key, bool down) {
	if (down) {
		if (key == 'c') {
			delete m_tank;
			m_tank = new Tank{ glm::vec3{ 0.f, 0.5f, 0.f } };
			return;
		}
	}

	m_tank->Input(key, down);
}

void Solution21::SpecialInput(int key, bool down) {
	m_tank->SpecialInput(key, down);
}

void Solution21::Update(float deltaTime) {
	m_tank->Update(deltaTime);
}

void Solution21::Render() {
	m_groundBuffer->SetTransformMat(glm::mat4{ 1.f });
	m_groundBuffer->Render();
	m_tank->Render();
}

#include "Robot.h"

bool collision(const Object& obj1, const Robot& robot) {
	if (robot.Collision(obj1)) {
		return true;
	}
	return false;
}

void Solution22::SetShaderProgramID(unsigned int shaderProgramID) {
	m_shaderProgramID = shaderProgramID;
}

void Solution22::SetRobotViewMode(bool mode) {
	m_robot;
}

const glm::mat4& Solution22::GetRobotViewMat() const {
	return m_robot->GetRobotViewMat();
}

void Solution22::Init() {
	m_robot = new Robot{ };
	m_robot->Init(m_shaderProgramID);

	m_cubes.push_back(new Object{ "cube", glm::vec3{ 2.f, 0.5f, 2.f } });
	m_cubes.push_back(new Object{ "cube", glm::vec3{ 3.f, 2.f, 3.f } });
	m_cubes.push_back(new Object{ "cube", glm::vec3{ 4.f, 3.5f, 4.f } });
	m_cubes.push_back(new Object{ "cube", glm::vec3{ 4.f, 3.5f, 6.f } });
	m_theaterBox =  new TheaterBox{ };
	m_theaterBox->Init(m_shaderProgramID);
}

void Solution22::ReInit() {
}

void Solution22::Input(unsigned char key, bool down) {
	if (down) {
		if (key == 'o') {
			m_theaterBox->SetBoxAnimationFlag();
		}
	}

	m_robot->Input(key, down);
}

void Solution22::SpecialInput(int key, bool down) {
	if (down) {
		if (key == GLUT_KEY_F6) {
			if (m_robotViewMode) {
				m_robot->SettingRobotViewMode(false);
				m_robotViewMode = false;
			}
			else {
				m_robot->SettingRobotViewMode(true);
				m_robotViewMode = true;
			}
		}
	}
}

void Solution22::MouseMotionInput(int x, int y, int prevX, int prevY) {
	m_robot->MouseMotionInput(x, y, prevX, prevY);
}

void Solution22::Update(float deltaTime) {
	m_theaterBox->Update(deltaTime);
	m_robot->Update(deltaTime);
	for (auto& cube : m_cubes) {
		cube->Update(deltaTime);
		m_robot->Collision(*cube);
	}
}

void Solution22::Render() {
	for(auto& cube : m_cubes) cube->Render();
	m_theaterBox->Render();
	m_robot->Render();
}

bool collisionAndIntegratedPosition(const Object& staticPositionObj, const Object& targetObj, glm::vec3& intergratedPosition, const glm::vec3& deltaPositions) 
{
	auto box1 = staticPositionObj.GetBoundingBox();
	auto box2 = targetObj.GetBoundingBox();

	glm::vec3 centerBox1{ (box1.first + box1.second) / 2.f };
	glm::vec3 centerBox2{ (box2.first + box2.second) / 2.f };

	glm::vec3 targetPosition{ targetObj.GetPosition() };

	glm::bvec3 deltaPosIsZero = glm::lessThanEqual(glm::abs(deltaPositions), glm::vec3{ 0.00001f });

	if (box1.second.x <= box2.first.x and box2.second.x <= box1.first.x and
		box1.second.y <= box2.first.y and box2.second.y <= box1.first.y and
		box1.second.z <= box2.first.z and box2.second.z <= box1.first.z) {

		float atLeastPos{ 0.001f };

		if (!deltaPosIsZero.x) {
			if (centerBox1.x < centerBox2.x) {
				intergratedPosition.x += box2.second.x - box1.first.x - atLeastPos;
			}
			else {
				intergratedPosition.x += box2.first.x - box1.second.x + atLeastPos;
			}
		}

		if (!deltaPosIsZero.y) {
			if (centerBox1.y < centerBox2.y) {
				intergratedPosition.y += box2.second.y - box1.first.y - atLeastPos;
			}
			else {
				intergratedPosition.y += box2.first.y - box1.second.y + atLeastPos;
			}
		}

		if (!deltaPosIsZero.z) {
			if (centerBox1.z < centerBox2.z) {
				intergratedPosition.z += box2.second.z - box1.first.z - atLeastPos;
			}
			else {
				intergratedPosition.z += box2.first.z - box1.second.z + atLeastPos;
			}
		}

		return true;
	}

	return false;
}

bool collision(const Object& obj1, const Object& obj2) 
{
	auto box1 = obj1.GetBoundingBox();
	auto box2 = obj2.GetBoundingBox();

	if (box1.second.x <= box2.first.x and box2.second.x <= box1.first.x and
		box1.second.y <= box2.first.y and box2.second.y <= box1.first.y and
		box1.second.z <= box2.first.z and box2.second.z <= box1.first.z) {
		return true;
	}

	return false;
}