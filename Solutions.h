#pragma once

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

	bool m_drawSolid{ false };
	bool m_culling{ false };

public:
	void Init();
	void ReInit();
	void Input(unsigned char key, bool down);
	void SpecialInput(int key, bool down);
	void Update(float deltaTime);
	void Render();
};