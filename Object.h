#pragma once
#include <string>
#include <memory>
#include "gl_headers.h"

//class ObjectMoveState {
//public:
//	ObjectMoveState();
//	~ObjectMoveState();
//
//private:
//	std::string state{ };
//
//public:
//	void Update(float deltaTime, Object* const object);
//};

class ObjectMove {
public:
	static glm::vec3 origin;
	static glm::mat4 unit;
	static glm::vec3 axisX;
	static glm::vec3 axisY;
	static glm::vec3 axisZ;

private:
	ObjectMove() = delete;
	~ObjectMove() = delete;

public:
	static void OrbitMove(glm::vec3& position, const float& angle, const glm::vec3& axis, const glm::vec3& center = ObjectMove::origin);
	static void Move(glm::vec3& position, const glm::vec3& direction, const float speed);
};

class Object {
public:
	Object(const std::shared_ptr<class Model>& model);
	Object(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition);
	Object(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition, std::string& modelTag);
	Object(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition, std::string&& modelTag);

	Object(const std::string& modelTag, const glm::vec3& initPosition);
	~Object();

protected:
	// 모델
	std::shared_ptr<class Model> m_model{ };
	std::string m_modelTag{ };

	// 위치, 회전 변수들
	glm::vec3 m_sizeScale{ 1.f };
	glm::vec3 m_position{ 0.f };
	glm::vec3 m_rotAngle{ 0.f };

	glm::vec3 m_orbitAngle{ 0.f };

	float m_moveSpeed{ 200.f };
	float m_angleSpeed{ 10.f };
	float m_orbitSpeed{ 10.f };

	float m_deltaTime{ };

	// test
	glm::mat4 unit{ 1.f };

	glm::mat4 scale{ 1.f };
	glm::mat4 rotate{ 1.f };
	glm::mat4 trans{ 1.f };

public:
	// getter
	glm::vec3 GetPosition() const;
	std::string GetModelTag();

	void SetPosition(const glm::vec3& position);
	void SetModel(const std::shared_ptr<class Model>& newModel);
	void SetModel(const std::string& newModelTag);

public:
	void RotateX(int rev = 1);
	void RotateY(int rev = 1);
	void RotateZ(int rev = 1);

	glm::vec3 OrbitX(int rev = 1);
	glm::vec3 OrbitY(int rev = 1);
	glm::vec3 OrbitZ(int rev = 1);

	glm::vec3 MoveX(int rev = 1);
	glm::vec3 MoveY(int rev = 1);
	glm::vec3 MoveZ(int rev = 1);

	glm::vec3 Move(glm::vec3& direction);

	glm::vec3 Orbit(const float& angle, const glm::vec3& axis, const glm::vec3& center);

public:
	void Update(float deltaTime);
	void Render();
};