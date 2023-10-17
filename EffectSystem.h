#pragma once

class EffectSystem {
public:
	EffectSystem() { }
	~EffectSystem() { }

private:
	static EffectSystem* m_instance;

public:
	static void GetInst();
	static void Destroy();

public:
	

public:
	void Init(unsigned int shaderProgramID);
	void Update(float deltaTime);
};

