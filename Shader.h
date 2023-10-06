#pragma once

class Shader {
public:
	Shader();
	~Shader();

private:
	unsigned int m_shaderProgram{ };
	unsigned int m_fragmentShader{ };
	unsigned int m_vertexShader{ };

	// ���̴� ������ ������ ������ ����
	char* m_vertexShaderFileContents{ };
	char* m_fragmentShaderFileContents{ };

public:
	// ���̴� ���� ������ �ҷ����� �Լ�
	void RoadVertexShaderFile(const char* filePath);
	void RoadFragmentShaderFile(const char* filePaht);

	// ���̴� �ۼ� �Լ���
	void CompileShaders();
	void AttachAndLinkShaders();
	void CreateShaderProgram();
	void UseProgram();

public:
	// Getter �Լ���
	unsigned int GetShaderProgramID() const { return m_shaderProgram; }
};

