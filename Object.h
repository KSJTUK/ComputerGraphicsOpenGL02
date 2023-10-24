#pragma once
#include <string>
#include <memory>
#include <queue>
#include "gl_headers.h"
#include "Spiral.h"

class Object;

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
	static void SpiralMove(Object& object, const Spiral& spiral, size_t step);
	static void OrbitMove(glm::vec3& position, const float& angle, const glm::vec3& axis, const glm::vec3& center = ObjectMove::origin);
	static void Move(glm::vec3& position, const glm::vec3& direction, const float speed);
	static bool MoveToPoints(const glm::vec3& start, const glm::vec3& end, glm::vec3& position, float& countStep);
	static bool RotateToAngles(std::queue<glm::vec3>& angles, glm::vec3& objectsAngle, float& rotatePercent);
	static bool RotateToTargetAngles(std::queue<glm::vec3>& angles, glm::vec3& startAngle, glm::vec3& objectsAngle, float& rotatePercent);
};

class Object {
public:
	Object(const std::shared_ptr<class Model>& model);
	Object(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition);
	Object(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition, std::string& modelTag);
	Object(const std::shared_ptr<class Model>& model, const glm::vec3& initPosition, std::string&& modelTag);

	Object(const std::string& modelTag, const glm::vec3& initPosition);
	Object(const std::string& modelTag);
	~Object();

protected:
	// 모델
	std::shared_ptr<class Model> m_model{ };
	std::string m_modelTag{ };

	// 위치, 회전 변수들
	glm::vec3 m_sizeScale{ 1.f };
	glm::vec3 m_position{ 0.f };
	glm::vec3 m_rotAngle{ 0.f };
	glm::vec3 m_scaleAll{ 1.f };

	float m_moveSpeed{ 200.f };
	float m_angleSpeed{ 200.f };
	float m_deltaTime{ };

	// test
	glm::mat4 unit{ 1.f };

	// 
	glm::vec3 m_prevPosition{ };

	size_t m_spiralStep{  };
	int m_spiralDir{ 1 };
	float m_spiralMoveTime{ 0.005f };
	float m_timeCount{ };

	// 
	glm::vec3 m_moveStartPoint{ };
	std::queue<glm::vec3> m_movePoints{ };
	float m_movePointSteps{ 0.f };

	std::queue<glm::vec3> m_rotateAngles{ };
	glm::vec3 m_startAngle{ };
	int m_autoRotateMode{ };
	float m_autoRotatePercent{ };

	bool m_autoRotated{ false };
	bool m_autoMoved{ false };

public:
	// getter
	glm::vec3 GetPosition() const;
	std::string GetModelTag();
	glm::vec3 GetDeltaPosition() const;
	glm::vec3 GetAngle() const;
	float GetRotateAngle() const;
	float GetAngleSpeed() const;

	bool IsAutoRotated() const;

	bool IsAutoMoved() const;

	void SetScaleFactor(const glm::vec3& factor);

	void SetPosition(const glm::vec3& position);
	void SetModel(const std::shared_ptr<class Model>& newModel);
	void SetModel(const std::string& newModelTag);
	void SetAngle(const glm::vec3& angle);

public:
	void RotateX(int rev = 1);
	void RotateY(int rev = 1);
	void RotateZ(int rev = 1);

	glm::vec3 MoveX(int rev = 1);
	glm::vec3 MoveY(int rev = 1);
	glm::vec3 MoveZ(int rev = 1);

	void Scale(const glm::vec3& factors);
	void ScaleAll(const glm::vec3& factors);

	glm::vec3 Move(glm::vec3& direction);
	void Move(const glm::vec3& direction, float speed);

	glm::vec3 Orbit(const float& angle, const glm::vec3& axis, const glm::vec3& center);

	glm::vec3 Orbit(float dir, float speed, const glm::vec3& axis, const glm::vec3& center);

	glm::vec3 MoveSpiral(const Spiral& move);

	void CancelAllAutoMove();
	void CancelAutoRotate();
	void CancelAutoMove();

	void RotateToFixedRotate(size_t count, ...);
	void RotateToTargetRotate(size_t count, ...);
	void MoveToPoint(size_t count, ...);
		
public:
	void Update(float deltaTime);
	void Render();
};