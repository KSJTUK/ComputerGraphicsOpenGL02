#pragma once

#include "gl_headers.h"
#include <vector>
#include <memory>

class Robot {
public:
	Robot();
	~Robot();

private:
	std::unique_ptr<class Camera> m_robotCamera{ };

	class Object* m_body{ };
	std::vector<class Object*> m_childs{ };

	glm::vec3 m_cameraPosition{ };
	glm::vec3 m_direction{ 0.f, 0.f, 1.f };

	glm::vec3 m_moveDirection{ 0.f, 0.f, 1.f };
	float m_moveDirectionAngle{ };
	
	glm::vec3 m_prevBodyPosition{ };
	glm::vec3 m_deltaPosition{ };

	float m_directionAngle{ };
	
	float m_speed{ 5.f };

	float m_height{ 0.5f };
	float m_width{ 0.5f };

	float m_armsAngle{ };
	float m_armsAngleDir{ 1.f };

	float m_footPosition{ };

	float EPSILON{ 0.00001f };

	float m_deltaTime{ };

	bool m_robotViewMode{ false };
	bool m_onGround{ true };

	float m_gravity{ 10.f };
	float m_jumpSpeed{ 5000.f };
	mutable float m_jumpPower{ };

	bool m_arrowDowned[4]{ false };
	enum {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	enum {
		UPANGLE = 0,
		DOWNANGLE = 180,
		LEFTANGLE = 90,
		RIGHTANGLE = -90,
		LEFTUPANGLE = 45,
		LEFTDOWNANGLE = 135,
		RIGHTUPANGLE = -45,
		RIGHTDOWNANGLE = -135
	};

public:
	void SettingRobotViewMode(bool mode);

	const glm::mat4& GetRobotViewMat() const;

public:
	bool AllArrowUp();
	void SetDirection();
	void Move();
	void CameraMove();
	void Jump();

	bool Collision(const Object& otherObj) const;

	void Gravity();

public:
	void Init(unsigned int shaderProgramID);
	void Input(unsigned char key, bool down);
	void MouseMotionInput(int x, int y, int prevX, int prevY);
	void Update(float deltaTime);
	void Render();
};

class VertexMove {
	VertexMove() = delete;
	~VertexMove() = delete;

public:
	static constexpr float EPSILON{ 0.000001f };

public:
	static void AngleAnimation(float& targetAngle, const float& minAngle, const float& maxAngle, float& angleDir, const float& angleSpeed);
	static void AngleAnimation(float& targetAngle, const float& minAngle, const float& maxAngle, float& angleDir, const float& angleSpeed, const float& deltaTime);
	static bool VectorEqual(const glm::vec3& v1, const glm::vec3& v2, float epsilon = VertexMove::EPSILON);
	static glm::vec3 VectorRotate(glm::vec3& targetVector, const float& angle, const glm::vec3& axis, bool normalization);

public:
	template <typename T>
	static T CalcDelta(const T& prevData, const T& curData) {
		T returnData{ curData - prevData };
		prevData = curData;
		return returnData;
	}

	template <typename T>
	static T __stdcall MoveToNextData(T& targetData, const T& start, const T& end, float step, bool(*equalFunc)(const T&, const T&) = nullptr) {

	}
};