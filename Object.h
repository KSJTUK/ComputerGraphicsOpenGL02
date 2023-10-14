#pragma once
#include <memory>
#include "gl_headers.h"

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

	float m_angleSpeed{ 10.f };
	float m_orbitSpeed{ 200.f };

	float m_deltaTime{ };

	// test
	glm::mat4 unit{ 1.f };

	glm::mat4 scale{ 1.f };
	glm::mat4 rotate{ 1.f };
	glm::mat4 trans{ 1.f };

public:
	// getter
	glm::vec3 GetPosition() const;

	void SetPosition(const glm::vec3& position);

public:
	void RotateX();
	void RotateY();
	void RotateZ();
	void OrbitX();
	void OrbitY();
	void OrbitZ();

	glm::vec3 Orbit(const float& angle, const glm::vec3& axis, const glm::vec3& center);

public:
	void Update(float deltaTime);
	void Render();
};