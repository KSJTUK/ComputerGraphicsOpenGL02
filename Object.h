#pragma once

class Object {
public:
	Object(const char* objFilePath);
	~Object();

private:
	float* m_pointInfo{ };
	float* m_colorInfo{ };
	unsigned int* m_meshIndexInfo{ };

public:
	void Update();
	void Render();
};