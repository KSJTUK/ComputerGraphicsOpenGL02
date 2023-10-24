#pragma once
#include "vertex_info.h"
#include <vector>
#include <memory>
#include "gl_headers.h"

class Solutions {
public: 
	Solutions() { };
	~Solutions() { };

public:
	virtual void Init() = 0;
	virtual void ReInit() = 0;
	virtual void Input(unsigned char, bool) = 0;
	virtual void SpecialInput(int, bool) = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;
};

class Solution15 : public Solutions {
public:
	Solution15() { };
	~Solution15() { }

private:
	class Object* m_object{ };
	class Tank* m_tank{ };

	int rotateX{ 0 };
	int rotateY{ 0 };

	float m_deltaTime{ };

	bool m_drawSolid{ true };
	bool m_culling{ true };
	

public:
	void Init();
	void ReInit();
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void Update(float deltaTime);
	void Render();
};

class Solution16 : public Solutions {
public:
	Solution16() { };
	~Solution16() { }

private:
	std::vector<class Object> m_objects{ };
	std::vector<int> m_rotateX{ };
	std::vector<int> m_rotateY{ };

	std::vector<class Object> m_orbitObject{ };
	
	int oribit{ 0 };

	float m_deltaTime{ };

public:
	void Init();
	void ReInit();
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void Update(float deltaTime);
	void Render();
};

class Solution17 : public Solutions {
public:
	Solution17() { };
	~Solution17() { }

private:
	unsigned int m_shaderProgramID{ };

	std::vector<class Object> m_objects{ };
	std::vector<int> m_rotateX{ };
	std::vector<int> m_rotateY{ };

	std::vector<class Object> m_orbitObject{ };

	std::vector<class Spiral> m_spirals{ };

	int oribit{ 0 };

	float m_deltaTime{ };

	glm::vec3 m_scaleAllFactors{ 1.f };

	bool drawSpiral{ true };

public:
	void SetShaderProgramID(unsigned int shaderProgramID);

public:
	void Init();
	void ReInit();
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void Update(float deltaTime);
	void Render();
};

class Solution18 : public Solutions {
public:
	Solution18() { }
	~Solution18() { }

private:
	class FaceAnimationCube* m_faceCube{ };
	class FaceAnimationCone* m_faceCone{ };

	float m_deltaTime{ };

	unsigned int m_shaderProgramID{ };

public:
	void SetShaderProgramID(unsigned int shaderProgramID);

public:
	void Init();
	void ReInit();
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void Update(float deltaTime);
	void Render();
};

class Solution19 : public Solutions {
public:
	Solution19() { }
	~Solution19() { }

private:
	glm::vec3 orbitAxis[3]{
		{ 0.f, 1.f, 0.f },
		{ 1.f, 1.f, 0.f },
		{ -1.f, 1.f, 0.f }
	};

	class Object* m_originPlanet{ };
	std::vector<class OrbitObject> m_orbitPlanet{ };
	std::vector<class OrbitObject> m_orbitPlanetsMoon{ };

	float m_rotateDirOrbitZ{ 0.f };
	float m_rotateDirOrbitY{ 0.f };

	glm::bvec3 rotate{ false };

public:
	void Init();
	void ReInit();
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void Update(float deltaTime);
	void Render();
};

class Solution20 : public Solutions {
public:
	Solution20() { }
	~Solution20() { }

private:
	std::vector<Vertex> ground{
		{ { -300.f, -0.001f, 300.f }, { 0.f, 0.5f, 0.f }, { } },
		{ { -300.f, -0.001f, -300.f }, { 0.f, 0.5f, 0.f }, { } },
		{ { 300.f, -0.001f, -300.f }, { 0.f, 0.5f, 0.f }, { } },
		{ { 300.f, -0.001f, 300.f }, { 0.f, 0.5f, 0.f }, { } }
	};
	std::vector<unsigned int> groundIndex{
		0, 1, 2, 0, 2, 3
	};

	std::unique_ptr<class GraphicBuffers> m_groundBuffer{ };
	unsigned int m_shaderProgramID{ };
	
	class Tank* m_tank{ };

public:
	void SetShaderProgramID(unsigned int shaderProgramID);

public:
	void Init();
	void ReInit();
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void Update(float deltaTime);
	void Render();

};