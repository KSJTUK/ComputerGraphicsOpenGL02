#include "Tank.h"
#include "Object.h"

Tank::Tank() {
	Object main{ "cube", glm::vec3{ } };
	Object loopTop{ "cube", glm::vec3{ 0.f, 1.f ,0.f } };
	Object leftMissile{ "cylinder", glm::vec3{ -1.f, 0.f, 0.5f } };
	Object rightMissile{ "cylinder", glm::vec3{ 1.f, 0.f, 0.5f } };
	Object leftHorn{ "cylinder", glm::vec3{ -0.3f, 1.f, 0.f } };
	Object rightHorn{ "cylinder", glm::vec3{ 0.3f, 1.f, 0.f} };


	main.SetScaleFactor(glm::vec3{ 4.f, 3.f, 4.f });
	loopTop.SetScaleFactor(glm::vec3{ 2.5f, 2.f, 2.5f });

	leftMissile.SetAngle(glm::vec3{ 90.f, 0.f, 0.f });
	leftMissile.SetScaleFactor(glm::vec3{ 0.4f, 1.5f, 0.4f });

	rightMissile.SetAngle(glm::vec3{ 90.f, 0.f, 0.f });
	rightMissile.SetScaleFactor(glm::vec3{ 0.4f, 1.5f, 0.4f });

	leftHorn.SetScaleFactor(glm::vec3{ 0.2f, 1.f, 0.2f });
	rightHorn.SetScaleFactor(glm::vec3{ 0.2f, 1.f, 0.2f });

	m_tankParts.push_back(main);
	m_tankParts.push_back(loopTop);
	m_tankParts.push_back(leftMissile);
	m_tankParts.push_back(rightMissile);
	m_tankParts.push_back(leftHorn);
	m_tankParts.push_back(rightHorn);
}

Tank::Tank(const glm::vec3& initPosition) {
	m_position = initPosition;

	Object main{ "cube", glm::vec3{ } };
	Object loopTop{ "cube", glm::vec3{ 0.f, 1.f ,0.f } };
	Object leftMissile{ "cylinder", glm::vec3{ -1.f, 0.f, 0.5f } };
	Object rightMissile{ "cylinder", glm::vec3{ 1.f, 0.f, 0.5f } };
	Object leftHorn{ "cylinder", glm::vec3{ -0.3f, 1.f, 0.f } };
	Object rightHorn{ "cylinder", glm::vec3{ 0.3f, 1.f, 0.f} };


	main.SetScaleFactor(glm::vec3{ 4.f, 3.f, 4.f });
	loopTop.SetScaleFactor(glm::vec3{ 2.5f, 2.f, 2.5f });

	leftMissile.SetAngle(glm::vec3{ 90.f, 0.f, 0.f });
	leftMissile.SetScaleFactor(glm::vec3{ 0.4f, 1.5f, 0.4f });

	rightMissile.SetAngle(glm::vec3{ 90.f, 0.f, 0.f });
	rightMissile.SetScaleFactor(glm::vec3{ 0.4f, 1.5f, 0.4f });

	leftHorn.SetScaleFactor(glm::vec3{ 0.2f, 1.f, 0.2f });
	rightHorn.SetScaleFactor(glm::vec3{ 0.2f, 1.f, 0.2f });

	m_tankParts.push_back(main);
	m_tankParts.push_back(loopTop);
	m_tankParts.push_back(leftMissile);
	m_tankParts.push_back(rightMissile);
	m_tankParts.push_back(leftHorn);
	m_tankParts.push_back(rightHorn);
}

Tank::~Tank() {
	if (!m_missileAutoMove) {
		m_tankParts[LEFT_MISSILE].RotateToTargetRotate(1, m_leftMissileAngles[0]);
		m_tankParts[LEFT_MISSILE].RotateToTargetRotate(1, m_rightMissileAngles[0]);
	}
}

void Tank::AutoMoveHorn() {
	if (!m_tankParts[LEFT_HORN].IsAutoRotated()) {
		m_tankParts[LEFT_HORN].RotateToTargetRotate(1, m_leftHornAngles[m_hornMoveAngleIndex]);
	}
	if (!m_tankParts[RIGHT_HORN].IsAutoRotated()) {
		m_tankParts[RIGHT_HORN].RotateToTargetRotate(1, m_rightHornAngles[m_hornMoveAngleIndex]);
	}
	m_hornMoveAngleIndex = !m_hornMoveAngleIndex;
}

void Tank::AutoMoveMissile() {
	if (m_tankParts[LEFT_MISSILE].IsAutoRotated()) {
		return;
	}

	if (!m_tankParts[LEFT_MISSILE].IsAutoMoved()) {
		m_tankParts[LEFT_MISSILE].MoveToPoint(1, m_leftMissileMovePoints[m_missileAutoMoveIndex]);
	}
	if (!m_tankParts[RIGHT_MISSILE].IsAutoMoved()) {
		m_tankParts[RIGHT_MISSILE].MoveToPoint(1, m_rightMissileMovePoints[m_missileAutoMoveIndex]);
	}

	m_missileAutoMoveIndex = !m_missileAutoMoveIndex;
}

void Tank::AutoRotateMissile() {
	glm::vec3 mainPartAngle{ m_tankParts[MAIN_PART].GetAngle() };
	if (!m_tankParts[LEFT_MISSILE].IsAutoRotated()) {
		m_tankParts[LEFT_MISSILE].RotateToTargetRotate(1, m_leftMissileAngles[m_missileAngleIndex] + mainPartAngle);
	}
	if (!m_tankParts[RIGHT_MISSILE].IsAutoRotated()) {
		m_tankParts[RIGHT_MISSILE].RotateToTargetRotate(1, m_rightMissileAngles[m_missileAngleIndex] + mainPartAngle);
	}

	m_missileAngleIndex = !m_missileAngleIndex;
}

void Tank::Fire() {
}

void Tank::Input(unsigned char key, bool down) {
	if (down) {
		if (key == 'w') {
			for (auto& part : m_tankParts) {
				part.Move(m_direction, m_speed);
			}
		}

		if (key == 'a') {
			float mainPartAngle{ m_tankParts[0].GetRotateAngle() };
			glm::vec3 mainPartsPosition{ m_tankParts[0].GetPosition() };
			for (auto& part : m_tankParts) {
				part.RotateY();
				if (&part != &m_tankParts[0]) {
					part.Orbit(mainPartAngle, glm::vec3{ 0.f, 1.f, 0.f }, mainPartsPosition);
				}
			}

			m_direction = glm::rotate(m_direction, glm::radians(mainPartAngle), glm::vec3{0.f, 1.f, 0.f});
		}

		if (key == 'd') {
			float mainPartAngle{ m_tankParts[0].GetRotateAngle() };
			glm::vec3 mainPartsPosition{ m_tankParts[0].GetPosition() };
			for (auto& part : m_tankParts) {
				part.RotateY(-1);
				if (&part != &m_tankParts[0]) {
					part.Orbit(-mainPartAngle, glm::vec3{ 0.f, 1.f, 0.f }, mainPartsPosition);
				}
			}
			
			m_direction = glm::rotate(m_direction, glm::radians(-mainPartAngle), glm::vec3{ 0.f, 1.f, 0.f });
		}

		if (key == 's') {
			for (auto& part : m_tankParts) {
				part.Move(-m_direction, m_speed);
			}
		}

		if (key == 'f') {
			if (m_missileAutoRotate) {
				m_missileAngleIndex = 0;
				m_missileAutoRotate = false;
				m_tankParts[LEFT_MISSILE].CancelAutoRotate();
				m_tankParts[RIGHT_MISSILE].CancelAutoRotate();
			}
			else {
				if (!m_missileAutoMove) {
					m_missileAutoRotate = true;
				}
			}
		}

		if (key == 'e') {
			if (m_missileAutoMove) {
				if (m_missileAutoMoveIndex == 0) {
					m_missileAutoMoveIndex = !m_missileAutoMoveIndex;
					m_tankParts[LEFT_MISSILE].MoveToPoint(1, m_leftMissileMovePoints[m_missileAutoMoveIndex]);
					m_tankParts[RIGHT_MISSILE].MoveToPoint(1, m_rightMissileMovePoints[m_missileAutoMoveIndex]);
				}
				m_missileAutoMove = false;
			}
			else {
				m_missileAutoRotate = false;
				m_tankParts[LEFT_MISSILE].CancelAutoRotate();
				m_tankParts[RIGHT_MISSILE].CancelAutoRotate();

				glm::vec3 mainPartAngle{ m_tankParts[MAIN_PART].GetAngle() };
				m_tankParts[LEFT_MISSILE].RotateToTargetRotate(1, glm::vec3{ 90.f, mainPartAngle.y, mainPartAngle.z });
				m_tankParts[RIGHT_MISSILE].RotateToTargetRotate(1, glm::vec3{ 90.f, mainPartAngle.y, mainPartAngle.z });
				m_missileAutoMove = true;
			}
		}

		if (key == 't') {
			if (m_hornAutoMove) {
				m_hornMoveAngleIndex = 0;
				m_hornAutoMove = false;
				m_tankParts[LEFT_HORN].CancelAutoRotate();
				m_tankParts[RIGHT_HORN].CancelAutoRotate();
			}
			else {
				m_hornAutoMove = true;
			}
		}

		if (key == 'b') {
			if (m_rotateTop == 0) {
				m_rotateTop = 1;
				m_rotateTopDir = 1.f;
			}
			else if (m_rotateTop == 1) {
				m_rotateTop = -1;
				m_rotateTopDir = -1.f;
			}
			else if (m_rotateTop == -1) {
				m_rotateTop = 0;
				m_rotateTopDir = 0.f;
			}
		}
	}
}

void Tank::SpecialInput(int key, bool down)
{
}

void Tank::Move(const glm::vec3& moveDirection) {
	m_position += moveDirection * 1.f;
}

void Tank::AutoMove(const glm::vec3& moveDirection) {
	m_direction = moveDirection;
}

void Tank::Update(float deltaTime) {
	m_deltaTime = deltaTime;
	for (auto& part : m_tankParts) {
		part.Update(m_deltaTime);

		if (m_autoMoveMode) {
			part.Move(m_direction, m_speed);
		}
	}

	if (m_missileAutoRotate) {
		AutoRotateMissile();
	}

	if (m_missileAutoMove) {
		AutoMoveMissile();
	}

	if (m_hornAutoMove) {
		AutoMoveHorn();
	}

	m_tankParts[LOOP_TOP].RotateY(m_rotateTop);
	m_tankParts[LEFT_HORN].RotateY(m_rotateTop);
	m_tankParts[RIGHT_HORN].RotateY(m_rotateTop);
	float loopTopSpeed{ m_tankParts[LOOP_TOP].GetAngleSpeed() };
	glm::vec3 loopTopPosition{ m_tankParts[LOOP_TOP].GetPosition() };
	m_tankParts[LEFT_HORN].Orbit(m_rotateTopDir, loopTopSpeed, glm::vec3{0.f, 1.f, 0.f}, loopTopPosition);
	m_tankParts[RIGHT_HORN].Orbit(m_rotateTopDir, loopTopSpeed,  glm::vec3{ 0.f, 1.f, 0.f }, loopTopPosition);

	for (auto& part : m_tankParts) {
		part.SetPosition((m_position - m_prevPosition) + part.GetPosition());
	}
	m_prevPosition = m_position;

	glm::vec3 leftMissilePosition{ m_tankParts[LEFT_MISSILE].GetPosition()};
	glm::vec3 rightMissilePosition{ m_tankParts[RIGHT_MISSILE].GetPosition()};

	m_leftMissileMovePoints[0] = { (leftMissilePosition + rightMissilePosition) / 2.f };
	m_rightMissileMovePoints[0] = { (leftMissilePosition + rightMissilePosition) / 2.f };
	if (m_missileAutoMove) {
		m_leftMissileMovePoints[1] += m_position - m_prevPosition;
		m_rightMissileMovePoints[1] += m_position - m_prevPosition;
	}
	else {
		m_leftMissileMovePoints[1] = { rightMissilePosition };
		m_rightMissileMovePoints[1] = { leftMissilePosition };
	}
}

void Tank::Render() {
	for (auto& part : m_tankParts) {
		part.Render();
	}
}
