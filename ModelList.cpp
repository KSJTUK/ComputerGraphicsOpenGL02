#include "ModelList.h"
#include "Model.h"

// constructor and distructor
// -------------------------------
ModelList::ModelList() { }

ModelList::~ModelList() { }
// -------------------------------

// static 변수
ModelList* ModelList::m_instance = nullptr;

// static Method (single tone)
// -------------------------------
ModelList* ModelList::GetInst() {
	if (!m_instance) {
		m_instance = new ModelList;
	}
	return m_instance;
}

void ModelList::Destroy() {
	if (m_instance) {
		delete m_instance;
	}
	m_instance = nullptr;
}
// -------------------------------

std::string MakeStringToKey(const std::string& str) {
	std::string key = str.substr(0, str.find('.'));
	return key;
}

void ModelList::Init(unsigned int shaderProgramID) {
	m_shaderProgramID = shaderProgramID;
	m_currentDrawMode = GL_TRIANGLES;
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
	// color
	newModel->SetRandomColor();
	// color
	m_modelList.insert(std::make_pair(key, newModel));
}

void ModelList::LoadModelFromFile(const std::string& modelsFilePath) {
}

void ModelList::SetDrawModes(int drawMode) {
	m_currentDrawMode = drawMode;
	for (auto& element : m_modelList) {
		element.second->SetDrawMode(m_currentDrawMode);
	}
}

int ModelList::GetCurrentDrawMode() const {
	return m_currentDrawMode;
}

std::shared_ptr<class Model> ModelList::GetModel(const std::string& key) const {
	auto iter = m_modelList.find(key);
	if (iter == m_modelList.end()) {
		return std::shared_ptr<Model>(nullptr);
	}

	return iter->second;
}
