#pragma once

#include <vector>
#include "gl_headers.h"
#include "vertex_info.h"

class FaceModel {
public:

private:
	std::vector<std::vector<Vertex>> m_facesVertex{ };
	std::vector<std::vector<unsigned int>> m_facesIndex{ };

public:
};