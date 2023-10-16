#pragma once
#include <vector>

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

	class Spiral* spiral{ nullptr };

	int oribit{ 0 };

	float m_deltaTime{ };

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