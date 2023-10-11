#pragma once

#include <string>
#include <unordered_map>
#include <memory>

class ModelList {
public:
	ModelList();
	~ModelList();

private:
	// �� ������ ���̴� �ʱ�ȭ�� �ʿ��� ���α׷� ID
	unsigned int m_shaderProgramID{ };

	// �𵨵��� ������ �� ��ü ����
	std::unordered_map<std::string, std::shared_ptr<class Model>> m_modelList{ };

public:
	std::shared_ptr<class Model> GetModel(const std::string& key);

public:
	void Init(unsigned int m_shaderProgramID);
	void LoadModel(const std::string& objectFilePath);
	void LoadModelFromFile(const std::string& modelsFilePath);
};