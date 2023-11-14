#include "Robot.h"
#include "Object.h"
#include "Camera.h"
#include "Solutions.h"
#include <iostream>

class VertexMove;

glm::vec3 vectorRotate(const glm::vec3& targetVec, const float& angle, const glm::vec3 axis = glm::vec3{ 0.f, 1.f, 0.f }) {
	glm::vec3 rt{ targetVec };
	ObjectMove::OrbitMove(rt, angle, axis);
	return rt;
}

Robot::Robot() { 
	Object* head = new Object{ "cube", glm::vec3{ 0.f, 0.75f, 0.f } };
	head->SetScaleFactor(glm::vec3{ 0.5f, 0.5f, 1.f });

	Object* leftLeg = new Object{ "cube", glm::vec3{ 0.f, -0.5f, 0.f } };
	leftLeg->SetScaleFactor(glm::vec3{ 0.2f, 1.3f, 0.3f });
	leftLeg->SetAfterPosition(glm::vec3{ -0.25f, -0.25f, 0.f });

	Object* rightLeg = new Object{ "cube", glm::vec3{ 0.f, -0.5f, 0.f } };
	rightLeg->SetScaleFactor(glm::vec3{ 0.2f, 1.3f, 0.3f });
	rightLeg->SetAfterPosition(glm::vec3{ 0.25f, -0.25f, 0.f });

	Object* leftArm = new Object{ "cube", glm::vec3{ 0.f, -0.5f, 0.f } };
	leftArm->SetScaleFactor(glm::vec3{ 0.2f, 1.3f, 0.3f });
	leftArm->SetAfterPosition(glm::vec3{ -0.6f, 0.35f, 0.f });
	
	Object* rightArm = new Object{ "cube", glm::vec3{ 0.f, -0.5f, 0.f } };
	rightArm->SetScaleFactor(glm::vec3{ 0.2f, 1.3f, 0.3f });
	rightArm->SetAfterPosition(glm::vec3{ 0.6f, 0.35f, 0.f });

	Object* body = new Object{ "cube", glm::vec3{ 0.f, 0.f , 0.f } };
	body->SetScaleFactor(glm::vec3{ m_width, m_height, m_width * 3.f / 4.f });

	glm::vec3 legY{ 0.f, (0.5f + 1.f) * m_height, 0.f };
	body->SetPosition(legY);

	m_body = body;
	m_childs.push_back(head);
	m_childs.push_back(leftLeg);
	m_childs.push_back(rightLeg);
	m_childs.push_back(leftArm);
	m_childs.push_back(rightArm);
}

Robot::~Robot() { }

void Robot::SettingRobotViewMode(bool mode) {
	m_robotViewMode = mode;
}

const glm::mat4& Robot::GetRobotViewMat() const {
	return m_robotCamera->GetViewMat();
}

bool Robot::AllArrowUp() {
	for (auto i = 0; i < 4; ++i) {
		if (m_arrowDowned[i]) {
			return false;
		}
	}

	return true;
}

void Robot::SetDirection() {
}

void Robot::Move() {
	float dir = 1.f;
	float angle = 0.f;
	if (m_arrowDowned[UP] and m_arrowDowned[DOWN]) {
		dir = 0.f;
	}
	else if (m_arrowDowned[UP]) {
		dir = 1.f;
	}
	else if (m_arrowDowned[DOWN]) {
		dir = -1.f;
	}

	if (m_arrowDowned[LEFT] and m_arrowDowned[RIGHT]) {
		angle = 0.f;
	}
	else if (m_arrowDowned[LEFT]) {
		angle = 90.f;
	}
	else if (m_arrowDowned[RIGHT]) {
		angle = -90.f;
	}


	glm::vec3 rotatedDirection{ glm::normalize(vectorRotate(m_direction, m_directionAngle + angle)) };
	m_body->Move(rotatedDirection, m_speed * dir);
}

void Robot::CameraMove() {
	m_cameraPosition = { (m_body->GetPosition() + m_childs[0]->GetPosition() * 0.5f) + m_direction * 0.1f };
	m_robotCamera->CameraPositionSet(m_cameraPosition);
	m_robotCamera->CameraPositionRotateX(m_directionAngle, m_body->GetPosition() + m_childs[0]->GetPosition() * 0.5f);
}

void Robot::Jump() {
	m_jumpPower = m_jumpSpeed;
}

bool Robot::Collision(const Object& otherObj) const {
	glm::vec3 movePos{ };
	if (collisionAndIntegratedPosition(*m_body, otherObj, movePos, m_deltaPosition)) {
		m_body->SetPosition(movePos + m_body->GetPosition());
		m_jumpPower = 0.f;
		return true;
	}

	for (auto& elem : m_childs) {
		if (collisionAndIntegratedPosition(*elem, otherObj, movePos, m_deltaPosition)) {
			m_body->SetPosition(movePos + m_body->GetPosition());
			m_jumpPower = 0.f;
			return true;
		}
	}

	return false;
}

void Robot::Gravity() {
	glm::vec3 bodyPosition{ m_body->GetPosition() };

	m_jumpPower -= m_gravity;
	bodyPosition.y += m_jumpPower * m_deltaTime * m_deltaTime;
	m_body->SetPosition(bodyPosition);

	bodyPosition = m_body->GetPosition();
	if (bodyPosition.y < 0.75f) {
		bodyPosition.y = 0.75f;
		m_body->SetPosition(bodyPosition);
		m_jumpPower = 0.f;
		return;
	}
}

void Robot::Init(unsigned int shaderProgramID) {
	m_robotCamera = std::make_unique<Camera>();
	m_cameraPosition = { m_body->GetPosition() + m_childs[0]->GetPosition() + m_direction * 0.3f };
	m_robotCamera->CameraPositionSet(m_cameraPosition);
	m_robotCamera->CameraViewPointSet(m_direction);
	m_robotCamera->CameraMoveSpeedSet(m_speed);

	m_prevBodyPosition = m_body->GetPosition();
	m_deltaPosition = { };
}

void Robot::Input(unsigned char key, bool down) {
	if (down) {
		if (key == 'w') {
			m_arrowDowned[UP] = true;
		}

		if (key == 's') {
			m_arrowDowned[DOWN] = true;
		}

		if (key == 'a') {
			m_arrowDowned[LEFT] = true;
		}

		if (key == 'd') {
			m_arrowDowned[RIGHT] = true;
		}

		if (key == ' ') {
			Jump();
		}
	}
	else {
		if (key == 'w') {
			m_arrowDowned[UP] = false;
		}

		if (key == 's') {
			m_arrowDowned[DOWN] = false;
		}

		if (key == 'a') {
			m_arrowDowned[LEFT] = false;
		}

		if (key == 'd') {
			m_arrowDowned[RIGHT] = false;
		}
	}
}

void Robot::MouseMotionInput(int x, int y, int prevX, int prevY) {
	m_robotCamera->MouseMotionInput(x, y, prevX, prevY);
	if (m_robotViewMode) {
		m_directionAngle = m_robotCamera->GetCameraAngleX();
		m_body->SetAngle(glm::vec3{ 0.f, m_directionAngle, 0.f });
		m_robotCamera->CameraPositionRotateX(m_directionAngle, m_body->GetPosition() + m_childs[0]->GetPosition() * 0.5f);
	}
}

void Robot::Update(float deltaTime) {
	m_deltaTime = deltaTime;

	m_body->Update(m_deltaTime);

	static glm::vec3 twoAngle{ };
	static float twoAngleDir = 1.f;
	twoAngle.y += twoAngleDir * 0.05f;
	
	if (twoAngle.y >= 90.f) {
		twoAngle.y = 90.f;
		twoAngleDir = -1.f;
	}
	else if (twoAngle.y <= -90.f) {
		twoAngle.y = -90.f;
		twoAngleDir = 1.f;
	}

	if (AllArrowUp()) {
		for (auto i = 1; i < 5; ++i) {
			m_childs[i]->SetAngle(glm::vec3{ });
		}
		m_armsAngle = 0.f;
		m_armsAngleDir = 1.f;

		m_childs[1]->RotateAll(glm::vec3{ m_armsAngle, 0.f, 0.f });
		m_childs[2]->RotateAll(glm::vec3{ -m_armsAngle, 0.f, 0.f });
		m_childs[3]->RotateAll(glm::vec3{ m_armsAngle, 0.f, 0.f });
		m_childs[4]->RotateAll(glm::vec3{ -m_armsAngle, 0.f, 0.f });
	}
	else {
		
		SetDirection();
		Move();

		VertexMove::AngleAnimation(m_armsAngle, -45.f, 45.f, m_armsAngleDir, 50.f * m_deltaTime);

		m_childs[1]->RotateAll(glm::vec3{ m_armsAngle, 0.f, 0.f });
		m_childs[2]->RotateAll(glm::vec3{ -m_armsAngle, 0.f, 0.f });
		m_childs[3]->RotateAll(glm::vec3{ m_armsAngle, 0.f, 0.f });
		m_childs[4]->RotateAll(glm::vec3{ -m_armsAngle, 0.f, 0.f });
	}

	Gravity();

	m_deltaPosition = m_body->GetPosition() - m_prevBodyPosition;
	m_prevBodyPosition = m_body->GetPosition();

	CameraMove();

	m_robotCamera->Update(m_deltaTime);
	m_robotCamera->Render();
}

void Robot::Render() {
	m_body->Render();
	m_body->SetColor(glm::vec3{ 1.f, 0.f, 1.f });
	for (auto& part : m_childs) {
		part->SetParentsModelTransMat(m_body->GetTransformMat());
		part->SetColor(glm::vec3{ 1.f, 0.f, 1.f });
		part->Render();
	}
}

void VertexMove::AngleAnimation(float& targetAngle, const float& minAngle, const float& maxAngle, float& angleDir, const float& angleSpeed) {
	targetAngle += angleDir * angleSpeed;
	if (targetAngle < minAngle) {
		targetAngle = minAngle;
		angleDir = -angleDir;
	}
	else if (targetAngle > maxAngle) {
		targetAngle = maxAngle;
		angleDir = -angleDir;
	}
}

void VertexMove::AngleAnimation(float& targetAngle, const float& minAngle, const float& maxAngle, float& angleDir, const float& angleSpeed, const float& deltaTime) {
	targetAngle += angleDir * angleSpeed * deltaTime;
	if (targetAngle < minAngle) {
		targetAngle = minAngle;
		angleDir = -angleDir;
	}
	else if (targetAngle > maxAngle) {
		targetAngle = maxAngle;
		angleDir = -angleDir;
	}
}

bool VertexMove::VectorEqual(const glm::vec3& v1, const glm::vec3& v2, float epsilon) {
	if (glm::all(glm::lessThanEqual(glm::abs(v1 - v2), glm::vec3{ epsilon }))) {
		return true;
	}
	return false;
}

glm::vec3 VertexMove::VectorRotate(glm::vec3& targetVector, const float& angle, const glm::vec3& axis, bool normalization) {
	return glm::vec3{ };
}