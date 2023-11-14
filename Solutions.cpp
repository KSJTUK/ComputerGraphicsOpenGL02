#include "Solutions.h"
#include "ModelList.h"
#include "Model.h"
#include "Object.h"
#include "Axis.h"
#include "Spiral.h"
#include "GraphicBuffers.h"
#include "Tank.h"
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

void Solution23::SetShaderProgramID(unsigned int shaderProgramID) { m_shaderProgramID = shaderProgramID; }

void Solution23::Init() {
	m_cubeMap.resize(m_cubeMapSize);
	for (int x = 0; x < m_cubeMapSize; ++x) {
		for (int y = 0; y < m_cubeMapSize; ++y) {
			m_cubeMap[x].push_back(new Object{ "cube", glm::vec3{ x * m_cubeSize * 1.f, 0.f, y * m_cubeSize * 1.f } });
			if ((x + y) % 2 == 0) {
				m_cubeMap[x][y]->SetColor(glm::vec3{ 0.5f, 0.3f, 0.3f });
			}
			else {
				m_cubeMap[x][y]->SetColor(glm::vec3{ 1.0f, 0.5f, 0.1f });
			}
			m_cubeMap[x][y]->SetScaleFactor(glm::vec3{ m_cubeSize });
		}
	}
}

void Solution23::ReInit() { }

void Solution23::Input(unsigned char key, bool down) { }

void Solution23::SpecialInput(int key, bool down) { }

void Solution23::MouseMotionInput(int x, int y, int prevX, int prevY) { }

void Solution23::MouseMotionPassiveInput(int x, int y, int prevX, int prevY) { }

void Solution23::Update(float deltaTime) { }

void Solution23::Render() {
	for (const auto& vector : m_cubeMap) {
		for (const auto& cube : vector) {
			cube->Render();
		}
	}
}
