#include "ModelList.h"
#include "Model.h"

ModelList::ModelList() { }

ModelList::~ModelList() { }

std::string MakeStringToKey(const std::string& str) {
	std::string key = str.substr(0, str.find('.'));
}

void ModelList::Init(unsigned int shaderProgramID) {
	m_shaderProgramID = shaderProgramID;
}

void ModelList::LoadModel(const std::string& objectFilePath) {
	std::string key = MakeStringToKey(objectFilePath);

	auto iter = m_modelList.find(key);
	if (iter != m_modelList.end()) {
		return;
	}

	std::shared_ptr<class Model> newModel{ };
	newModel = std::make_shared<class Model>(objectFilePath);
	newModel->Init(m_shaderProgramID);
	m_modelList.insert(std::make_pair(key, newModel));
}

void ModelList::LoadModelFromFile(const std::string& modelsFilePath) {
}

std::shared_ptr<class Model> ModelList::GetModel(const std::string& key) {
	auto iter = m_modelList.find(key);
	if (iter == m_modelList.end()) {
		return std::shared_ptr<Model>(nullptr);
	}

	return iter->second;
}
