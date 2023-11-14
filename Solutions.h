#pragma once
#include "vertex_info.h"
#include <vector>
#include <memory>
#include "gl_headers.h"
#include "OrbitObject.h"
#include "FaceAnimationCube.h"

class Solutions {
public: 
	Solutions() { };
	~Solutions() { };

public:
	virtual void Init() = 0;
	virtual void ReInit() = 0;
	virtual void Input(unsigned char, bool) = 0;
	virtual void SpecialInput(int, bool) = 0;
	virtual void MouseMotionInput(int x, int y, int prevX, int prevY) = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;
};

class Solution22 : public Solutions {
public:
	Solution22() { }
	~Solution22() { }

private:
	class Robot* m_robot{ };
	bool m_robotViewMode{ false };
	unsigned int m_shaderProgramID{ };

	std::vector<Object*> m_cubes{ };
	class FaceAnimationCube* m_box{ };
	class TheaterBox* m_theaterBox{ };

public:
	bool IsRobotViewMode() const { return m_robotViewMode; }

public:
	void SetShaderProgramID(unsigned int shaderProgramID);
	void SetRobotViewMode(bool mode);

	const glm::mat4& GetRobotViewMat() const;

public:
	void Init();
	void ReInit();
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void MouseMotionInput(int x, int y, int prevX, int prevY);
	void MouseMotionPassiveInput(int x, int y, int prevX, int prevY);
	void Update(float deltaTime);
	void Render();
};

class Solution23 : public Solutions {
public:
	Solution23() { }
	~Solution23() { }

private:
	class Robot* m_robot{ };
	bool m_robotViewMode{ false };
	unsigned int m_shaderProgramID{ };

	int m_cubeMapSize{ 100 };
	float m_cubeSize{ 3.f };
	std::vector<std::vector<class Object*>> m_cubeMap{ };

public:
	bool IsRobotViewMode() const { return m_robotViewMode; }

public:
	void SetShaderProgramID(unsigned int shaderProgramID);
	void SetRobotViewMode(bool mode);

	const glm::mat4& GetRobotViewMat() const;

public:
	void Init();
	void ReInit();
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void MouseMotionInput(int x, int y, int prevX, int prevY);
	void MouseMotionPassiveInput(int x, int y, int prevX, int prevY);
	void Update(float deltaTime);
	void Render();

};

bool collisionAndIntegratedPosition(const Object& staticPositionObj, const Object& targetObj, glm::vec3& intergratedPosition, const glm::vec3& deltaPositions);
bool collision(const Object&, const Object&);