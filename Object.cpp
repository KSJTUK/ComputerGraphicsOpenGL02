#include "Object.h"
#include "Model.h"
#include "ModelList.h"

glm::vec3 ObjectMove::origin = glm::vec3{ 0.f };
glm::mat4 ObjectMove::unit = glm::mat4{ 1.f };
glm::vec3 ObjectMove::axisX = glm::vec3{ 1.f, 0.f, 0.f };
glm::vec3 ObjectMove::axisY = glm::vec3{ 0.f, 1.f, 0.f };
glm::vec3 ObjectMove::axisZ = glm::vec3{ 0.f, 0.f, 1.f };

Object::Object(const std::shared_ptr<class Model>& model) {
	m_model = model;
}

Object::Object(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition) {
	m_model = model;
	m_position = initPosition;
}

Object::Object(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition, std::string& modelTag) {
	m_model = model;
	m_position = initPosition;
	m_modelTag = modelTag;
}

Object::Object(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition, std::string&& modelTag) {
	m_model = model;
	m_position = initPosition;
	m_modelTag = modelTag;
}

Object::Object(const std::string& modelTag, const glm::vec3& initPosition) {
	m_model = ModelList::GetInst()->GetModel(modelTag);
	m_modelTag = modelTag;
	m_position = initPosition;
}

Object::Object(const std::string& modelTag) {
	m_model = ModelList::GetInst()->GetModel(modelTag);
	m_modelTag = modelTag;
}

Object::~Object() { }

void Object::RotateX(int rev) {
	m_rotAngle.x += rev * m_angleSpeed * m_deltaTime;
}

void Object::RotateY(int rev) {
	m_rotAngle.y += rev * m_angleSpeed * m_deltaTime;
}

void Object::RotateZ(int rev) {
	m_rotAngle.z += rev * m_angleSpeed * m_deltaTime;
}

glm::vec3 Object::MoveX(int rev) {
	glm::vec3 rtVec{ m_position };
	ObjectMove::Move(m_position, static_cast<float>(rev) * ObjectMove::axisX, m_moveSpeed * m_deltaTime);
	rtVec = m_position - rtVec;
	return rtVec;
}

glm::vec3 Object::MoveY(int rev) {
	glm::vec3 rtVec{ m_position };
	ObjectMove::Move(m_position, static_cast<float>(rev) * ObjectMove::axisY, m_moveSpeed * m_deltaTime);
	rtVec = m_position - rtVec;
	return rtVec;
}

glm::vec3 Object::MoveZ(int rev) {
	glm::vec3 rtVec{ m_position };
	ObjectMove::Move(m_position, static_cast<float>(rev) * ObjectMove::axisZ, m_moveSpeed * m_deltaTime);
	rtVec = m_position - rtVec;
	return rtVec;
}

void Object::Scale(const glm::vec3& factors) {
	m_sizeScale += factors;
}

void Object::ScaleAll(const glm::vec3& factors) {
	m_scaleAll += factors;
}

glm::vec3 Object::Move(glm::vec3& direction) {
	glm::vec3 rtVec{ m_position };
	ObjectMove::Move(m_position, direction, m_moveSpeed * m_deltaTime);
	return rtVec;
}

glm::vec3 Object::Orbit(const float& angle, const glm::vec3& axis, const glm::vec3& center) {
	glm::vec3 rtVec{ m_position };
	ObjectMove::OrbitMove(m_position, angle, axis, center);
	rtVec = m_position - rtVec;
	return rtVec;
}

glm::vec3 Object::MoveSpiral(const Spiral& move) {
	glm::vec3 rtVec{ m_position };
	if (m_spiralMoveTime < m_timeCount) {
		m_timeCount = 0.f;
		ObjectMove::SpiralMove((*this), move, m_spiralStep);
		m_spiralStep += m_spiralDir;
		if (m_spiralStep >= move.GetSpiralSize()) {
			m_spiralStep = move.GetSpiralSize() - 1;
			m_spiralDir = -1;
		}
		else if (m_spiralStep <= 0) {
			m_spiralStep = 0;
			m_spiralDir = 1;
		}
	}
	rtVec = m_position - rtVec;
	return rtVec;
}

void Object::MoveToPoint(size_t count, ...) {
	va_list list;

	va_start(list, count);
	for (auto i = 0; i < count; ++i) {
		m_movePoints.push(va_arg(list, glm::vec3));
	}
	va_end(list);
}

glm::vec3 Object::GetPosition() const {
	return m_position;
}

std::string Object::GetModelTag() {
	return m_modelTag;
}

glm::vec3 Object::GetDeltaPosition() const {
	return m_position - m_prevPosition;
}

void Object::SetScaleFactor(const glm::vec3& factor) {
	m_sizeScale = factor;
}

void Object::SetPosition(const glm::vec3& position) {
	m_position = position;
}

void Object::SetModel(const std::shared_ptr<class Model>& newModel) {
	m_model = newModel;
}

void Object::SetModel(const std::string& newModelTag) {
	m_model.reset();
	m_model = ModelList::GetInst()->GetModel(newModelTag);
	m_modelTag = newModelTag;
}

void Object::Update(float deltaTime) {
	m_prevPosition = m_position;
	m_deltaTime = deltaTime;
	m_timeCount += deltaTime;
	if (m_movePoints.empty()) {
		m_moveStartPoint = m_position;
		return;
	}
	if (!ObjectMove::MoveToPoints(m_moveStartPoint, m_movePoints.front(), m_position, m_movePointSteps)) {
		m_moveStartPoint = m_movePoints.front();
		m_movePoints.pop();
	}
}

void Object::Render() {
	glm::mat4 transform{ 1.f };
	glm::vec3 angles{ glm::radians(m_rotAngle) };
	glm::mat4 rot = glm::yawPitchRoll(angles.y, angles.x, angles.z);
	glm::mat4 trans = glm::translate(unit, m_position);
	glm::mat4 scale = glm::scale(unit, m_sizeScale);
	glm::mat4 scaleAll = glm::scale(unit, m_scaleAll);

	transform = scaleAll * trans * rot * scale;

	m_model->SetTransformMat(transform);
	m_model->Render();
}

void ObjectMove::SpiralMove(Object& object, const Spiral& spiral, size_t step) {
	object.SetPosition(spiral[step].position);
}

void ObjectMove::OrbitMove(glm::vec3& position, const float& angle, const glm::vec3& axis, const glm::vec3& origin) {
	glm::vec3 rotPos{ position - origin };
	position = glm::rotate(rotPos, glm::radians(angle), axis);
	position += origin;
}

void ObjectMove::Move(glm::vec3& position, const glm::vec3& direction, const float speed) {
	position += direction * speed;
}

bool ObjectMove::MoveToPoints(const glm::vec3& start, const glm::vec3& end, glm::vec3& position, float& countStep) {
	float moveStep{ (1.f / glm::length(end - start)) / 1000.f };
	position = (1.f - countStep) * start + countStep * end;
	if (countStep >= 1.f) {
		position = end;
		countStep = 0.f;
		return false;
	}
	countStep += moveStep;
	return true;
}
