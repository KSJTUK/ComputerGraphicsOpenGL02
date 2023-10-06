#include "Shader.h"
#include "pch.h"

Shader::Shader() { }
Shader::~Shader() {
	SafeDeleteArrayPointer(m_vertexShaderFileContents);
	SafeDeleteArrayPointer(m_fragmentShaderFileContents);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_shaderProgram);
}

void Shader::RoadVertexShaderFile(const char* filePath) {
	std::fstream vertexFile{ filePath, std::ios::in };

	try {
		if (!vertexFile.is_open()) {
			throw "vertex shader file open error";
		}
	}
	catch (std::string expn) {
		std::cerr << expn << std::endl;
	}

	std::string contents{ };
	std::string line{ " " };
	while (!vertexFile.eof()) {
		std::getline(vertexFile, line);
		contents.append(line + "\n");
	}

	std::string::size_type size = contents.size();
	m_vertexShaderFileContents = new char[size + 1] {};
	memcpy(m_vertexShaderFileContents, contents.c_str(), size + 1);

	vertexFile.close();
}

void Shader::RoadFragmentShaderFile(const char* filePath) {
	std::fstream fragmentFile{ filePath, std::ios::in };

	try {
		if (!fragmentFile.is_open()) {
			throw "fragment shader file open error";
		}
	}
	catch (std::string expn) {
		std::cerr << expn << std::endl;
	}

	std::string contents{ };
	std::string line{ " " };
	while (!fragmentFile.eof()) {
		std::getline(fragmentFile, line);
		contents.append(line + "\n");
	}

	std::string::size_type size = contents.size();
	m_fragmentShaderFileContents = new char[size + 1] {};
	memcpy(m_fragmentShaderFileContents, contents.c_str(), size + 1);

	fragmentFile.close();
}

void Shader::CompileShaders() {
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// ���̴� �ҽ��ڵ� �ҷ�����
	glShaderSource(m_vertexShader, 1, &m_vertexShaderFileContents, NULL);
	glShaderSource(m_fragmentShader, 1, &m_fragmentShaderFileContents, NULL);

	// ���̴� ������
	glCompileShader(m_vertexShader);
	glCompileShader(m_fragmentShader);

	// ���̴� ������ ���� Ȯ��
	int result{ };
	char errLog[BUFSIZ]{ };

	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_vertexShader, sizeof(errLog), NULL, errLog);
		std::cout << "vertex shader ������ ����: " << errLog << std::endl;
	}

	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_fragmentShader, sizeof(errLog), NULL, errLog);
		std::cout << "fragment shader ������ ����: " << errLog << std::endl;
	}
}

void Shader::AttachAndLinkShaders() {
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// ���̴� ��ũ
	glLinkProgram(m_shaderProgram);

	// ���̴����� ����� ��ũ �Ǿ����� Ȯ��
	int result{ };
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		std::cerr << "Shaders are not Linked" << std::endl;
	}
}

void Shader::CreateShaderProgram() {
	m_shaderProgram = glCreateProgram();
	RoadVertexShaderFile("vertex_shader.glsl");
	RoadFragmentShaderFile("fragment_shader.glsl");
	CompileShaders();
	AttachAndLinkShaders();
}

void Shader::UseProgram() {
	glUseProgram(m_shaderProgram);
}